// Case:  04_optional
// Topic: optional as a nullable value, value_or, has_value
// RUN:   ./build.sh 04_optional
// CHECK: ./build.sh --check 04_optional
#include <bits/stdc++.h>
using namespace std;

optional<int> parse_int(const string& s) {
    try {
        size_t pos = 0;
        int value = stoi(s, &pos);
        if (pos != s.size()) {
            return nullopt;
        }
        return value;
    } catch (const exception&) {
        return nullopt;
    }
}

int main() {
    for (const char* s : {"123", "abc", "45x"}) {
        if (auto v = parse_int(s)) {
            cout << s << " -> " << *v << '\n';
        } else {
            cout << s << " -> invalid\n";
        }
    }
    cout << "value_or = " << parse_int("nope").value_or(-1) << '\n';
    return 0;
}
