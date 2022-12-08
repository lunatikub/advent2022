#!/bin/bash

INPUT="$1"
[ -z "$INPUT" ] && echo "input needed..." && exit 1

h=0
d=0
a=0

while IFS= read -r line
do
  cmd=$(echo $line | cut -d ' ' -f 1)
  n=$(echo $line | cut -d ' ' -f 2)
  if [ $cmd = "forward" ]
  then
    h=$((h + n))
    d=$((d + a * n))
  elif [ $cmd = "down" ]
  then
    a=$((a + n))
  elif [ $cmd = "up" ]
  then
    a=$((a - n))
  else
    exit 1
  fi
done < $INPUT

echo "h: $h, d: $d, result: $((d * h))"

exit 0
