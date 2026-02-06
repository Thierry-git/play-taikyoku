#!/usr/bin/env bash
set -euo pipefail

if [[ -z "${BUILD_WORKSPACE_DIRECTORY:-}" ]]; then
    echo "ERROR: This script must be run via 'bazel run //tools/coverage:report'." >&2
    exit 1
fi

cd "${BUILD_WORKSPACE_DIRECTORY}"

OUTPUT_DIR="${BUILD_WORKSPACE_DIRECTORY}/coverage_html"
COVERAGE_DAT="$(bazel info output_path)/_coverage/_coverage_report.dat"

if ! command -v genhtml &>/dev/null; then
    echo "ERROR: 'genhtml' not found. Install lcov (e.g. 'sudo apt install lcov')." >&2
    exit 1
fi

echo "Running bazel coverage //..."
COVERAGE_EXIT=0
bazel coverage //... || COVERAGE_EXIT=$?

if [[ ${COVERAGE_EXIT} -ne 0 ]]; then
    echo "WARNING: bazel coverage exited with code ${COVERAGE_EXIT} (some tests may have failed)." >&2
fi

if [[ ! -f "${COVERAGE_DAT}" ]]; then
    echo "ERROR: Coverage report not found at ${COVERAGE_DAT}" >&2
    exit 1
fi

echo "Generating HTML report..."
genhtml \
    --branch-coverage \
    --filter branch \
    --rc no_exception_branch=1 \
    --output "${OUTPUT_DIR}" \
    "${COVERAGE_DAT}"

echo ""
echo "Coverage report generated at: ${OUTPUT_DIR}/index.html"
xdg-open "${OUTPUT_DIR}/index.html" >/dev/null 2>&1
