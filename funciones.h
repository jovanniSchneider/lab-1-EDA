#include <stdlib.h>
#include <stdio.h>

//------------------------------Estructuras--------------------------------

typedef struct torrePizzas
{
    int sePudo; // Si se pudo leer el archivo vale 1 en caso contrario 0.
    int cantidad; //Cuantas masas de pizza hay
    int * masas; //Array que contiene los diametros de las masas
} torrePizzas;

typedef struct volteretas
{
    int cantidad; //Cuantas volteretas se han hecho
    int * swaps; //Array que contiene la secuencia de volteretas
}volteretas;

//-----------------------------Funciones----------------------------------

//Entrada: nombre del archivo ("string") y puntero a estructura del tipo torrePizzas, donde se guardaran los datos de las masas
//Salida: no entrega, ya que se utiliza paso por referencia
//Funcion: Lee el archivo y si es que existe guarda sus datos en la estructura del tipo torrePizzas.
void leerArchivo(char * nombreArchivo, torrePizzas *lectura)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    int aux;
    if (!(archivo == NULL))
    {
        lectura->sePudo = 1;
        fscanf(archivo, "%d", &lectura->cantidad);
        lectura->masas = (int *)malloc(sizeof(int) * lectura->cantidad);
        for (int i = 0; i < lectura->cantidad; i++)
        {
            fscanf(archivo, "%d", &lectura->masas[i]);
        }
    }
    fclose(archivo);
}

//Entrada: Array de enteros que contiene los diametros de las masas, entero que representa la cantidad de masas presentes en la "torre" 
//y un entero que indica desde donde se empieza a buscar el mayor numero.
//Salida: un entero que representa una posicion dentro del array
//Funcion: Encuentra el mayor numero dentro de un subgrupo de un array (conjunto [desde,n]) y devuelve su posicion en el array
int encontrarMayor(int *masas, int n, int desde)
{
    int mayor = masas[desde];
    int indice = desde;
    for (int i = desde; i < n; i++)
    {
        if (masas[i] > mayor)
        {
            mayor = masas[i];
            indice = i;
        }
    }
    return indice;
}

//Entrada: Array de enteros que contiene los diametros de las masas, entero que representa la cantidad de masas presentes en la "torre" 
//y un entero que indica desde donde se realiza la voltereta.
//Salida: No entrega, ya que trabaja sobre punteros.
//Funcion: Realiza una voltereta desde una posicion hasta la n (invierte el orden de un subgrupo)
void swap(int *masas, int n, int desde)
{
    int aux;
    for (int i = desde - 1; i < n; i++)
    {
        aux = masas[n - 1];
        masas[n - 1] = masas[i];
        masas[i] = aux;
        n--;
    }
}

//Entrada: un Array de enteros que representa la secuencia de volteretas, un entero que representa la cantidad de volteretas y la nueva voltereta a agregar (entero).
//Salida: Un array de enteros con un elemento adicional al de entrada. tamaño = n+1
//Funcion: Agrega una voltereta a una secuencia de volteretas representadas por un array de enteros
int *agregarVoltereta(int *volteretas, int n, int newVoltereta)
{
    int *volteretasNew = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; i++)
    {
        volteretasNew[i] = volteretas[i];
    }
    volteretasNew[n] = newVoltereta;
    free(volteretas);
    return volteretasNew;
}

//Entrada: una estructura del tipo torrePizzas y el puntero a una estructura del tipo volteretas
//Salida: no entrega ya que trabaja por referencia
//Funcion: ordena una torre de mayor a menor realizando "volteretas" y guarda la secuencia de volteretas (indice desde donde se realiza)
void ordenar(torrePizzas torre, volteretas * vueltas)
{
    vueltas->cantidad = 0;
    vueltas->swaps = (int *)malloc(sizeof(int) * vueltas->cantidad);
    int separador = 1; //separa el subgrupo ordenado y el desordenado, es el primer elemento del subgrupo desordenado
    int mayor;
    //Cuando el separador llegue al valor de la cantidad de masas, quiere decir que no quedan elementos desordenados
    while (separador < torre.cantidad)
    {
        //encuentra el mayor y verifica si es que está en la cima de la torre, si es asi realiza la voltereta desde el separador
        mayor = encontrarMayor(torre.masas, torre.cantidad, separador - 1);
        if (mayor + 1 == torre.cantidad)
        {
            swap(torre.masas, torre.cantidad, separador); //voltereta desde el separador porque el mayor está en la cima
            vueltas->swaps = agregarVoltereta(vueltas->swaps,vueltas->cantidad,separador); //se agrega la voltereta
            vueltas->cantidad++; //se aumenta en 1 la cantidad de volteretas
            separador = separador + 1; //se tiene un elemento ordenado adicional, por lo que el separador avanza a la siguiente posicion
        }
        else
        {
            //si no está en la ultima posición puede estar justo en la posicion del separador, si es asi ya está ordenado, por lo que se avanza el separador
            if (mayor + 1 == separador)
            {
                separador++;
            }else
            //sino esta arriba ni abajo (separador), está entremedio por lo que habria que llevarlo arriba para que en la siguiente iteracion baje
            {
                swap(torre.masas, torre.cantidad, mayor + 1); //se lleva el mayor a la cima de la torre
                swap(torre.masas, torre.cantidad, separador); //voltereta desde el separador porque el mayor está en la cima
                separador = separador + 1; //se tiene un elemento ordenado adicional, por lo que el separador avanza a la siguiente posicion
                vueltas->swaps = agregarVoltereta(vueltas->swaps,vueltas->cantidad,mayor+1);
                vueltas->cantidad++;
                //aca no se aumenta el separador porque aun no está ordenado
            }
            
        }
    }
}


//Entrada: estructura del tipo volteretas que contiene la secuencia de volteretas y la cantidad; el nombre del archivo de salida ("string").
//Salida: Un archivo
//Funcion: graba la secuencia de volteretas en un archivo
void escribirArchivo(volteretas vueltas, char * nombreArchivo){
    FILE * archivo = fopen(nombreArchivo,"w");
    for (int i = 0; i < vueltas.cantidad; i++)
    {
        fprintf(archivo,"%d ",vueltas.swaps[i]);
    }
    fprintf(archivo,"%d",0);
    fclose(archivo);
}