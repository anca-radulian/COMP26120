//==============================================================================
// The code used for sorting is taken from http://www.geeksforgeeks.org/merge-sort/
//==============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

FILE *fp;

typedef struct book
{
  double rating;
  double price;
  double relevance;
  int ID;
} B;

B *list;

//---- merging method used in mergeSort
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(B *arr, int l, int m, int r,int(*compar)(const void *, const void *))
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    B L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {

      if((compar)(&L[i], &R[j]) < 0 )
      {
        arr[k] = L[i];
        i++;
      }
      else
      {
        arr[k] = R[j];
        j++;
      }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// The method used for sorting
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(B *arr, int l, int r, int(*compar)(const void *, const void *))
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m, compar);
        mergeSort(arr, m+1, r, compar);

        merge(arr, l, m, r, compar);
    }
}



int read_file(char *infile, int N)
{
  int c;
  if((fp=fopen(infile, "rb")))
    {
      fscanf(fp, "%*s\t%*s\t%*s\t%*s\n");
      c=0;
      while((!feof(fp))&&(c<N))
	{
	  fscanf(fp, "%lf\t%lf\t%lf\t%d\n", &list[c].rating,  &list[c].price, &list[c].relevance, &list[c].ID);
	  c++;
	}
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"%s did not open. Exiting.\n",infile);
      exit(-1);
    }
  return(c);
}

int comp_on_rating(const void *a, const void *b)
{
  if ((*(B *)a).rating < (*(B *)b).rating)
  {
     return -1;
  }
    else
  {
    if ((*(B *)a).rating > (*(B *)b).rating)
    {
      return 1;
    }
      else
    {
      return 0;
    }
  }
}

int comp_on_relev(const void *a, const void *b)
{

  if ((*(B *)a).relevance < (*(B *)b).relevance)
  {
     return -1;
  }
     else
  {
     if ((*(B *)a).relevance > (*(B *)b).relevance)
     {
       return 1;
     }
       else
     {
       return 0;
     }
  }
}

int comp_on_price(const void *a, const void *b)
{

  if ((*(B *)a).price < (*(B *)b).price)
  {
     return 1;
  }
     else
  {
     if ((*(B *)a).price > (*(B *)b).price)
     {
       return -1;
     }
       else
     {
       return 0;
     }
  }
}

void user_interface(int N)
{
  // For Part 1 this function calls the sort function to sort on Price only

  // mergeSort(list, 0, N - 1 , comp_on_price);

  // For Part 2 this function
  // (1) asks the user if they would like to sort their search results
  // (2) asks for the most important field (or key), the next most etc
  // (3) calls your sort function

  char ans[100];
  printf("Would you like a lexicographic sorting?\n");
  scanf("%s", ans);

  if(strcmp(ans, "yes") == 0)
  {
    char field1[100],field2[100],field3[100];
    printf("Please type the order of the fields(stars,price,relv) based on their importance:\n");
    scanf("%s %s %s", field1, field2, field3);

    // Least important field
    if(strcmp(field3, "stars") == 0)
      //mergeSort(list, 0, N - 1, comp_on_rating);
      qsort(list,N,sizeof(B), comp_on_rating);
    else if(strcmp(field3, "price") == 0)
      //mergeSort(list, 0, N - 1, comp_on_price);
      qsort(list,N,sizeof(B), comp_on_price);
    else
      //mergeSort(list, 0, N - 1, comp_on_relev);
      qsort(list,N,sizeof(B), comp_on_relev);

    // Second field
    if(strcmp(field2, "stars") == 0)
      //mergeSort(list, 0, N - 1, comp_on_rating);
      qsort(list,N,sizeof(B), comp_on_rating);
    else if(strcmp(field2, "price") == 0)
      //mergeSort(list, 0, N - 1, comp_on_price);
      qsort(list,N,sizeof(B), comp_on_price);
    else
      //mergeSort(list, 0, N - 1, comp_on_relev);
      qsort(list,N,sizeof(B), comp_on_relev);

    // Most important field
    if(strcmp(field1, "stars") == 0)
      //mergeSort(list, 0, N - 1, comp_on_rating);
      qsort(list,N,sizeof(B), comp_on_rating);
    else if(strcmp(field1, "price") == 0)
      //mergeSort(list, 0, N - 1, comp_on_price);
      qsort(list,N,sizeof(B), comp_on_price);
    else
      //mergeSort(list, 0, N - 1, comp_on_relev);
      qsort(list,N,sizeof(B), comp_on_relev);


  }
  else
  {
    printf("Ok! Bye - bye!\n");
  }

}


void print_results(int N)
{
    int i;
    if((fp=fopen("top20.txt","w")))
    {
      for(i=N-1;i>=N-20;i--)
      {
	  printf("%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);
	  fprintf(fp, "%g %g %g %d\n", list[i].rating, list[i].price, list[i].relevance, list[i].ID);

      }
      fclose(fp);
    }
      else
    {
      fprintf(stderr,"Trouble opening output file top20.txt\n");
      exit(-1);
    }

}


int main(int argc, char *argv[])
{
  int N;

  if(argc!=3)
    {
      fprintf(stderr, "./exec <input_size> <filename>\n");
      exit(-1);
    }

  N=atoi(argv[1]);

  list = (B *)malloc(N*sizeof(B));

  N=read_file(argv[2], N);

  user_interface(N);

  print_results(N);

  // Part 2: Anna's book. The importance of three fields are the following:
  // star relv price.

  // The book we are loging for has the following ID.
  int id = list[N -1].ID;
  printf("Anna's book has the following ID: %d\n", id );

  int min_price = list[N-1].price;
  int index_book, index;
  for(index = N-1; index >= 0 ; index--)
  {
    if(list[index].relevance < 9.5 || list[index].rating != 5)
      break;

    if(min_price > list[index].price)
    {
      min_price = list[index].price;
      index_book = index;
    }
  }

  printf("Anna's cheapest book with relevance bigger than 9.5 and rating 5 has the following ID: %d\n", list[index_book].ID );



  return(0);
}
