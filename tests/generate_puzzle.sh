#!/usr/bin/bash

script_dir=$(realpath $(readlink -f $(dirname $0)))

source $script_dir/conf
source $script_dir/common.sh

OUT=$(mktemp -t "AOC.OUT.XXXXXX")

generate_puzzle() {
  local start=$(get_time_ms)
  make puzzle.h > $OUT 2>&1
  res=$?
  local end=$(get_time_ms)
  tot_ms=$((tot_ms + (end - start)))
  if [ $res -ne 0 ]
  then
    ko
    echo ""
    cat $OUT
    exit 1
  fi
  ok
}

tot_ms=0
title "generate puzzle"
foreach_day generate_puzzle
echo -e "\nTotal: ${CYAN}${tot_ms}ms${ENDCOLOR}"

rm -rf $OUT
exit 0
