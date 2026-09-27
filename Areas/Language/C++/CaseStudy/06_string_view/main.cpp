// Case:  06_string_view
// Topic: std::string_view - non-owning, cheap string slices
// RUN:   ./build.sh 06_string_view
// CHECK: ./build.sh --check 06_string_view
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

std::size_t count_vowels(std::string_view text) {
    std::size_t n = 0;
    for (char c : text) {
        switch (c) {
            case 'a': case 'e': case 'i': case 'o': case 'u': ++n; break;
            default: break;
        }
    }
    return n;
}

int main() {
    std::string owned = "hello world";
    std::cout << "vowels = " << count_vowels(owned) << '\n';

    const char* raw = "the quick brown fox";
    std::string_view view(raw, std::strlen(raw));
    std::cout << "substr = " << view.substr(4, 5) << '\n';
    return 0;
}
