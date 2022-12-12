#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
#include "inst.h"

static const inst_t insts[] = {
EOF

nr_inst=0

while read -r line
do
  type=$(echo $line | cut -d' ' -f1)
  if [ "$type" = "addx" ]
  then
    type=INST_ADDX
    val=$(echo $line | cut -d' ' -f2)
  else
    type=INST_NOOP
    val=0
  fi
  echo "  { $type, $val },"
  nr_inst=$((nr_inst + 1))
done < $INPUT

cat <<EOF
};

#define NR_INST $nr_inst
EOF

exit 0
