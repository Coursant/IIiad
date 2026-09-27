#!/usr/bin/env bash
#
# new_case.sh - scaffold a new self-contained CaseStudy example.
#
# Usage: ./scripts/new_case.sh <NN_snake_name>
#
# Options:
#   -h, --help   show this help
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
CASE_DIR="$ROOT/CaseStudy"

usage() {
    sed -n '2,8p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

case "${1:-}" in
    -h|--help) usage; exit 0 ;;
esac

name="${1:-}"
if [[ -z "$name" ]]; then
    usage >&2
    exit 2
fi

dir="$CASE_DIR/$name"
if [[ -e "$dir" ]]; then
    echo "error: already exists: $dir" >&2
    exit 1
fi

mkdir -p "$dir"
cat > "$dir/main.cpp" <<EOF
// Case:  $name
// Topic: <describe the C++17 feature(s) demonstrated>
// RUN:   ./build.sh $name
// CHECK: ./build.sh --check $name
#include <iostream>

int main() {
    std::cout << "$name\\n";
    return 0;
}
EOF

echo "created $dir/main.cpp"
 