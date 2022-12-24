#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_line=0

while read -r line
do
  line=$(echo $line | sed 's/\\\\/@B/g')
  line=$(echo $line | sed 's/\\"/@D/g')
  line=$(echo $line | sed 's/\\x/@X/g')
  echo "{$line},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
