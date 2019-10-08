// Program to calculate the longest string from a given number of command-line
// parameters.
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{

  int max_length = 0;
  int max_index;

  // Search for the longest parameter.
  for(int index = 1 ; index < argc; index ++)
  {
    if(max_length < strlen(argv[index]))
    {
      max_length = strlen(argv[index]);
      max_index = index;
    }
  }

  // If the length is 0, then there aren't any parameters.
  if(max_length != 0)
    printf("The longest parameter is \"%s\".\n", argv[max_index] );
  else
    printf("There are no command line arguments.\n");
}
