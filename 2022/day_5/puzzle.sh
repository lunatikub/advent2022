#!/bin/bash

INPUT="$1"

###
### Moves
###

MOVES=/tmp/moves
grep "^move" $INPUT > $MOVES

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

while read -r line
do
  nr=$(echo $line | cut -d' ' -f2)
  from=$(echo $line | cut -d' ' -f4)
  to=$(echo $line | cut -d' ' -f6)
  echo "{$nr,$from,$to},"
  nr_input=$((nr_input + 1))
done < $MOVES

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

rm -rf $MOVES

###
### Crates
###

CRATES=/tmp/crates
grep -v "^move" $INPUT > $CRATES

tot_crate=$(tail -n 2 $CRATES | head -n1 | sed 's/.* \([0-9]*\)/\1/')

cat $CRATES | head -n -2 > /tmp/tmp_crates
mv /tmp/tmp_crates $CRATES

while IFS= read line
do
  for i in $(seq 0 $((tot_crate - 1)))
  do
    start=$((i * 4 + 1))
    n=${line:$start:1}

    if [ "$n" != " " ] && [ "$n" != "" ]
    then
      crates[$i]="$n ${crates[$i]}"
      nr_crate[$i]=$((nr_crate[$i] + 1))
    fi
  done
done < $CRATES

echo ""
echo "static crate_t crates[] = {"

for i in $(seq 0 $((tot_crate - 1)))
do
  echo -n "  { {"
  for j in $(seq 1 ${nr_crate[$i]})
  do
    crate=$(echo ${crates[$i]} | cut -d' ' -f$j)
    echo -n "'$crate', "
  done
  echo "}, ${nr_crate[$i]}, $i },"
done

echo "};"
echo ""

echo "#define NR_CRATE $tot_crate"

rm -rf $CRATES
rm -rf /tmp/tmp_crates

exit 0
