// Case:  04_optional
// Topic: std::optional as a nullable value, value_or, has_value
// RUN:   ./build.sh 04_optional
// CHECK: ./build.sh --check 04_optional
#include <iostream>
#include <optional>
#include <string>

std::optional<int> parse_int(const std::string& s) {
    try {
        std::size_t pos = 0;
        int value = std::stoi(s, &pos);
        if (pos != s.size()) {
            return std::nullopt;
        }
        return value;
    } catch (const std::exception&) {
        return std::nullopt;
    }
}

int main() {
    for (const char* s : {"123", "abc", "45x"}) {
        if (auto v = parse_int(s)) {
            std::cout << s << " -> " << *v << '\n';
        } else {
            std::cout << s << " -> invalid\n";
        }
    }
    std::cout << "value_or = " << parse_int("nope").value_or(-1) << '\n';
    return 0;
}
