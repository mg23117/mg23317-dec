# Resolución a la actividad planteada - MG23117-DEC

## Requisitos 

1. Contar con gcc.
2. Tener instaladas las bibliotecas necesarias para poder compilar programas de 32 bits.

Explicación de la actividad **MG23117-DEC**.

## Ejercicio 1:

**Resta de tres enteros**

Escriba un programa para restar tres enteros, usando sólo registros de 16 bits. 

- Archivo: resta.c
- Registros usados: AX (16 bits)

## Explicación de la parte de ensamblador

```C
	asm volatile(
	
    /*  "cld"
        Usamos esta instrucción para limpiar (o sea, en 0) el "Direction Flag" (DF)
		y DF controla si las operaciones con cadenas (como movs) van hacia adelante o hacia atrás
		Aunque aquí no usamos operaciones de cadena, ase suele poner por convención para evitar problemas 
    */
		"cld\n\t"
		"movw %1, %%ax\n\t"			/* Usamos movw, ya que movw = mover una palabra (word = 16 bits) de un lugar a otro
                                       %1 es la segunda variable que pasamos a asm (en este caso, la variable 'a') 
                                       %%ax significa el registro 'AX' de 16 bits (registro principal para operaciones aritméticas) */

		"subw %2, %%ax\n\t" 		/* Le restamos 'b' a la variable 'ax'. ax = a - b 
                                       subw = resta una palabra (16 bits)
		                               %2 es la tercer variable pasada a asm (la variable 'b', que vale 3)
		                               O sea: AX = AX - b, es decir: AX = a - b. AX = 10 - 3 = 7 */

		"subw %3, %%ax\n\t"			/* Al resultado de antes (a - b) le restamos ahora 'c'. AX = AX - c. O sea: AX = 7 - 2 = 5 */

		"movw %%ax, %0\n\t"			/* Pasamos el resultado (que esta almacenado en 'AX') a la variable resultado (que es el %0). */
		
		: "=r" (resultado)          /* %0: salida. "=r" significa que el programa puede usar cualquier registro general para guardar el resultado */

		: "r" (a), "r" (b), "r" (c)     /* Primera "r" --> %1: entrada. 'a' se pasa a un registro general
                                         * Segunda "r" --> %2: entrada. Igual que antes, pero ahora con 'b'
                                         * Tercera "r" --> %3: entrada. Igual que antes, pero ahora con 'c'
                                        */

		: "%ax"                     /* Aquí indicamos que vamos a modificar el registro AX, para que el compilador no lo use durante la ejecución */
	);
```
## Como compilarlo:

1. **Compilar en la terminal:** gcc -m32 -o resta resta.c
2. **Ejecutar en la terminal:** ./resta

## Ejercicio 2:

**Multiplicación**

Escriba un programa para multiplicar dos números enteros, usando registros de 8 bits.

- Archivo: multiplicacion.c
- Registros usados: AL, AH (8 bits, parte baja/alta de AX)

## Explicación de la parte de ensamblador

```C

asm volatile(

    /*  "cld"
        Usamos esta instrucción para limpiar (o sea, en 0) el "Direction Flag" (DF)
		y DF controla si las operaciones con cadenas (como movs) van hacia adelante o hacia atrás
		Aunque aquí no usamos operaciones de cadena, ase suele poner por convención para evitar problemas 
    */
		"cld\n\t"
		"movb %1, %%al\n\t"         /* %1 es la variable 'a' (equivale a 10)
                                     * %%al es el registro AL, que es la parte baja del registro AX (AX = AH:AL)
                                     * Entonces, pasamos el valor de 'a'a 'AL'  (quedando: AL = a = 10) */

		"mulb %2\n\t"               /* mulb = Multiplica el segundo valor del operando (o sea, a la variable 'b') por el contenido de AL (que es donde
                                     * almacenamos el valor de 'a'. Entonces, queda: a * b)
                                     * el resultado se guarda automáticamente en el registro 'AX' */

		"movw %%ax, %0\n\t"         /* Como el resultado de la operación dado por 'mulb', se guarda en 'AX', ahora pasaremos el valor de 'AX' a la
                                     * variable de salida (resultado)*/
		
		: "=r" (resultado)          /* %0: salida. "=r" significa que el programa puede usar cualquier registro general para guardar el resultado */

		: "r" (a), "r" (b)          /* Primera "r" --> %1: entrada. 'a' se pasa a un registro general
                                     * Segunda "r" --> %2: entrada. Igual que antes, pero ahora con 'b' */

		: "al", "ah", "ax"          /* Aquí indicamos que vamos a modificar esos registros, para que el compilador no los use durante la ejecución */
		
	);

```
## Como compilarlo:

1. **Compilar en la terminal:** gcc -m32 -o multiplicacion multiplicacion.c
2. **Ejecutar en la terminal:** ./multiplicacion

## Ejercicio 3:

**División**

Escriba un programa para dividir dos números enteros, usando registros de 32 bits.

- Archivo: div.c
- Registros usados: EAX, EDX (32 bits)

## Explicación de la parte de ensamblador

```C
asm volatile(
		
    /*  "cld"
        Usamos esta instrucción para limpiar (o sea, en 0) el "Direction Flag" (DF)
		y DF controla si las operaciones con cadenas (como movs) van hacia adelante o hacia atrás
		Aunque aquí no usamos operaciones de cadena, ase suele poner por convención para evitar problemas 
    */
		"cld\n\t"
		"movl $0, %%edx\n\t"		/* En una división de 32 bits, la instrucción DIVL espera  el dividendo completo esté EDX:EAX, es decir, usa los 64 bits
                                     * combinando los registros EDX (parte alta) y EAX (parte baja). Pero como nosotros solo vamos a dividir en 32 bits (no vamos * a usar la parte alta), entonces asegurarnos de que EDX sera 0, o la división va a dar error. */

		"movl %2, %%eax\n\t"		/* Pasamos el valor del dividendo (que es 42) al registro EAX. Ahora, EDX:EAX tienen el valor completo del dividendo (0:42) */

		"divl %3\n\t"				/* DIVL es la instrucción para realizar una división sin signo (por eso usamos unsigned en las variables) de 32 bits
                                     * Esta instrucción divide EDX:EAX entre el valor pasado que es '%3 ' (la variable 'divisor' que vale '9'). 
                                     * Después de la ejecución:
                                     *  - El cociente se guarda automáticamente en EAX
                                     *  - El residuo guarda automáticamente en EDX */

		"movl %%eax, %0\n\t"		/* Almacenamos el resultado de la división (O sea, el cociente) en la variable de 'cociente' */
        
		"movl %%edx, %1"			/* Almacenamos el residuo de la división en la variable 'residuo' */
		
		: "=r" (cociente), "=r" (residuo)       /* %0 (cociente): salida. "=r" significa que el programa puede usar cualquier registro general para guardar el
                                                 * resultado
                                                 *
                                                 * %1 (residuo): salida. "=r" significa que el programa puede usar cualquier registro general para guardar el
                                                 * resultado */

		: "r" (dividendo), "r" (divisor)        /* Primera "r" --> %1: entrada. 'dividendo' se pasa a un registro general
                                                 * Segunda "r" --> %2: entrada. Igual que antes, pero ahora con 'divisor' */

		: "%eax", "edx"                         /* Aquí indicamos que vamos a modificar esos registros, para que el compilador no los use durante la ejecución */
	);
```
## Como compilarlo:

1. **Compilar en la terminal:** gcc -m32 -o div div.c
2. **Ejecutar en la terminal:** ./div