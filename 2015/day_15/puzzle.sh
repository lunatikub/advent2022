#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  ingredient=$(echo $line | cut -d ':' -f 1)
  capacity=$(echo $line | cut -d ' ' -f 3 | sed 's/,//')
  durability=$(echo $line | cut -d ' ' -f 5 | sed 's/,//')
  flavor=$(echo $line | cut -d ' ' -f 7 | sed 's/,//')
  texture=$(echo $line | cut -d ' ' -f 9 | sed 's/,//')
  calories=$(echo $line | cut -d ' ' -f 11)
  echo "  { \"$ingredient\", $capacity, $durability, $flavor, $texture, $calories },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
