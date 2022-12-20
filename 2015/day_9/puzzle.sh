#!/bin/bash

INPUT="$1"
[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
static dist_t dists[] = {
EOF

nr_dist=0

while read -r line
do
  city_1=$(echo $line | cut -d' ' -f1)
  city_2=$(echo $line | cut -d' ' -f3)
  dist=$(echo $line | cut -d' ' -f5)
  echo "  { \"$city_1\", \"$city_2\", $dist },"
  nr_dist=$((nr_dist + 1))
done < $INPUT

cat <<EOF
};

#define NR_DIST $nr_dist
EOF

exit 0
