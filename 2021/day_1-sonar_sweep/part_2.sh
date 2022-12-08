#!/bin/bash

INPUT="$1"
[ -z "$INPUT" ] && echo "input needed..." && exit 1

nr_line=$(cat $INPUT | wc -l)

echo -n "" > /tmp/adventofcode

for (( i = 0; i <= nr_line - 3; i += 1 ))
do
  n1=$(sed "$((i + 1))q;d" $INPUT)
  n2=$(sed "$((i + 2))q;d" $INPUT)
  n3=$(sed "$((i + 3))q;d" $INPUT)
  echo $((n1 + n2 + n3)) >> /tmp/adventofcode
done

./part_1.sh /tmp/adventofcode
