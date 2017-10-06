#include "SimpleEvaluator.h"
#include <algorithm>
#include <cctype>

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
        value_part = input.substr(beg_value_part);
        input.erase(beg_value_part, input.size() - beg_value_part);
    }

    size_t first_equal_sign = input.find('=');
    // if the next character is still '=', means we have "=="
    if (input.size() > first_equal_sign + 1 && input[first_equal_sign + 1] == '=') {
        // TODO
        // pass 'input' directly to parser
    } else {
        // TODO
        // split around '=', pass the right part to parser,
        // then assign it to the left part (as an identifier)
    }
}

}
}
}
}
