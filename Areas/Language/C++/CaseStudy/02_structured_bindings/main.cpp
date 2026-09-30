// Case:  02_structured_bindings
// Topic: auto [a, b, ...] over tuple, pair, array and map entries
// RUN:   ./build.sh 02_structured_bindings
// CHECK: ./build.sh --check 02_structured_bindings
#include <bits/stdc++.h>
using namespace std;

tuple<int, string, double> make_record() {
    return {7, "seven", 7.5};
}

int main() {
    auto [id, name, score] = make_record();
    cout << "tuple: " << id << ' ' << name << ' ' << score << '\n';

    array<int, 3> a{1, 2, 3};
    auto [x, y, z] = a;
    cout << "array: " << x << y << z << '\n';

    map<string, int> ages{{"ada", 36}, {"linus", 54}};
    for (const auto& [who, age] : ages) {
        cout << who << " is " << age << '\n';
    }
    return 0;
}
