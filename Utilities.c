#include <stdio.h> 
#include <string.h> 
#include <openssl/bn.h>

#define NBITS 1024

//Anastasia, Jonatham and Ruicheng
//CP460 Applied Cryptography Project

void printBN(char *msg, BIGNUM * a)
{
/* Use BN_bn2hex(a) for hex string
* Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

/*
Generate d values according to e*d mod phi = 1.
Paramters:
    r - result pointer 
    e - e value
    phi - used to help compute results
    ctx - BIGNUM temporary variables
*/

void generate_private_key(BIGNUM * r, BIGNUM * e, BIGNUM * phi, BN_CTX * ctx){
    // performing inverse mod to find d
    // r * e mod phi = 1 
    // return r (d)
    BN_mod_inverse(r, e, phi, ctx);
}

/*
Generate BIGNUM prime key.
Parameters: 
    r - pointer where result is stored 
    e - e value 
    ctx - BIGNUM temporary variables
*/
void generate_key(BIGNUM * r, BIGNUM * e, BN_CTX * ctx){
    BIGNUM * temp = BN_new();
    while (1){
        // generates a pseudo-random prime number of NBITS/2 length
        BN_generate_prime_ex(r, NBITS / 2, 1, NULL, NULL, NULL);
        // BN_div with first parameter set to NULL corresponds as mod function
        // perform r % e and store results in temp
        BN_div(NULL, temp, r, e, ctx);
        // check if r % e == 1 if yes (0) break while loop
        if (BN_is_one(temp) == 0){
            break;
        }
    }
}

/*
Calculate Euler Phi value.
phi = (p-1)(q-1)
Parameters: 
    r - result pointer
    p - BIGNUM prime 
    q - BIGNUM prime 
    e - e value 
    ctx - BIGNUM temporary variables
*/
void Euler_Phi(BIGNUM * r, BIGNUM * p, BIGNUM * q, BN_CTX * ctx){
    //(p-1)
    BN_sub_word(p,1);
    //(q-1)
    BN_sub_word(q,1);
    //(p-1)(q-1)
    BN_mul(r, p, q, ctx);
    //(p+1)
    BN_add_word(p,1);
    //(q+1)
    BN_add_word(q,1);
}

/*
Convert string to hexidecimal.
Parameters: 
    message - character string
Return: 
    hexStr - String of hexidecimal corresponding to message
*/
const char* stringToHex(char message[]){
    // initialize hexStr and allocate for length 1000 
    char* hexStr= (char*)malloc(sizeof(char)*1000); 
    int i, j = 0; 

    for (i = 0; i < strlen(message); i++){
        sprintf(hexStr + j, "%02X", message[i]);
        j += 2;
    }
    // indicate end of string
    hexStr[j] = '\0';

    return hexStr;
}


/*
Convert hexidecimal to ASCII integer.
Parameters: 
    c - char array of hexidecimal
Return: 
    result - ASCII integer 
*/
int hex_to_int(char c){
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first*10 + second;
    if(result > 9) result--;
    return result;
}

/*
Convert hexidecimal to ASCII character.
Parameters: 
    c - used to calculate high bound
    d - used to calculate low bound
Return: 
    result - high + low
*/
int hex_to_ascii(char c, char d){
    int high = hex_to_int(c) * 16;
    int low = hex_to_int(d);
    return high+low;
}


/*
Encryption. 
Parameters:
    hexPlaintext - hexidecimal of plaintext 
    cipherText - ptr for where ciphertext will be stored
    message - char array of ASCII character from user
    e - e value
    n - p * q
    ctx - BIGNUM temporary variables 
*/
void encrypt(BIGNUM *  hexPlaintext, BIGNUM * cipherText, char message[], BIGNUM * e, BIGNUM * n, BN_CTX * ctx){
    // converting to hexadecimal string to BN
    BN_hex2bn(&hexPlaintext, stringToHex(message));
    // perform encryption 
    // hexPlaintext ^ e mod n and store in cipherText 
    BN_mod_exp(cipherText, hexPlaintext, e, n, ctx);
}

/*
Decryption. 
Parameters:
    strHexPlaintext - hexidecimal in string form.
Returns:
    message - decrypted message from ciphertext.
*/
const char * decrypt(BIGNUM * plainText, BIGNUM * cipherText, BIGNUM * d, BIGNUM * n, BN_CTX * ctx){
    // perform cipherText ^ d mod n 
    // store in plainText (hexadecimal)
    BN_mod_exp(plainText, cipherText, d, n, ctx);
    printBN("\tPlaintext = ", plainText);
    // convert hexadecimal to string hexadecimal
    const char * strHexPlaintext = BN_bn2hex(plainText);
    int length = strlen(strHexPlaintext);
    int i;
    char buf = 0; 
    int counter = 0;
    // initializing message of size 100 chars
    char * message = (char*)malloc(sizeof(char)*100);
    for (i = 0; i < length; i++){
        if (i % 2 != 0){
            message[counter] = hex_to_ascii(buf, strHexPlaintext[i]);
            counter++;
        }
        else {
            buf = strHexPlaintext[i];
        }
    }
    message[counter] = '\0';
    return message;
}







