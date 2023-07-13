#!/bin/sh

if [ $# -eq 0 ]
  then
    echo "No arguments supplied, file to test missing"
    exit 1
fi

./etapa5 < $1 > output.txt && python3 toAST.py output.txt ast.dot && xdot ast.dot &