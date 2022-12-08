#!/usr/bin/bash

INPUT="$1"

[ -z "$INPUT" ] && echo "input needed..." && exit 1

nr_ls=0
nr_cmd=0
nr_entry=0
cmds=""
files=""

while read -r line
do
  if [ ${line:0:1} == "$" ]
  then
    if [[ "${line}" =~ "cd" ]]
    then
      path=$(echo $line | cut -d ' ' -f3)
      cmds="$cmds\n  { CD, \"$path\" },"
    elif [[ "${line}" =~ "ls" ]]
    then
      path=$(echo $line | cut -d ' ' -f3)
      cmds="$cmds\n  { LS, NULL },"
      nr_ls=$((nr_ls + 1))
    fi
    nr_cmd=$((nr_cmd + 1))
  else
    name=$(echo $line | cut -d' ' -f2)
    if [ ${line:0:1} == "d" ]
    then
      files="$files\n  { $nr_ls, D, \"$name\", 0 },"
    else
      sz=$(echo $line | cut -d' ' -f1)
      files="$files\n  { $nr_ls, F, \"$name\", $sz },"
    fi
    res="$res\n  { }"
    nr_entry=$((nr_entry + 1))
  fi
done < $INPUT

echo "#include \"command.h\""
echo "#include \"entry.h\""
echo ""
echo "static const command_t cmds[] = {"
echo -e $cmds
echo "};"
echo ""
echo "#define NR_CMD $nr_cmd"
echo ""
echo "static const entry_t entries[] = {"
echo -e $files
echo "};"
echo ""
echo "#define NR_ENTRY $nr_entry"

exit 0
