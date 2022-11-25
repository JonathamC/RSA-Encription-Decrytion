    char message[] = "Hi! Let's go to the playground!";
    const char* cipherText = stringToInt(message);
    printf("\nCiphertext = %s\n\n", cipherText);

    const char* plainText = intToString(cipherText);
    printf("\nPlaintext = %s\n", plainText);