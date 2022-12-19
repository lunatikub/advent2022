#!/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
static const char *puzzle[] = {
EOF

nr_str=0

while read -r line
do
  echo "  \"$line\","
  nr_str=$((nr_str + 1))
done < $INPUT

cat <<EOF
};

#define NR_STR $nr_str
EOF

exit 0
