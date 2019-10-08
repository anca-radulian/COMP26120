// Program to create and intialiase an array of structures.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	struct person *nextPerson;
};

int compare_people_by_name(struct person *people1, struct person *people2)
{
	char name1[20], name2[20];
	strcpy(name1, people1->name);
	strcpy(name2, people2->name);
	return strcmp(name1,name2);

}

int compare_people_by_age(struct person *people1, struct person *people2)
{
	return people1->age - people2->age;
}

// Insert elements at the start of the list
static struct person *insert_start(struct person *people, char *name, int age)
{
	// Allocate memory for each structure
	struct person *newPerson=(struct person *) malloc(sizeof(struct person));
	// Check if the malloc works, if not exit with a message.
	if(newPerson == NULL)
	{
		printf("No memory could be allocated!\n");
		exit(0);
	}
	else
	{
		// Assign the attributes values
		newPerson->name = name;
		newPerson->age = age;
		newPerson->nextPerson = people;
		return newPerson;
	}
}

static struct person *insert_end(struct person *people, char *name, int age)
{
	// Allocate memory for each structure
	struct person *newPerson=(struct person *) malloc(sizeof(struct person));
	// Check if the malloc works, if not exit with a message.
	if(newPerson == NULL)
	{
		printf("No memory could be allocated!\n");
		exit(0);
	}
	else
	{
		// Assign the attributes values
		newPerson->name = name;
		newPerson->age = age;
		if(people == NULL)
		{
			newPerson->nextPerson = NULL;
			return newPerson;
		}
		else
		{
			struct person *lastElement = people;
			while(lastElement->nextPerson!= NULL)
				lastElement = lastElement->nextPerson;
			newPerson->nextPerson = NULL;
			lastElement->nextPerson = newPerson;
			return people;
		}

	}
}

static struct person* insert_sorted(struct person *people, char *name, int age, int (*compare_people)(struct person *p1, struct person *p2))
{
	// Allocate memory for each structure
	struct person *newPerson=(struct person *) malloc(sizeof(struct person));
	// Check if the malloc works, if not exit with a message.
	if(newPerson == NULL)
	{
		printf("No memory could be allocated!\n");
		exit(0);
	}
	else
	{
		// Assign the attributes values
		newPerson->name = name;
		newPerson->age = age;

		if(people == NULL || compare_people(newPerson, people) < 0)
		{
			newPerson->nextPerson = people;
			return newPerson;
		}
		else
		{
			struct person *lastElement = people;
			while(lastElement->nextPerson!= NULL && compare_people(lastElement->nextPerson, newPerson)< 0)
				lastElement = lastElement->nextPerson;
			newPerson->nextPerson = lastElement->nextPerson;
			lastElement->nextPerson = newPerson;

			return people;
		}

	}
}


// Print the linked list
void printList(struct person *people)
{
	struct person *ptr = people;
	while(ptr!= NULL)
	{
		printf("%s %d\n", ptr->name, ptr->age);
		ptr = ptr->nextPerson;
	}

}
// Free the memory
void freeMemory(struct person *people)
{
	while(people!= NULL)
	{
		struct person *nextElement = people->nextPerson;
		free(people);
		people = nextElement;
	}
}


int main(int argc, char **argv)
{
	struct person *people1 = NULL;

	// Part 1
  for (int index = 0; index < HOW_MANY; index ++)
  {
    people1 = insert_start(people1, names[index], ages[index]);
  }

		// Print the people
	  printList(people1);
		freeMemory(people1);

		// Part 2
		printf("\n");

		struct person *people2 = NULL;

		for (int index = 0; index < HOW_MANY; index ++)
	  {
	    people2 = insert_end(people2, names[index], ages[index]);
	  }

		// Print the people
		printList(people2);
		freeMemory(people2);


		// Part 3
		printf("\n");

		struct person *people3 = NULL;

		for (int index = 0; index < HOW_MANY; index ++)
		{
			people3 = insert_sorted(people3, names[index], ages[index], compare_people_by_name);
		}

		// Print the people
		printList(people3);
		freeMemory(people3);

		// Part 4
		printf("\n");

		struct person *people4 = NULL;

		for (int index = 0; index < HOW_MANY; index ++)
		{
			people4= insert_sorted(people4, names[index], ages[index], compare_people_by_age);
		}

		// Print the people
		printList(people4);
		freeMemory(people4);





  return 0;
}
