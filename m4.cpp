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
		return -1;													// exit program if error
	}

	char filename[kMaxLineLength + 1] = "";							// +1 for the NULL
	while (!feof(fpText)) {
		if ( (fgets(filename, sizeof filename, fpText)) != 0) {		// reading each line into filename array
			clearCR(filename);										// clearing \n
			printf("Processing %s:\n", filename);
			processGames(filename);
		}
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
				-1 : 
*/
int processGames(char filename[]) {

	FILE* gameResult = NULL;
	gameResult = fopen(filename, "r");								// opening text file to read from
	if (gameResult == NULL) {
		printf("Can't open file for reading\n");
		return -1;													// skip this line if error 
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
		if ((fgets(wholeLine, sizeof wholeLine, gameResult)) != 0) {
			clearCR(wholeLine);										// clearing \n
			parseLine(wholeLine, oppName, &teamScore, &oppScore);

			if (teamScore > oppScore) {								// primary team wins
				printf("\t%s beat %s %d-%d\n", primaryTeam, oppName, teamScore, oppScore);
				win += 1;
			}
			else if (teamScore < oppScore) {						// opp team wins
				printf("\t%s lost to %s %d-%d\n", primaryTeam, oppName, oppScore, teamScore);
				loss += 1;
			}
			else {													// tie game
				printf("\t%s and %s tied at %d\n", primaryTeam, oppName, teamScore);
				tie += 1;
			}
		}
	}

	winningPercentage = (2.0 * win + tie) / (2.0 * (win + tie + loss));
	printf("Season result for %s: %.3lf (%d-%d-%d)\n\n", primaryTeam, winningPercentage, win, loss, tie);

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
*				-1 : 
*/
int parseLine(char wholeLine[], char oppName[], int *teamScore, int *oppScore) {

	for (int i = 0; oppName[i]; i++) {
		if (oppName[i] != '\0') {
			oppName[i] = '\0';
		}
	}

	int commaIndex = NULL;
	for (int i = 0; wholeLine[i] != ','; i++) {
		oppName[i] = wholeLine[i];
		commaIndex = i;
	}
	char score[7] = "";												// 6 bytes to allow for four digits, one space, one dash, and a NULL
	int scoreIndex = 0;
	for (int i = 0; wholeLine[commaIndex + 2] != '\0'; commaIndex++) { // +2 to skip the last character in the name and the comma
		score[scoreIndex] = wholeLine[commaIndex + 2];
		scoreIndex += 1;
	}

	char delimiters[3] = { ' ', '-', '\0' };
	char* token1 = NULL;
	char* token2 = NULL;
	token1 = strtok(score, delimiters);
	token2 = strtok(NULL, delimiters);
	*teamScore = atoi(token1);
	*oppScore = atoi(token2);

	return 0;														// happy path
}



/*
* Function: parsePrimaryTeam()
* Description: This function removes the file extension of a string
* Parameters: char filename[]  : a string to remove the file extension
* Returns: void
*/
void parsePrimaryTeam(char filename[], char primaryTeam[]) {
	char delimiter[2] = { '.', '\0' };
	char* token = NULL;
	strcpy(primaryTeam, filename);
	token = strtok(primaryTeam, delimiter);
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