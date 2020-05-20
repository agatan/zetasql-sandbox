load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")


# http_archive(
#     name = "com_google_absl",
#     # Commit from 2020-03-03
#     url = "https://github.com/abseil/abseil-cpp/archive/b19ba96766db08b1f32605cb4424a0e7ea0c7584.tar.gz",
#     sha256 = "c7ff8decfbda0add222d44bdc27b47527ca4e76929291311474efe7354f663d3",
#     strip_prefix = "abseil-cpp-b19ba96766db08b1f32605cb4424a0e7ea0c7584",
# )
#
#
# http_archive(
#     name = "com_google_protobuf",
#     urls = ["https://github.com/protocolbuffers/protobuf/archive/v3.6.1.3.tar.gz"],
#     sha256 = "73fdad358857e120fd0fa19e071a96e15c0f23bb25f85d3f7009abfd4f264a2a",
#     strip_prefix = "protobuf-3.6.1.3",
#     patches = ["@com_google_zetasql//bazel:protobuf-v3.6.1.3.patch"],
# )
#


git_repository(
    name = "com_google_zetasql",
    branch = "master",
    remote = "https://github.com/google/zetasql",
)

load("@com_google_zetasql//bazel:zetasql_deps_step_1.bzl", "zetasql_deps_step_1")

zetasql_deps_step_1()

load("@com_google_zetasql//bazel:zetasql_deps_step_2.bzl", "zetasql_deps_step_2")

zetasql_deps_step_2()

load("@com_google_zetasql//bazel:zetasql_deps_step_3.bzl", "zetasql_deps_step_3")

zetasql_deps_step_3()

load("@com_google_zetasql//bazel:zetasql_deps_step_4.bzl", "zetasql_deps_step_4")

zetasql_deps_step_4()
