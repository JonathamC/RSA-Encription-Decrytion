#include <stdio.h> 
#include <math.h>


int keyGenerator(){
    return 0; 
}

int EulerFunc(){
    return 0; 
}


int encryption(int message, int n, int e){
    int y = pow(message, e);
    return y % n;
}

int decryption(int d, int y, int n){
    float x = pow(31,7);
    printf("\n%f", x);
    return 27512614911 % n;
}
int main(){
    // char userInput[50]; 
    // printf("Enter your message: "); 
    // gets(userInput);

    // printf("Hello %s", userInput);

    int p = 3, q = 11;
    int n = p * q; 
    int euler = (p-1)*(q-1);
    int e = 3; 
    int d = 7; 

    int message = 4; 
    int y = encryption(message, n, e); 
    printf("Encription: %d", y);
    int x = decryption(d,y,n);
    printf("\nDecription: %d", x);
    return 0;
}