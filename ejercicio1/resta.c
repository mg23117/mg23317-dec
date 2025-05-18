/* . */

#include <stdio.h>

int main(){
	
	/* Declaramos las variables a utilizar de forma estatica (de tipo short ya que estamos trabajando con 16 bits) */
	
	short a = 10;
	short b = 3;
	short c = 2;
	short resultado;

	asm volatile(
	
		"cld\n\t"
		"movw %1, %%ax\n\t"				/* Aqui indicamos que 'ax' sera igual a 'a'. */
		"subw %2, %%ax\n\t" 			/* Le restamos 'b' a la variable 'ax'. ax = a - b */
		"subw %3, %%ax\n\t"				/* Al resultado de antes (a - b) le restamos ahora 'c'. ax = (a - b) - c. */
		"movw %%ax, %0\n\t"				/* Pasamos el resultado a la variable resultado. */
		
		: "=r" (resultado)
		: "r" (a), "r" (b), "r" (c)
		: "%ax"
	);
	
	printf("El resultado de la operacion '%d - %d - %d' es = %d\n", a, b ,c, resultado);
	
	return 0;
}
