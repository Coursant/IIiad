// Case:  05_variant
// Topic: std::variant + std::visit (type-safe union)
// RUN:   ./build.sh 05_variant
// CHECK: ./build.sh --check 05_variant
#include <iostream>
#include <string>
#include <variant>
#include <vector>

using Value = std::variant<int, double, std::string>;

struct Printer {
    void operator()(int v) const { std::cout << "int    " << v << '\n'; }
    void operator()(double v) const { std::cout << "double " << v << '\n'; }
    void operator()(const std::string& v) const { std::cout << "string " << v << '\n'; }
};

int main() {
    std::vector<Value> values{42, 3.14, std::string("hello")};
    for (const auto& v : values) {
        std::visit(Printer{}, v);
    }
    return 0;
}
