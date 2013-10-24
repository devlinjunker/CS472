#include <stdio.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define SWAP(X) (X>>8)|(X<<8)
#else
#define SWAP(X) X
#endif

int is_little_endian()
{
	short s= 1;
	char * p = (char*)&s;
	return p[0];
}

short swap(short num)
{
	if(is_little_endian())
	{
		num = (num >>8)|(num << 8);
	}
	return num;
}


int main(int argc, char **argv)
{
	short val, result, runtime;
	char *p_val;
	p_val = (char *) &val;
	/*
	  The following two lines assume big-endian
	  Architecture to initialize the variable Val
	  to 0x1234.
	*/
	p_val[0] = 0x12;
	p_val[1] = 0x34;
	result = SWAP(val);
	runtime = swap(val);
	printf("pre-processor: %x\n", result);
	printf("runtime: %x\n", runtime);
	return 0;
}
