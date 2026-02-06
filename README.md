# GETTING STARTED

## PREREQUISITES

1. GCC 15.2

The C++ portion of this repository is compiled using GCC 15.2.

2. Bazelisk.

Bazel is the build system which is used by this project. To install it, use bazelisk, which is a wrapper around bazel that will install bazel for you (with the right version, as per the .bazelversion file). Follow the directions [here](https://github.com/bazelbuild/bazelisk)

## BUILDING VIA THE TERMINAL

This repo pins the Bazel version in `.bazelversion`. Bazelisk will automatically download and run that version.

Basic usage (from the repo root):

```sh
bazelisk --version
bazelisk test //:token_test
```

Common commands:

```sh
# Build a target
bazelisk build //:token_test

# Run tests
bazelisk test //:token_test --test_output=errors

# List targets in a package
bazelisk query //:*
```

If you prefer typing `bazel` instead of `bazelisk`, you can create a shell alias / wrapper so that `bazel` invokes `bazelisk`.

## BUILDING VIA THE VSCODE EXTENSION

1. Install the VS Code extension named "Bazel".
2. Configure the extension to use Bazelisk as the Bazel executable.

In your workspace settings (for example `.vscode/settings.json`), set:

```json
{
  "bazel.executable": "bazelisk"
}
```

Then you can use the Command Palette:

- **Build**: run the Bazel build command for a target.
- **Test**: run the Bazel test command for a target.
- **Query**: discover targets (often via a `bazel query`-style command).

If the extension can’t find `bazelisk`, make sure it’s on your `PATH`, or set `bazel.executable` to the full path to `bazelisk`.


## CODE COVERAGE

### Prerequisites

- `lcov` (provides `genhtml`). Install via: `sudo dnf install lcov`

### Running coverage

```sh
# Run all tests with coverage and generate an HTML report
bazelisk run //tools/coverage:report
```

This will:
1. Run `bazel coverage //...` (collecting lcov data for all test targets)
2. Generate an HTML report in `coverage_html/`

Open `coverage_html/index.html` in a browser to view the results.

To collect coverage data without generating HTML:

```sh
bazelisk coverage //...
```

The raw lcov report is located at `$(bazel info output_path)/_coverage/_coverage_report.dat`.

### Known limitation: gcc and branch coverage

When using gcc, branch coverage reports include compiler-generated branches (e.g., exception
handler paths on `throw` statements) that are not meaningful to test. This inflates the total
branch count and makes 100% branch coverage unachievable in practice.

To keep branch coverage reports clean, **prefer alternatives to `throw`** (e.g., return error codes, `std::optional`, `std::expected`) where practical.

If the project switches to clang for coverage in the future, the `genhtml` flags already in
place (`--filter branch`, `--rc no_exception_branch=1`) will correctly exclude these
compiler-generated branches.
