#!/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
static wire_t wires[] = {
EOF

nr_wire=0

while read -r line
do

  if [[ "$line" =~ "AND" ]] || [[ "$line" =~ "OR" ]] ||
     [[ "$line" =~ "LSHIFT" ]] || [[ "$line" =~ "RSHIFT" ]]
  then
    op=$(echo $line | cut -d ' ' -f 2)
    in_1=$(echo $line | cut -d ' ' -f 1)
    in_2=$(echo $line | cut -d ' ' -f 3)
    out=$(echo $line | cut -d ' ' -f 5)
    echo "  { $op, \"$in_1\", \"$in_2\", \"$out\", 0, false },"
  elif [[ "$line" =~ "NOT" ]]
  then
    in=$(echo $line | cut -d ' ' -f 2)
    out=$(echo $line | cut -d ' ' -f 4)
    echo "  { NOT, \"$in\", NULL, \"$out\", 0, false },"
  else
    in=$(echo $line | cut -d ' ' -f 1)
    out=$(echo $line | cut -d ' ' -f 3)
    echo "  { ASSIGN,  \"$in\", NULL, \"$out\", 0, false},"
  fi

  nr_wire=$((nr_wire + 1))
done < $INPUT

cat <<EOF
};

#define NR_WIRE $nr_wire
EOF

exit 0
