#!/bin/bash

INPUT="$1"
[ -z "$INPUT" ] && echo "input needed..." && exit 1

prev=$(head -n1 $INPUT)
n=0

while IFS= read -r line
do
  [ $prev -lt $line ] && n=$((n + 1))
  prev=$line
done < $INPUT

echo $n

exit 0
