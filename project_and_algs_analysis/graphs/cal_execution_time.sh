#!/bin/bash

rm executions

for file in $(ls $1/in)
do		
	printf %"s\n\n" $file 1>> executions
	for i in {1..50}		
	do	
		filename="${file%.*}"
		{ /usr/bin/time -f%e ./tp_grafos < $1/in/$file > cecilia-out/$filename-cecilia.out; } 2>> executions 
	done
	printf "\n" 1>> executions
done

#for file in $(ls $1/out)
#do		
#	echo $file
#	filename="${file%.*}"
#	diff $1/out/$file cecilia-out/$filename-cecilia.out
#done