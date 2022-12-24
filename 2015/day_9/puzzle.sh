#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  city_1=$(echo $line | cut -d' ' -f1)
  city_2=$(echo $line | cut -d' ' -f3)
  dist=$(echo $line | cut -d' ' -f5)
  echo "  { \"$city_1\", \"$city_2\", $dist },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
