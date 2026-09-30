// Case:  09_lambda_init_capture
// Topic: lambda init-capture (generalized capture) and mutable
// RUN:   ./build.sh 09_lambda_init_capture
// CHECK: ./build.sh --check 09_lambda_init_capture
#include <bits/stdc++.h>
using namespace std;

int main() {
    auto counter = make_shared<int>(0);

    auto bump = [n = 0]() mutable { return ++n; };
    cout << "bump: " << bump() << ' ' << bump() << ' ' << bump() << '\n';

    auto tag = [label = string("tick "), count = counter]() {
        return label + to_string(++*count);
    };
    cout << tag() << '\n';
    cout << tag() << '\n';
    cout << "shared counter = " << *counter << '\n';
    return 0;
}
