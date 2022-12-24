#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  name=$(echo $line | cut -d ' ' -f1)
  next=$(echo $line | cut -d ' ' -f11 | sed 's/.$//')
  gain=$(echo $line | cut -d' ' -f3)
  [ "$gain" = "gain" ] && sign="" || sign="-"
  h=$(echo $line | cut -d ' ' -f4)
  echo "  { \"$name\", \"$next\", $sign$h },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
