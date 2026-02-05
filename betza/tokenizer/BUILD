cc_library(
    name = "token",
    srcs = ["token.cc"],
    hdrs = ["token.hh"],
    includes = ["."],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "token_test",
    size = "small",
    srcs = ["token_test.cc"],
    deps = [
        ":token",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)
