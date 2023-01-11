#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  side_1=$(echo $line | cut -d ' ' -f 1)
  side_2=$(echo $line | cut -d ' ' -f 2)
  side_3=$(echo $line | cut -d ' ' -f 3)
  echo "{$side_1,$side_2,$side_3},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
