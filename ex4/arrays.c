// Program to create and intialiase an array of structures.
#include <stdio.h>
#include<stdlib.h>

/* these arrays are just used to give the parameters to 'insert',
   to create the 'people' array
*/
#define HOW_MANY 7
char *names[HOW_MANY]= {"Simon", "Suzie", "Alfred", "Chip", "John", "Tim",
		      "Harriet"};
int ages[HOW_MANY]= {22, 24, 106, 6, 18, 32, 24};


/* declare your struct for a person here */
struct person{
	char *name;
	int age;
} *people[HOW_MANY];

static void insert(struct person *people[], char *name, int age, int *nextfreeplace)
{
	// Allocate memory for each structure
	people[*nextfreeplace] = (struct person *) malloc(sizeof(struct person));
	// Check if the malloc works, if not exit with a message.
	if(people[*nextfreeplace] == NULL){
		printf("No memory could be allocated!\n");
		exit(0);
	}
	else
	{
		// Assign the attributes values
		people[*nextfreeplace]->name = name;
		people[*nextfreeplace]->age = age;

		// Increase the array index
		(*nextfreeplace)++;
	}

}

int main(int argc, char **argv)
{
	int nextfreeplace = 0;

  /* declare the people array here */
  for (int index = 0; index < HOW_MANY; index ++)
  {

    insert (people, names[index], ages[index], &nextfreeplace);
  }

		// Print the people
	  for (int index = 0; index < HOW_MANY; index ++)
	  {
			printf("%s %d\n", people[index]->name, people[index]->age);
		}

		// Free the memory
		for (int index = 0; index < HOW_MANY; index ++)
		{
			free(people[index]);
		}

  return 0;
}
