// Program to convert all the upper-case characters into lower-case ones and output some counts.

#include <stdio.h>  // FILE stderr fopen fclose fprintf printf fgets
#include <ctype.h>  // Use functions to manipulate characters
#include <stdlib.h>	// for using exit()

int main()
{
 	
 	// Get the names of the infile and outfile from the user.
 	char in_name[128];
 	char out_name[128];
 	scanf("%s%s", in_name, out_name);
 	
 	// Create the two files.
	FILE *file1= fopen(in_name, "r");
	FILE *file2= fopen(out_name, "w");
	
	// Check if the files exists.
	if (!file1) 
 	{
		fprintf(stderr, "can't open %s for reading\n", in_name);
		exit(-1);
	}
	if (!file2) 
 	{
		printf("can't open file for writing\n");
		exit(-1);
	}
	
	// Initialise variables.
	int ch, countCh = 0, countUpCh = 0, countLoCh = 0;
	
	// Read the first character in case that the file is empty.
	ch = getc(file1);
	

	while(!feof(file1))
	{
		countCh++;
		
		if(isupper(ch))
		{
			putc(tolower(ch), file2);
			countUpCh++;
		}
		else
		{
			putc(toupper(ch), file2);
			countLoCh++;
		}
		// Read the next character.
		ch = getc(file1);
	}
	
	// Print results
	fprintf(file2,"\nRead %d characters in total, %d converted to upper-case, %d to lower-case.\n"
			,countCh, countLoCh, countUpCh);
	
	// Close the file.
	fclose (file1);
	fclose(file2);
	return 0;
}
		
