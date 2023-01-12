#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  line=$(echo $line | sed 's/"/@/g')
  echo "{\"$line\"},"
  nr_input=$((nr_input + 1))
done < $INPUT

part_2=$(python3 part_2.py)

cat <<EOF
};

#define NR_INPUT $nr_input
#define PART_2 $part_2
EOF

exit 0
