// Program to count the number of characters from a file given as a program
// parameter. Output how many instaces of each differnt character are in the
//file.
#include<stdio.h>
#include <stdlib.h>	// for using exit()

int chars[256];

int main(int argc, char *argv[])
{
  // Check the number of argumets.
  if(argc != 2)
  {
    printf("Please supply only one file name.\n");
    return 0;
  }
  // Open the file.
  char *file_name = argv[1];
  FILE *file = fopen(file_name, "r");

  // Check if the file exists.
  if (!file)
 	{
		fprintf(stderr, "Can't open %s for reading\n.", file_name);
		return 0;
	}



  // Read the first character in case the file is empty.
  int ch = getc(file);

  // Read the file.
  while(!feof(file))
	{
    chars[ch] ++;
    ch = getc(file);
  }

  // Output the counting.
  for(int index = 0 ; index < 256; index ++)
  {
    if(chars[index] == 1)
      printf("%2d instance of character 0x%.2x (%c).\n ", chars[index], index, index);
    else if (chars[index] > 0)
      printf("%2d instances of character 0x%.2x (%c).\n ", chars[index], index, index);
  }

  fclose(file);
  return 0;
}
