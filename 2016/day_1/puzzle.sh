#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

for i in $(cat $INPUT | tr ',' '\n')
do
  turn=${i:0:1}
  block=${i:1}
  echo "{'$turn',$block},"
  nr_input=$((nr_input + 1))
done

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
