#!/usr/bin/env bash
#
# build.sh - compile and run a single CaseStudy example independently.
#
# Every case is self-contained: this script compiles only that case's
# sources with -std=c++17 and then executes the resulting binary.
#
# Usage:
#   ./build.sh <case-name|dir|file.cpp> [-- program args...]
#
# Options:
#   --check        compile only, do not run
#   --all          compile every case under CaseStudy (no run)
#   --list         list available cases
#   --san          enable AddressSanitizer + UBSan
#   --std=<std>    override the C++ standard (default: c++17)
#   --cxx=<cmd>    override the compiler   (default: $CXX or g++)
#   -h, --help     show this help
#
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CASE_DIR="$ROOT/CaseStudy"
BUILD_DIR="$ROOT/build"
CXX="${CXX:-g++}"
STD="c++17"
SAN=0
CHECK_ONLY=0
LIST_ONLY=0
ALL=0

usage() {
    sed -n '2,19p' "${BASH_SOURCE[0]}" | sed 's/^# \{0,1\}//'
}

POSITIONAL=()
PROG_ARGS=()
while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)   usage; exit 0 ;;
        --check)     CHECK_ONLY=1; shift ;;
        --san)       SAN=1; shift ;;
        --all)       ALL=1; shift ;;
        --list)      LIST_ONLY=1; shift ;;
        --std=*)     STD="${1#--std=}"; shift ;;
        --cxx=*)     CXX="${1#--cxx=}"; shift ;;
        --)          shift; PROG_ARGS=("$@"); break ;;
        -*)          echo "unknown option: $1" >&2; usage; exit 2 ;;
        *)           POSITIONAL+=("$1"); shift ;;
    esac
done

FLAGS=("-std=$STD" -Wall -Wextra -Wpedantic -Wshadow -O2 -g)
if [[ $SAN -eq 1 ]]; then
    FLAGS+=(-fsanitize=address,undefined -fno-omit-frame-pointer)
fi

list_cases() {
    find "$CASE_DIR" -mindepth 1 -maxdepth 1 -type d | sort | while read -r d; do
        printf '  %s\n' "$(basename "$d")"
    done
}

if [[ $LIST_ONLY -eq 1 ]]; then
    list_cases
    exit 0
fi

if [[ $ALL -eq 1 ]]; then
    status=0
    while read -r d; do
        if ! "$0" --check --std="$STD" --cxx="$CXX" "$d"; then
            status=1
        fi
    done < <(find "$CASE_DIR" -mindepth 1 -maxdepth 1 -type d | sort)
    exit "$status"
fi

if [[ ${#POSITIONAL[@]} -eq 0 ]]; then
    echo "error: no case given" >&2
    usage
    exit 2
fi

TARGET="${POSITIONAL[0]}"
if [[ -d "$TARGET" ]]; then
    SRC_DIR="$(cd "$TARGET" && pwd)"
    NAME="$(basename "$SRC_DIR")"
elif [[ -f "$TARGET" ]]; then
    SRC_DIR="$(cd "$(dirname "$TARGET")" && pwd)"
    NAME="$(basename "$TARGET" .cpp)"
elif [[ -d "$CASE_DIR/$TARGET" ]]; then
    SRC_DIR="$CASE_DIR/$TARGET"
    NAME="$TARGET"
else
    echo "error: case not found: $TARGET" >&2
    echo "available:" >&2
    list_cases >&2
    exit 2
fi

mapfile -t SRCS < <(find "$SRC_DIR" -maxdepth 1 -name '*.cpp' | sort)
if [[ ${#SRCS[@]} -eq 0 ]]; then
    echo "error: no .cpp sources in $SRC_DIR" >&2
    exit 2
fi

OUT_DIR="$BUILD_DIR/$NAME"
BIN="$OUT_DIR/app"
mkdir -p "$OUT_DIR"

echo "[build] $NAME  ($STD, $("$CXX" --version | head -1))"
"$CXX" "${FLAGS[@]}" -I"$SRC_DIR" "${SRCS[@]}" -o "$BIN"

if [[ $CHECK_ONLY -eq 1 ]]; then
    echo "[ok]    $NAME compiled"
    exit 0
fi

echo "[run]   $NAME"
cd "$SRC_DIR"
exec "$BIN" "${PROG_ARGS[@]}"
