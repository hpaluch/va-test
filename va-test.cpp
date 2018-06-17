
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// uncomment to buggy build (will crash on gcc platform when run)
// #define MY_BUG_VA_ARGS

void writeShort(unsigned short v){
	printf("Short value=%hu\n",v);
}

// WARNING arguments passed to ... are promoted to different types...
// see http://www.gnu.org/software/libc/manual/html_node/Argument-Macros.html#Argument-Macros
void arg_test(int n, ...){

	va_list ap;

	// n is ignored by us, but va_start() requires name of last
	// argument before ...
	va_start(ap,n);
	printf("i1=%d\n",va_arg(ap,int));

#ifdef MY_BUG_VA_ARGS
/* BAD! */
   
	writeShort(va_arg(ap,unsigned short));
/*
        above code produces grave warning (gcc 4.9.2, Debian 8.9):

In file included from va-test.cpp:4:0:
va-test.cpp: In function ‘void arg_test(int, ...)’:
va-test.cpp:24:23: warning: ‘short unsigned int’ is promoted to ‘int’ when passed through ‘...’
  writeShort(va_arg(ap,unsigned short));
                       ^
va-test.cpp:24:23: note: (so you should pass ‘int’ not ‘short unsigned int’ to ‘va_arg’)
va-test.cpp:24:23: note: if this code is reached, the program will abort

Yes! this program will really Abort inside glibc...
*/
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
