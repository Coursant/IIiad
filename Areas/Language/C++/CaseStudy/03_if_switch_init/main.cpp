// Case:  03_if_switch_init
// Topic: init-statement inside if / switch (C++17)
// RUN:   ./build.sh 03_if_switch_init
// CHECK: ./build.sh --check 03_if_switch_init
#include <bits/stdc++.h>
using namespace std;

int main() {
    map<string, int> stock{{"apple", 3}};

    if (auto it = stock.find("apple"); it != stock.end()) {
        cout << "apple stock = " << it->second << '\n';
    } else {
        cout << "no apple\n";
    }

    switch (int code = 42; code) {
        case 42:
            cout << "code is 42\n";
            break;
        default:
            cout << "other\n";
            break;
    }
    return 0;
}
