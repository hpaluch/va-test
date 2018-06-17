
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// uncomment to buggy build (will crash when run)
//#define MY_BUG_VA_ARGS

void writeShort(unsigned short v){
	printf("Short value=%hu\n",v);
}

void arg_test(int n, ...){

	va_list ap;

	// n is ignored by us, but va_start() requires name of last
	// argument before ...
	va_start(ap,n);
	printf("i1=%d\n",va_arg(ap,int));

#ifdef MY_BUG_VA_ARGS
	// BAD!
	writeShort(va_arg(ap,unsigned short));
#else
	// OK -> unsigned int...
	writeShort((unsigned short)va_arg(ap,unsigned int));
#endif

	printf("i2=%d\n",va_arg(ap,int));
	va_end(ap);
}


int main(int argc, char **argv) {
	int i1=1234567890,i2=987654321;
	unsigned short s1=32123;

	arg_test(3,i1,s1,i2);

	return 0;
}
