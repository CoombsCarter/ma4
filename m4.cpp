/*
* FILE           : m4.cpp
* PROJECT        : SENG1000 - Major Assignment 4
* PROGRAMMER     : Carter Coombs
* FIRST VERSION  : 2023-11-28
* DESCRIPTION    : 
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)



// constants
const int kMaxLineLength = 40;
const int kFileError = -1;
const int kNoDash = -2;
const int kNoComma = -3;


// prototypes
int processGames(char[]);
int parseLine(char[], char[], int*, int*);
void parsePrimaryTeam(char[], char[]);
void clearCR(char[]);



int main(void) {

	FILE* fpText = NULL;
	fpText = fopen("teams.txt", "r");								// opening text file to read from
	if (fpText == NULL) {
		printf("Can't open file for reading\n");
		return kFileError;											// exit program if error
	}

	char filename[kMaxLineLength + 1] = "";							// +1 for the NULL
	while (!feof(fpText)) {
		if (fgets(filename, sizeof filename, fpText) != 0) {		// reading each line into filename array
			if (filename[0] != '\n') {								// checking for blank line
				clearCR(filename);									// clearing \n
				printf("Processing %s:\n", filename);
				processGames(filename);
			}
		}
	}

	if (fclose(fpText) != 0) {										// closing the file
		printf("Error closing file.\n");
		return kFileError;											// exit program if error
	}

	return 0;
}



/*
* Function: processGames()
* Description: This function calculates the winning percentage
		       of a team based on their game result data.
* Parameters: char filename : the name of the file that holds the relevant data.
* Returns: int: an integer that represents whether the function worked perfectly or not.
			    0  : processGames() worked perfectly.
				-1 : Error with opening or closing the file.
*/
int processGames(char filename[]) {

	FILE* gameResult = NULL;
	gameResult = fopen(filename, "r");								// opening text file to read from
	if (gameResult == NULL) {
		printf("Can't open file for reading\n");
		return kFileError;											// skip this line if error 
	}

	char wholeLine[kMaxLineLength + 1] = "";						// +1 for NULL 
	char primaryTeam[kMaxLineLength + 1] = "";
	char oppName[kMaxLineLength + 1] = "";
	int teamScore = -1;
	int oppScore = -1;
	int win = 0;
	int tie = 0;
	int loss = 0;
	double winningPercentage = 0.000;

	parsePrimaryTeam(filename, primaryTeam);						// parsing the file extension off the filename

	while (!feof(gameResult)) {
		if (fgets(wholeLine, sizeof wholeLine, gameResult) != 0) {
			if (wholeLine[0] != '\n') {
				clearCR(wholeLine);									// clearing \n
				if (parseLine(wholeLine, oppName, &teamScore, &oppScore) == 0) {

					if (teamScore > oppScore) {						// primary team wins
						printf("\t%s beat %s %d-%d\n", primaryTeam, oppName, teamScore, oppScore);
						win += 1;
					}
					else if (teamScore < oppScore) {				// opp team wins
						printf("\t%s lost to %s %d-%d\n", primaryTeam, oppName, oppScore, teamScore);
						loss += 1;
					}
					else {											// tie game
						printf("\t%s and %s tied at %d\n", primaryTeam, oppName, teamScore);
						tie += 1;
					}
				}
			}
		}
	}

	winningPercentage = (2.0 * win + tie) / (2.0 * (win + tie + loss));
	printf("Season result for %s: %.3lf (%d-%d-%d)\n\n", primaryTeam, winningPercentage, win, loss, tie);

	if (fclose(gameResult) != 0) {									// closing the file
		printf("Error closing file.\n");
		return kFileError;											// skip this line
	}

	return 0;														// happy path
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
*				kNoDash : There was no dash delimiter, skip line.
*				kNoComma : There was no comma delimiter, skip line.
*/
int parseLine(char wholeLine[], char oppName[], int *teamScore, int *oppScore) {

	for (int i = 0; oppName[i]; i++) {								// clearing the last opponents name from the char array
		if (oppName[i] != '\0') {
			oppName[i] = '\0';
		}
	}

	int commaIndex = -1;
	for (int i = 0; (wholeLine[i] != ',') && (i <= (kMaxLineLength + 2)); i++) {	// stop at a comma or stop at the end of the array
																					// +2 to allow the for loop to last the entire array
		oppName[i] = wholeLine[i];
		commaIndex = i;
	}
	if ( (commaIndex == -1) || (commaIndex > kMaxLineLength) ) {	// checking for comma delimiter
		printf("\tNo comma delimiter, skipping this line.\n");
		return kNoComma;											// skip line if no comma
	}

	char score[7] = "";												// 6 bytes to allow for four digits, one space, one dash, and a NULL
	int scoreIndex = 0;
	for (int i = 0; wholeLine[commaIndex + 2] != '\0'; commaIndex++) {	// +2 to skip the last character in the name and the comma
		score[scoreIndex] = wholeLine[commaIndex + 2];
		scoreIndex += 1;
	}

	int dashIndex = -1;												// checking for dash delimiter
	for (int i = 0; (wholeLine[i] != '-') && (i <= (kMaxLineLength + 2)); i++) {	// +2 to allow the for loop to last the entire array
		dashIndex = i;
	}
	dashIndex++;													// so dashIndex represents the correct position of the dash
	if ( (dashIndex == -1) || (dashIndex > kMaxLineLength) ) {
		printf("\tNo dash delimiter, skipping this line.\n");
		return kNoDash;												// skip line if no dash
	}
	char delimiters[3] = { ' ', '-', '\0' };						// 3 bytes as there are 3 delimiter values
	char* token1 = NULL;
	char* token2 = NULL;
	token1 = strtok(score, delimiters);								// separating the two numbers into separate strings
	token2 = strtok(NULL, delimiters);
	*teamScore = atoi(token1);										// converting those numbers into integers and saving them into the correct pointer variables
	*oppScore = atoi(token2);

	return 0;														// happy path
}



/*
* Function: parsePrimaryTeam()
* Description: This function removes the file extension of a char array and
*			   saves the new string into a second char array
* Parameters: char filename[]  : a string to remove the file extension
* Returns: void
*/
void parsePrimaryTeam(char filename[], char primaryTeam[]) {
	char delimiter[2] = { '.', '\0' };								// 2 bytes as there are two delimiter values
	char* token = NULL;
	strcpy(primaryTeam, filename);									// copying filename into primaryTeam to avoid editing filename
	token = strtok(primaryTeam, delimiter);							// splitting the filename from the file extension
}



/*
* Function: clearCR()
* Description: This function is a safer way to clear a new line character
*			   that may or may not be there.
* Parameters: char buf[]  : a string to remove the new line character
* Returns: void
*/
void clearCR(char buf[])
{
	char* whereCR = strchr(buf, '\n');
	if (whereCR != NULL)
	{
		*whereCR = '\0';
	}
}
