#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct registroSala registroSala;

struct registroSala{
    char id[20];
    char ubicacion[200];
    int capacidad;
    char recursos[200];
    char estado[50];
    int calificacion;
};

int main(){
    char capacidad[10];
    registroSala registroSala[2];
    FILE *Archivo;
    Archivo = fopen("Registro","a");

    for (int i = 0; i < 2; ++i) {
        printf("\nIngrese el ID de la sala %i: ",i+1);
        scanf("%s",&registroSala[i].id);
        printf("\nIngrese la ubicacion de la sala %i: ",i+1);
        scanf("%s",&registroSala[i].ubicacion);
        printf("\nIngrese la capacidad de la sala %i: ",i+1);
        scanf("%s",&capacidad);
        registroSala[i].capacidad = atoi(capacidad);
        printf("\nIngrese los recursos de la sala %i: ",i+1);
        scanf("%s",&registroSala[i].recursos);
        printf("\nIngrese el estado de la sala %i: ",i+1);
        scanf("%s",&registroSala[i].estado);
        registroSala[i].calificacion = 100;
        printf("\nID: %s\nUbicacion: %s\nCapacidad: %i\nRecursos: %s\nEstado: %s\nCalificacion: %i",registroSala[i].id,registroSala[i].ubicacion,registroSala[i].capacidad,registroSala[i].recursos,registroSala[i].estado,registroSala[i].calificacion);
        fprintf(Archivo,"\nID: %s\nUbicacion: %s\nCapacidad: %i\nRecursos: %s\nEstado: %s\nCalificacion: %i",registroSala[i].id,registroSala[i].ubicacion,registroSala[i].capacidad,registroSala[i].recursos,registroSala[i].estado,registroSala[i].calificacion);
    }
    fclose(Archivo);
    return 0;
}