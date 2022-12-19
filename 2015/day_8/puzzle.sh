#!/bin/bash

INPUT="$1"
[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
static const char* lines[] = {
EOF

nr_line=0

while read -r line
do
  line=$(echo $line | sed 's/\\\\/@B/g')
  line=$(echo $line | sed 's/\\"/@D/g')
  line=$(echo $line | sed 's/\\x/@X/g')
  echo "  $line,"
  nr_line=$((nr_line + 1))
done < $INPUT

cat <<EOF
};

#define NR_LINE $nr_line
EOF

exit 0
