// Case:  06_string_view
// Topic: string_view - non-owning, cheap string slices
// RUN:   ./build.sh 06_string_view
// CHECK: ./build.sh --check 06_string_view
#include <bits/stdc++.h>
using namespace std;

size_t count_vowels(string_view text) {
    size_t n = 0;
    for (char c : text) {
        switch (c) {
            case 'a': case 'e': case 'i': case 'o': case 'u': ++n; break;
            default: break;
        }
    }
    return n;
}

int main() {
    string owned = "hello world";
    cout << "vowels = " << count_vowels(owned) << '\n';

    const char* raw = "the quick brown fox";
    string_view view(raw, strlen(raw));
    cout << "substr = " << view.substr(4, 5) << '\n';
    return 0;
}
