#!/usr/bin/bash

script_dir=$(realpath $(readlink -f $(dirname $0)))

source $script_dir/../tests/conf
source $script_dir/common.sh

OUT=$(mktemp -t "AOC.OUT.XXXXXX")

clean() {
  local start=$(get_time_ms)
  make clean >/dev/null 2>&1
  local end=$(get_time_ms)
  tot_ms=$((tot_ms + (end - start)))
  ok
}

tot_ms=0
title "clean"
foreach_day clean
echo -e "\nTotal: ${CYAN}${tot_ms}ms${ENDCOLOR}"

rm -rf $OUT
exit 0
