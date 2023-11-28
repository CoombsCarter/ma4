/*
* FILE           : m4.cpp
* PROJECT        : SENG1000 - Major Assignment 4
* PROGRAMMER     : Carter Coombs
* FIRST VERSION  : 2023-11-28
* DESCRIPTION    : 
*/



#include <stdio.h>
#include <string.h>
#pragma warning(disable: 4996)



// constants



// prototypes
int processGames(char);
int parseLine(char[], char[], int*, int*);


int man(void) {
	/*	
	*	open teams.txt
	*	exit program if error
	*	loop
	*	read a single line
	*	"Processing Detroit Red Wings.txt:\n"
	*	call processGames() with that line as the parameter
	*/
	return 0;
}



/*
* Function: processGames()
* Description: This function calculates the winning percentage
		       of a team based on their game result data.
* Parameters: char filename : the name of the file that holds the relevant data.
* Returns: int: an integer that represents whether the function worked perfectly or not.
			    0  : processGames() worked perfectly.
				-1 : 
*/
int processGames(char filename) {
	/*
	*	open filename
	*	loop
	*	read single line
	*	call parseLine() with that line as parameter
	*	output "<Team> <Result> <Opponent> <Score>\n"
	*	calculate winning percentage
	*	output winning percentage and record
	*/
	return 0; // happy path
}


/*
* Function: parseLine()
* Description: This function parses each line of a file to gain
			   the relevant information needed.
* Parameters: char gameResult[] : array containing the game result string.
*			  char oppName[]    : array that will be filled with the opponent team name.
*			  int *teamScore    : a pointer to the primary teams score.
*			  int *oppScore     : a pointer to the opposing teams score.
* Returns: int: an integer that represents whether the function worked perfectly or not.
*			    0  : parseLine() worked perfectly.
*				-1 : 
*/
int parseLine(char gameResult[], char oppName[], int *teamScore, int *oppScore) {
	/* 
	*	strchr()
	*	strcpy() copy team name into oppName using comma position from strchr()
	*	strchr() to look for dash
	*	find primary score between comma and dash, opponent score after dash and before NULL
	*	use atoi() to put those scores into the integer arguments
	*/
	return 0; // happy path
}