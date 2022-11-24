#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <time.h>

const char* stringToInt(char message[]){
    int lenMessage = strlen(message) * 3; 
    char* cipherText= (int*)malloc(sizeof(int)*lenMessage); 

    int counter = 0;
    for (int i = 0 ; i < strlen(message); i ++){
        char temp[4] = {'\0'}; 
        sprintf(temp, "%03d", (int)message[i]);
        printf("%c %d\t%s\n", message[i], (int)message[i], temp);
        for (int i = 0; i < strlen(temp); i++){
            cipherText[counter] = temp[i];
            counter++;
        }
    }
    cipherText[counter] = '\0';
    return cipherText;
}

char* substring(char *destination, const char *source, int beg, int n)
{
    while (n > 0)
    {
        *destination = *(source + beg);
 
        destination++;
        source++;
        n--;
    }
    *destination = '\0';
    return destination;
}

 const char* intToString(char cipherText[]){
    int lenCipher = strlen(cipherText) / 3;
    char* plainText= (int*)malloc(sizeof(int)*lenCipher);
    int counter = 0; 

    for (int i = 0 ; i < strlen(cipherText) ; i = i+3){
        char temp[4] = {'\0'};
        substring(temp, cipherText, i, 3);
        printf("%s\t", temp);
        int x = atoi(temp);
        printf("%c\n",(char)x);
        plainText[counter] = (char)x;
        counter++;
    }
    plainText[counter] = '\0';
    return plainText;

 }


int coprime(int num1, int num2)  
{  
    int min, count, found = 1;  
    min = num1 < num2 ? num1 : num2;  
    for(count = 2; count <= min; count++)  
    {  
        if( num1 % count == 0 && num2 % count == 0 ) 
        {  
            found = 0;  
            break;  
        }  
    }  
    return(found);  
}

int check_prime(int a)
{
   int c;
 
   for ( c = 2 ; c <= a - 1 ; c++ )
   { 
      if ( a%c == 0 )
     return 0;
   }
   return 1; // is prime
}

int RNG_prime(){
    int i, n;
    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    /* random numbers from 0 to 1000 */
    int randomInt = rand() % 1000;
    if (check_prime(randomInt) == 1){
        return randomInt;
    }
    else { 
        while(1){
            randomInt = rand() % 1000;
            if (check_prime(randomInt) == 1){
                return randomInt;
            }
        }
    }
}
int main(){
    // char message[] = "Hi! Let's go to the playground!";
    // const char* cipherText = stringToInt(message);
    // printf("\nCiphertext = %s\n\n", cipherText);

    // const char* plainText = intToString(cipherText);
    // printf("\nPlaintext = %s\n", plainText);
    int p = RNG_prime();
    printf("%d\n", p);
    return 0; 
}