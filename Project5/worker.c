// Title        :Worker
// Description  :Example of fork() and exec() to find a largest prime number smaller than a number given as an argument.
// Author       :Jared Diehl
// Date         :20190509
// Version      :1.0
// Usage        :./worker number
// Notes        :CMPSCI2750 Project5 - 2 of 2

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define SHM_KEY 0x1971

int isNumeric(const char *str)
{
        if (*str == '-') str++; // check if negative
        while (*str != '\0') // until null terminator
        {
                if (*str < '0' || *str > '9') return 0; // check if non-digit and return isn't numeric
                str++;
        }
        return 1; // return is numeric
}

int isPrime(const int n)
{
	if (n <= 1) return 0;
	int i, flag = 0;
	for (i = 2; i <= n / 2; ++i)
		if (n % i == 0)
		{
			flag = 1;
			break;
		}
	if (flag == 0) return 1;
	return 0;
}

int getPreviousPrime(const int n)
{
	// loop through numbers descending from n checking if i is prime
	int i;
	for (i = n - 1; i > 1; --i)
		if (isPrime(i)) return i;
	return -1;
}

int main(const int argc, char* const argv[])
{
	// check arguments
	if (argc != 2)
	{
		printf("Usage: %s number\n", argv[0]);
		return EXIT_FAILURE;
	}
	
	int n; // set n
	
	// check if first argument is numeric then set to n otherwise output error and exit
	if (isNumeric(argv[1])) n = atoi(argv[1]);
	else
	{
		fprintf(stderr, "%s isn't a number!\n", argv[1]);
		return EXIT_FAILURE;
	}
	
	printf("[worker] number is %d\n", n);
	
	printf("[worker] getting shared memory\n");
        int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT); // get shared memory id
        if (shmid < 0)
        {
                perror("[worker] shmget\n");
                return EXIT_FAILURE;
        }

        int* shm = (int *) shmat(shmid, NULL, 0); // attach to shared memory
        if (shm == (int *) -1)
        {
                perror("[worker] shmat\n");
                return EXIT_FAILURE;
        }
	
	// check if shared memory integer is zero
	if (*shm == 0) printf("[worker] shared memory is zero\n");
	else
	{
		printf("[worker] shared memory is not zero\n");
		return EXIT_FAILURE;
	}
	
	printf("[worker] finding smaller prime\n");
	*shm = getPreviousPrime(n); // find largest prime smaller than n
	
	printf("[worker] waiting for shared memory to be zero\n");
	while (*shm != 0) // wait until shared memory integer is zero
		sleep(1);
	
	printf("[worker] shared memory reset back to zero\n");
	
	printf("[worker] terminating\n");
	
	// yay, we're done
        return EXIT_SUCCESS;
}
