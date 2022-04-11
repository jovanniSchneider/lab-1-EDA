//
// Created by jovan on 4/9/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    torrePizzas torre;
    leerArchivo("entrada1.in", &torre);
    if (torre.sePudo == 1)
    {
        volteretas vueltas;
        ordenar(torre, &vueltas);
        escribirArchivo(vueltas, "salida.out");
        free(torre.masas);
        free(vueltas.swaps);
    }
    else
    {
        printf("Error al leer el archivo\n");
    }

    return 0;
}
