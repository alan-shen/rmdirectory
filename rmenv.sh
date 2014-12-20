#!/bin/bash

rm -rfv data

mkdir data
mkdir -p data/media/0
touch data/media/0/shen.txt
touch data/media/0/peng.txt
touch data/media/0/ruru.txt

touch data/android.txt
touch data/linux.txt
touch data/pclinux.txt

for i in $(seq 2)
do
	mkdir -p data/${i}
	touch data/${i}/${i}.txt
	touch data/${i}/${i}.patch
	for j in $(seq 1)
	do
		mkdir -p data/${i}/${j}
		for k in $(seq 1)
		do
			mkdir -p data/${i}/${j}/${k}
			for l in $(seq 1)
			do
				mkdir -p data/${i}/${j}/${k}/${l}
				for m in $(seq 1)
				do
					mkdir -p data/${i}/${j}/${k}/${l}/${m}
					for n in $(seq 1)
					do
						mkdir -p data/${i}/${j}/${k}/${l}/${m}/${n}
						touch    data/${i}/${j}/${k}/${l}/${m}/${n}/.android
					done
				done
			done
		done
	done
done
