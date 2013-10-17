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
//#define F64_GET_MANT(fp) (long) ( F64_GET_MANT_HI(fp) | F64_GET_MANT_MED(fp) | F64_GET_MANT_LOW(fp) )
#define F64_GET_MANT(fp) *(long*)&fp & F64_MANT_MASK

#define F64_GET_MANT_HI(fp) ( (long)(((int)BYTE_ARR(x)[6] & 0x0F) << 8 | ((int)BYTE_ARR(x)[5] & 0xFF)) << 40 )
#define F64_GET_MANT_MED(fp) ( ((int)BYTE_ARR(x)[4] & 0xFF) << 32 | ((int)BYTE_ARR(x)[3] & 0xFF) << 24  )
#define F64_GET_MANT_LOW(fp) ( ((int)BYTE_ARR(x)[2] & 0xFF) << 16 | ((int)BYTE_ARR(x)[1] & 0xFF)  )

double frexp(double x, int *exp)
{
    unsigned long stored_mant;
    unsigned long temp;

    double ret = 1;

    // Check if x is equal to zero
    if(x - 0 < 0.0000001 & x - 0 > -0.0000001){
        exp = 0;
        ret = 0;
    }else{
        *exp = F64_GET_EXP(x) ;
        stored_mant = F64_GET_MANT(x);
        
        // TODO: Check for denormalized numbers;

        temp = stored_mant << 12;

        int new_val = 0;
        double pow2 = 0.5;

        while(temp != 0){

            new_val = ((temp & (((unsigned long)1)<<63)) >> 63); 

            ret += new_val * pow2;

            temp <<= 1;
            pow2 = pow2/2;;
        }

        printf("%f \n", ret);
        printf("%d \n", *exp);

        while(ret > 1 || ret < 0.5){
            if(ret > 1){
                ret = ret / 2; 
                *exp = *exp + 1;
            }else if(ret < 0.5){
                ret = ret * 2;
                *exp = *exp - 1;
            }

        }
    }

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

        //r = frexp(0.0/0.0, &exp);
        //printf("value of %g, returns normalized fraction = %g and exponent = %d \n", 0.0/0.0, r, exp);

        //r = frexp(8.9/0.0, &exp);
        //printf("value of %g, returns normalized fraction = %g and exponent = %d \n", 8.9/0.0, r, exp);


        printf("exponent: %d \n", F64_GET_EXP(x));
        printf("mantissa: %lx \n", F64_GET_MANT(x));

        long a = F64_GET_MANT(x) << 12;

        long val = a << 1;

        printf("mantissa shifted: %lx \n", a);
        printf("shifted result: %lx \n", val);

        val = a >> 2;

        printf("mantissa shifted: %lx \n", a);
        printf("shifted result: %lx \n", val);
//        test = (unsigned char*)(((long)x) << 52);

        printf("test: %hu \n", ( BYTE_ARR(x)[6] & 0x0F));
        printf("test: %hu \n", ( BYTE_ARR(x)[5] & 0xFF));
        printf("test: %hu \n", ( BYTE_ARR(x)[4] & 0xFF));
        printf("test: %hu \n", ( BYTE_ARR(x)[3] & 0xFF));
        printf("test: %hu \n", ( BYTE_ARR(x)[2] & 0xFF));
        printf("test: %hu \n", ( BYTE_ARR(x)[1] & 0xFF));

        printf("test (1 << 63) %lx", ((long)1)<<63);
    }   

    return 0;
}
