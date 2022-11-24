#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

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
// int main(){
//     char message[] = "Hi! Let's go to the playground!";
//     const char* cipherText = stringToInt(message);
//     printf("\nCiphertext = %s\n\n", cipherText);

//     const char* plainText = intToString(cipherText);
//     printf("\nPlaintext = %s\n", plainText);
//     return 0; 
// }