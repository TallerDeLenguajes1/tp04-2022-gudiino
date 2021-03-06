#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareas(Tarea **listaTareas, int nTareas);
void MostrarUnaTarea(Tarea *ptarea);
Tarea **ControlTareas(Tarea **TareasRealizadas, Tarea **listaTareas, int nTareas);
void MostrarTareas(Tarea **listaTareas, int nTareas);
void LiberacionMemoria(Tarea **lista, int nTareas);
Tarea *BusquedaPorPalabra(Tarea **Lista, int nTareas, char *palabraTareaBuscar);
Tarea *BusquedaPorId(Tarea **Lista,  int nTareas, int idTareaBuscar);

int main(){
    int nTareas, idTareaBuscar, opBusca;
    char *palabraTareaBuscar, *Buff;
    Tarea **listaTareas, **TareasRealizadas, *tareaAbuscar;
    printf("\n=========================================");
    printf("\nIngrese la cantidad de tareas a cargar: ");
    scanf("%d", &nTareas);
    listaTareas = (Tarea **)malloc(nTareas*sizeof(Tarea *));
    cargarTareas(listaTareas, nTareas);
    printf("\n=========================================");
    printf("\nControl de tareas cargadas");
    TareasRealizadas = (Tarea **)malloc(nTareas*sizeof(Tarea *));
    TareasRealizadas = ControlTareas(TareasRealizadas, listaTareas, nTareas);
    printf("\n=========================================");
    printf("\nTareas cargadas realizadas");
    MostrarTareas(TareasRealizadas, nTareas);
    printf("\n=========================================");
    printf("\nTareas cargadas pendientes");
    MostrarTareas(listaTareas, nTareas);
    printf("\n=========================================");
    ////////////////////////////////
    printf("\nIngrese la opcion de busqueda deseada:");
    printf("\n1 -> Busqueda por palabra clave");
    printf("\n2 -> Busqueda por Id de tarea");
    printf("\nSeleccion: ");
    scanf("%d", &opBusca);
    if (opBusca==1)
    {
        printf("\nIngrese la palabra clave para buscar la de tarea: ");
        Buff= (char *) malloc(50*sizeof(char));
        fflush(stdin);
        gets(Buff);
        palabraTareaBuscar = (char *) malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(palabraTareaBuscar,Buff);
        free(Buff);
        tareaAbuscar = BusquedaPorPalabra(listaTareas, nTareas, palabraTareaBuscar);
    }
    if (opBusca==2)
    {
        printf("\nIngrese el numero de tarea a buscar: ");
        scanf("%d", &idTareaBuscar);
        tareaAbuscar = BusquedaPorId(listaTareas, nTareas, idTareaBuscar);
    }
    if (tareaAbuscar==NULL)
    {
        switch (opBusca)
        {
        case 1:
            tareaAbuscar=BusquedaPorPalabra(TareasRealizadas, nTareas, palabraTareaBuscar);
            break;
        case 2:
             tareaAbuscar=BusquedaPorId(TareasRealizadas, nTareas, idTareaBuscar);        
            break;
        }
       if (tareaAbuscar==NULL)
       {
           printf("\nNo se ecnontraron coincidencias.");
       }else{
           printf("\n.....................\n");
           printf("\nLa tarea buscada se encuenta realizada");
           MostrarUnaTarea(tareaAbuscar);
       }
    }else{
        printf("\n.....................\n");
        printf("\nLa tarea buscada se encuenta pendiente");
        MostrarUnaTarea(tareaAbuscar);
    } 
    //liberacion de todas las memorias
    LiberacionMemoria(listaTareas, nTareas);
    free(listaTareas);
    LiberacionMemoria(TareasRealizadas, nTareas);
    free(TareasRealizadas);
    return 0;
}
void cargarTareas(Tarea **listaTareas, int nTareas)
{
    char *Buff; 
    Buff= (char *) malloc(200*sizeof(char));
    srand(time(NULL));
    printf("\nIngrese los datos de las tareas");
    for (int i = 0; i < nTareas; i++)
    {
        printf("\n.....................\n");
        listaTareas[i]=(Tarea *)malloc(sizeof(Tarea));
        listaTareas[i]->TareaID=i+1;
        printf("Id tarea %d", i+1);
        printf("\nDescripcion: "); 
        fflush(stdin);
        gets(Buff);
        listaTareas[i]->Descripcion=(char *)malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(listaTareas[i]->Descripcion, Buff);
        listaTareas[i]->Duracion = rand()%90+10;
        printf("Duracion: %d", listaTareas[i]->Duracion);
    }
    free(Buff);
}
void MostrarUnaTarea(Tarea *pTarea)
{
    if (pTarea!=NULL)
    {
        printf("\nId tarea: %d", pTarea->TareaID);
        printf("\nDescripcion: ");
        puts(pTarea->Descripcion);
        printf("Duracion: %d Hs", pTarea->Duracion);
    }else{
        printf("\nNo hay tarea designada");
    }
}

Tarea **ControlTareas(Tarea **TareasRealizadas, Tarea **listaTareas, int nTareas)
{
    int cont=0, aux;
    printf("\n\nIndique si realizo la siguientes tareas");
    for (int i = 0; i < nTareas; i++)
    {
        printf("\n.....................");
        MostrarUnaTarea(listaTareas[i]);
        printf("\n¿Se realizo la tarea?");
        printf("\n1 -> SI");
        printf("\n2 -> NO");
        printf("\nSeleccion: ");
        scanf("%d", &aux);
        if (aux==1)
        {
            TareasRealizadas[cont] = (Tarea *) malloc(sizeof(Tarea));
            *TareasRealizadas[cont] = *listaTareas[i];
            free(listaTareas[i]);
            listaTareas[i]=NULL;
            cont++;
        }
    }
    for (int i = cont; i < nTareas; i++)
    {
        TareasRealizadas[i] = NULL;
    }
    return TareasRealizadas;
}

void MostrarTareas(Tarea **listaTareas, int nTareas)
{
    for (int i = 0; i < nTareas; i++)
    {
        printf("\n.....................\n");
        printf("Casilla %d", i+1);
        MostrarUnaTarea(listaTareas[i]);
    }
}
void LiberacionMemoria(Tarea **lista, int nTareas)
{
    for (int i = 0; i < nTareas; i++)
    {
        free(lista[i]);
    } 
}

Tarea *BusquedaPorPalabra(Tarea **Lista, int nTareas, char *palabraTareaBuscar)
{
    int cont=0, tarea=0;
    while (cont < nTareas && tarea == 0)
    {
        if (Lista[cont]!= NULL && strstr(Lista[cont]->Descripcion, palabraTareaBuscar)!=NULL)//funcion strstr compara de la cad2 esta dentro de la cad1
        {
            return Lista[cont]; 
            tarea=1;
        }     
        cont++;
    }
    if (cont == nTareas && Lista[cont-1]==NULL)
    {
        return NULL; 
    }

}

Tarea *BusquedaPorId(Tarea **Lista, int nTareas, int idTareaBuscar)
{
    int cont=0, tarea=0;
    while (cont < nTareas && tarea == 0)
    {
        if (Lista[cont]!= NULL && Lista[cont]->TareaID==idTareaBuscar)
        {
            return Lista[cont]; 
            tarea=1;
        }     
        cont++;
    }
    if (cont == nTareas && Lista[cont-1]==NULL)
    {
        return NULL; 
    }       
}