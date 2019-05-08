#!/bin/bash -
#title		:testaverager.sh
#description	:Average a persons grades.
#author		:Jared Diehl
#date		:20190305
#version	:1.0
#usage		:./testaverager.sh firstname lastname grade...
#notes		:CMPSCI2750 Project1 - 3 out of 3
#=====================================================================================================================

function displayUsage() { # Declare a usage function at the top of the script so the program knows it exists when called below.
	echo "Usage: ./testaverager.sh firstname lastname grade..." # Display a helpful usage message to the user.
	exit 1 # Terminate program with a non-zero status.
}

if [ -z $1 ] # Check if first argument exists.
then # If first argument does not exist.
	displayUsage # Display a usage message since the first argument does not exist.
else # If first argument does exist.
	if [ $(($1)) != $1 ] # Check if first argument is not a number.
	then # If first argument is not a number.
		firstname="$1" # If not a number then it's a string and store first argument in firstname.
	else # If first argument is a number.
		echo "The first name cannot be a number." # Display error message to user.
		displayUsage # Name cannot be a number. At least not yet.
	fi # end if
fi # end if

if [ -z $2 ] # Check if second argument exists.
then # If second argument does not exist.
	displayUsage # Display a usage message since the second argument does not exist.
else # If second argument does exist.
	if [ $(($2)) != $2 ] # Check if second argument is not a number.
	then # If second argument is not a number.
		lastname="$2" # If not a number then it's a string and store second argument in lastname.
	else # If second argument is a number.
		echo "The last name cannot be a number." # Display error message to user.
		displayUsage # Name cannot be a number. At least not yet.
	fi # end if
fi # end if

shift 2 # Remove first 2 arguments which are firstname and lastname.

firstname=${firstname,,} # convert firstname to lowercase
firstname=${firstname^} # capitalize first letter of firstname
lastname=${lastname,,} # convert lastname to lowercase
lastname=${lastname^} # capitalize first letter of lastname

if [ $# -gt 0 ] # Are the number of current arguments greater than zero?
then # If the number of current arguments is greater than zero.
	sum=0 # Initialize sum variable to zero.
	for var in "$@" # Iterate through list of all current arguments.
	do # The var variable stores the current argument in the list of arguments.
		intVal=$(echo $var | grep "^[0-9]*$") # check if var is number
		intRes=$(echo $?) # 0 if intVal is an integer, 1 otherwise
		floatVal=$(echo $var | grep "^[0-9]*[.][0-9]*$") # check if var is number
		floatRes=$(echo $?) # 0 if floatVal is a float, 1 otherwise
		
		if [ $intRes -eq 0 ] || [ $floatRes -eq 0 ] # Check if var variable is a number.
		then # If var variable is a number.
			sum=$(bc <<< "scale=2; $sum + $var") # Add var to sum with at least two decimal places.
		else # If var variable is not a number.
			echo "Found a non-number in the list of grades." # Display an error message to the user.
			displayUsage # Display a usage message.
		fi # end if
	done # end for loop
	avg=$(bc <<< "scale=2; $sum / $#") # Average the results by taking the sum divided by the number of current arguments with at least two decimal places.
	
	if (( $(echo "$avg < 70" | bc -l) )) # Check if avg variable is less than 70.
	then # if avg < 70
		echo "Sorry $firstname $lastname but you will have to retake the class!" # Display this message to the user.
	else # if avg >= 70
		echo "Congratulations $firstname $lastname, you passed with an average of $avg!" # Display this message to the user.
	fi # end if
else # If the number of current arguments is less than or equal to zero.
	echo "Found no list of grades." # Display error message to user.
	displayUsage # Display a usage message if the number of arguments is not greater than zero.
fi # end if
