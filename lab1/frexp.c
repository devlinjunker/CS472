#include <stdio.h>
#include <stdlib.h>

#define BYTE_ARR(a) ((unsigned char*)&a)

#define F64_EXP_BIAS 1023

#define F64_EXP_SHIFT 12 
#define F64_GET_EXP_HI(fp) (int)((BYTE_ARR(fp)[7] & 0x7F) << 4 )
#define F64_GET_EXP_LOW(fp) (int)((BYTE_ARR(fp)[6] & 0xF0) >> 4)
#define F64_GET_EXP(fp) ((int)( F64_GET_EXP_HI(fp) | F64_GET_EXP_LOW(fp) ) - F64_EXP_BIAS)

#define F64_MANT_MASK 0x000FFFFFFFFFFFFF
#define F64_MANT_SHIFT 12
#define F64_GET_MANT(fp) *(long*)&fp & F64_MANT_MASK

#define F64_GET_MANT_HI(fp) ( (long)(((int)BYTE_ARR(x)[6] & 0x0F) << 8 | ((int)BYTE_ARR(x)[5] & 0xFF)) << 40 )
#define F64_GET_MANT_MED(fp) ( ((int)BYTE_ARR(x)[4] & 0xFF) << 32 | ((int)BYTE_ARR(x)[3] & 0xFF) << 24  )
#define F64_GET_MANT_LOW(fp) ( ((int)BYTE_ARR(x)[2] & 0xFF) << 16 | ((int)BYTE_ARR(x)[1] & 0xFF)  )

double frexp(double x, int *exp)
{
    unsigned long stored_mant;
    unsigned long temp;

    double ret = 1;

    *exp = F64_GET_EXP(x) ;
    stored_mant = F64_GET_MANT(x);
    
    // Check if exponent is all 1s
    if( (*exp+F64_EXP_BIAS) & (((unsigned long)0)-1) == (((unsigned long)0)-1)){
        ret = x;
        goto end;
    }

    // Move bits all the way to the right to cover hole left by sign and exponent
    temp = stored_mant << 12;

    // Check if mantissa is 0
    if(temp | (unsigned long)0 == 0){
        ret = 0;
        *exp = 0;
        goto end;
    }

    int new_val = 0; // holds the most significant bit
    double pow2 = 0.5; // starting power of 2

    // while there are still 1s in the mantissa
    while(temp != 0){

        // grab most sig bit
        new_val = ((temp & (((unsigned long)1)<<63)) >> 63); 

        // multiply by power of 2 for that bit in the function
        ret += new_val * pow2;

        // shift out most significant bit
        temp <<= 1;
        // next power of 2 lower
        pow2 = pow2/2;
    }

    // normalized fractions are between 0.5 and 1
    while(ret > 1 || ret < 0.5){
        if(ret > 1){
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
    }   

    return 0;
}
