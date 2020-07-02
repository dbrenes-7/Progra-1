#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANO 300

typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Nodo
{
    int dato;
    Nodo *siguiente;
};

struct Lista
{
    Nodo *inicio;
};

struct Estudiante
{
    char nombre[100];
    char carrera[100];
    char correo[200];
    int carnet, numero;
}est;

struct Sala{
    int capacidad;
    char ubicacion[TAMANO];
    char recursos[TAMANO];
    char estado[TAMANO];
    char id[TAMANO];
    char horario[TAMANO];
    int calificacion;
}sala;


struct Reserva{
    char estudiante[TAMANO];
    char id[TAMANO];
    char fecha[TAMANO];
    char ubicacion[TAMANO];
    int inicio;
    int fin;
    int prioridad;
}reserva;

Lista *listaNueva(void)
{
    Lista *L;
    L = (Lista *) malloc(sizeof(Lista));
    L->inicio = NULL;
    return L;
}

void agregarEstudiante();
int verificarCarnet(Lista *L, int elemento);
void agregarSala();
void mostrarSalas();
void calificarSala(char id[30]);
void consultarSala(char sala[TAMANO]);
void crearReserva();
void consultarReserva(char estudiante[50]);
int atenderReserva(char id[TAMANO],char ubicacio[TAMANO],char fechas[TAMANO], int incio,int final);
void pasarArchivos();


void agregarEstudiante()
{
    int M;
    Lista *L;
    printf("Indique el nombre: ");
    gets(est.nombre);
    printf("\nIndique la carrera: ");
    gets(est.carrera);
    printf("Indique el correo: ");
    gets(est.correo);
    printf("Indique el carnet: ");
    scanf("%d",&est.carnet);
    printf("Indique el numero telefonico: ");
    scanf("%d",&est.numero);
    FILE *ptr;
    ptr = fopen("Estudiante.txt", "a+");
    M = verificarCarnet(L,est.carnet);
    if(M==-1){
        fprintf(ptr,"%s\n",est.nombre);
        fprintf(ptr,"%s\n",est.carrera);
        fprintf(ptr,"%s\n",est.correo);
        fprintf(ptr,"%d\n",est.carnet);
        fprintf(ptr,"%d\n",est.numero);
        printf("DATOS GUARDADOS...");
    }else{
        int opcion;
        printf("Parece que este carnet ya esta registrado. ¿Desea intentarlo de nuevo?\n\n[1] Intentar de nuevo\n[2] Ir al menu principal\n\n");
        scanf("%d", opcion);
        if(opcion == 1){
            return agregarEstudiante();
        }else
        {
            return;
        }
    }

    fclose(ptr);
}

int verificarCarnet(Lista *L, int elemento)
{
    FILE *ptr;
    ptr = fopen("nuevo.txt", "r");
    char linea[1024];
    int posicion = 0;
    while(fgets(linea, 1024, (FILE*) ptr)) {
        if(atoi(linea)==elemento){
            return posicion;
        }
        ++posicion;
    }
    return -1;
}

void agregarSala()
{
    FILE *Archivo;
    Archivo = fopen("Registro.dat","ab");

    printf("\nIndique el ID de la sala: ");
    scanf("%s",&sala.id);
    fprintf(Archivo,"%s\n",sala.id);

    printf("\n[1]Biblioteca Jose Figueres Ferrer\n[2]Learning Commons\nIndique la ubicacion de la sala: ");
    scanf("%s",&sala.ubicacion);
    fprintf(Archivo,"%s\n",sala.ubicacion);

    printf("\nIndique los recursos de la sala(PIZARRA/PROYECTOR/AC/COMPUTADORA): ");
    scanf("%s",&sala.recursos);
    fprintf(Archivo,"%s\n",sala.recursos);
    printf("\nIndique el estado de la sala(ACTIVA/INACTIVA/MANTENIMIENTO): ");
    scanf("%s",&sala.estado);
    fprintf(Archivo,"%s\n",sala.estado);
    printf("\nIndique el horario de operacion de la sala: ");
    scanf("%s",&sala.horario);
    fprintf(Archivo,"%s\n",sala.horario);
    printf("\nIndique la capacidad de la sala: ");
    scanf("%d",&sala.capacidad);
    fprintf(Archivo,"%d\n",sala.capacidad);
    calificarSala(sala.id);
}

void mostrarSalas(){
    FILE *fich;
    fich = fopen("Registro.dat", "r");
    char registro[1024];
    while(fgets(registro, 1024, (FILE*) fich)) {//muestra todas las salas registradas
        printf(registro);
    }
}

void calificarSala(char id[30]){
    FILE *Archivo;
    Archivo = fopen("Calificaciones.dat","ab");
    printf("Indique la calificacion de la sala: ");
    scanf("%d",&sala.calificacion);

    fprintf(Archivo,"%s\n",id);
    fprintf(Archivo,"%d\n",sala.calificacion);

}

void consultarSala(char sala[TAMANO]){
    char registro[1024],reserva[1024],calif[1024];
    FILE *fich;
    fich = fopen("Registro.dat", "r");
    FILE *arch;
    FILE *Archivo;
    Archivo = fopen("Calificaciones.dat","r");
    arch = fopen("Reserva.dat","r");
    while(fgets(registro, 1024, (FILE*) fich)) {//esto agarra linea por linea toodo el documento
        if(strcmp(registro,sala)==0){
            printf("%s", registro);//ID
            printf(fgets(registro, 1024, (FILE*) fich));//UBICACION
            printf(fgets(registro, 1024, (FILE*) fich));//RECURSOS
            printf(fgets(registro, 1024, (FILE*) fich));//ESTADO
            printf(fgets(registro, 1024, (FILE*) fich));//HORARIO DE OPERACION
            printf(fgets(registro, 1024, (FILE*) fich));//CAPACIDAD
            while(fgets(calif, 1024, (FILE*) Archivo)){
                if(strcmp(calif,sala)==0){
                    printf(fgets(calif, 1024, (FILE*) Archivo));//CALIFICACION
                    while(fgets(reserva, 1024, (FILE*) arch)){
                        if(strcmp(reserva,sala)==0){
                            printf("\n");
                            printf(fgets(reserva, 1024, (FILE*) arch));//fecha de la reserva
                            printf(fgets(reserva, 1024, (FILE*) arch));//hora inicio reserva
                            printf(fgets(reserva, 1024, (FILE*) arch));//hora fin reserva
                        }
                    }
                }
            }
        }
    }
    fclose(Archivo);
    fclose(fich);
    fclose(arch);
}

void crearReserva()
{
    FILE *Archivo;
    Archivo = fopen("Reserva.dat","ab");
    char estudiante[TAMANO],id[TAMANO],fecha[TAMANO], ubicacion[TAMANO];
    int inicio, final, prioridad;
    printf("\nIngrese el carnet del estudiante: ");
    scanf("%s",&estudiante);

    mostrarSalas();
    printf("Ingrese el ID de la sala: ");
    scanf("%s",&id);

    printf("\n[1]Biblioteca Jose Figueres Ferrer\n[2]Learning Commons\nIndique la ubicacion de la sala: ");
    scanf("%s",&ubicacion);

    printf("\nIngrese la fecha de la reserva: ");
    scanf("%s",&fecha);

    printf("\nIngrese la hora en formato de 24 horas, sin AM O PM\nIngrese la hora de incio de la reserva de la sala: ");
    scanf("%d",&inicio);

    printf("\nIngrese la hora en formato de 24 horas, sin AM O PM\nIngrese la hora del final de la reserva de la sala: ");
    scanf("%d",&final);

    prioridad = rand() % 4;

    if(atenderReserva(strcat(id,"\n"), strcat(ubicacion,"\n"), strcat(fecha,"\n"), inicio, final)==0){
        fprintf(Archivo,"%s\n",estudiante);
        fprintf(Archivo,"%s",id);
        fprintf(Archivo,"%s",ubicacion);
        fprintf(Archivo,"%s",fecha);
        fprintf(Archivo,"%d\n",inicio);
        fprintf(Archivo,"%d\n",final);
        fprintf(Archivo,"%d\n",prioridad);
    } else{
        printf("VUELVA A INTENTARLO");
        crearReserva();
    }


    fclose(Archivo);

}

void consultarReserva(char carnet[50])
{
    char linea[1024];
    FILE *fich;
    fich = fopen("Reserva.dat", "r");
    while(fgets(linea, 1024, (FILE*) fich)) {//esto agarra linea por linea toodo el documento
        strcpy(reserva.estudiante,linea);
        fgets(linea, 1024, (FILE*) fich);//ID
        strcpy(reserva.id,linea);
        fgets(linea, 1024, (FILE*) fich);//UBICACION
        strcpy(reserva.ubicacion,linea);
        fgets(linea, 1024, (FILE*) fich);//FECHA
        strcpy(reserva.fecha,linea);
        fgets(linea, 1024, (FILE*) fich);//INICIO
        reserva.inicio = atoi(linea);
        fgets(linea, 1024, (FILE*) fich);//FIN
        reserva.fin = atoi(linea);
        fgets(linea, 1024, (FILE*) fich);//PRIORIDAD
        reserva.prioridad = atoi(linea);
        if(strcmp(carnet,reserva.estudiante)==0){//esto agarra la sala ingresada en la funcion y dice si la encuentra en el documento
            //printf("%s",reserva.estudiante);//Estudiante
            printf("%s",reserva.id);//ID  de la sala
            printf("%s",reserva.ubicacion);//Ubicacion de la sala
            printf("%s",reserva.fecha);//Fecha de la reserva
            printf("%d\t",reserva.inicio);//Hora de inicio de la reserva
            printf("%d\n",reserva.fin);//Hora del final de la reserva
        }
    }
    fclose(fich);
}

int atenderReserva(char id[TAMANO], char ubicacion[TAMANO], char fechas[TAMANO], int inicio, int final)
{
    char linea[1024];
    int cont , aux, flag;
    FILE *fich;
    fich = fopen("Reserva.dat", "r");
    while(fgets(linea, 1024, (FILE*) fich)){
        fgets(linea, 1024, (FILE*) fich);//id primera
        strcpy(reserva.id,linea);
        fgets(linea, 1024, (FILE*) fich);//ubicacion
        strcpy(reserva.ubicacion,linea);
        fgets(linea, 1024, (FILE*) fich);//fecha
        strcpy(reserva.fecha,linea);
        fgets(linea, 1024, (FILE*) fich);//hora de inicio
        cont = atoi(linea);//guarda
        fgets(linea, 1024, (FILE*) fich);//hora final
        aux = atoi(linea);
        if(strcmp(reserva.id,id)==0 && strcmp(reserva.ubicacion,ubicacion)==0){
            if(strcmp(reserva.fecha,fechas)==0){
                if(cont==inicio){
                    printf("ERROR, CHOQUE DE HORARIO");
                    flag = 1;
                } else if (inicio>=cont && inicio<=aux){
                    printf("ERROR, CHOQUE DE HORARIO");
                    flag = 1;
                } else if (final>=cont && final<=aux){
                    printf("ERROR, CHOQUE DE HORARIO");
                    flag = 1;
                }
            }
        }
    }

    if(flag ==1){
        return 1;
    } else{
        return 0;
    }
}


void modificarSala(char idSala[TAMANO],char ubicacion[TAMANO]){
    char linea[1024], recursos[TAMANO], estado[TAMANO];
    FILE *Archivo, *arch;
    Archivo = fopen("Registro.dat", "r");
    arch = fopen("ModificacionesSala.dat", "w");
    printf("Indique los recursos actualizados de la sala: ");
    scanf("%s", &recursos);
    printf("Indique el estado actualizado de la sala: ");
    scanf("%s", &estado);
    while(fgets(linea, 1024, (FILE*) Archivo)){
        printf("%s",linea);
        if(strcmp(idSala,linea)==0) {
            fprintf(arch,"%s",linea);
            if (strcmp(ubicacion, fgets(linea, 1024, (FILE *) Archivo)) == 0) {
                fprintf(arch,"%s",linea);
                fgets(linea, 1024, (FILE *) Archivo);//RECURSOS
                fprintf(arch,"%s\n",recursos);
                fgets(linea, 1024, (FILE *) Archivo);//ESTADO
                fprintf(arch,"%s\n",estado);
                fgets(linea, 1024, (FILE *) Archivo);
            }
        }
        fprintf(arch,"%s",linea);
    }
    fclose(Archivo);
    fclose(arch);
}

void pasarArchivos(){
    FILE *Archivo, *fich;
    char linea[1024];
    Archivo = fopen("ModificacionesSala.dat", "r");
    fich = fopen("Registro.dat", "w");
    while(fgets(linea, 1024, (FILE*) Archivo)){
        fprintf(fich,"%s",linea);
    }
}


int main()
{
    //agregarEstudiante();
    //agregarSala();
    //consultarSala("SAL001\n");
    //crearReserva();
    //calificarSala("SAL001\n");
    //consultarReserva("2019061571\n");
    //modificarSala("SAL002\n","1\n");
    pasarArchivos();
    return 0;
}
