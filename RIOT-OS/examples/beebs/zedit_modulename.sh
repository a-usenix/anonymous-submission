#!/bin/bash

function exprReplace() {
  # Check if the file exists
  if [[ -f "$1" ]]; then
    ed -s "$1" <<EOF
%s/$2/$3/g
w
EOF
  else
    echo "File $1 does not exist."
  fi
}

dir=`ls`

cur="./"
prev="./"
for i in $dir
do
  cur="${i}"
  echo "cur ${cur}, prev ${prev}"
  exprReplace "./${cur}/main.c" "aha-compress" ${cur}
  echo "replace done!"
  prev="${i}"
done

