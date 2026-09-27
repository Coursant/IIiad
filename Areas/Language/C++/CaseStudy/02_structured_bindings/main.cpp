// Case:  02_structured_bindings
// Topic: auto [a, b, ...] over tuple, pair, array and map entries
// RUN:   ./build.sh 02_structured_bindings
// CHECK: ./build.sh --check 02_structured_bindings
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

std::tuple<int, std::string, double> make_record() {
    return {7, "seven", 7.5};
}

int main() {
    auto [id, name, score] = make_record();
    std::cout << "tuple: " << id << ' ' << name << ' ' << score << '\n';

    std::array<int, 3> a{1, 2, 3};
    auto [x, y, z] = a;
    std::cout << "array: " << x << y << z << '\n';

    std::map<std::string, int> ages{{"ada", 36}, {"linus", 54}};
    for (const auto& [who, age] : ages) {
        std::cout << who << " is " << age << '\n';
    }
    return 0;
}
