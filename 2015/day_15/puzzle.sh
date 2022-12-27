#!/usr/bin/bash

INPUT="$1"

TARGET=100

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  ingredient=$(echo $line | cut -d ':' -f 1)
  capacity=$(echo $line | cut -d ' ' -f 3 | sed 's/,//')
  durability=$(echo $line | cut -d ' ' -f 5 | sed 's/,//')
  flavor=$(echo $line | cut -d ' ' -f 7 | sed 's/,//')
  texture=$(echo $line | cut -d ' ' -f 9 | sed 's/,//')
  calories=$(echo $line | cut -d ' ' -f 11)
  echo "  { \"$ingredient\", $capacity, $durability, $flavor, $texture, $calories },"
  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input

const int combis[][NR_INPUT] = {
EOF

if [ $nr_input -eq 2 ]
then
  n=0
  for a in $(seq 0 $TARGET)
  do
    for b in $(seq 0 $TARGET)
      do
        if [ $((a + b)) -eq $TARGET ]
        then
          if [ $((n % 4 )) -eq 0 ]
          then
            echo -n "  { $a, $b },"
          else
            echo -n " { $a, $b },"
            if [ $((n % 4)) -eq 3 ]
            then
              echo ""
            fi
          fi
          n=$((n + 1))
        fi
    done
  done
elif [ $nr_input -eq 4 ]
then
  n=0
  for a in $(seq 0 $TARGET)
  do
    for b in $(seq 0 $TARGET)
    do
      [ $((a + b)) -gt $TARGET ] && continue
      for c in $(seq 0 $TARGET)
      do
        [ $((a + b + c)) -gt $TARGET ] && continue
        d=$(($TARGET - a - b - c))
        if [ $((n % 4 )) -eq 0 ]
        then
          echo -n "  { $a, $b, $c, $d },"
        else
          echo -n " { $a, $b, $c, $d },"
          [ $((n % 4)) -eq 3 ] && echo ""
        fi
        n=$((n + 1))
      done
    done
  done
fi

cat <<EOF
};

#define NR_COMBI $n
EOF

exit 0
