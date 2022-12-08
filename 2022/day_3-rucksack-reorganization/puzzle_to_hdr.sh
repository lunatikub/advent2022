#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

nr_rucksack=0

echo "static const struct ruckstack ruckstacks[] = {"

while read -r line
do
  sz=$(echo -n $line | wc -m)
  sz=$((sz / 2))
  c1=${line:0:$sz}
  c2=${line:$sz:$sz}
  echo "  { \"$c1\", \"$c2\", $sz },"
  nr_rucksack=$((nr_rucksack + 1))
done < $INPUT

echo "};"

echo "#define NR_RUCKSTACK $nr_rucksack"

exit 0
