#include <stdio.h>
#include <stdlib.h>

#define BYTE_ARR(a) ((unsigned char*)&a)

#define F64_EXP_BIAS 1023

#define F64_GET_EXP(fp) ((int)( (((long)(BYTE_ARR(fp)[7]) & 0x7F) << 4 ) | (((long)(BYTE_ARR(fp)[6]) & 0xF0) >> 4) ) - F64_EXP_BIAS)

#define F64_MANT_SHIFT 12
#define F64_GET_MANT_HIGH(fp) (long)( (((long)(BYTE_ARR(fp)[6]) & 0x0F) << 16 | (long)(BYTE_ARR(fp)[5]) << 8 | (long)(BYTE_ARR(fp)[4])) << F64_MANT_SHIFT)
#define F64_GET_MANT_LOW(fp) (long)((long)(BYTE_ARR(fp)[3]) << 24 | (long)(BYTE_ARR(fp)[2]) << 16 | (long)(BYTE_ARR(fp)[1]) << 8 | (long)BYTE_ARR(fp)[0])

double frexp(double x, int *exp)
{
	unsigned long mant_word;

	double ret = 1; // represents the hidden bit

	*exp = F64_GET_EXP(x) ;
	mant_word = F64_GET_MANT_HIGH(x);



	// Check if exponent is all 1s (nan, inf, -inf)
	if( ((*exp+F64_EXP_BIAS) ^ ((unsigned long)0)) == 0x7FF){
    		ret = x;
		goto end;
	}else if(((*exp + F64_EXP_BIAS) & 0xFFFFFFFF) == 0){
		ret = 0;
	}

	// Check if mantissa(first high then low bytes) is 0
//    	if( (mant_word | (unsigned long)0) == 0 && (F64_GET_MANT_LOW(x) | (unsigned long)0) == 0){
//		ret = 0;
//		*exp = 0;
//		goto end;
//    	}

	// Converting the mantissa to a double

	int new_val = 0; // holds the most significant bit
	double pow2 = 0.5; // starting power of 2

	int second_byte = 0;

	// while there are still 1s in the mantissa
	while(mant_word != 0){

		// grab most sig bit
        	new_val = ((mant_word & (((unsigned long)1)<<31)) >> 31); 

        	// multiply by power of 2 for that bit in the function
        	ret += new_val * pow2;

		// shift out most significant bit
		mant_word <<= 1;
		// next power of 2 lower
		pow2 = pow2/2;
	
		// check the second byte toooo..!!
		if(mant_word == 0 && second_byte == 0){
			second_byte = 1;
			mant_word = F64_GET_MANT_LOW(x);
		}
	}

	// normalized fractions are between 0.5 (inclusive) and 1 (exclusive)
    	while((int)ret >= 1 || ret < 0.5){
		if((int)ret >= 1){
			ret = ret / 2; 
			*exp = *exp + 1;
		}else if(ret < 0.5){
			ret = ret * 2;
			*exp = *exp - 1;
		}

	}
	
end:
	return ret;
}

int main(int argc, char *argv[])
{
	int exp;
	double x;
	double r;

	unsigned char *test;
	unsigned char fraction[7];

	if(argc < 2){
		printf("You must enter a number to frexp() \n");
	}else{
		x = strtod(argv[1], NULL);
		r = frexp(x, &exp);
		printf("value of %g, returns normalized fraction = %g and exponent = %d \n", x, r, exp);
        
	       	// denormalized values
		r = frexp(4.0/0.0, &exp);
		printf("value of %g, returns normalized fraction = %g and exponent = %d \n", 4.0/0.0, r, exp);
        
		r = frexp(-4.0/0.0, &exp);
		printf("value of %g, returns normalized fraction = %g and exponent = %d \n", -4.0/0.0, r, exp);

		r = frexp(0.0/0.0, &exp);
		printf("value of %g, returns normalized fraction = %g and exponent = %d \n", 0.0/0.0, r, exp);

		printf("test %u \n", F64_GET_MANT_HIGH(x) && ((unsigned long) 1 << 31));
		printf("byte7: %u \n", ( BYTE_ARR(x)[7] & 0x7F));
		printf("byte6: %u \n", ( BYTE_ARR(x)[6] & 0xFF));
		printf("byte5: %u \n", ( BYTE_ARR(x)[5] & 0xFF));
		printf("byte4: %u \n", ( BYTE_ARR(x)[4] & 0xFF));
		printf("byte3: %u \n", ( BYTE_ARR(x)[3] & 0xFF));
		printf("byte2: %u \n", ( BYTE_ARR(x)[2] & 0xFF));
		printf("byte1: %u \n", ( BYTE_ARR(x)[1] & 0xFF));
		printf("byte0: %u \n", ( BYTE_ARR(x)[0] & 0xFF));
	}   

	return 0;
}
