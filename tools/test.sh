#!/usr/bin/bash

script_dir=$(realpath $(readlink -f $(dirname $0)))

source $script_dir/../tests/conf
source $script_dir/common.sh

OUT=$(mktemp -t "AOC.OUT.XXXXXX")
OUT_2=$(mktemp -t "AOC.OUT.XXXXXX")

test_day() {
  local start=$(get_time_ms)
  ./aoc_puzzle > $OUT
  local expected="$script_dir/../tests/${y}_day_${d}.txt"
  diff $OUT $expected > $OUT_2
  res=$?
  local end=$(get_time_ms)
  tot_ms=$((tot_ms + (end - start)))
  if [ $res -ne 0 ]
  then
    ko
    echo ""
    cat $OUT_2
    exit 1
  fi
  ok
}

tot_ms=0
title "test"
foreach_day test_day
echo -e "\nTotal: ${CYAN}${tot_ms}ms${ENDCOLOR}"

rm -rf $OUT
rm -rf $OUT_2
exit 0
