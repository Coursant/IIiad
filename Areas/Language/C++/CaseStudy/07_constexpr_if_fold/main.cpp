// Case:  07_constexpr_if_fold
// Topic: if constexpr compile-time branching + fold expressions
// RUN:   ./build.sh 07_constexpr_if_fold
// CHECK: ./build.sh --check 07_constexpr_if_fold
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
std::string describe(const T& value) {
    if constexpr (std::is_integral_v<T>) {
        return "integral: " + std::to_string(value);
    } else if constexpr (std::is_floating_point_v<T>) {
        return "floating: " + std::to_string(value);
    } else {
        (void)value;
        return "other";
    }
}

template <typename... Ts>
auto sum(Ts... values) {
    return (... + values);
}

template <typename... Ts>
auto sum_plus_100(Ts... values) {
    return (values + ... + 100);
}

int main() {
    std::cout << describe(10) << '\n';
    std::cout << describe(2.5) << '\n';
    std::cout << describe(std::string("x")) << '\n';
    std::cout << "unary fold  = " << sum(1, 2, 3, 4, 5) << '\n';
    std::cout << "binary fold = " << sum_plus_100(1, 2, 3) << '\n';
    return 0;
}
