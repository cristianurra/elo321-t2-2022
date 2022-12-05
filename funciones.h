#ifndef FUNCIONES_H
#define FUNCIONES_H

#define BUFFER 1024

typedef struct Pedido
{
    char Tipo;
    int Hojas;
    char Urgente;
} pedido;

typedef struct ElementoLista
{
    struct Pedido *dato;
    struct ElementoLista *siguiente;
} Elemento;

typedef struct ListaIdentificar
{
    Elemento *inicio;
    Elemento *fin;
    int tamano;
} Lista;

//int sim_work_t_usuario(pedido *ped);

//int sim_wort_t_impresora(pedido *ped);

void print_pedido(pedido *ped);

void msj_error(char *const msg);

void precio(pedido *ped);

pedido *iniciar_pedido(char tipo, int hojas, char urgencia);

int ins_en_lista_vacia(Lista *lista, pedido *dato);

int ins_fin_lista(Lista *lista, Elemento *actual, pedido *dato);

int sup_inicio(Lista *lista);

void visualizacion(Lista *lista);

int contar_pedidos();

void read_pedidos(pedido *prods, Elemento *elemento, Lista *lista);

Lista *inicializacion();

//bool revisar_urgencia(Elemento *lista_pedidos);

#endif
