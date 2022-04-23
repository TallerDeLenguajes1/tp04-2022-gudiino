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


int main(){
    int nTareas;
    Tarea **listaTareas, **TareasRealizadas;
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
    printf("\nTareas cargadas pendientes");
    MostrarTareas(listaTareas, nTareas);
    printf("\n=========================================");
    printf("\nTareas cargadas realizadas");
    MostrarTareas(TareasRealizadas, nTareas);
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
        listaTareas[i]->TareaID=i;
        printf("Tarea numero %d", i+1);
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
        printf("\nTarea numero: %d", pTarea->TareaID+1);
        printf("\nDescripcion: ");
        puts(pTarea->Descripcion);
        printf("Duracion: %d", pTarea->Duracion);
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
            cont++;
            TareasRealizadas[cont-1] = (Tarea *) malloc(sizeof(Tarea));
            *TareasRealizadas[cont-1] = *listaTareas[i];
            free(listaTareas[i]);
            listaTareas[i]=NULL;
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
        printf("Tarea numero %d", i+1);
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