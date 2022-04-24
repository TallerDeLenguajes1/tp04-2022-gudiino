#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea; 

struct TNODO{
    Tarea *dato;
    struct TNODO *siguiente;
}typedef Lista;
Lista *crearLista();
Lista *InsertarTarea(Lista *ListaX, Tarea *NuevaTarea);
Lista *cargarTareas(Lista *ListaX, int nTareas);
Lista *ControlTareas(Lista *TareasRealizadas, Lista *listaTareas);
void MostrarUnaTarea(Tarea *pTarea);
Lista *BorrarTareaX(Lista *listaX, Tarea *tareaRealizada);
void MostrarTareas(Lista *listaTareas);
Tarea *BusquedaPorPalabra(Lista *ListaX, char *palabraTareaBuscar);
Tarea *BusquedaPorId(Lista *ListaX, int idTareaBuscar);
Lista *borrarPrimerElemento(Lista *ListaX);

int main(){
    Lista *ListaTareas, *TareasRealizadas;
    int nTareas, opBusca, idTareaBuscar;
    char *Buff, *palabraTareaBuscar; 
    Tarea *tareaAbuscar;
    printf("\n=========================================");
    ListaTareas=crearLista();
    printf("\nIngrese la cantidad de tareas a cargar: ");
    scanf("%d", &nTareas);
    // listaTareas = (Tarea **)malloc(nTareas*sizeof(Tarea *));
    ListaTareas = cargarTareas(ListaTareas, nTareas);
    printf("\n=========================================");
    printf("\nControl de tareas cargadas");
    TareasRealizadas=crearLista();
    TareasRealizadas = ControlTareas(TareasRealizadas, ListaTareas);
    printf("\n=========================================");
    printf("\nTareas cargadas realizadas");
    MostrarTareas(TareasRealizadas);
    printf("\n=========================================");
    printf("\nTareas cargadas pendientes");
    MostrarTareas(ListaTareas);
    printf("\n=========================================");
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
        tareaAbuscar = BusquedaPorPalabra(ListaTareas, palabraTareaBuscar);
    }
    if (opBusca==2)
    {
        printf("\nIngrese el numero de tarea a buscar: ");
        scanf("%d", &idTareaBuscar);
        tareaAbuscar = BusquedaPorId(ListaTareas, idTareaBuscar);
    }
    if (tareaAbuscar==NULL)
    {
        switch (opBusca)
        {
        case 1:
            tareaAbuscar=BusquedaPorPalabra(TareasRealizadas, palabraTareaBuscar);
            break;
        case 2:
             tareaAbuscar=BusquedaPorId(TareasRealizadas, idTareaBuscar);        
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
    while (ListaTareas!=NULL)
   {
       ListaTareas=borrarPrimerElemento(ListaTareas);
   }
   while (TareasRealizadas!=NULL)
   {
       TareasRealizadas=borrarPrimerElemento(TareasRealizadas);
   }
   
    return 0;
}
//*************************************************************************
Lista *crearLista()
{
    return NULL;
}

Lista *InsertarTarea(Lista *ListaX, Tarea *NuevaTarea)
{
    struct TNODO *nuevo;
    nuevo = (struct TNODO*)malloc(sizeof(struct TNODO));
    nuevo->dato = (struct Tarea*)malloc(sizeof(struct Tarea));
    nuevo->dato->TareaID = NuevaTarea->TareaID;
    nuevo->dato->Descripcion = NuevaTarea->Descripcion;
    nuevo->dato->Duracion = NuevaTarea->Duracion;
    nuevo->siguiente = ListaX;
    ListaX = nuevo;
    return ListaX;
}

Lista *cargarTareas(Lista *ListaX, int nTareas)
{
    char *Buff;
    Tarea *nuevo;
    nuevo=(Tarea *) malloc(sizeof(Tarea));
    Buff= (char *) malloc(250*sizeof(char));
    srand(time(NULL));
    printf("\nIngrese los datos de las tareas");
    for (int i = 0; i < nTareas; i++)
    {
        printf("\n.....................\n");
        nuevo->TareaID=i+1;
        printf("Id tarea %d", i+1);
        printf("\nDescripcion: "); 
        fflush(stdin);
        gets(Buff);
        nuevo->Descripcion=(char *)malloc((strlen(Buff)+1)*sizeof(char));
        strcpy(nuevo->Descripcion, Buff);
        nuevo->Duracion = rand()%90+10;
        printf("Duracion: %d", nuevo->Duracion);
        ListaX=InsertarTarea(ListaX,nuevo);
    }
    free(Buff);
    free(nuevo);
    return ListaX;
}

Lista *ControlTareas(Lista *TareasRealizadas, Lista *listaTareas)
{
    int aux;
    Lista *pTarea;
    pTarea=listaTareas;
    printf("\n\nIndique si realizo la siguientes tareas");
    while (pTarea!=NULL)
    {
        printf("\n.....................");
        MostrarUnaTarea(pTarea->dato);
        printf("\n¿Se realizo la tarea?");
        printf("\n1 -> SI");
        printf("\n2 -> NO");
        printf("\nSeleccion: ");
        scanf("%d", &aux);
        if (aux==1)
        {
            TareasRealizadas = InsertarTarea(TareasRealizadas, pTarea->dato);
            pTarea=pTarea->siguiente;
            listaTareas = BorrarTareaX(listaTareas, TareasRealizadas->dato);
        }else{
            pTarea=pTarea->siguiente;
        }
    }
    return TareasRealizadas;
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

void MostrarTareas(Lista *listaTareas)
{
    if (listaTareas!=NULL)
    {
        while (listaTareas!=NULL)
        {
            printf("\n.....................\n");
            MostrarUnaTarea(listaTareas->dato);
            listaTareas=listaTareas->siguiente;
        }     
    }else{
        printf("\nLa Lista de tareas esta vacia.\n");
    }
    
}

Lista *BorrarTareaX(Lista *listaX, Tarea *tareaRealizada)
{
    Lista *pAnterior, *pActual;
    bool aux=false;
    pActual=listaX;
    pAnterior = NULL;
    if (pActual!=NULL)
    {
        while (pActual!=NULL&& !aux)
        {
            if (pActual->dato->TareaID==tareaRealizada->TareaID)
            {
                aux=true;
                if (pAnterior==NULL)
                {
                    listaX=pActual->siguiente;
                    free(pActual);              
                }else{
                    pAnterior->siguiente=pActual->siguiente;
                    free(pActual);
                }               
            }else{
                pAnterior=pActual;
                pActual=pActual->siguiente;
            }  
        }    
    }
    return listaX;
}

Tarea *BusquedaPorPalabra(Lista *ListaX, char *palabraTareaBuscar){
    int tarea=0;
    Lista *pTarea;
    pTarea=ListaX;
    while (pTarea!=NULL && tarea == 0)
    {
        if (pTarea!= NULL && strstr(pTarea->dato->Descripcion, palabraTareaBuscar)!=NULL)//funcion strstr compara de la cad2 esta dentro de la cad1
        {
            return pTarea->dato; 
            tarea=1;
        }
        pTarea=pTarea->siguiente;
    }
    if (pTarea==NULL)
    {
        return NULL; 
    }
}

Tarea *BusquedaPorId(Lista *ListaX, int idTareaBuscar)
{
    int tarea=0;
    Lista *pTarea;
    pTarea=ListaX;
    while (pTarea!=NULL && tarea == 0)
    {
        if (pTarea!= NULL && pTarea->dato->TareaID==idTareaBuscar)
        {
            return pTarea->dato; 
            tarea=1;
        }
        pTarea=pTarea->siguiente;
    }
    if (pTarea==NULL)
    {
        return NULL; 
    }       
}

Lista *borrarPrimerElemento(Lista *ListaX)
{
    if(ListaX != NULL){
        Lista *borrar;
        borrar = ListaX;
        ListaX = ListaX->siguiente;
        free(borrar);//pendiente de correccion
    }
}
