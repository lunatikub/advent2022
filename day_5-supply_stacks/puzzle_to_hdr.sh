#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

MOVES=/tmp/moves
CRATES=/tmp/crates

grep "^move" $INPUT > $MOVES
grep -v "^move" $INPUT > $CRATES

nr_move=0

echo "#include \"struct.h\""
echo ""

echo "static const move_t moves[] = {"

while read -r line
do
  nr=$(echo $line | cut -d' ' -f2)
  from=$(echo $line | cut -d' ' -f4)
  to=$(echo $line | cut -d' ' -f6)
  echo "  { $nr, $from, $to },"
  nr_move=$((nr_move + 1))
done < $MOVES

echo "};"

echo ""
echo "#define NR_MOVE $nr_move"
echo ""

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

exit 0
