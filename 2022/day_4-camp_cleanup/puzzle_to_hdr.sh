#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

nr_pair=0

echo "static const struct pair assignments[] = {"

while read -r line
do
  section_1=$(echo $line | cut -d',' -f1)
  section_2=$(echo $line | cut -d',' -f2)
  section_1_from=$(echo $section_1 | cut -d'-' -f1)
  section_1_to=$(echo $section_1 | cut -d'-' -f2)
  section_2_from=$(echo $section_2 | cut -d'-' -f1)
  section_2_to=$(echo $section_2 | cut -d'-' -f2)

  echo "  { { $section_1_from, $section_1_to }, { $section_2_from, $section_2_to } },"
  nr_pair=$((nr_pair + 1))

done < $INPUT

echo "};"

echo "#define NR_PAIR $nr_pair"

exit 0
