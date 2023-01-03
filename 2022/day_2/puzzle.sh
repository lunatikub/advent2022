#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  opponent=$(echo $line | cut -d ' ' -f 1)
  me=$(echo $line | cut -d ' ' -f 2)
  echo "{'$opponent', '$me'},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
