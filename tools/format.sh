#!/usr/bin/env bash
set -euo pipefail

cd "${BUILD_WORKSPACE_DIRECTORY}"


if ! command -v buildifier >/dev/null 2>&1; then
    echo "buildifier not found; skipping BUILD file formatting"
else
    echo "Running buildifier..."
    buildifier -r .
fi


if ! command -v clang-format >/dev/null 2>&1; then
    echo "clang-format not found; skipping C++ file formatting"
else
    mapfile -t files < <(git ls-files '*.cc' '*.hh')

    if [ "${#files[@]}" -eq 0 ]; then
    echo "No C++ files found; skipping clang-format"
    else
    echo "Running clang-format..."
    clang-format -i "${files[@]}"
    fi
fi
