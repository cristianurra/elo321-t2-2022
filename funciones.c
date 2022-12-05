#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE 512

#define SIZE 512
#define LSIZ 128
#define RSIZ 10

Lista *inicializacion()
{
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fin = NULL;
    return lista;
}

pedido *iniciar_pedido(char tipo, int hojas, char urgencia)
{
    pedido *ped = (pedido *)malloc(sizeof(pedido));
    ped->Tipo = tipo;
    ped->Hojas = hojas;
    ped->Urgente = urgencia;
    return ped;
}

void print_pedido(pedido *ped)
{
    char *tipo_mensaje;
    char *urgencia_mensaje;
    if (ped->Tipo == 'C')
    {
        tipo_mensaje = "A Color";
    }
    else if (ped->Tipo == 'B')
    {
        tipo_mensaje = "Blanco y Negro";
    }
    else
    {
        msj_error("Formato incorrecto en el pedido");
    }

    if (ped->Urgente == 'N')
    {
        urgencia_mensaje = "No Urgente";
    }
    else if (ped->Urgente == 'S')
    {
        urgencia_mensaje = "Urgente";
    }
    printf("%s, %d hojas y %s\n", tipo_mensaje, ped->Hojas, urgencia_mensaje);
}

void msj_error(char *mensaje)
{
    printf("%s\n", mensaje);
    exit(1);
}
/* inserción en una lista vacía */
int ins_en_lista_vacia(Lista *lista, pedido *dato)
{
    Elemento *nuevo_elemento;
    if ((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento))) == NULL)
        return -1;
    if ((nuevo_elemento->dato = (pedido *)malloc(sizeof(pedido))) == NULL)
        return -1;
    nuevo_elemento->dato = dato;
    nuevo_elemento->siguiente = NULL;
    lista->inicio = nuevo_elemento;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}

/*inserción al final de la lista */
int ins_fin_lista(Lista *lista, Elemento *actual, pedido *dato)
{
    Elemento *nuevo_elemento;
    if ((nuevo_elemento = (Elemento *)malloc(sizeof(Elemento))) == NULL)
        return -1;
    if ((nuevo_elemento->dato = (pedido *)malloc(sizeof(pedido))) == NULL)
        return -1;
    nuevo_elemento->dato = dato;
    actual->siguiente = nuevo_elemento;
    nuevo_elemento->siguiente = NULL;
    lista->fin = nuevo_elemento;
    lista->tamano++;
    return 0;
}

/* eliminación al inicio de la lista */
int sup_inicio(Lista *lista)
{
    if (lista->tamano == 0)
        return -1;
    Elemento *sup_elemento;
    sup_elemento = lista->inicio;
    lista->inicio = lista->inicio->siguiente;
    if (lista->tamano == 1)
        lista->fin = NULL;
    free(sup_elemento->dato);
    free(sup_elemento);
    lista->tamano--;
    return 0;
}

/* visualización de la lista */
void visualizacion(Lista *lista)
{
    Elemento *actual;
    actual = lista->inicio;
    while (actual != NULL)
    {
        printf("t: %c h: %d u: %c\n", actual->dato->Tipo, actual->dato->Hojas, actual->dato->Urgente);
        actual = actual->siguiente;
    }
}

void parse_producto_from_line(pedido *ped, char line[BUFFER])
{
    char *tok;
    int x;
    x = 0;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        switch (x)
        {
        case 0:
            ped->Tipo = tok[0];
            break;
        case 1:
            ped->Hojas = atoi(tok);
            break;
        case 2:
            ped->Urgente = (tok[0] == 'S');
            break;
        default:
            msj_error("Error de formato");
            break;
        }
    }
}

/*int sim_work_t_usuario(pedido *ped)
{
    int time;
    if (ped->Tipo == 'C')
    {
        time = 200 * ped->Hojas;
    }
    else
        time = 100 * ped->Hojas;

    msleep(time);
    return time;
}

int sim_wort_t_impresora(pedido *ped)
{
    int time;
    time = 150 * ped->Hojas;
    msleep(time);
    return time;
}
*/
void precio(pedido *ped)
{
    int precio;
    if (ped->Tipo = 'C')
    {
        precio = 20 * ped->Hojas;
    }
    else
    {
        precio = 10 * ped->Hojas;
    }
    printf("SERVER: ");
    printf(" pagar %d por orden: ", precio);
    print_pedido(ped);
}

/*bool revisar_urgencia(Elemento *lista_pedidos)
{
    Elemento *current = lista_pedidos;
    while (current != NULL)
    {
        if (current->dato->Urgente == 'S')
        {
            return true;
        }
        current = current->siguiente;
    }
    return false;
}
* */

int contar_pedidos()
{
    int c = 0;
    char line[RSIZ][LSIZ];
    char fname[20] = "test.txt";
    FILE *fptr = NULL;
    int i = 0;
    int tot = 0;

    fptr = fopen(fname, "r");
    while (fgets(line[i], LSIZ, fptr))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        i++;
    }
    tot = i;
    for (i = 0; i < tot; ++i)
    {
        c++;
    }
    fclose(fptr);
    return c;
}

void read_pedidos(pedido *prods, Elemento *elemento, Lista *lista)
{
    FILE *fp = fopen("test.txt", "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        parse_producto_from_line(&prods[i], line);

        pedido *prod = &prods[i];
        if (i == 0)
        {
            ins_en_lista_vacia(lista, prod);
        }
        else
        {
            ins_fin_lista(lista, lista->fin, prod);
        }
        i++;
    }
}
/*
int read_productos(pedido *prods, Elemento *elemento, Lista *lista)
{
    FILE *fp = fopen("test.txt", "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        parse_producto_from_line(&prods[i], line);

        i++;
    }
    fclose(fp);
    return i;
}
*/
