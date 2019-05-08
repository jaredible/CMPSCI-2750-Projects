// Title	:Master
// Description	:Example of fork() and exec() to find a largest prime number smaller than a number given as an argument.
// Author	:Jared Diehl
// Date		:20190509
// Version	:1.0
// Usage	:./master [-n number]
// Notes	:CMPSCI2750 Project5 - 1 of 2

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>
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

int main(const int argc, char* const argv[])
{
	//system("clear");
	
	int n = 100; // initialize integer n with default value of 100
	
	// check arguments
	int opt;
	while ((opt = getopt(argc, argv, "hn:")) != -1)
		switch (opt)
		{
			case 'h':
				printf("Usage: %s [-n number]\n", argv[0]);
				return EXIT_SUCCESS;
			case 'n':
				// if argument is numeric then set to n otherwiae output error and exit
				if (isNumeric(optarg))
				{
					n = atoi(optarg);
				}
				else
				{
					fprintf(stderr, "%s isn't a number!\n", optarg);
					return EXIT_FAILURE;
				}
				break;
			default:
				// these arguments aren't known so output error and exit
				fprintf(stderr, "I don't know what to do with this argument!\n");
				return EXIT_FAILURE;
		}
	
	if (optind != argc)
	{
		fprintf(stderr, "Found an unknown argument!\n");
		return EXIT_FAILURE;
	}
	
	printf("[master] number is %d\n", n);
	
	printf("[master] getting shared memory\n");
	int shmid = shmget(SHM_KEY, sizeof(int), 0666 | IPC_CREAT); // get shared memory id
	if (shmid < 0) // check if shared memory get error
	{
		perror("[master] shmget\n");
		return EXIT_FAILURE;
	}
	
	int *shm = (int *) shmat(shmid, NULL, 0); // attach to shared memory
	if (shm == (int *) -1) // check if shared memory attachment error
	{
		perror("[master] shmat\n");
		return EXIT_FAILURE;
	}
	
	*shm = 0; // set shared memory integer to zero
	printf("[master] shared memory set to zero\n");
	
	printf("[master] forking...\n");
	int pid = fork(); // duplicate process
	if (pid < 0) // check if fork error
	{
		perror("[master] fork\n");
		return EXIT_FAILURE;
	}
	else if (pid == 0) // check if is child
	{
		// CHILD
		
		printf("[master] child is executing worker\n");
		
		// convert integer to string
		char number[256];
		sprintf(number, "%d", n);
		
		execl("./worker", "./worker", number, NULL); // execute worker with parameter from -n argument
	}
	
	// PARENT
	
	// wait until shared memory memory is not zero
	printf("[master] parent is waiting for shared memory not to be zero\n");
	while (*shm == 0)
		sleep(1);
	
	if (*shm < 2) // check if shared memory isn't a possible prime
	{
		printf("[master] no smaller prime found\n");
		
		// kill child because it's waiting on parent which won't change shared memory for it to terminate
		kill(pid, SIGTERM);
		sleep(1);
		int status;
		waitpid(pid, &status, WNOHANG);
		if (status)
		{
			kill(pid, SIGKILL);
			waitpid(pid, &status, 0);
		}
		
		// stop everything
		return EXIT_FAILURE;
	}
	
	printf("[master] lowest prime smaller than %d is %d\n", n, *shm); // we found a prime!
	
	*shm = 0; // reset shared memory integer to zero
	printf("[master] shared memory set to zero\n");
	
	printf("[master] waiting for child to terminate\n");
	wait(NULL); // wait until child terminates
	printf("[master] child terminated\n");
	
	shmdt(shm); // reattach to shared memory just in case
	shmctl(shmid, IPC_RMID, NULL); // remove shared memory integer
	printf("[master] shared memory freed\n");
	
	printf("[master] terminating\n");
	
	// all right, we're done now
	return EXIT_SUCCESS;
}
