#!/usr/bin/env bash

cd examples
files=$(find . -name "*.cpp" | cut -d/ -f2-)

for file in $files; do
    outputName=$(cut -d. -f1 <<< $file)
    make $outputName
done
