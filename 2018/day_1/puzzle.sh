#!/usr/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  [ "${line:0:1}" = "+" ] && op='P' || op='M'
  val=$(echo ${line:1})
  echo "  { $op, $val },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
