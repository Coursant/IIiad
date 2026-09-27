// Case:  01_hello
// Topic: toolchain smoke test - iostream and __cplusplus
// RUN:   ./build.sh 01_hello
// CHECK: ./build.sh --check 01_hello
#include <iostream>
#include <string>

int main() {
    const std::string name = "C++17";
    std::cout << "Hello, " << name << "!\n";
    std::cout << "__cplusplus = " << __cplusplus << '\n';
    return 0;
}
