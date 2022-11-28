#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <openssl/bn.h>

#define NBITS 256

int coprime(const BIGNUM *num1, const BIGNUM *num2, BN_CTX *ctx);
int* generate_key(int n,int phi);
char encrypt(int plain, int n, int e);
char decrypt(int cipher,int n, int d);
const char* intToString(char cipherText[]);
char* substring(char *destination, const char *source, int beg, int n);
const char* stringToInt(char message[]);
int generate_eValue(BIGNUM *phi, BIGNUM * n);
//Anastasia, Jonatham and Ruicheng
//CP460 Applied Cryptography Project

//Module used for utility functions for RSA 
//Classes can be used to form attributes such as:
//Sender info, reciever info, sender/reciever public and private key



/* 
Parameters:
    num1 - integer
    num2 - integer
Returns: 
    found - returns 1 if they are coprime and 0 otherwise*/
int coprime(const BIGNUM *num1, const BIGNUM *num2, BN_CTX *ctx)  
{  

    BIGNUM *r= BN_new(); 
    int gcd = BN_gcd(r, num1, num2, ctx);
    if (BN_is_one(r) == 1){
        return 1;
    }
    
    return 0;
}


/*
Generates e and d values according to e*d mod phi = 1
Paramters:
    phi - used to help compute results
    n - p*q
Returns:
    arr - array of size 2 [e,d]
*/
int* generate_key(int n,int phi){
    //e must be less than phi
    //e must be coprime of n and phi
    int* arr = (int*)malloc(sizeof(int)*2);
    // for (int i=2;i<phi;i++){
    //     if (coprime(i,n) && coprime(i,phi)){
    //         arr[0]=i;
    //         break;
    //     }
    // }

    int i=1;
    for (;;){
        int value=i*arr[0];
        if (value%phi==1){
            arr[1]=i;
            break;
        }
        i++;
    }
    return arr;
}


/*
Parameters:
    plain - string as plain text
Returns:
    output - string as cipher text
*/
char encrypt(int plain, int n, int e){
    // double y=pow(plain,e);
    // long w=y;
    // return w%n;
    return 'c';
}

/*
Parameters:
    cipher - string as cipher text
Returns:
    output - string as plain text
*/
char decrypt(int cipher,int n, int d){
    //double x=pow(cipher, d);
    return 'c';
}


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

void printBN(char *msg, BIGNUM * a)
{
/* Use BN_bn2hex(a) for hex string
* Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int generate_eValue(BIGNUM *phi, BIGNUM * n){
    

    return 0;
}


int main(){
    // char message[] = "A top secret!";
    // const char* cipherText = stringToInt(message);
    // printf("\nCiphertext = %s\n\n", cipherText);

    // const char* plainText = intToString(cipherText);
    // printf("\nPlaintext = %s\n", plainText);

    BN_CTX *ctx = BN_CTX_new();
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *res = BN_new();


    // Initialize a, b, n
    BN_generate_prime_ex(p, NBITS, 1, NULL, NULL, NULL);
    BN_generate_prime_ex(q, NBITS, 1, NULL, NULL, NULL);
    // n = p * q
    BN_mul(n, p, q, ctx);

    // Calculating Phi 
    BIGNUM *phi = BN_new();
    //(p-1)
    BN_sub_word(p,1);
    //(q-1)
    BN_sub_word(q,1);
    //(p-1)(q-1)
    BN_mul(phi, p, q, ctx);
    BN_add_word(p,1);
    BN_add_word(q,1);

    printBN("p = ", p);
    printBN("q = ", q);
    printBN("n = ", n);
    printBN("phi = ", phi);
    // res = aˆb mod n
    // BN_mod_exp(res, a, b, n, ctx);

    // int eValues[] = {"65537", "257", "17", "5", "3"};
    BIGNUM *e = BN_new(); 
    BN_dec2bn(&e, "65537");
    printBN("\ndec2bn of e = ", e);

    BIGNUM * d = BN_new(); 
    BN_mod_inverse(d, e, phi, ctx);
    printBN("d = ", d);

    BN_mod_exp(res, e, d, phi, ctx);
    printBN("result: ", res);
    printf("%d", BN_is_one(res));
}

// to compile
// gcc ASCII_to_Hex.c -o ASCII_to_Hex -I /usr/local/ssl/include -L /usr/local/ssl/lib -lssl -lcrypto -Wall

// res = aˆb mod n
// BN_mod_exp(res, a, b, n, ctx);