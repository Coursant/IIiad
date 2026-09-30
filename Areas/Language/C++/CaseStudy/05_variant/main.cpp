// Case:  05_variant
// Topic: variant + visit (type-safe union)
// RUN:   ./build.sh 05_variant
// CHECK: ./build.sh --check 05_variant
#include <bits/stdc++.h>
using namespace std;

using Value = variant<int, double, string>;

struct Printer {
    void operator()(int v) const { cout << "int    " << v << '\n'; }
    void operator()(double v) const { cout << "double " << v << '\n'; }
    void operator()(const string& v) const { cout << "string " << v << '\n'; }
};

int main() {
    vector<Value> values{42, 3.14, string("hello")};
    for (const auto& v : values) {
        visit(Printer{}, v);
    }
    return 0;
}
