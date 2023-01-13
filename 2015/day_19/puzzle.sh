#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  [ "$line" = "" ] && break
  line=$(echo $line | sed 's/=> //')
  from=$(echo $line | cut -d ' ' -f1)
  to=$(echo $line | cut -d ' ' -f2)
  echo "{\"$from\",\"$to\"},"
  nr_input=$((nr_input + 1))
done < $INPUT

molecule=$(tail -n1 $INPUT)

cat <<EOF
};

#define NR_INPUT $nr_input

static const char base_molecule[] = "$molecule";
EOF

exit 0
