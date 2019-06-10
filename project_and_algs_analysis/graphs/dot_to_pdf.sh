#!/bin/bash
for file in $(ls $1)
do
	filename="${file%.*}"
	dot -T$2 -o $1$filename.$2 $1$file
done
