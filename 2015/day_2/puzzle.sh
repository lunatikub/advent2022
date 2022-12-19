#!/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
static const dim_t dims[] = {
EOF

nr_dim=0

while read -r line
do
  l=$(echo $line | cut -d 'x' -f1)
  h=$(echo $line | cut -d 'x' -f2)
  w=$(echo $line | cut -d 'x' -f3)
  echo "  { $l, $h, $w },"
  nr_dim=$((nr_dim + 1))
done < $INPUT

cat <<EOF
};

#define NR_DIM $nr_dim
EOF

exit 0
