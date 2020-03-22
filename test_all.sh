#!/bin/bash
value=0
while  IFS= read -r input 
do
	
	./test/bin/"$input" > /dev/null 2>&1
	if [ $? -ne 0 ]
	then
		exit 1
	fi
done < "test_args.txt"
exit 0


