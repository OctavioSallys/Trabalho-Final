#ifndef LISTCLIENTES_H_INCLUDED
#define LISTCLIENTES_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "model.h"

typedef struct CelulaCliente {
    Cliente dado;
    struct CelulaCliente *prox;
} CelulaCliente;

typedef struct ListaClientes {
    CelulaCliente *inicio;
    CelulaCliente *fim;
    int tamanho;
} ListaClientes;

typedef struct GuardCliente{
    Cliente *cliente;
    int valido;
}GuardCliente;

bool criaListaClientes(ListaClientes *lista){
    CelulaCliente *tmp = (CelulaCliente *) malloc (sizeof(CelulaCliente));
    if (tmp == NULL) {
        return false;
    }
    tmp->prox = NULL;
    lista->inicio = tmp;
    lista->fim = tmp;
    lista->tamanho = 0;
    return true;
}

bool adicionarCliente(ListaClientes *lista, Cliente cliente){
    CelulaCliente *tmp = (CelulaCliente *)malloc(sizeof(CelulaCliente));
    CelulaCliente *aux = lista->inicio->prox;
    if(tmp == NULL){
        return false;
    }
    for (*aux; aux != NULL; aux = aux->prox) {
        if (strcmp(aux->dado.cpf, cliente.cpf) == 0){
            return false;
        }
    }
    tmp->dado = cliente;
    tmp->prox = NULL;
    lista->fim->prox = tmp;
    lista->tamanho++;
    return true;
}

GuardCliente *buscarCliente(ListaClientes *lista, char *cpf){
    CelulaCliente *tmp = lista->inicio->prox;
    GuardCliente resultado;
    for (*tmp; tmp != NULL; tmp = tmp->prox) {
        if (strcmp(tmp->dado.cpf, cpf) == 0){
            resultado.cliente =  &tmp->dado;
            resultado.valido = 1;
            return &resultado;
        }
    }
    resultado.valido = 0;
    return &resultado;
}

bool atualizaCliente(ListaClientes *lista, char *cpf, Cliente cliente){
    CelulaCliente *tmp = lista->inicio->prox;
    for (*tmp; tmp != NULL; tmp = tmp->prox) {
        if (strcmp(tmp->dado.cpf, cpf) == 0){
            tmp->dado = cliente;
            return true;
        }
    }
    return false;
}

bool deletarCliente(ListaClientes *lista, char *cpf){
    if (lista->inicio->prox == NULL){
        return false;
    }
    CelulaCliente *tmp = lista->inicio->prox;
    CelulaCliente *anterior = lista->inicio;
    for (*tmp; tmp != NULL; tmp = tmp->prox, anterior = anterior->prox) {
        if (strcmp(tmp->dado.cpf, cpf) == 0){
            anterior->prox = tmp->prox;
            if (tmp->prox == NULL){
                lista->fim = anterior;
            }
            free(tmp);
            lista->tamanho--;
            return true;
        }
    }
    return false;
}

void imprimirListaCliente(ListaClientes *x){
    setlocale(LC_ALL, "portuguese");
    CelulaCliente *tmp = x->inicio->prox;
    if (tmp == NULL) {
        printf("Lista vazia.\n");
    }
    while (tmp != NULL){
        imprimirCliente(tmp->dado);
        tmp = tmp->prox;
    }
}

#endif
