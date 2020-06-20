#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct consulta{
    char id[1024];
    char estado[50];
};

void agregarSala(){
    char capacidad[10], ubicacion[200],recursos[200],estado[50],id[20];

    FILE *Archivo;
    Archivo = fopen("Registro.txt","a");//CON w modifica el documento

    printf("\nIngrese el ID de la sala: ");
    scanf("%s",&id);
    fprintf(Archivo,"ID: %s\n",id);


    printf("\nIngrese la ubicacion de la sala: ");
    scanf("%s",&ubicacion);
    fprintf(Archivo,"Ubicacion: %s\n",ubicacion);

    printf("\nIngrese la capacidad de la sala: ");
    scanf("%s",&capacidad);
    fprintf(Archivo,"Capacidad: %s\n",capacidad);


    printf("\nIngrese los recursos de la sala: ");
    scanf("%s",&recursos);
    fprintf(Archivo,"Recursos: %s\n",recursos);


    printf("\nIngrese el estado de la sala: ");
    scanf("%s",&estado);
    fprintf(Archivo,"Estado: %s\n",estado);

    fprintf(Archivo,"Calificacion: 100\n");

    fprintf(Archivo,"Horario de operacion: 8am - 8pm\n");


    printf("\nID: %s\nUbicacion: %s\nCapacidad: %s\nRecursos: %s\nEstado: %s\nCalificacion: %i",id,ubicacion,capacidad,recursos,estado,100);


    fclose(Archivo);
}

void consultarSalas(char sala[20]){
    char linea[1024];
    FILE *fich;
    fich = fopen("Registro.txt", "r");
    while(fgets(linea, 1024, (FILE*) fich)) {//esto agarra linea por linea toodo el documento
        if(strcmp(sala,linea)==0){//esto agarra la sala ingresada en la funcion y dice si la encuentra en el documento
            printf("LO LOGRASTE\n");
            printf("%s", linea);
            printf(fgets(linea, 1024, (FILE*) fich));
            printf(fgets(linea, 1024, (FILE*) fich));//esto imprime el resto de datos de la sala, solo si se busca por ID
            printf(fgets(linea, 1024, (FILE*) fich));
            printf(fgets(linea, 1024, (FILE*) fich));
            printf(fgets(linea, 1024, (FILE*) fich));
            printf(fgets(linea, 1024, (FILE*) fich));
        }
    }
    fclose(fich);
}

void modificarSala(char sala[20]){
    FILE *Archivo;
    Archivo = fopen("Registro.txt","a");
    consultarSalas(sala);
    
}

void crearReserva()
{
    char id[20], inicio[20], fin[20], estudiante[50];
    FILE *Archivo;
    Archivo = fopen("Reserva.txt","a");

    printf("\nIngrese el nombre del estudiante: ");
    scanf("%s",&estudiante);
    fprintf(Archivo,"Estudiante: %s\n",estudiante);

    printf("\nIngrese el ID de la sala: ");
    scanf("%s",&id);
    fprintf(Archivo,"ID: %s\n",id);


    printf("\nIngrese la hora de incio de la reserva de la sala: ");
    scanf("%s",&inicio);
    fprintf(Archivo,"Hora de inicio: %s\n",inicio);


    printf("\nIngrese la hora del final de la reserva de la sala: ");
    scanf("%s",&fin);
    fprintf(Archivo,"Hora del fin: %s\n",fin);


    printf("\nID: %s\nHora de Inicio: %s\nHora del Final: %s",id,inicio,fin);

}

void consultarReserva(char estudiante[50])
{
    char linea[1024];
    FILE *fich;
    fich = fopen("Reserva.txt", "r");
    while(fgets(linea, 1024, (FILE*) fich)) {//esto agarra linea por linea toodo el documento
        if(strcmp(estudiante,linea)==0){//esto agarra la sala ingresada en la funcion y dice si la encuentra en el documento
            printf(fgets(linea, 1024, (FILE*) fich));//ID  de la sala
            printf(fgets(linea, 1024, (FILE*) fich));//Hora de inicio de la reserva
            printf(fgets(linea, 1024, (FILE*) fich));//Hora del final de la reserva

        }
    }
    fclose(fich);
}

void atenderReserva(char id[20])
{
    char linea[1024];
    char aux[1024], curr[1024];
    FILE *fich;
    fich = fopen("Reserva.txt", "r");
    while(fgets(linea, 1024, (FILE*) fich)){
        if(strcmp(id,linea)==0){
            fgets(linea, 1024, (FILE*) fich);//agarra nombre estudiante
            fgets(linea, 1024, (FILE*) fich);//ID DE LA SALA
            fgets(linea, 1024, (FILE*) fich);//HORA DE INICIO
            strcpy(aux,linea);
            fgets(linea, 1024, (FILE*) fich);//HORA FIN
            fgets(linea, 1024, (FILE*) fich);//agarra nombre estudiante
            fgets(linea, 1024, (FILE*) fich);//ID
            fgets(linea, 1024, (FILE*) fich);//hora inicio siguiente sala
            strcpy(curr,linea);
            if(strcmp(aux,curr)==0){
                printf("INCIDENTE");
            }
        }
    }
    return;
}


int main(){
    //agregarSala();
    //consultarSalas("ID: SAL001\n");
    //crearReserva();
    //consultarReserva("Estudiante: Samuel\n");
    atenderReserva("ID: SAL001\n");

    return 0;
}