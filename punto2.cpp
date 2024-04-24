/*--    en este archivo se resuelve todo lo pedido en el práctico N°4 de taller de lenguajes I    --*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TAMA 30

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
};

struct Nodo
{
    Tarea T;
    Nodo *siguiente;
};


Nodo *crearTarea();
Nodo *agregarTarea(Nodo *tarea, int id, char *descripcion, int duracion);
bool tareaRealizada(Nodo** pendiente, Nodo** realizada, int id);
int longitud(Nodo* tarea);
void mostraTareas(Nodo* tarea);
void mostrarTareasPorID(Nodo* tareaP, Nodo* tareaR, int id);
void liberarMemoria(Nodo* tarea);

int main()
{
    Nodo* TareasPendientes = crearTarea();                                    //creo la lista de tareas pendientes
    Nodo* TareasRealizadas = crearTarea();                                    //creo la lista de tareas realizadas

    int ID = 1000;
    int auxID;
    char descrip[TAMA];
    int duracion;
    short int seguirCargando;
    short int accion;
    short int seguirAccion = 1;
    while(seguirAccion)                                                       //pregunto las acciones siempre que no se haya elegido la opción de terminar proceso
    {
        printf("\nque desea hacer?:\n\t1. agregar tarea pendiente\n\t2. elegir tarea realizada\n\t3. mostrar todas las tareas\n\t4. buscar tarea por id\n\t5. terminar proceso\n");
        scanf("%d", &accion);
        switch (accion)                                                       //cada "interfaz" pedida en el enunciado del práctico es un caso del switch
        {
        case 1:                                                               //agrego tarea, mientras el usuario quiera seguir agregando
            do
            {
                printf("agregar tarea (id: %d)\n\t", ID);
                printf("Descripcion: ");
                fflush(stdin);
                gets(descrip);
                char *descripcion = new char[strlen(descrip) + 1];
                strcpy(descripcion, descrip);
                printf("\nDuracion: ");
                scanf("%d", &duracion);
                TareasPendientes = agregarTarea(TareasPendientes, ID, descripcion, duracion);
                ID++;
                printf("desea seguir cargando tareas?\n0. NO\n1. SI\n");
                scanf("%d", &seguirCargando);

            }while(seguirCargando);
            break;
        
        case 2:                                                               //marcar una tarea pendiente como realizada
            printf("ingrese el ID de la tarea realizada: ");
            scanf("%d", &auxID);
            if(tareaRealizada(&TareasPendientes, &TareasRealizadas, auxID))
            {
                printf("tarea realizada con exito\n");
            }
            else 
            {
                printf("no se encontro una tarea pendiente cuyo ID es %d\n", auxID);
            }
            break;

        case 3:                                                               //muestro las listas de tareas con la función mostraTareas
            printf("Tareas pendientes:\n\n");
            mostraTareas(TareasPendientes);
            printf("\nTareas realizadas:\n\n");
            mostraTareas(TareasRealizadas);
            printf("\n\n");
            break;

        case 4:                                                               //buscar una tarea en cualquiera de las dos listas por id
            printf("ingrese el ID de la tarea que desea buscar: ");
            scanf("%d", &auxID);
            mostrarTareasPorID(TareasPendientes, TareasRealizadas, auxID);
            break;

        case 5:                                                               //libero la memoria reservada del heap, digo que el proceso se finalizó y hago que el while termine
            liberarMemoria(TareasPendientes);
            liberarMemoria(TareasRealizadas);
            printf("proceso finalizado");
            seguirAccion = 0;
            break;
        }
    }
    return 0;
}


Nodo *crearTarea()
{
    Nodo* nTarea = NULL;
    return nTarea;
}


Nodo *agregarTarea(Nodo *tarea, int id, char *descripcion, int duracion)
{
    Nodo *aux = tarea;                                                        //guardo el principio de la lista en una variable auxiliar
    Nodo *nTarea = new Nodo;                                                  //creo un nuevo nodo
    nTarea->siguiente = aux;                                                  //hago que el nodo creado apunte al principio de la lista
    nTarea->T.TareaID = id;                                                   
    nTarea->T.Descripcion = descripcion;                                      //guardo los valores ingresados al nuevo nodo
    nTarea->T.Duracion = duracion;

    return nTarea;                                                            //retorno el nuevo nodo, que es el principio de la lista
}

int longitud(Nodo* tarea)
{
    int i=0;
    while (tarea != NULL)
    {
        i++;
        tarea = tarea->siguiente;
    }
    return i;
}

bool tareaRealizada(Nodo** pendiente, Nodo** realizada, int id)
{
    Nodo* auxp = *pendiente;                                                //guardo la dirección inicial de pendiente
    Nodo* pendAnterior = *pendiente;                                        //defino un puntero anterior al pendiente, que al principio es igual

    while (id != (*pendiente)->T.TareaID && *pendiente != NULL)             //itero hasta que el id coincida con el ingresado o se me terminen los nodos
    {
        pendAnterior = *pendiente;                                          //guardo la dirección actual en puntero anterior
        *pendiente = (*pendiente)->siguiente;                               //avanzo por la lista con el puntero referenciado
    }

    if(*pendiente != NULL)                                                  //condición que se hace sólo si se encontró el id en la lista
    {
        Nodo *auxr = *realizada;                                            //guardo la dirección inicial de realizada
        *realizada = *pendiente;                                            //apunto la lista realizada a la tarea pendiente que quiero mover (con la que se hizo coincidencia)
        if (pendAnterior != *pendiente)                                     //hago esta evaluación por si el id coincide al instante, es decir, no entra al while
        {
            *pendiente = pendAnterior;                                      //como son distintos los valores, guardo el valor del puntero anterior en el puntero referenciado
            (*pendiente)->siguiente = (*realizada)->siguiente;              /*hago que el puntero al nodo siguiente al anterior del que quiero mover sea igual al siguiente del nodo al que apunta realizada (la tarea que quiero mover) 
                                                                            A esto lo hago usando el puntero referenciado para que la edición se guarde fuera de la función*/
            *pendiente = auxp;                                              //apunto el puntero referenciado al principio de la lista
        }
        else                                                                //si NO se hizo ninguna iteración en el while
        {
            *pendiente = (*pendiente)->siguiente;                           //avanzo por la lista una sola vez

        }
        (*realizada)->siguiente = auxr;                                     //hago que el nodo que quiero mover apunte al principio de la lista de realizadas
        return true;
    }
    else 
    {
        return false;
    }
}

void mostraTareas(Nodo* tarea)
{
    while(tarea != NULL)
    {
        printf("ID: %d\ndescripcion: %s\nduracion: %d\n\n", tarea->T.TareaID, tarea->T.Descripcion, tarea->T.Duracion);
        tarea = tarea->siguiente;
    }    
}

void mostrarTareasPorID(Nodo* tareaP, Nodo* tareaR, int id)
{
    int esTareaP = 0;                                                       //creo una variable para comprobar si es que el id está en la lista de pendientes
    while(tareaP != NULL && tareaP->T.TareaID != id)                        //itero hasta que el id coincida o se me terminen los nodos
    {
        tareaP = tareaP->siguiente;                                         //avanzo por la lista de pendientes
    }

    if(tareaP != NULL)                                                      //si salió de la iteración porque encontró el id en la lista pendientes
    {
        esTareaP = 1;                                                       //digo que si es tarea pendiente
    }

    if(!esTareaP)                                                           //si no es tarea pendiente
    {
        while(tareaR != NULL && tareaR->T.TareaID != id)                    //itero hasta que el id coincida o se me terminen los nodos
        {
            tareaR = tareaR->siguiente;                                     //avanzo por la lista de realizadas
        }
        if(tareaR != NULL)                                                  //si salió de la iteración porque encontró el id en la lista realizadas
        {
            printf("tarea realizada:\n\n");                                 //digo que la tarea está realizada
            printf("ID: %d\ndescripcion: %s\nduracion: %d\n\n", tareaR->T.TareaID, tareaR->T.Descripcion, tareaR->T.Duracion);  //muestro la tarea realizada
        }   
        else                                                                //si no es tarea realizada, ni tampoco es pendiente
        {
            printf("no se encontro tarea cuyo id es %d\n", id);             //imprimo que no se encontró la tarea con el id ingresado
        }
    }
    else                                                                    //si es tarea pendiente
    {
        printf("tarea pendiente:\n\n");                                     //digo que es tarea pendiente
        printf("ID: %d\ndescripcion: %s\nduracion: %d\n\n", tareaP->T.TareaID, tareaP->T.Descripcion, tareaP->T.Duracion);  //muestro la tarea pendiente
    }
}

void liberarMemoria(Nodo* tarea)
{
    Nodo* aux;                                  //creo un nodo auxiliar para guardar la dirección de los nodos de la lista
    while(tarea != NULL)                        //itero hasta que me quede sin nodos
    {
        aux = tarea;                            //guardo la dirección del nodo actual de la lista
        free(tarea->T.Descripcion);             //libero el puntero a la cadena descripción que reservé al momento de ingresar dicha cadena
        tarea = tarea->siguiente;               //avanzo por la lista
        delete(aux);                            //libero la memoria del nodo actual de la lista
    }
}