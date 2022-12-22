#!/usr/bin/bash

set -e

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  coord=$(echo $line | cut -d ' ' -f 3)
  x=$(echo $coord | cut -d ',' -f1)
  y=$(echo $coord | cut -d ',' -f2 | sed 's/://')
  size=$(echo $line | cut -d ' ' -f 4)
  w=$(echo $size | cut -d'x' -f 1)
  h=$(echo $size | cut -d'x' -f 2)
  echo "{ $((nr_input + 1)), $x, $y, $w, $h },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
