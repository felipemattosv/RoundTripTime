#!/bin/bash

if [ -z "$1" ]; then
  echo "usage: $0 in out myout"
  exit 1
fi

if [ -z "$2" ]; then
  echo "usage: $0 in out myout"
  exit 1
fi

out=$1
myout=$2

orig_dir=$(pwd)
cd $out

files=(*)
cd $orig_dir

for file in "${files[@]}"; do
  echo "$file"
  python scripts/diff.py $out/$file $myout/$file 
done