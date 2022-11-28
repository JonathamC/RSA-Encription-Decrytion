CC = gcc
CFLAGS = -Werror -Wall -g -std=gnu99
LDFLAGS = -lrt -lssl -lcrypto
TARGET = RSA 
OBJFILES = RSA.o 
all: $(TARGET)
RSA: RSA.c
	$(CC) $(CFLAGS) -o RSA RSA.c $(LDFLAGS)

runRSA: RSA
	./RSA
clean:
	rm -rf $(OBJFILES) $(TARGET) *~ 
	rm -rf *.exe
	rm -rf *.out