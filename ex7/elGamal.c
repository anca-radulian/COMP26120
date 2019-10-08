#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

unsigned long hcf(unsigned long a,unsigned long b)
{
    unsigned long r = 0;
    // Euclide algorithm
    while(b!=0)
    {
        r = a%b;
        a = b;
        b = r;

    }

    return a;
}
/* From the math course from last year.
        power = g^x mod p
   Complexity for this is O(log x) beacuse we are dividing each time by 2.

 */
unsigned long long fme(unsigned long long g,unsigned long long x,unsigned long long p)
{
    if(x==0)
        return 1;
    else
    {
        unsigned long long power = 1;
        while(x!=0)
        {
            if(x%2 == 1)
                power = (power* g) %p;
            g = (g*g) % p;
            x = x/2;
        }

        return power;
    }
}

unsigned long dl(unsigned long y,unsigned long g,unsigned long p)
{
    unsigned long power = 1;
    unsigned long x;
    for(x = 1; x < p; x++)
    {
        power =(power *g) %p;

        if(power == y)
            return x;

    }
    // Not found
    return -1;
}

unsigned long imp(unsigned long y, unsigned long p)
{
    // Using Euler Theorem: y^fi(p) ≡ 1 mod p
    // y * y^fi(p)-1 = 1 mod p => modular inverse of y is y^fi(p)-1 mod p, where fi(p) = p-1 because p is prime
    return fme(y,p-2,p);

}

int main(int argc, char **argv)
{
    //-- First part: highest common divisor----------------
    unsigned long long result1 = hcf(14, 28);
    printf("Hcf for 28 and 14 is %llu\n", result1);

    unsigned long long result2 = hcf(27, 14);
    printf("Hcf for 27 and 14 is %llu\n", result2);

    unsigned long long result3 = hcf(106, 32);
    printf("Hcf for 106 and 32 is %llu\n", result3);


    //-- Second part: fast modular exponentiation---------
    printf("-----------------------------\n");

    result1 = fme(13, 5, 197);
    printf("Fme for 13^5 mod 197 is %llu\n", result1);

    result2 = fme(7, 7, 11);
    printf("Fme for 7^7 mod 11 is %llu\n", result2);


    //-- Fourth part: inverse modulo ------------------
    printf("-----------------------------\n");
    result1 = imp(5,7);
    printf("The inverse modulo for 5 mod 7 is %lu\n", result1);

    result2 = imp(3,23);
    printf("The inverse modulo for 3 mod 23 is %lu\n", result2);

    printf("-----------------------------\n");

    //----- EL GAMAL ------
    int run = 1;
    char* option = " ";
    unsigned long long private_key,result, message,k,a,b,public_key;
    srand(time(0));
    while(run)
    {
        option = ' ';
        if(option!= '\n')
            printf("\nPrime modulus is 65537\nPrimitive root wrt 65537 is 3\nChoose: e (encrypt) | d (decrypt) | k (get public key)  | x(exit)?");
        scanf("%s",&option);

        if(option == 'k')
        {
            // Get input
            printf("\nType private key:");
            scanf("%llu", &private_key);

            // Use fast modular exponentiation to find out y.
            result = fme(3, private_key, 65537);
            printf("Public key is: %llu\n", result);
        }
        else if(option == 'e')
        {
            // Get input
            printf("\nType secret number to send:");
            scanf("%llu", &message);
            printf("\nType recipient's public key:");
            scanf("%llu", &public_key);

            // Get a random k
            k = rand() % 65537;

            // Calculate the two elements of the pair
            a = fme(3,k,65537);
            b = message * fme(public_key,k, 65537) % 65537;

            printf("\nThe encrypted secret is: (%llu,%llu)\n", a,b);
        }
        else if(option == 'd')
        {


            printf("\nType in received message in form (a,b): ");
            scanf("%llu %llu", &a, &b);

            printf("\nType in your private key: ");
            scanf("%llu", &private_key);

            // Calculate the k used
            k = dl(a,3,65537);

            // calculate b = M* y^k mod p;
            message = b* imp(fme(fme(3,private_key,65537),k,65537), 65537) % 65537;

            printf("\nThe decrypted secret is: %llu\n", message);

        }
        else if(option == 'x')
        {
            run = 0;
            printf("You exit El Gamal.\n");
        }

    }


    return 0;
}
