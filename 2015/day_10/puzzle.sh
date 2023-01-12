#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  echo -n "{{"
  for i in $(seq 0 $((${#line} - 1)))
  do
    echo -n "${line:$i:1},"
    nr_input=$((nr_input + 1))
  done
  echo "}}"
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
