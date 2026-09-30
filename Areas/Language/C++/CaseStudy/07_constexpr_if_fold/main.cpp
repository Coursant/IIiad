// Case:  07_constexpr_if_fold
// Topic: if constexpr compile-time branching + fold expressions
// RUN:   ./build.sh 07_constexpr_if_fold
// CHECK: ./build.sh --check 07_constexpr_if_fold
#include <bits/stdc++.h>
using namespace std;

template <typename T>
string describe(const T& value) {
    if constexpr (is_integral_v<T>) {
        return "integral: " + to_string(value);
    } else if constexpr (is_floating_point_v<T>) {
        return "floating: " + to_string(value);
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
    cout << describe(10) << '\n';
    cout << describe(2.5) << '\n';
    cout << describe(string("x")) << '\n';
    cout << "unary fold  = " << sum(1, 2, 3, 4, 5) << '\n';
    cout << "binary fold = " << sum_plus_100(1, 2, 3) << '\n';
    return 0;
}
