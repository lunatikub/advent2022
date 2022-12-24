#!/usr/bin/bash

script_dir=$(realpath $(readlink -f $(dirname $0)))

for src in $(find $script_dir/.. -name "*.[c|h]")
do
  clang-format $src > /tmp/foo
  mv /tmp/foo $src
done

exit 0
