load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository", "new_git_repository")

http_archive(
  name = "com_grail_bazel_compdb",
  strip_prefix = "bazel-compilation-database-master",
  urls = ["https://github.com/grailbio/bazel-compilation-database/archive/master.tar.gz"],
)

load("@com_grail_bazel_compdb//:deps.bzl", "bazel_compdb_deps")
bazel_compdb_deps()