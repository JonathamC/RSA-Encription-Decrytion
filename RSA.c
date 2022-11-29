#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#include "Utilities.c"


int main ()
{
    BN_CTX *ctx = BN_CTX_new();

    // User Input 
    char message[1000];
    printf("\nEnter message: ");
    fgets(message, 1000, stdin);


    
    
    // Key Generation
    BIGNUM *e = BN_new(); 
    BN_dec2bn(&e, "65537");
    printBN("\ne = ", e);

    // Generate p 
    BIGNUM *p = BN_new(); 
    generate_key(p, e, ctx);
    printBN("p = ", p); 
    

    // Generate q 
    BIGNUM *q = BN_new(); 
    generate_key(q, e, ctx);
    printBN("q = ", q); 
    

    // Generate n = pq
    BIGNUM *n = BN_new();
    BN_mul(n, p, q, ctx);
    printBN("n = ", n);

    // Generate Euler Phi function
    BIGNUM *phi = BN_new();
    Euler_Phi(phi, p, q, ctx);
    printBN("phi = ", phi);

    // Generate d => (e * d) mod phi == 1
    BIGNUM * d = BN_new(); 
    generate_private_key(d, e, phi, ctx);
    printBN("d = ", d);

    // Encryption step
    printf("\nEncrypting: \n");
    BIGNUM * hexPlaintext = BN_new();
    BIGNUM * cipherText = BN_new();
    encrypt(hexPlaintext, cipherText, message, e, n, ctx);
    printBN("\thexPlaintext = ", hexPlaintext);
    printBN("\tCiphertext = ", cipherText);


    // Decryption Step
    printf("\nDecrypting: \n");
    BIGNUM * plainText = BN_new(); 
    BN_mod_exp(plainText, cipherText, d, n, ctx);
    printBN("\tPlaintext = ", plainText);
    const char * strHexPlaintext = BN_bn2hex(plainText);
    const char * decryptedMessage = decrypt(strHexPlaintext);
    printf("\tDecrypted Message = %s\n\n", decryptedMessage);
    return 0;
}
// to compile
// gcc RSA.c -o RSA -I /usr/local/ssl/include -L /usr/local/ssl/lib -lssl -lcrypto -Wall 