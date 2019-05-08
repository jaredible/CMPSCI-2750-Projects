#!/bin/bash
#title		:contact_one.sh
#description	:Search HERE document for user prompted pattern.
#author		:Jared Diehl
#date		:20190321
#version	:1.0
#usage		:./contact_one.sh
#notes		:CMPSCI2750 Project2 - 2 out of 3
#================================================

# Define and store a HERE document in the doc variable.
IFS='' read -r -d '' doc <<'myContactList'
Elon Musk, 1 Crater Mars, elon.musk@dankest.com, 6969696969
Jared Diehl, 7259 Gadwall Way, jared@jaredible.net, 3146291836
John Doe, 69 Street, john@doe.com, 3149116969
Jane Dough, 911 Avenue, jane@dough.us, 3149119696
Donald Trump, 911 Street, donald@trump.merica 0000000000
Miley Cyrus, 67 Boulevard, miley@cyrus.us 9999999999
myContactList

echo "Enter a pattern or hit \"Enter\" to exit." # Prompt user for a pattern to exit.
read pattern # Read the users input.

while [[ $pattern ]] # Check if pattern is not empty.
do # Begin loop
	if [[ $(echo "$doc" | grep "$pattern") ]] # Check if the users pattern exists in the HERE document.
	then # If the pattern exists.
		echo "$doc" | grep "$pattern" # Display the line(s) matching the pattern.
	else # If there is nothing matching the pattern.
		echo "No matches were found." # Display a message to the user stating there was no match.
	fi # End if
	
	pattern="" # Clear the pattern variable.
	echo "Enter a pattern or hit \"Enter\" to exit." # Prompt use for a pattern to exit.
	read pattern # Read the users input.
done # End loop
