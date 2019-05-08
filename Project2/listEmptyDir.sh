#!/bin/bash
#title		:listEmptyDir.sh
#description	:Store empty directories.
#author		:Jared Diehl
#date		:20190321
#version	:1.0
#usage		:./listEmptyDir.sh directory
#notes		:CMPSCI2750 Project2 - 1 out of 3
#================================================

if [ "$#" -ne 1 ] || ! [ -d $1 ] # Check if the total number of parameters given is equal to one or if the parameter is not a directory.
then # If total number of parameters is equal to one or parameter is not a directory.
	echo "usage: $0 directory" # Display usage message to user.
	exit 1 # Exit with non-zero status.
fi # End if

listing=`ls $1` # ls the directory using the first positional parameter and store that text data in a variable.

for file in $listing # Loop through all lines in listings variable. Each line is a file.
do
	echo "$file" # Display the files name.
	
	pathToFile="$1/$file" # Get the files path from current directory.
	
	if [ -d $pathToFile ] && [ -z "$(ls -A $pathToFile)" ] # Check if pathToFile variable is a directory and the directory is empty.
	then # If the pathToFile variable is a directory and the directory is empty.
		echo "$file" >> EmptyDir.txt # Append the filename to the text file EmptyDir.txt.
	fi # End if
done # End loop
