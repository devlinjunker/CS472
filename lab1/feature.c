#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>

union Data
{
	char str[8];
	float d;
	long l;
};


void feature(union Data newData)
{
	int dummy;
	printf("double mantissa: %f\n", frexp(newData.d, &dummy));
	printf("double exponent: %d\n", dummy);
	dummy = newData.d < 0 ? -1 : 1; 
	printf("double sign: %d\n", dummy);
	printf("long value: %ld\n", newData.l);
	dummy = newData.l < 0 ? -1 : 1;
	printf("long sign: %d\n", dummy);
	printf("char array: \n");
	int i = 0;
	for(i = 0; i < 8; i++)
	{
		printf("%c\n", newData.str[i]);
	}
}

int main()
{

	union Data user_data;
	user_data.l = 0x449A4400;
	feature(user_data);
}
