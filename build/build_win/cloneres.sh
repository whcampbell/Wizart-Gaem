#!/bin/bash

# Disable shell glob expansion within the script
# Required to stop bash from expndinging the glob in $1
set -f

for file in `find . ! -name $1 | sed 's/^.\///'`
  do if [ -d "./$file" ]; then
    mkdir -p "$2/$file"
  else
    cp "./$file" "$2/$file"
fi
done