// Case:  08_filesystem
// Topic: filesystem - paths, directories, file queries
// RUN:   ./build.sh 08_filesystem
// CHECK: ./build.sh --check 08_filesystem
#include <bits/stdc++.h>
using namespace std;

namespace fs = filesystem;

int main() {
    const fs::path dir = fs::temp_directory_path() / "iiad_fs_demo";
    fs::create_directories(dir);
    const fs::path file = dir / "note.txt";

    {
        ofstream out(file);
        out << "hello filesystem\n";
    }

    cout << "file size = " << fs::file_size(file) << '\n';
    cout << "exists    = " << boolalpha << fs::exists(file) << '\n';
    cout << "filename  = " << file.filename().string() << '\n';
    cout << "extension = " << file.extension().string() << '\n';

    fs::remove_all(dir);
    return 0;
}
