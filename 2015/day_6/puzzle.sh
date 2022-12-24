#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  if [[ "$line" =~ "turn on" ]]
  then
    from=$(echo $line | cut -d' ' -f 3)
    from_x=$(echo $from | cut -d',' -f1)
    from_y=$(echo $from | cut -d',' -f2)
    to=$(echo $line | cut -d' ' -f 5)
    to_x=$(echo $to | cut -d',' -f1)
    to_y=$(echo $to | cut -d',' -f2)
    echo "  { TURN_ON, { $from_x, $from_y }, { $to_x, $to_y } },"
  elif [[ "$line" =~ "turn off" ]]
  then
    from=$(echo $line | cut -d' ' -f 3)
    from_x=$(echo $from | cut -d',' -f1)
    from_y=$(echo $from | cut -d',' -f2)
    to=$(echo $line | cut -d' ' -f 5)
    to_x=$(echo $to | cut -d',' -f1)
    to_y=$(echo $to | cut -d',' -f2)
    echo "  { TURN_OFF, { $from_x, $from_y }, { $to_x, $to_y } },"
  elif [[ "$line" =~ "toggle" ]]
  then
    from=$(echo $line | cut -d' ' -f 2)
    from_x=$(echo $from | cut -d',' -f1)
    from_y=$(echo $from | cut -d',' -f2)
    to=$(echo $line | cut -d' ' -f 4)
    to_x=$(echo $to | cut -d',' -f1)
    to_y=$(echo $to | cut -d',' -f2)
    echo "  { TOGGLE, { $from_x, $from_y }, { $to_x, $to_y } },"
  else
    echo 2>&1 "errrrrrr" && exit 1
  fi

  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
