
#!/bin/bash

FILES=files/input/*

for f in $FILES
do
	echo $f
	time ./main < $f > trash.txt
# 	time ./main < $f
	echo

done
