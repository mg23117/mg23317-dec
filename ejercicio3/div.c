/* Division en 32 bits */

#include <stdio.h>

int main(){

	unsigned int dividendo = 42;		/* Este es %2 */
	unsigned int divisor = 9;			/* Este es %3 */
	unsigned int cociente;				/* Este es %0 */
	unsigned int residuo;				/* Este es %1 */
	
	asm volatile(
		
		"cld\n\t"
		"movl $0, %%edx\n\t"		/* Hacemos esto para que EDX Sea = 0*/
		"movl %2, %%eax\n\t"		/* Pasamos el dividendo a la variable eax. eax = dividendo */
		"divl %3\n\t"				/* Divide EDX:EAX entre el divisor (%3). Una vez se divide, el residuo va a 'EDX' y el cociente a 'EAX' */
		"movl %%eax, %0\n\t"		/* Pasamos el cociente el cual se guardo en 'EAX' a la variable 'Cociente (%0)' */
		"movl %%edx, %1"			/* Pasamos el residuo el cual se guardo en 'EDX' a la variable 'Residuo (%1)' */
		
		: "=r" (cociente), "=r" (residuo)
		: "r" (dividendo), "r" (divisor)
		: "%eax", "edx"
	
	);
	
	printf("El resultado de dividir '%u / %u' es = %u. Su residuo es '%u'\n", dividendo, divisor, cociente, residuo);
	
	return 0;
}
