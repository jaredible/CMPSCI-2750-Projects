#!/bin/bash -
#title		:info.sh
#description	:Displays some system information given a file and a directory.
#author		:Jared Diehl
#date		:20190305
#version	:1.0
#usage		:./info.sh file directory
#notes		:CMPSCI2750 Project1 - 1 out of 3
#=====================================================================================================================

if [ $# -gt 2 ] # Check if the number of arguments is greater than two.
then # If the number of arguments is greater than two.
	echo "Max number of parameters is 2." # Display error message to user.
	echo "Usage: ./info.sh file directory" # Display usage message to user.
	exit 1 # Terminate program with a non-zero status.
fi # end if

if [ -z $1 ] # Check if first argument is empty.
then # If first argument is empty.
	echo "No file specified." # Display error message to user.
	echo "Usage: ./info.sh file directory" # Display usage message to user.
	exit 1 # Terminate program with a non-zero status.
else # If first argument is not empty.
	if ! [ -f $1 ] # Check if first argument is not a file.
	then # If first argument references an existing file.
		echo "That file does not exist." # Display error message to user.
		echo "Usage: ./info.sh file directory" # Dislay usage message to user.
		exit 1 # Terminate program with a non-zero status.
	fi # end if
fi # end if

if [ -z $2 ] # Check if second argument is empty.
then # If second argument is empty.
	echo "No directory specified." # Display error message to user.
	echo "Usage: ./info.sh file directory" # Dislay usage message to user.
	exit 1 # Terminate program with a non-zero status.
else # If second argument is not empty.
	if ! [ -d $2 ] # Check if second argument is not a directory.
	then # If second argument references an existing directory.
		echo "That directory does not exist." # Display error message to user.
		echo "Usage: ./info.sh file directory" # Display usage message to user.
		exit 1 # Terminate program with a non-zero status.
	fi # end if
fi # end if

# The information will be enclosed in equal sign lines so that the user can identify the data more clearly.
echo "==============================================================================" # Display some equals signs at the beginning so that the user can identify the data more clearly.
echo Name of script:					$(basename -- "$0") # display the name of this script
echo "Usage: ./info.sh file directory"
echo Current date and time:				`date +"%m-%d-%Y %T %Z"` # display the current date and time
echo User:						$USER # display the user
echo Current working directory:				"$PWD" # display the current working directory
echo Name of UNIX machine:				`hostname` # display the name of the UNIX machine
echo Name of login shell:				"$SHELL" # display the name of the login shell
echo Contents of the required file:			;cat $1; echo ""
echo Number of text lines in file:			"$( cut -d ' ' -f 1 <<< `wc -l $1` )" # display the number of lines of the required file
echo "Listing of the required directory:"		;ls $2 | cat; echo "" # display the listing of the required directory
echo Total number of script parameters:			"$#" # display the total number of script parameters
echo "Calendar for October of the current year:"	;cal 10 $(date +'%Y') # display October calendar of current year
echo Disk usage:					;du -sh $1; du -sh $2; echo "" # display disk usage of file and directory
echo Current number of users in system:			`who | wc -l` # display current number of users in system
echo Current time:					`date +"%T %Z"` # display current time
echo "==============================================================================" # Display some equals at the end so that the user can identify the data more clearly.
