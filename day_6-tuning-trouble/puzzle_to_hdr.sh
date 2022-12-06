#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

echo "static const subroutine_t subroutine = {"

read -r line < $INPUT
datastream_sz=$(echo $line | awk '{print length}')

echo "  \"$line\",  $datastream_sz"

echo "};"

exit 0
