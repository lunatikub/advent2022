#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

nr_X=0

echo "static const struct X Y[] = {"

while read -r line
do
  nr_X=$((nr_X + 1))
done < $INPUT

echo "};"

echo "#define NR_X $nr_X"

exit 0
