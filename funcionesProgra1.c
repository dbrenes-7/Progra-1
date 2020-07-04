#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANO 300

typedef struct Lista Lista;
typedef struct Nodo Nodo;

struct Nodo
{
    int elemento;
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
    int carnet, numero, contador;
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

struct Incidentes{
    char sala[100];
    char codigo[100];
    char situacion[500];
    char fecha[200];
}inci;

struct Reserva{
    char estudiante[TAMANO];
    char id[TAMANO];
    char fecha[TAMANO];
    char ubicacion[TAMANO];
    int inicio;
    int fin;
    int prioridad;
    int contador;
}reserva;

Lista *listaNueva(void)
{
    Lista *L;
    L = (Lista *) malloc(sizeof(Lista));
    L->inicio = NULL;
    return L;
}

int agregarEstudiante();
int verificarCarnet(int elemento);
void agregarSala();
void mostrarSalas();
int calificarSala();
int consultarSala();
int crearReserva();
int consultarReserva();
int atenderReserva(char id[TAMANO],char ubicacio[TAMANO],char fechas[TAMANO], int incio,int final);
void pasarArchivosSala();
void pasarArchivosCalificaciones();
void pasarArchivosReserva();
int main();


int agregarEstudiante()
{
    int M;
    Lista *L;
    printf("\nIndique el nombre: ");//esto es para saber que datos se van a guardar en el archivo que se llama "Estudiante"
    scanf("%s",&est.nombre);
    printf("\nIndique la carrera: ");
    scanf("%s",&est.carrera);
    printf("\nIndique el correo: ");
    scanf("%s",&est.correo);
    printf("\nIndique el carnet: ");
    scanf("%d",&est.carnet);
    printf("\nIndique el numero telefonico: ");
    scanf("%d",&est.numero);
    FILE *ptr;
    ptr = fopen("Estudiante.txt", "a");
    M = verificarCarnet(est.carnet);//esto es para verificar que el carnet no se haya ingresado antes
    if(M==-1){
        fprintf(ptr,"%s\n",est.nombre);//aqui se guardan los datos en el archivo Estudiante
        fprintf(ptr,"%s\n",est.carrera);
        fprintf(ptr,"%s\n",est.correo);
        fprintf(ptr,"%d\n",est.carnet);
        fprintf(ptr,"%d\n",est.numero);
        printf("DATOS GUARDADOS...");
    }else{
        printf("Parece que este carnet ya esta registrado");

    }

}


int verificarCarnet(int elemento)//funcion que verifica si el carnet ingresado esta repetido
{
    FILE *ptr;
    ptr = fopen("Estudiante.txt", "r");
    char linea[1024];
    int posicion = 0;
    while(fgets(linea, 1024, (FILE*) ptr)) {//esto revisa linea por linea el codigo hasta que ya no haya nada
        if(atoi(linea)==elemento){//esto compara la linea del archivo obtenida, la transforma a un interger y lo compara con el carnet ingresado
            return posicion;
        }
        ++posicion;
    }
    return -1;
}

void agregarSala()
{
    FILE *Archivo, *arch;
    Archivo = fopen("Registro.dat","ab");
    arch = fopen("Calificaciones.dat","ab");

    printf("\nIndique el ID de la sala: ");//ingresa los datos que se van a guardar en los archivos Registro y Calificaciones
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
    fprintf(Archivo,"%d\n",sala.capacidad);//aqui se guardan los datos en los archivos Registro y Calificaciones
    fprintf(arch,"%s\n",sala.id);
    fprintf(arch,"%s\n",sala.ubicacion);
    fprintf(arch,"%d\n",100);

    fclose(Archivo);
    fclose(arch);

}

void mostrarSalas(){
    FILE *fich;
    fich = fopen("Registro.dat", "r");
    char registro[1024];
    while(fgets(registro, 1024, (FILE*) fich)) {//muestra todas las salas registradas
        printf(registro);
    }
}

int calificarSala(){
    char sala[TAMANO], linea[1024], ubicacion[TAMANO], calificacion[TAMANO];
    FILE *Archivo, *aux;
    Archivo = fopen("Calificaciones.dat","r");
    aux = fopen("auxiliar.dat","w");
    printf("\nIndique el ID de la sala: ");//ingresa los datos necesarios para guardar los datos de una sala especifica
    scanf("%s",&sala);
    strcat(sala,"\n");
    printf("\n[1]Biblioteca Figueres Ferrer\n[2]Learning Commons\nIndique la ubicacion de la sala: ");
    scanf("%s",&ubicacion);
    strcat(ubicacion,"\n");
    printf("\nIndique la calificacion de la sala: ");
    scanf("%s",&calificacion);
    strcat(calificacion,"\n");
    while(fgets(linea, 1024, (FILE*) Archivo)){//dentro de este ciclo se buscan los datos previamente ingresados y modifica la calificacion de la sala establecida
        if(strcmp(linea,sala)==0){
            fprintf(aux,"%s",linea);
            fgets(linea, 1024, (FILE*) Archivo);
            if(strcmp(linea,ubicacion)==0){
                fprintf(aux,"%s",linea);
                fgets(linea, 1024, (FILE*) Archivo);
                if(strcmp(linea,calificacion)!=0){
                    fprintf(aux,"%s",calificacion);
                }
            }
        }
        fprintf(aux,"%s",linea);
    }
    fclose(Archivo);
    fclose(aux);
}

void actualizarCalificaciones(char id[TAMANO],char ubicacion[TAMANO]){
    char linea[1024];
    int num;
    FILE *arch, *aux;
    arch = fopen("Calificaciones.dat","r");
    aux = fopen("auxiliar.dat","w");
    while(fgets(linea, 1024, (FILE*) arch)){//aqui se actualizan las calificaciones cada vez que se cancela una reserva
        if (strcmp(linea,id)==0){
            fprintf(aux,"%s",linea);
            fgets(linea, 1024, (FILE*) arch);
            if(strcmp(linea,ubicacion)==0){
                fprintf(aux,"%s",linea);
                fgets(linea, 1024, (FILE*) arch);//calificacion
                num = atoi(linea);
                num=num-1;
                fprintf(aux,"%d\n",num);
            }
        }
        fprintf(aux,"%s",linea);
    }
    fclose(arch);
    fclose(aux);
}

void pasarArchivosCalificaciones(){
    FILE *Archivo, *fich;
    char linea[1024];
    Archivo = fopen("auxiliar.dat", "r");
    fich = fopen("Calificaciones.dat", "w");
    while(fgets(linea, 1024, (FILE*) Archivo)){//aqui se pasan los datos del archivo auxiliar al archivo de calificaciones
        fprintf(fich,"%s",linea);
    }
}

int consultarSala(){
    char registro[1024],reserva[1024],calif[1024], sala[TAMANO];
    printf("Indique la sala que vaya a consultar: ");//aqui se toman los datos necesarios para encontrar la sala y mostrar su informacion
    scanf("%s",&sala);
    strcat(sala,"\n");
    FILE *fich;
    fich = fopen("Registro.dat", "r");
    FILE *arch;
    FILE *Archivo;
    Archivo = fopen("Calificaciones.dat","r");
    arch = fopen("Reserva.dat","r");
    while(fgets(registro, 1024, (FILE*) fich)) {//esto agarra linea por linea toodo el documento
        if(strcmp(registro,sala)==0){
            printf("%s", registro);//ID
            printf(fgets(registro, 1024, (FILE*) fich));//UBICACION     /aqui se obtienen los datos de la sala y se imprimen para poder visualizarlos
            printf(fgets(registro, 1024, (FILE*) fich));//RECURSOS
            printf(fgets(registro, 1024, (FILE*) fich));//ESTADO
            printf(fgets(registro, 1024, (FILE*) fich));//HORARIO DE OPERACION
            printf(fgets(registro, 1024, (FILE*) fich));//CAPACIDAD
            while(fgets(calif, 1024, (FILE*) Archivo)){
                if(strcmp(calif,sala)==0){
                    fgets(calif, 1024, (FILE*) Archivo);//UBICACION
                    printf(fgets(calif, 1024, (FILE*) Archivo));//CALIFICACION
                    while(fgets(reserva, 1024, (FILE*) arch)){
                        if(strcmp(reserva,sala)==0){
                            printf(fgets(reserva, 1024, (FILE*) arch));//ubicacion
                            printf("\n");
                            printf(fgets(reserva, 1024, (FILE*) arch));//fecha de la reserva
                            printf(fgets(reserva, 1024, (FILE*) arch));//hora inicio reserva
                            printf(fgets(reserva, 1024, (FILE*) arch));//hora fin reserva3
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

int crearReserva()
{
    FILE *Archivo;
    Archivo = fopen("Reserva.dat","ab");
    char estudiante[TAMANO],id[TAMANO],fecha[TAMANO], ubicacion[TAMANO];
    int inicio, final, prioridad;
    printf("\nIngrese el carnet del estudiante: ");//aqui se toman los datos necesarios para hacer una reserva de una sala especifica
    scanf("%s",&estudiante);

    mostrarSalas();
    printf("\nIngrese el ID de la sala: ");
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

    if(atenderReserva(strcat(id,"\n"), strcat(ubicacion,"\n"), strcat(fecha,"\n"), inicio, final)==0){//aqui se guardan los datos en caso de que no haya un choque de horario en las reservas
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

int consultarReserva()
{
    char carnet[TAMANO];
    printf("Indique el carnet del estudiante: ");
    scanf("%s",&carnet);
    strcat(carnet,"\n");
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
    while(fgets(linea, 1024, (FILE*) fich)){//aqui se obtienen datos necesarios para luego verificar que no hayan choques de horario con las reservas existentes
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


int modificarSala(){
    char linea[1024], recursos[TAMANO], estado[TAMANO], idSala[TAMANO], ubicacion[TAMANO];
    FILE *Archivo, *arch;
    printf("\nIndique la sala que desea modificar: ");//aqui se obtienen los datos para encontrar la sala que se desea modificar
    scanf("%s",&idSala);
    printf("\n[1]Biblioteca Figueres Ferrer\n[2]Learning Commons\nIndique la ubicacion de la sala: ");
    scanf("%s",&ubicacion);
    strcat(idSala,"\n");
    strcat(ubicacion,"\n");
    Archivo = fopen("Registro.dat", "r");
    arch = fopen("ModificacionesSala.dat", "w");
    printf("\nIndique los recursos actualizados de la sala: ");
    scanf("%s", &recursos);
    printf("\nIndique el estado actualizado de la sala: ");
    scanf("%s", &estado);
    while(fgets(linea, 1024, (FILE*) Archivo)){//dentro de este ciclo se busca la sala que se va a modificar y cambia los datos previos con los recientemente obtenidos
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

void pasarArchivosSala(){
    FILE *Archivo, *fich;
    char linea[1024];
    Archivo = fopen("ModificacionesSala.dat", "r");//esta funcion pasa los datos del archivo modificacionesSala a Registro
    fich = fopen("Registro.dat", "w");
    while(fgets(linea, 1024, (FILE*) Archivo)){
        fprintf(fich,"%s",linea);
    }
}

void cancelarReserva(){
    char carnet[TAMANO],idSala[TAMANO], ubicacion[TAMANO], fecha[TAMANO], linea[1024],estado[]="RESERVA CANCELADA\n";
    int inicio, final;
    printf("\nIndique el carnet del estudiante: ");//aqui se toman los datos de una reserva ya existente
    scanf("%s",&carnet);
    strcat(carnet,"\n");
    printf("\n Indique el ID de la sala: ");
    scanf("%s",&idSala);
    strcat(idSala,"\n");
    printf("\n[1]Biblioteca Figueres Ferrer\n[2]Learning Commons\nIndique la ubicacion de la sala: ");
    scanf("%s",&ubicacion);
    strcat(ubicacion,"\n");
    printf("\nIndique la fecha de la reserva: ");
    scanf("%s",&fecha);
    strcat(fecha,"\n");
    printf("\nIndique la hora de inicio de la reserva: ");
    scanf("%d",&inicio);
    printf("\nIndique la hora del final de la reserva: ");
    scanf("%d",&final);
    FILE *arch, *fich;
    arch = fopen("Reserva.dat", "r");
    fich = fopen("Cancelaciones.dat", "w");
    while(fgets(linea, 1024, (FILE*) arch)){//aqui se busca la reserva para cancelarla, se agrega a la reserva un mensaje que dice RESERVA CANCELADA
        if(strcmp(linea,carnet)==0){//linea = carnet estudiante
            fprintf(fich,"%s",linea);
            fgets(linea, 1024, (FILE*) arch);//id sala
            if(strcmp(linea,idSala)==0){//linea = id sala
                fprintf(fich,"%s",linea);
                fgets(linea, 1024, (FILE*) arch);//ubicacion
                if(strcmp(linea,ubicacion)==0){
                    fprintf(fich,"%s",linea);
                    fgets(linea, 1024, (FILE*) arch);//fecha
                    if(strcmp(linea,fecha)==0){
                        fprintf(fich,"%s",linea);
                        fgets(linea, 1024, (FILE*) arch);//hora inicio
                        if(atoi(linea)==inicio){
                            fprintf(fich,"%s",linea);
                            fgets(linea, 1024, (FILE*) arch);//hora final
                            if(atoi(linea)==final){
                                fprintf(fich,"%s",linea);
                                fgets(linea, 1024, (FILE*) arch);//prioridad
                                fprintf(fich,"%s",linea);
                                fprintf(fich,"%s",estado);
                            }
                        }
                    }
                }
            }
        } else{
            fprintf(fich,"%s",linea);
        }
    }
    fclose(arch);
    fclose(fich);
    actualizarCalificaciones(idSala,ubicacion);
}

void pasarArchivosReserva(){
    FILE *Archivo, *fich;
    char linea[1024];
    Archivo = fopen("Cancelaciones.dat", "r");//esta funcion pasa los datos del archivo cancelaciones al archivo de reserva
    fich = fopen("Reserva.dat", "wb");
    while(fgets(linea, 1024, (FILE*) Archivo)){
        fprintf(fich,"%s",linea);
    }
    fclose(Archivo);
    fclose(fich);
}

int BuscarEstudiante(){
    char nom[20], linea[1024];
    FILE *ptr;
    ptr = fopen("Estudiante.txt", "r");
    if (ptr==NULL)
    {
        printf("NO");
        return 0;
    }
    printf("\t\t\tBUSCAR UN ESTUDIANTE\n");
    printf("Inserte el nombre del estudiante que desea buscar: ");//aqui se toma el nombre del estudiante para buscarlo en los archivos e imprimir sus datos
    scanf("%s", &nom);
    strcat(nom,"\n");
    while(fgets(linea,1024,ptr))
    {
        if(strcmp(linea,nom)==0){
            printf("%s",linea);//nombre
            fgets(linea,1024,ptr);
            printf("%s",linea);
            fgets(linea,1024,ptr);
            printf("%s",linea);//nombre
            fgets(linea,1024,ptr);
            printf("%s",linea);//nombre
            fgets(linea,1024,ptr);
            printf("%s",linea);//nombre

        }
    }
    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void registroIncidentes()
{
    FILE*ptr;
    ptr = fopen("INCIDENTES.txt","a+");//aqui se ingresan los datos de un incidente dentro de una sala
    int contador=0;
    printf("\t\t\tREGISTRAR UN INCIDENTE\n");
    printf("Indique la sala que desea registrar: ");
    scanf("%s", &inci.sala);
    printf("Indique el codigo de reservacion de la sala: ");
    scanf("%s", &inci.codigo);
    printf("De una palabra clave para describir el incidente: ");
    scanf("%s", &inci.situacion);
    printf("Indique la fecha (debe estar en formato ddmmaa): ");
    scanf("%s", &inci.fecha);
    printf("\nSALA: %s\nCODIGO: %s\nINCIDENTE: %s\nFECHA: %s%", inci.sala, inci.codigo, inci.situacion, inci.fecha);
    fwrite(&inci,sizeof(inci), 1, ptr);
    printf("\n\nIncidente registrado, gracias por su colaboracion\n\n");
    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void consultaPorSala(){
    int contador =0 ;
    char sala[30];
    FILE *ptr;
    ptr = fopen("INCIDENTES.txt","r");//aqui se muestran todos los incidentes registrados en una sala especifica
    printf("\t\t\tBUSQUEDA POR SALA\n");
    printf("Ingrese el nombre de la sala que desea ver: ");
    scanf("%s", &sala);
    while(!feof(ptr)){
        fread(&inci,sizeof(inci),1,ptr);
        if(strstr(sala,inci.sala)!=NULL){
            printf("\nSALA: %s \nCODIGO DE SALA: %s \nINCIDENTE: %s \nFECHA: %s \n",inci.sala,inci.codigo,inci.situacion,inci.fecha);
        }
    }
    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void consultaPorCalendario(){
    int x;
    int inicio;
    int fin;
    FILE *ptr;
    ptr = fopen("INCIDENTES.txt","r");//aqui se muestran todos los incidentes que sucedieron en una fecha especifica
    printf("\t\t\tBUSQUEDA POR CALENDARIO\n");
    printf("Indique la fecha de inicio (debe estar en formato ddmmaa): ");
    scanf("%d", &inicio);
    printf("Indique la fecha de finalizacion (debe estar en formato ddmmaa: ");
    scanf("%d", &fin);
    while(!feof(ptr)){
        fread(&inci, sizeof(inci),1,ptr);
        x = atoi(inci.fecha);
        if(x>=inicio && x<=fin);
        {
            printf("\n\nSALA: %s \nCODIGO: %s\nINCIDENTE: %s\nFECHA: %s", inci.sala, inci.codigo, inci.situacion, inci.fecha);
        }
    }

    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void busqueda()
{
    int eleccion;// esta funcion proporciona un menu para mostrar los incidentes registrados
    printf("\t\t\tOPCIONES DE BUSQUEDA\n");
    printf("\n[1] Busqueda por sala");
    printf("\n[2] Busqueda por calendario");
    printf("\nEscoja el metodo que prefiera: ");
    scanf("%d", &eleccion );
    if (eleccion == 1)
    {
        consultaPorSala();
    }else if (eleccion==2)
    {
        consultaPorCalendario();
    }
}

int topSalas()
{
    int menor = 0;
    char primer[100];
    char segundo[100];
    char tercer[100];
    char cuarto[100];
    char quinto[100];
    FILE* ptr;
    ptr = fopen("Reservas.txt", "r");
    fread(&reserva, sizeof(reserva),1, ptr);//esta funcion pretende llevan cuenta de cuales son las 5 salas mas utilizadas
    while(!feof(ptr))
    {
        if(reserva.contador> menor)
        {
            if (reserva.contador>atoi(primer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(primer, segundo);
                strcpy(reserva.id, primer);
            }else if(reserva.contador<atoi(primer) && reserva.contador>atoi(segundo))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(reserva.id, segundo);
            }else if(reserva.contador<atoi(segundo) && reserva.contador>atoi(tercer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(reserva.id, tercer);
            }else if(reserva.contador<atoi(tercer) && reserva.contador>atoi(cuarto))
            {
                strcpy(cuarto,quinto);
                strcpy(reserva.id, cuarto);
            }else if(reserva.contador<atoi(tercer) && reserva.contador>atoi(quinto))
            {
                strcpy(reserva.id, quinto);
            }
        }
        printf("\n[1] %s", primer);//y aqui se muestran las salas mas utilizadas
        printf("\n[2] %s", segundo);
        printf("\n[3] %s", tercer);
        printf("\n[4] %s", cuarto);
        printf("\n[5] %s", quinto);
        fclose(ptr);
        int volver;
        printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
        scanf("%d", &volver);
        if (volver == 1)
        {
            return main();
        }else{exit(0);}
    }
}

void topHorarios()
{
    int menor = 0;
    char primer;
    char segundo[100];
    char tercer[100];
    char cuarto[100];
    char quinto[100];
    FILE* ptr;
    ptr = fopen("Reservas.txt", "r");//esta funcion pretende identificar cuales son los horarios mas frecuentados de las salas
    fread(&reserva, sizeof(reserva),1, ptr);
    while(!feof(ptr))
    {
        if(reserva.contador> menor)
        {
            if (reserva.contador>atoi(primer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(primer, segundo);
                strcpy(reserva.inicio, primer);
            }else if(reserva.contador<atoi(primer) && reserva.contador>atoi(segundo))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(reserva.inicio, segundo);
            }else if(reserva.contador<atoi(segundo) && reserva.contador>atoi(tercer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(reserva.inicio, tercer);
            }else if(reserva.contador<atoi(tercer) && reserva.contador>atoi(cuarto))
            {
                strcpy(cuarto,quinto);
                strcpy(reserva.inicio, cuarto);
            }else if(reserva.contador<atoi(tercer) && reserva.contador>atoi(quinto))
            {
                strcpy(reserva.inicio, quinto);
            }
        }
    }
    printf("\n[1] %s", primer);//aqui muestra los resultados identificados
    printf("\n[2] %s", segundo);
    printf("\n[3] %s", tercer);
    printf("\n[4] %s", cuarto);
    printf("\n[5] %s", quinto);
    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void carreraConReserva()
{
    int x;
    FILE*ptr;
    FILE*Archivo;
    ptr= fopen("nuevo.txt", "w");
    Archivo= fopen("Reserva.txt", "r");
    fread(&reserva, sizeof(reserva), 1, Archivo);
    fread(&est, sizeof(est), 1, ptr);
    while(!feof(Archivo))
    {
        while(!feof(ptr))
        {
            if (strstr(reserva.estudiante, est.nombre)!=NULL)
            {
                x = atoi(est.contador);
                x++;
            }
        }
    }
    fclose(ptr);
    fclose(Archivo);
}

void topCarreras()
{
    int menor = 0;
    char primer;
    char segundo[100];
    char tercer[100];
    char cuarto[100];
    char quinto[100];
    FILE* ptr;
    ptr = fopen("Reservas.txt", "r");
    fread(&reserva, sizeof(reserva),1, ptr);//aqui se trata de definir cuales carreras del TEC frecuentan mas las salas
    while(!feof(ptr))
    {
        if(est.contador> atoi(menor))
        {
            if (est.contador>atoi(primer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(primer, segundo);
                strcpy(est.carrera, primer);
            }else if(est.contador<atoi(primer) && est.contador>atoi(segundo))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(est.carrera, segundo);
            }else if(est.contador<atoi(segundo) && est.contador>atoi(tercer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(est.carrera, tercer);
            }else if(est.contador<atoi(tercer) && est.contador>atoi(cuarto))
            {
                strcpy(cuarto,quinto);
                strcpy(est.carrera, cuarto);
            }else if(est.contador<atoi(tercer) && est.contador>atoi(quinto))
            {
                strcpy(est.carrera, quinto);
            }
        }
        printf("\n[1] %s", primer);// aqui se muestra un top 5 de las carreras que mas frecuentan las salas
        printf("\n[2] %s", segundo);
        printf("\n[3] %s", tercer);
        printf("\n[4] %s", cuarto);
        printf("\n[5] %s", quinto);
        fclose(ptr);
        int volver;
        printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
        scanf("%d", &volver);
        if (volver == 1)
        {
            return main();
        }else{exit(0);}
    }
}


int topCalificaciones()
{
    int menor = 0;
    char primer;
    char segundo[100];
    char tercer[100];
    char cuarto[100];
    char quinto[100];
    FILE* ptr;
    ptr = fopen("Registro.txt", "r");// esta funcion pretende buscar cuales son las 5 calificaciones mas comunes entre todas las salas
    fread(&sala, sizeof(sala),1, ptr);
    while(!feof(ptr))
    {
        if(sala.calificacion> menor)
        {
            if (sala.calificacion>atoi(primer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(primer, segundo);
                strcpy(sala.id, primer);
            }else if(sala.calificacion<atoi(primer) && sala.calificacion>atoi(segundo))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(segundo,tercer);
                strcpy(sala.id, segundo);
            }else if(sala.calificacion<atoi(segundo) && sala.calificacion>atoi(tercer))
            {
                strcpy(cuarto,quinto);
                strcpy(tercer, cuarto);
                strcpy(sala.id, tercer);
            }else if(sala.calificacion<atoi(tercer) && sala.calificacion>atoi(cuarto))
            {
                strcpy(cuarto,quinto);
                strcpy(sala.id, cuarto);
            }else if(sala.calificacion<atoi(tercer) && sala.calificacion>atoi(quinto))
            {
                strcpy(sala.id, quinto);
            }
        }
    }
    printf("\n[1] %s", primer);//aqui se muestran los resultados identificados previamente
    printf("\n[2] %s", segundo);
    printf("\n[3] %s", tercer);
    printf("\n[4] %s", cuarto);
    printf("\n[5] %s", quinto);
    fclose(ptr);
    int volver;
    printf("\n\nSi desea volver al menu principal presione 1, presione cualquier otra tecla para salir: \n");
    scanf("%d", &volver);
    if (volver == 1)
    {
        return main();
    }else{exit(0);}
}

void analisisDatos()
{
    int eleccion;
    printf("\t\t\tOPCIONES DE ANALISIS DE DATOS\n");//esta funcion muestra un menu para visualizar los tops de salas mas utilizadas, calificacion mas comunes, las carreras que usan mas salas, cual sala tiene mejor calificacion
    printf("\n[1] TOP 5 SALAS MAS UTILIZADAS");
    printf("\n[2] TOP 5 HORARIOS MAS UTILIZADOS");
    printf("\n[3] TOP 5 CARRERAS QUE MAS UTILIZAN SALAS");
    printf("\n[4] TOP 5 SALAS CON MEJOR CALIFICACION");
    printf("\nElija el dato que desea consultar: ");
    scanf("%d", eleccion);
    if (eleccion ==1)
    {
        topSalas();
    }else if (eleccion ==2)
    {
        topHorarios();
    }else if (eleccion==3)
    {
        topCarreras();
    }else if (eleccion ==4)
    {
        topCalificaciones();
    }else{printf("Eleccion invalida, el sistema le expulsara");
        exit(0);}
}

int main()
{
    int opcion;
    printf("\n\n\t\t\tPROYECTO PROGRAMADO #1\n\n");//este es el menu principal, donde se elige que funcion desea implementar, con opciones limitadas
    printf("[1] Agregar un estudiante \n");
    printf("[2] Consultar un estudiante \n");
    printf("[3] Agregar una sala \n");
    printf("[4] Modificar los datos de una sala \n");
    printf("[5] Calificar una sala \n");
    printf("[6] Consultar una sala \n");
    printf("[7] Crear una reserva \n");
    printf("[8] Consultar reservas de un estudiante \n");
    printf("[9] Cancelar una reserva \n");
    printf("[10] Registrar un incidente \n");
    printf("[11] Consultar incidentes \n");
    printf("[12] Analisis de datos \n");
    printf("Escoja la opcion que desea: \n");
    scanf("%d", &opcion);
    if (opcion==1)
    {
        agregarEstudiante();
    }else if (opcion==2)
    {
        BuscarEstudiante();
    }else if (opcion ==3)
    {
        agregarSala();
    }else if (opcion ==4)
    {
        modificarSala();
        pasarArchivosSala();
    }else if (opcion==5)
    {
        calificarSala();
        pasarArchivosCalificaciones();
    }else if (opcion == 6)
    {
        consultarSala();
    }else if (opcion ==7)
    {
        crearReserva();
    }else if (opcion ==8)
    {
        consultarReserva();
    }else if (opcion == 9)
    {
        cancelarReserva();
        pasarArchivosReserva();
    }else if (opcion ==10)
    {
        registroIncidentes();
    }else if (opcion ==11)
    {
        busqueda();
    }else if (opcion ==12)
    {
        analisisDatos();
    }else
    {
        printf("Opcion invalida, el sistema le expulsara");
    }
    return 0;
}
