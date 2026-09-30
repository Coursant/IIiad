#!/usr/bin/env bash
set -euo pipefail

case_dir=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
mkdir -p "$case_dir/build"
"${CC:-cc}" -std=c11 -D_DEFAULT_SOURCE -Wall -Wextra -Wpedantic -Wshadow -Werror -O2 \
  "$case_dir/main.c" -o "$case_dir/build/app"
"$case_dir/build/app"
