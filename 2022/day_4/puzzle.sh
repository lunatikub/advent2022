#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
    s1=$(echo $line | cut -d ',' -f 1)
    s2=$(echo $line | cut -d ',' -f 2)
    s1_from=$(echo $s1 | cut -d '-' -f 1)
    s1_to=$(echo $s1 | cut -d '-' -f 2)
    s2_from=$(echo $s2 | cut -d '-' -f 1)
    s2_to=$(echo $s2 | cut -d '-' -f 2)
    echo "{$s1_from, $s1_to, $s2_from, $s2_to},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
