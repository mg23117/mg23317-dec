/* multiplicacion con registros de 8 bits */

#include <stdio.h>

int main(){

	unsigned char a = 10;
	unsigned char b = 2;
	unsigned short resultado; 
	
	asm volatile(
		
		"cld\n\t"
		"movb %1, %%al\n\t"
		"mulb %2\n\t"
		"movw %%ax, %0\n\t"
		
		: "=r" (resultado)
		: "r" (a), "r" (b)
		: "al", "ah", "ax"
		
	);
	
	printf("El resultado de la multiplicacion '%u * %u' es = %u \n", a, b, resultado);
	
	return 0;
}
