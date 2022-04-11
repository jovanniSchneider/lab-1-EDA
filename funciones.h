//
// Created by jovan on 4/9/2022.
//
#include <stdlib.h>
#include <stdio.h>

typedef struct torrePizzas
{
    int sePudo; // Si se pudo leer el archivo vale 1 en caso contrario 0.
    int cantidad;
    int *masas;
} torrePizzas;

typedef struct volteretas
{
    int cantidad;
    int * swaps;
}volteretas;


void leerArchivo(char *nombreArchivo, torrePizzas *lectura)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    int aux;
    if (!(archivo == NULL))
    {
        lectura->sePudo = 1;
        lectura->masas = (int *)malloc(sizeof(int) * lectura->cantidad);
        fscanf(archivo, "%d", &lectura->cantidad);
        for (int i = 0; i < lectura->cantidad; i++)
        {
            fscanf(archivo, "%d", &lectura->masas[i]);
        }
    }
    fclose(archivo);
}

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


int *agregarVoltereta(int *volteretas, int n, int newVoltereta)
{
    int *volteretasNew = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; i++)
    {
        volteretasNew[i] = volteretas[i];
    }
    volteretasNew[n] = newVoltereta;
    return volteretasNew;
}

void ordenar(torrePizzas torre, volteretas * vueltas)
{
    vueltas->cantidad = 0;
    vueltas->swaps = (int *)malloc(sizeof(int) * vueltas->cantidad);
    int separador = 1;
    int mayor;
    while (separador < torre.cantidad)
    {
        mayor = encontrarMayor(torre.masas, torre.cantidad, separador - 1);
        if (mayor + 1 == torre.cantidad)
        {
            swap(torre.masas, torre.cantidad, separador);
            vueltas->swaps = agregarVoltereta(vueltas->swaps,vueltas->cantidad,separador);
            vueltas->cantidad++;
            separador = separador + 1;
        }
        else
        {
            if (mayor + 1 != separador)
            {
                swap(torre.masas, torre.cantidad, mayor + 1);
                vueltas->swaps = agregarVoltereta(vueltas->swaps,vueltas->cantidad,mayor+1);
                vueltas->cantidad++;
            }else
            {
                separador++;
            }
            
        }
    }
}

void escribirArchivo(volteretas vueltas, char * nombreArchivo){
    FILE * archivo = fopen(nombreArchivo,"w");
    for (int i = 0; i < vueltas.cantidad; i++)
    {
        fprintf(archivo,"%d ",vueltas.swaps[i]);
    }
    fprintf(archivo,"%d",0);
    fclose(archivo);
}