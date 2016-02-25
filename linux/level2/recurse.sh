#!/usr/bin/env bash

for f in $(find .)
do
	stat -c "%a %n" $f
done

for f in $(find . -type d)
do
	chmod 775 $f
done

for f in $(find . -type f)
do
	chmod +wr $f
	chmod o-w $f
done


for f in $(find . )
do
	stat -c "%a %n" $f
done