#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  room=$(echo $line | sed 's/-[0-9]*\[.*//')
  checksum=$(echo $line | sed 's/.*\[//' | sed 's/]$//')
  id=$(echo $line | sed 's/.*-\(.*\)/\1/' | sed s'/\[.*//')
  echo "{\"$room\", $id, \"$checksum\"},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
