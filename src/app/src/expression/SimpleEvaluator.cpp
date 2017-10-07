#include "SimpleEvaluator.h"
#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <fmt/format.h>
#include "../Executor.h"
#include "ParseError.h"

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

std::shared_ptr<Service::Polynomial> SimpleEvaluator::parse(const std::string &str) {
    return std::make_shared<Service::Polynomial>(
            std::initializer_list<Service::Monomial>(
                    {{1, 2},
                     {1}}));
    // TODO implement Shunting-Yard Algorithm.
}

}
}
}
}
