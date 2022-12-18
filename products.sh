#!/bin/bash
while [ 1 ];
do
	site1=$1
	site2=$2
	site1_base=`basename $1 .txt`
	site2_base=`basename $2 .txt`
	flag=0
	num=1

	if [ $site1_base == 'swim2000' ];
	then
		(( flag++ ))
	fi

	mkdir metroswimshop/
	mkdir swim2000/
	#mkdir metroswimshop_htmls/
	#mkdir swim2000_htmls/

	while read -r line
	do
		touch ${num}.html
		l=`echo "$line"`
		curl "$l" -o ${num}.html
		java -jar tagsoup-1.2.1.jar --files ${num}.html
		if [ $flag == 1 ]
		then
			rm ${num}.html 
			#mv ${num}.html ${site1_base}_htmls
			mv ${num}.xhtml $site1_base
		else
			rm ${num}.html
			#mv ${num}.html ${site2_base}_htmls
			mv ${num}.xhtml $site2_base
		fi
		(( num++ ))

	done < $site1

	num=1
	while read -r line
	do
		touch ${num}.html
		l=`echo "$line"`
		curl "$line" -o ${num}.html
		java -jar tagsoup-1.2.1.jar --files ${num}.html
		if [ $flag == 0 ]
		then
			rm ${num}.html
			#mv ${num}.html ${site1_base}_htmls
			mv ${num}.xhtml $site1_base
		else
			rm ${num}.html
			#mv ${num}.html ${site2_base}_htmls
			mv ${num}.xhtml $site2_base
		fi
		(( num++ ))
	done < $site2

	python3 parser.py swim2000 metroswimshop

	rm ${site1_base}/*.xhtml
	rmdir $site1_base
	rm ${site2_base}/*.xhtml
	rmdir $site2_base
	
	sleep 21600
done
