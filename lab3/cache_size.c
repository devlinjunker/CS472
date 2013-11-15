#include <stdio.h>
#include <time.h>

#define SIZE (1<<17)
#define NPAD 15

struct l {
	struct l *n;
	long int pad[NPAD];
};

struct l big_array[SIZE];

int main()
{
	printf("%d\n", sizeof(struct l));
	int meow = 0;
	for(meow = 0; meow < SIZE; meow++)
	{
		if (meow == SIZE - 1)
		{
			big_array[meow].n = &big_array[0];
		}
		else
		{
			big_array[meow].n = &big_array[meow+1];
		}
	}

	struct l current = big_array[0];
	clock_t t; 
	
	struct l new;
	int j = 0;
	t = clock();
	for (j = 0; j < (1<<24); j++)
	{
		new  = *current.n;
		current = new;
	}
	
	t = clock() - t; 
	printf("time: %d\n", t);
	printf("time in seconds: %f\n", (float)t/CLOCKS_PER_SEC);

}
