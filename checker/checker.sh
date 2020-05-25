#!/bin/bash
cpecif=$@
char="ali test"
flag="0 + - # "
flag2="0 + - # ."
len="l h ll hh"
gcc main.c -L ../ -ldprintf -I ../includes -o dprintf
if [ "${cpecif}" == "" ]
then
	cpecif="c s d i o u x X p"
fi
for f in ${cpecif}
do
	for l in ${len}
	do
		for fl in ${flag}
		do
			for fl2 in ${flag2}
			do
				for i in {0..30}
				do
					if [ "${f}" != "s" ]
					then
						if [ "${f}" == "c"  ]
						then
							l=""
							if [ "${i}" == "10" ]
							then
								i=11
							fi
							if [ "${i}" == "0" ]
							then
								i=1
							fi
						fi
						./dprintf "d" "% ${fl}${fl2}${i}${l}${f}" "${i}" 0>diff
						line=$(head -1 diff)
						line2=$(tail -1 diff)
						if [ "${line}" != "${line2}" ]
						then
							echo -e "\e[31m \"% ${fl}${fl2}${i}${l}${f}\" ,${i}\e[0m"
						else
							echo -e "\e[32m \"% ${fl}${fl2}${i}${l}${f}\" ,${i}\e[0m"

						fi
					fi
					#sleep 0.001
					if [ "${f}" == "s" ] || [ "${f}" == "p" ]
					then
						if [ "${f}" == "s" ]
						then
							l=""
						fi
						./dprintf "s" "% ${fl}${fl2}${i}${l}${f}" "${char}" 0>diff
						line=$(head -1 diff)
						line2=$(tail -1 diff)
						if [ "${line}" != "${line2}" ]
						then
							echo -e "\e[31m \"% ${fl}${fl2}${i}${l}${f}\" ,${char}\e[0m"
						else
							echo -e "\e[32m \"% ${fl}${fl2}${i}${l}${f}\" ,${char}\e[0m"

						fi
					fi
					#sleep 0.001
				done
			done
		done
	done
done
rm -f diff
