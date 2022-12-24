#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  if [[ "$line" =~ "AND" ]] || [[ "$line" =~ "OR" ]] ||
     [[ "$line" =~ "LSHIFT" ]] || [[ "$line" =~ "RSHIFT" ]]
  then
    op=$(echo $line | cut -d ' ' -f 2)
    in_1=$(echo $line | cut -d ' ' -f 1)
    in_2=$(echo $line | cut -d ' ' -f 3)
    out=$(echo $line | cut -d ' ' -f 5)
    echo "  { $op, \"$in_1\", \"$in_2\", \"$out\" },"
  elif [[ "$line" =~ "NOT" ]]
  then
    in=$(echo $line | cut -d ' ' -f 2)
    out=$(echo $line | cut -d ' ' -f 4)
    echo "  { NOT, \"$in\", NULL, \"$out\" },"
  else
    in=$(echo $line | cut -d ' ' -f 1)
    out=$(echo $line | cut -d ' ' -f 3)
    echo "  { ASSIGN,  \"$in\", NULL, \"$out\" },"
  fi
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
