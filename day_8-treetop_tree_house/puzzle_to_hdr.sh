#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

W=$(head -n1 $INPUT)
W=${#W}
H=$(wc -l $INPUT | cut -d' ' -f1)

echo "#include <stdint.h>"
echo ""

echo "#define W $W"
echo "#define H $H"
echo ""

echo "static const uint8_t grid[H][W] = {"

while read -r line
do
  echo -n "  { "
  for (( i = 0; i < ${#line}; ++i ))
  do
    echo -n "${line:$i:1}, "
  done
  echo "},"
done < $INPUT

echo "};"

echo ""

exit 0
