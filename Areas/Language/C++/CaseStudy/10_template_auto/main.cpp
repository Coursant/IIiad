// Case:  10_template_auto
// Topic: auto non-type template parameters (C++17)
// RUN:   ./build.sh 10_template_auto
// CHECK: ./build.sh --check 10_template_auto
#include <bits/stdc++.h>
using namespace std;

template <auto Value>
struct Constant {
    static constexpr auto value = Value;
};

enum class Color { red, green, blue };

int main() {
    cout << Constant<42>::value << '\n';
    cout << Constant<'x'>::value << '\n';
    cout << static_cast<int>(Constant<Color::blue>::value) << '\n';
    return 0;
}
