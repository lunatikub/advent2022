RED="\e[31m"
GREEN="\e[32m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
ENDCOLOR="\e[0m"

ok() {
  echo -e "${GREEN}[OK] ${MAGENTA}($((end - start)) ms)${ENDCOLOR}"
}

ko() {
  echo -e "${RED}[KO] ${MAGENTA}($((end - start)) ms)${ENDCOLOR}"
}

foreach_day() {
  local cb=$1
  for y in $years
  do
    echo -e "${YELLOW}[[[$y]]]${ENDCOLOR}"
    for d in ${days[$y]}
    do
      echo -en "  + day $d "
      pushd $y/day_$d/ >/dev/null
      $cb
      popd >/dev/null
    done
  done
}

title() {
  local title=$1
  echo -e "------- ${BLUE}${title}${ENDCOLOR} -------"
  echo ""
}

get_time_ms() {
  date +%s%N | cut -b1-13
}
