#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#define NBITS 1024
void printBN(char *msg, BIGNUM * a)
{
/* Use BN_bn2hex(a) for hex string
* Use BN_bn2dec(a) for decimal string */
    char * number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

const char* stringToHex(char message[]){
    char* hexStr= (int*)malloc(sizeof(int)*100); 
    int i, j = 0; 

    for (i = 0; i < strlen(message); i++){
        sprintf(hexStr + j, "%02X", message[i]);
        j += 2;
    }
    hexStr[j] = '\0';

    return hexStr;
}

int hex_to_int(char c){
    int first = c / 16 - 3;
    int second = c % 16;
    int result = first*10 + second;
    if(result > 9) result--;
    return result;
}

int hex_to_ascii(char c, char d){
    int high = hex_to_int(c) * 16;
    int low = hex_to_int(d);
    return high+low;
}

int main ()
{
    // Printing message
    char message[100];
    printf("\nEnter message: ");
    fgets(message, 100, stdin);


    BN_CTX *ctx = BN_CTX_new();
    
    // Key Generation
    BIGNUM *e = BN_new(); 
    BN_dec2bn(&e, "65537");
    printBN("\ne = ", e);

    // Generate p 
    BIGNUM *p = BN_new(); 
    BIGNUM * temp = BN_new();
    while (1){
        BN_generate_prime_ex(p, NBITS / 2, 1, NULL, NULL, NULL);
        BN_div(NULL, temp, p, e, ctx);
        if (BN_is_one(temp) == 0){
            break;
        }
    }
    // nChecks is usually 64, 128 rounds for >= 1024 bits
    //printf("Is p prime? %d\t", BN_is_prime(p, 64, NULL, ctx, NULL));
    printBN("p = ", p); 
    

    // Generate q 
    BIGNUM *q = BN_new(); 
    while (1){
        BN_generate_prime_ex(q, NBITS / 2, 1, NULL, NULL, NULL);
        BN_div(NULL, temp, q, e, ctx);
        if (BN_is_one(temp) == 0){
            break;
        }
    }
    //printf("Is q prime? %d\t", BN_is_prime(q, 64, NULL, ctx, NULL));
    printBN("q = ", q); 
    

    // Generate n = pq
    BIGNUM *n = BN_new();
    BN_mul(n, p, q, ctx);
    printBN("n = ", n);

    // Generate Euler Phi function
    BIGNUM *phi = BN_new();
    //(p-1)
    BN_sub_word(p,1);
    //(q-1)
    BN_sub_word(q,1);
    //(p-1)(q-1)
    BN_mul(phi, p, q, ctx);
    BN_add_word(p,1);
    BN_add_word(q,1);
    printBN("phi = ", phi);

    // Generate d => (e * d) mod phi == 1
    BIGNUM * res = BN_new();
    BIGNUM * d = BN_new(); 
    BN_mod_inverse(d, e, phi, ctx);
    printBN("d = ", d);

    
    BN_mod_mul(res, e, d, phi, ctx);
    printf("(e * d) mod phi = %d --> ", BN_is_one(res));
    printBN("result: ", res);





    // Encryption step
    printf("\nEncrypting: \n");
    printf("\tHexadecimal string = %s\n", stringToHex(message));
    BIGNUM * hexPlaintext = BN_new();
    BN_hex2bn(&hexPlaintext, stringToHex(message));
    printBN("\tBIGNUM hexPlaintext = ", hexPlaintext);
    
    BIGNUM * cipherText = BN_new();
    BN_mod_exp(cipherText, hexPlaintext, e, n, ctx);
    printBN("\tCiphertext = ", cipherText);


    // Decryption Step
    printf("\nDecrypting: \n");
    BIGNUM * plainText = BN_new(); 
    BN_mod_exp(plainText, cipherText, d, n, ctx);
    printBN("\tPlaintext = ", plainText);
    const char * strHexPlaintext = BN_bn2hex(plainText);
    printf("\tstring representation of hexPlaintext = %s\n", strHexPlaintext);
    int length = strlen(strHexPlaintext);
    int i;
    char buf = 0; 
    char decryptedMessage[100];
    int counter = 0;
    for (i = 0; i < length; i++){
        if (i % 2 != 0){
            decryptedMessage[counter] = hex_to_ascii(buf, strHexPlaintext[i]);
            counter++;
        }
        else {
            buf = strHexPlaintext[i];
        }
    }
    decryptedMessage[counter] = '\0';
    printf("\tMessage = %s\n\n", decryptedMessage);
    return 0;
}
// to compile
// gcc RSA.c -o RSA -I /usr/local/ssl/include -L /usr/local/ssl/lib -lssl -lcrypto -Wall 