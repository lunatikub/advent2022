#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

cat <<EOF
#include "motion.h"

static const motion_t motions[] = {
EOF

nr_motion=0

while read -r line
do
  type=$(echo $line | cut -d' ' -f1)
  step=$(echo $line | cut -d' ' -f2)
  echo "  { $type, $step },"
  nr_motion=$((nr_motion + 1))
done < $INPUT

cat <<EOF
};

#define NR_MOTION $nr_motion
EOF

exit 0
