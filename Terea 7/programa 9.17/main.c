#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Reemplaza palabras.
El programa lee cadenas de caracteres de un archivo y cada que vez que
\encuentra la palabra M�xico escrita en forma incorrecta �la primera con
min�scula� la reemplaza por su forma correcta y escribe la cadena en otro
archivo. */

void cambia(FILE *, FILE *);
/* Prototipo de funci�n. Se pasan dos archivos como par�metros. */
void main(void)
{
FILE *ar;
FILE *ap;
ar = fopen("arc.txt", "r"); /* Se abre el archivo arc.txt para lectura. */
ap = fopen("arc1.txt", "w"); /* Se abre el archivo arc1.txt para escritura. */
if ((ar != NULL) && (ap != NULL))
{
cambia(ar, ap);
fclose(ar);
fclose(ap);
}
else
printf("No se pueden abrir los archivos");
}
void cambia(FILE *ap1, FILE *ap2)
{
/* Esta funci�n reemplaza en la cadena de caracteres la palabra m�xico escrita
con min�sculas �la primera letra� por su forma correcta y escribe la cadena
de caracteres en un nuevo archivo. */
int i, j, k;
char cad[30], *cad1="", *cad2="", aux[30];
while (!feof(ap1))
{
fgets(cad, 30, ap1);
strcpy(cad1, cad);
cad2 = strstr(cad1, "m�xico"); /* Localiza la subcadena m�xico
en cad1. */
while (cad2!=NULL)
{
cad2[0]='M'; /* Reemplaza la letra min�scula por la may�scula. */
i = strlen(cad1);
j = strlen(cad2);
k = i - j; /* En k se almacena la diferencia de las longitudes de
las cadenas
cad1 y cad2. */
if (k)
{
strncpy(aux, cad1, k);

/* Se copia la subcadena de k caracteres de cad1 a aux �desde el
inicio de
cad1 hasta el caracter anterior a m�xico. */

aux[k] = '\0';
strcat(aux, cad2);
strcpy(cad1, aux);
}
else
strcpy(cad1, cad2);
cad2 = strstr(cad1, "m�xico");
}
fputs(cad1, ap2); /* Se escribe la cadena correcta en el archivo ap2. */
}
}
