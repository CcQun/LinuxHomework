#!/bin/bash

i=0
for filename in `ls *.c` 
do
	clist[${i}]=${filename}
	((i++))
done

main=main:
for filename in ${clist[@]}
do
	main="$main ${filename/.c/.o}"
done
echo $main > GNUmakefile
echo "	gcc $^ -o main" >> GNUmakefile

for filename in ${clist[@]}
do
	target="${filename/.c/.o}: "
	prerequisites=${filename}
	j=0
	for fdp in `awk -F'"' '/^#include/{print $2}' ${filename}`
	do
		prerequisites="$prerequisites $fdp"
		for cdp in `awk -F'"' '/^#include/{print $2}' ${fdp}`
		do
			prerequisites="$prerequisites $cdp"
		done
	done
	echo "$target$prerequisites" >> GNUmakefile
	echo "	gcc -c ${filename}" >> GNUmakefile
done

echo "clean:" >> GNUmakefile
echo "	-rm main *.o" >> GNUmakefile
echo "	@echo "Finished"" >> GNUmakefile
