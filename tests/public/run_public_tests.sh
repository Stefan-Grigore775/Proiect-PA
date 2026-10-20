#!/bin/sh

set -eu

ROOT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
BUILD_DIR="$ROOT_DIR/build"
PUBLIC_DIR="$ROOT_DIR/tests/public"

run_case() {
    stage="$1"
    binary="$2"
    case_dir="$3"
    actual="$BUILD_DIR/${stage}_actual.txt"

    "$binary" \
        "$case_dir/entitati.csv" \
        "$case_dir/relatii.csv" \
        "$case_dir/interogari.txt" \
        > "$actual"

    if diff -u "$case_dir/expected.txt" "$actual"; then
        printf '[OK] %s\n' "$stage"
    else
        printf '[FAIL] %s\n' "$stage"
        exit 1
    fi
}

run_case "public_pas1" "$BUILD_DIR/public_pas1" "$PUBLIC_DIR/pas1"
run_case "public_pas2" "$BUILD_DIR/public_pas2" "$PUBLIC_DIR/pas2"
run_case "public_pas3" "$BUILD_DIR/public_pas3" "$PUBLIC_DIR/pas3"
run_case "public_pas4" "$BUILD_DIR/public_pas4" "$PUBLIC_DIR/pas4"
