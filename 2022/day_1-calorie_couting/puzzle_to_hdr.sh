#!/usr/bin/env sh

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

echo "static const int calories[] = {"

nr_elve=1
nr_line=0

while read -r line
do
  nr_line=$((nr_line + 1))
  if [ "$line" = "" ]
  then
    echo "  -1,"
    nr_elve=$((nr_elve + 1))
  else
    echo "  $line,"
  fi
done < $INPUT

echo "};"

echo "#define NR_ELVE $nr_elve"
echo "#define NR_LINE $nr_line"

exit 0
