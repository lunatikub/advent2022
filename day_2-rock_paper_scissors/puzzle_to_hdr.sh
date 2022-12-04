#!/usr/bin/env sh

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

echo "static const struct round rounds[] = {"

nr_round=0

while read -r line
do
  opponent=$(echo $line | cut -d' ' -f1)
  you=$(echo $line | cut -d' ' -f2)
  echo "  { '$opponent', '$you' },"
  nr_round=$((nr_round + 1))
done < $INPUT

echo "};"

echo "#define NR_ROUND $nr_round"

exit 0
