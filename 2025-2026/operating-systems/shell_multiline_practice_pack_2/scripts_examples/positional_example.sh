#!/bin/sh
if [ $# -ne 2 ]; then
  echo "Usage: $0 <pattern> <file>" >&2
  exit 1
fi

pattern=$1
file=$2

grep "$pattern" "$file"
