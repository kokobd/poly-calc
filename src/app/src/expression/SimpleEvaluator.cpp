#include "SimpleEvaluator.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>
#include "../Executor.h"
#include "ParseError.h"
#include <stack>
#include <map>
#include <cstdlib>
#include "operators/BiOperator.h"

namespace Zelinf {
namespace PolyCalc {
namespace App {
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

enum class TokenType {
    BiOp, // BiOperator
    Num, // Integer
    Var, // Variable
    L_P, // left parentheses
    R_P // right parentheses
};

struct Token {
    union {
        std::shared_ptr<Operators::BiOperator> biOp;
        int64_t num;
        std::string var;
    };
    TokenType type;
};

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
            tok.type = TokenType::L_P;
            ++it;
        } else if (*it == ')') {
            tok.type = TokenType::R_P;
            ++it;
        } else if (std::isdigit(*it)) {
            tok.type = TokenType::Num;
            std::string num;
            while (std::isdigit(*it) && it != str.cend()) {
                num.push_back(*it);
                ++it;
            }
            tok.num = std::atoi(num.c_str());
        } else if (std::isalpha(*it)) {
            tok.type = TokenType::Var;
            while (std::isalpha(*it) && it != str.cend()) {
                tok.var.push_back(*it);
                ++it;
            }
        } else {
            bool valid = false;
            for (const auto &p : defaultSymbols()) {
                if (*it == p.first) {
                    tok.type = TokenType::BiOp;
                    tok.biOp = p.second;
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

std::shared_ptr<Service::Polynomial> SimpleEvaluator::parse(const std::string &str) {
    using namespace Operators;
    std::stack<std::shared_ptr<Service::Polynomial>> outStack;
    std::stack<std::shared_ptr<BiOperator>> opStack;

    if (str.empty()) {
        throw ParseError("The expression is empty.");
    }


}

}
}
}
}
