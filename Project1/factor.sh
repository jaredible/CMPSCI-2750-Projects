#!/bin/bash -
#title		:factor.sh
#description	:Finds the smallest prime factor of a chosen number from 10 to 100.
#author		:Jared Diehl
#date		:20190305
#version	:1.0
#usage		:./factor.sh
#notes		:CMPSCI2750 Project1 - 2 out of 3
#=====================================================================================================================

echo -n " Enter an integer from 10 to 100: " # prompt user for an integer from 10 to 100

read n # store the users chosen number

if [ -z "$n" ] # check if n is empty
then # if n is empty
	echo "You must choose an integer from 10 to 100." # display error message to user
	exit 1 # terminate program
fi # end if

if [ $((n)) != $n ] # check if n is not an integer
then # if n is not an integer
	echo "Must be an integer." # display error message to user
	exit 1 # terminate program
fi # end if

if [ "$n" -lt 0 ] # check if n is less than 0
then # if n < 0
	echo "Must be a positive integer." # echoed if n is less than 0
else # if n >= 0
	if [ "$n" -ge 10 ] && [ "$n" -le 100 ] # check if n is integer from 10 to 100
	then # if n >= 10 and n <= 100
		factors=`factor $n | cut -f 1 -d " " --complement` # prime factorize n then store all prime factors as space delimited string
		
		IFS=' ' read -a primes <<< "$factors" # convert space delimited string of prime factors into integer array of prime factors, stored in primes variable
		
		if [ ${#primes[@]} -eq 1 ] # check if factors variable size is equal to one
		then # if primes variable length is equal to 1, implies the number will be prime
			echo "The number is prime." # display message to user that the number is prime
		else # if primes variable length is greater than 0, implies that there will be a list of prime factors
			echo "The smallest prime factor is "${primes[0]}. # display a message to user containing prime factor, the zeroth index of primes variable is the smallest prime
		fi # end if
	else # if n < 10 or n > 100
		echo "Must be from 10 to 100." # display error message to user
	fi # end if
fi # end if
