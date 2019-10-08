#include<stdio.h>

unsigned long dl(unsigned long y,unsigned long g,unsigned long p)
{
    unsigned long power = 1;
    unsigned long x;
    // check foe each x if y = g^x mod p
    for(x = 1; x < p; x++)
    {
        power =(power *g) %p;

        if(power == y)
            return x;

    }
    // Not found
    return -1;
}

int main()
{
    // Testing
    printf("The x we are looking for is %lu\n",  dl(145, 13, 197));
    printf("The x we are looking for is %lu\n", dl(6,7,11));


    return 0;

}
