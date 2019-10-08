// Program to find the largest element in an array of integers. If the array is
// empty( length = 0) return -1.
#include<stdio.h>

 int largest(int array[], int length)
{
  // Consider the case where the aray is empty
  if(length == 0)
    return -1;

  // Initialise the maximum number with the first element.
  int max = array[0];
  int maxIndex = 0;

  // Search for the maximum element
  for(int index = 1 ; index < length; index ++)
  {
    if(max < array[index])
    {
      max = array[index];
      maxIndex = index;
    }
  }

  return maxIndex;
}

int main()
{

  int largestIndex;

  // First test
  int array1 [] = {};
  largestIndex = largest(array1, 0);
  printf("The array is empty.\n");

  // Second test
  int array2 [] = {57};
  largestIndex = largest(array2, 1);
  printf("The largest element is %d.\n", array2[largestIndex]);

  // Third test
  int array3 [] = {0, -6, 36, 85, 7};
  largestIndex = largest(array3, 5);
  printf("The largest element is %d.\n", array3[largestIndex]);

  // Fourth test
  int array4 [] = {7230, -7643, 1789, 85, -973, 789, 3296};
  largestIndex = largest(array4, 7);
  printf("The largest element is %d.\n", array4[largestIndex]);

  return 0;

}
