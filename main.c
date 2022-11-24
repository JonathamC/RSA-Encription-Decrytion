#include <stdio.h> 
#include <math.h>


int keyGenerator(){
    return 0; 
}

int EulerFunc(){
    return 0; 
}


int encryption(int message, int n, int e){
    double y = pow(message, e);
    long w = y;
    return w % n;
}

int decryption(int d, int y, int n){
    double x = pow(y,d);
    long v = x;

    return v % n;
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
    printf("\nDecription: %d\n", x);
    return 0;
}