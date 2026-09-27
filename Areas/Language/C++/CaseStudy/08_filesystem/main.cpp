// Case:  08_filesystem
// Topic: std::filesystem - paths, directories, file queries
// RUN:   ./build.sh 08_filesystem
// CHECK: ./build.sh --check 08_filesystem
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int main() {
    const fs::path dir = fs::temp_directory_path() / "iiad_fs_demo";
    fs::create_directories(dir);
    const fs::path file = dir / "note.txt";

    {
        std::ofstream out(file);
        out << "hello filesystem\n";
    }

    std::cout << "file size = " << fs::file_size(file) << '\n';
    std::cout << "exists    = " << std::boolalpha << fs::exists(file) << '\n';
    std::cout << "filename  = " << file.filename().string() << '\n';
    std::cout << "extension = " << file.extension().string() << '\n';

    fs::remove_all(dir);
    return 0;
}
