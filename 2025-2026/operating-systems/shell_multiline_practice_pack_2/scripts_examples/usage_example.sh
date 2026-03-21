#!/bin/sh
usage() {
  echo "Usage: $0 --input FILE [--output FILE] [--verbose]" >&2
}

input=""
output=""
verbose=0

while [ $# -gt 0 ]; do
  case "$1" in
    --input) input=$2; shift 2 ;;
    --output) output=$2; shift 2 ;;
    --verbose) verbose=1; shift ;;
    --help) usage; exit 0 ;;
    *) echo "Unknown argument: $1" >&2; usage; exit 1 ;;
  esac
done
