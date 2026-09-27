// Case:  09_lambda_init_capture
// Topic: lambda init-capture (generalized capture) and mutable
// RUN:   ./build.sh 09_lambda_init_capture
// CHECK: ./build.sh --check 09_lambda_init_capture
#include <iostream>
#include <memory>
#include <string>

int main() {
    auto counter = std::make_shared<int>(0);

    auto bump = [n = 0]() mutable { return ++n; };
    std::cout << "bump: " << bump() << ' ' << bump() << ' ' << bump() << '\n';

    auto tag = [label = std::string("tick "), count = counter]() {
        return label + std::to_string(++*count);
    };
    std::cout << tag() << '\n';
    std::cout << tag() << '\n';
    std::cout << "shared counter = " << *counter << '\n';
    return 0;
}
