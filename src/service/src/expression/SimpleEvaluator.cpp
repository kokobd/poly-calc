#include <poly-calc/service/expression/SimpleEvaluator.h>
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>
#include <poly-calc/service/Executor.h>
#include <poly-calc/service/expression/ParseError.h>
#include <stack>
#include <map>
#include <cstdlib>
#include <poly-calc/service/expression/BiOperator.h>
#include <mapbox/variant.hpp>
#include <poly-calc/service/poly/Polynomial.h>

namespace Zelinf {
namespace PolyCalc {
namespace Service {
namespace Expression {

std::string removeSpaces(const std::string &str) {
    std::string result;
    for (char ch : str) {
        if (!std::isspace(ch)) {
            result.push_back(ch);
        }
    }
    return result;
}

std::string SimpleEvaluator::evaluate(const std::string &input_) {
    std::string input = removeSpaces(input_);
    if (input.empty()) {
        return "";
    }

    std::string value_part;
    if (input.back() == ']') {
        size_t beg_value_part = input.find_last_of('[');
        if (beg_value_part == std::string::npos || beg_value_part == input.size() - 1) {
            value_part = "";
        } else {
            value_part = input.substr(beg_value_part + 1, input.size() - beg_value_part - 2);
            input.erase(beg_value_part, input.size() - beg_value_part);
        }
    }

    std::string expr;
    std::string expr_name;

    size_t first_equal_sign = input.find('=');
    if (first_equal_sign == std::string::npos) {
        expr = std::move(input);
    } else {
        expr_name = input.substr(0, first_equal_sign);
        expr = input.substr(first_equal_sign + 1);
    }

    std::ostringstream result;
    try {
        auto poly = parse(expr);
        result << poly->show();

        if (!value_part.empty()) {
            std::istringstream reader(value_part);
            int64_t value;
            if (reader >> value) {
                result << fmt::format(" [x={}]={}", value, poly->evaluate(value));
            }
        }

        result << '\n';

        if (!expr_name.empty()) {
            if (std::all_of(expr_name.cbegin(), expr_name.cend(), [](char ch) {
                return std::isalpha(ch);
            })) {
                executor.getStoredPolys()[expr_name] = poly;
            } else {
                result << fmt::format("'{}' is not a valid identifier. All identifiers"
                                              "must be consist of english letters, and"
                                              "can not be a single 'x'.\n", expr_name);
            }
        }
    } catch (ParseError &e) {
        result << e.what();
        result << '\n';
    }
    return result.str();
}

std::map<char, std::shared_ptr<Operators::BiOperator>> defaultSymbols() {
    using namespace Operators;
    std::map<char, std::shared_ptr<Operators::BiOperator>> symbols;
    for (auto op : BiOperator::defaultOperators) {
        symbols[op->symbol()] = op;
    }
    return symbols;
}

struct LeftParens {

};

struct RightParens {

};

using Token = mapbox::util::variant<
        std::shared_ptr<Operators::BiOperator>,
        int64_t,
        std::string,
        LeftParens,
        RightParens>;

/**
 * Convert input string into a vector of tokens.
 * @param str The string to be parsed.
 * @return a vector of token.
 * @throws ParseError if can not convert some part to a valid token.
 */
std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> result;
    for (auto it = str.cbegin(); it != str.cend();) {
        Token tok;
        if (*it == '(') {
            tok = LeftParens();
            ++it;
        } else if (*it == ')') {
            tok = RightParens();
            ++it;
        } else if (std::isdigit(*it)) {
            std::string num;
            while (std::isdigit(*it) && it != str.cend()) {
                num.push_back(*it);
                ++it;
            }
            tok = std::atoi(num.c_str());
        } else if (std::isalpha(*it)) {
            std::string var;
            while (std::isalpha(*it) && it != str.cend()) {
                var.push_back(*it);
                ++it;
            }
            tok = var;
        } else {
            bool valid = false;
            for (const auto &p : defaultSymbols()) {
                if (*it == p.first) {
                    tok = p.second;
                    valid = true;
                }
            }
            if (!valid) {
                throw ParseError(fmt::format("Unexpected character '{}' can not form a valid token.", *it));
            }
            ++it;
        }
        result.push_back(tok);
    }
    return result;
}

void applyOperatorToOutStack(std::shared_ptr<Operators::BiOperator> op,
                             std::stack<std::shared_ptr<Poly::Polynomial>> &outStack) {
    if (outStack.size() < 2) {
        throw ParseError(fmt::format("Too less operands for {}", op->symbol()));
    }
    std::shared_ptr<Poly::Polynomial> rhs = outStack.top();
    outStack.pop();
    std::shared_ptr<Poly::Polynomial> lhs = outStack.top();
    outStack.pop();
    outStack.push(op->apply(lhs, rhs));
}

std::shared_ptr<Poly::Polynomial> SimpleEvaluator::parse(const std::string &str) {
    using namespace Operators;
    std::stack<std::shared_ptr<Poly::Polynomial>> outStack;
    std::stack<Token> opStack;

    std::vector<Token> tokens = tokenize(str);
    if (tokens.empty()) {
        throw ParseError("No tokens found.");
    }

    for (const Token &tok : tokens) {
        tok.match(
                [&opStack](LeftParens p) {
                    opStack.push(Token(p));
                },
                [&opStack, &outStack](RightParens p) {
                    bool parensMatch = false;
                    while (!opStack.empty() && !(parensMatch = opStack.top().is<LeftParens>())) {
                        applyOperatorToOutStack(opStack.top().get<std::shared_ptr<BiOperator>>(), outStack);
                        opStack.pop();
                    }
                    if (parensMatch) {
                        opStack.pop();
                    } else {
                        throw ParseError("Parentheses mismatch.");
                    }
                },
                [this, &outStack](const std::string &var) {
                    std::shared_ptr<Poly::Polynomial> result;
                    if (var == "x") {
                        result = std::make_shared<Poly::Polynomial>(
                                std::initializer_list<Poly::Monomial>{{1, 1}});
                    } else {
                        auto it = executor.getStoredPolys().find(var);
                        if (it == executor.getStoredPolys().cend()) {
                            throw ParseError(fmt::format("{} is not a stored polynomial.", var));
                        } else {
                            result = it->second;
                        }
                    }
                    outStack.push(result);
                },
                [&outStack](int64_t num) {
                    std::shared_ptr<Poly::Polynomial> result =
                            std::make_shared<Poly::Polynomial>(
                                    std::initializer_list<Poly::Monomial>({num})
                            );
                    outStack.push(result);
                },
                [&opStack, &outStack](std::shared_ptr<BiOperator> op) {
                    while (!opStack.empty()) {
                        Token top = opStack.top();
                        if (top.is<LeftParens>()) {
                            break;
                        }
                        if (top.is<std::shared_ptr<BiOperator>>()) {
                            auto top_precedence = top.get<std::shared_ptr<BiOperator>>()->precedence();
                            if (op->leftAssoc()) {
                                if (top_precedence < op->precedence()) {
                                    break;
                                }
                            } else {
                                if (top_precedence <= op->precedence()) {
                                    break;
                                }
                            }
                            applyOperatorToOutStack(opStack.top().get<std::shared_ptr<BiOperator>>(), outStack);
                            opStack.pop();
                        } else {
                            throw std::logic_error("Impossible code path");
                        }
                    }
                    opStack.push(op);
                });
    }

    while (!opStack.empty()) {
        Token &top = opStack.top();
        if (top.is<LeftParens>()) {
            throw ParseError("Parentheses mismatch.");
        }
        applyOperatorToOutStack(top.get<std::shared_ptr<BiOperator>>(), outStack);
        opStack.pop();
    }

    if (outStack.size() == 1) {
        return outStack.top();
    } else {
        throw ParseError("Too many operands.");
    }
}

}
}
}
}
