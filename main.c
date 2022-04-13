//Nombre: Jovanni Schneider Pizarro
//Curso: Analisis de algoritmos y estructuras de datos
//Seccion: C3
//Profesora: Lilian Salazar

//IMPORTANTE: Se debe contener el archivo llamado "funciones.h" en el mismo directorio desde donde se compila y ejecuta el programa

/*Se tiene el siguiente problema de ordenamiento:
Una pizzeria requiere ordenar sus masas de pizza de distintos diametros de mayor a menor (desde la base) realizando volteretas, las cuales 
consisten en meter la espatula debajo de una masa y voltear todas las que esten sobre esta, inviertiendo el orden de la posicion desde
la que se hizo la voltereta hasta la cima de la torre. Por ejemplo si tenemos la funcion voltereta definida como V(x) donde x es la posicion
desde la cual se realiza la voltereta, y se tiene una torre formada por los diametros (3, 5, 2 ,6 ,10) y realizamos V(2), nuestra torre de salida
seria (3, 10, 6, 2, 5).
La pizzeria nos entrega un archivo en el cual en su primera linea contiene un entero que corresponde a la cantidad de masas presentes en la torre
y en la segunda linea contiene los diametros de las pizzas separados por espacios, teniendo este archivo hemos de generar un archivo de salida el cual
contenga la secuencia de volteretas representadas por los indices desde donde se hacen las volteretas. Por ejemplo si tenemos la siguiente secuencia:
V(3)->V(1)->V(5)->V(1)
El contenido de nuestro archivo de salida debiese una sola linea con lo siguiente: 3 1 5 1
*/

//--------------------------------Tarea de laboratorio N°1--------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones.h"

int main(int argc, char * argv[])
{
    clock_t inicio;
    clock_t final;
    inicio = clock();
    torrePizzas torre; //se crea la base de las pizzas para poder guardar los datos
    char * nombreEntrada = argv[1];
    char * nombreSalida = argv[2];
    leerArchivo(nombreEntrada, &torre); //Se lee el archivo y se guardan sus datos la estructura torre
    if (torre.sePudo == 1)// ese atributo de la estructura indica si se pudo leer satisfactoriamente el archivo (1 = True, 0 = False)
    {
        volteretas vueltas; // Se crea la estructura donde se guardara la secuencia de volteretas
        ordenar(torre, &vueltas);// Se ordena la torre y se guarda la secuencia en la estructura vueltas
        escribirArchivo(vueltas, nombreSalida); //Se graba la secuencia de volteretas en el archivo de salida
        
        //Se libera la memoria dinamica
        free(torre.masas);
        free(vueltas.swaps);
    }
    else
    {
        printf("Error al leer el archivo\n");
    }
    final = clock();
    //double segundos = (double)(inicio - final) / CLOCKS_PER_SEC;
    //printf("%f segundos de ejecucion\n",segundos);
    return 0;
}