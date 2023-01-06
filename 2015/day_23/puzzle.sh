#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  inst=$(echo $line | cut -d ' ' -f 1)
  reg=0
  offset=0

  if [ $inst = "hlf" ] || [ $inst = "tpl" ] || [ $inst = "inc" ]
  then
    reg=$(echo $line | cut -d ' ' -f 2)
  elif [ $inst = "jmp" ]
  then
    offset=$(echo $line | cut -d ' ' -f2)
  elif [ $inst = "jie" ] || [ $inst = "jio" ]
  then
    reg=$(echo $line | cut -d ' ' -f 2 | sed 's/,$//')
    offset=$(echo $line | cut -d ' ' -f 3)
  else
    exit 1
  fi
  echo "{$nr_input,${inst^^},'$reg',$offset},"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
