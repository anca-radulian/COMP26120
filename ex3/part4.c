// Program to convert temperatures between Celsius and Farenheit. It uses
// program parameters to know to which scale to convert.
#include<stdio.h>
#include<string.h>

float c2f(float c)
{
  return (9*c)/ 5 + 32;
}

float f2c(float f)
{
  return 5*(f - 32)/9;
}

int main(int argc, char *argv[])
{

  float temperature;

  //Check if the number of arguments is correct.
  if(argc != 3)
  {
    printf("Please supply exactly two parameters.\n");
    return 0;
  }
  // Check if the right flag s provided.
  if(strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-f"))
  {
    printf("Please provide the right flag.\n");
    return 0;
  }

  // Save the temperature as a float.
  sscanf(argv[2], "%f", &temperature);

  // Check if the temperature is below zero absolute.
  if((strcmp(argv[1], "-f") == 0 && temperature < -459.67)
      || (strcmp(argv[1], "-c") == 0 && temperature < -273.15))
  {
    printf("Cannot declare a temperature below zero absolute.\n");
    return 0;
  }

  // Convert to celsius if the temperature is given in Farenheit.
  if(strcmp(argv[1], "-f") == 0)
  {
    float c_temp = f2c(temperature);
    printf("%.2f\n", c_temp);
  }
  // Convert to Farenheit if the temperature is given in Celsius.
  if(strcmp(argv[1], "-c") == 0)
  {
    float f_temp = c2f(temperature);
    printf("%.2f\n", f_temp);
  }
  return 0;

}
