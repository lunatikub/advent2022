#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  name=$(echo $line | cut -d ' ' -f 1)
  speed=$(echo $line | cut -d ' ' -f 4)
  fly=$(echo $line | cut -d' ' -f 7)
  rest=$(echo $line | cut -d' ' -f 14)

  echo "  { \"$name\", $speed, $fly, $rest },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
