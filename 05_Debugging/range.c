#include <stdio.h>
#include <stdlib.h>


void rangeFunc (long M, long N, long S)
{
	long i;
	for (i = M; i < N; i += S)
	{
		printf("%ld\n", i);
	}
	return;
}


int main(int argc, char* argv[])
{
	long int N, M = 0, S = 1;
	if (argc == 1)
	{
		printf("./range           display this help and exit\n");
		printf("./range N         print numbers [0, 1, ..., N - 1] in column\n");
		printf("./range M N       print numbers [M, M + 1, ..., N - 1] in column\n");
		printf("./range M N S     print numbers [M, M + S, M  + 2S, ..., N - 1] in column\n");	
		return 0;			
	}
	if (argc == 2)
	{
		N = atoi(argv[1]);
	}
	if (argc >= 3)
	{
		N = atoi(argv[2]);
		M = atoi(argv[1]);
		if (argc == 4)
		{
			S = atoi(argv[3]);
		}
	}
	rangeFunc(M, N, S);
	return 0; 
}