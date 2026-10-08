// Case:  vector
// Topic: <describe the C++17 feature(s) demonstrated>
// RUN:   ./build.sh vector
// CHECK: ./build.sh --check vector
#include <bits/stdc++.h>
using namespace std;

int main() {
    double* p = new double[10]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    double* q = new double[10]{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    delete[] p;
    delete[] q;
}
class vector {
    int size;
    double* data;
    public:
    vector(int s) : size(s), data(new double[s]) {};//初始化是（）还是{}都可以
    ~vector() { delete[] data; }
    vector(const vector& v) : size(v.size), data(new double[v.size]) {
        copy(v.data, v.data + v.size, data);
    }
};