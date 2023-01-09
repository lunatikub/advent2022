#!/bin/bash

INPUT="$1"

cat <<EOF
static const input_t inputs[] = {
EOF

nr_input=0

get() {
  local name="$1"
  local line="$2"
  echo $line | grep -q $name
  [ $? -ne 0 ] && echo -n "-1" && return
  echo $line | sed  "s/.*$name: \([^,$]*\).*/\1/"
}

while read -r line
do
  children=$(get "children" "$line")
  cats=$(get "cats" "$line")
  samoyeds=$(get "samoyeds" "$line")
  pomeranians=$(get "pomeranians" "$line")
  akitas=$(get "akitas" "$line")
  vizslas=$(get "vizslas" "$line")
  goldfish=$(get "goldfish" "$line")
  trees=$(get "trees" "$line")
  cars=$(get "cars" "$line")
  perfumes=$(get "perfumes" "$line")
  echo -n "{{$children,$cats,$samoyeds,$pomeranians,"
  echo "$akitas,$vizslas,$goldfish,$trees,$cars,$perfumes}},"

  nr_input=$((nr_input + 1))
done < $INPUT

cat <<EOF
};

#define NR_INPUT $nr_input
EOF

exit 0
