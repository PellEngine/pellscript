rm ./compile_commands.json
bazel build ///src:compdb
outfile="$(bazel info bazel-bin --compiler=mingw-gcc)/src/compile_commands.json"

execroot=""
sed -i.bak "s@__EXEC_ROOT__@${execroot}@" "${outfile}"

cp $outfile ./compile_commands.json
