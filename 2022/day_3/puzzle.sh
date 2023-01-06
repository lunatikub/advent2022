#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  sz=$(echo -n $line | wc -m)
  sz=$((sz / 2))
  c1=${line:0:$sz}
  c2=${line:$sz:$sz}
  echo "{\"$c1\",\"$c2\",$sz},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
