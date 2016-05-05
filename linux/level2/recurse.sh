#!/usr/bin/env bash

list ()
{
	for f in $(find . )
	do
		stat -c "%a %n" "$f"
	done
}

recurse ()
{
	for f in *; do
		# echo $f
		if [ -f "$f" ]; then
			# stat -c "%a %n" "$f"
			chmod ug+wr $f
			chmod o-w $f
			# stat -c "%a %n" "$f"

		elif [ -d "$f" ]; then
			# echo "${PWD}:"
			# stat -c "%a %n" "$f"
			chmod 775 "$f"
			# stat -c "%a %n" "$f"

			cd $f
			recurse
			cd ..

		fi
		# echo
	done
}

list
echo
echo "Editing files..."
recurse
echo
list

# for f in $(find . )
# do
# 	echo
# 	recurse $f

	# stat -c "%a %n" $f

# 	if [ -d "$f" ]
# 	then
# 		chmod 775 $f
# 	elif [ -f "$f" ]
# 	then
# 		chmod +wr $f
# 		chmod o-w $f
# 	fi

# 	stat -c "%a %n" $f
# done