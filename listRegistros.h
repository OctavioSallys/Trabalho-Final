#ifndef LISTREGISTROS_H_INCLUDED
#define LISTREGISTROS_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#include "model.h"

typedef struct Celula {
    Registro dado;
    struct Celula *prox;
} Celula;

typedef struct Lista {
    Celula *inicio;
    Celula *fim;
    int tamanho;
} Lista;

typedef struct GuardRegistro{
    Registro registro;
    int valid;
}GuardRegistro;

bool criaLista(Lista *lista){
    Celula *tmp = (Celula *) malloc (sizeof(Celula));
    if (tmp == NULL) {
        return false;
    }
    tmp->prox = NULL;
    lista->inicio = tmp;
    lista->fim = tmp;
    lista->tamanho = 0;
    return true;
}

bool adicionarRegistro(Lista *lista, Registro registro){
    Celula *tmp = (Celula *)malloc(sizeof(Celula));
    if(tmp == NULL){
        return false;
    }
    
    tmp->dado = registro;
    tmp->prox = NULL;
    lista->fim->prox = tmp;
    lista->fim = tmp;
    lista->tamanho++;
    return true;
}

GuardRegistro buscarRegistro(Lista *lista, int cod){
    Celula *tmp = lista->inicio->prox;
    GuardRegistro resultado;
    for (*tmp; tmp != NULL; tmp = tmp->prox) {
        if (tmp->dado.codVenda == cod){
            resultado.registro = tmp->dado;
            resultado.valid = 1;
            return resultado;
        }
    }
    resultado.valid = 0;
    return resultado;
}

bool atualizaRegistro(Lista *lista, int cod, Registro registro){
    Celula *tmp = lista->inicio->prox;
    for (*tmp; tmp != NULL; tmp = tmp->prox) {
        if (tmp->dado.codVenda == cod){
            tmp->dado = registro;
            return true;
        }
    }
    return false;
}

bool deletarRegistro(Lista *lista, int cod){
    if (lista->inicio->prox == NULL){
        return false;
    }
    Celula *tmp = lista->inicio->prox;
    Celula *anterior = lista->inicio;
    for (*tmp; tmp != NULL; tmp = tmp->prox, anterior = anterior->prox) {
        if (tmp->dado.codVenda == cod){
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

void imprimirListaRegistros(Lista *x){
    Celula *tmp = x->inicio->prox;
    if (tmp == NULL) {
        printf("Lista vazia.\n");
    }
    while (tmp != NULL){
        imprimirRegistro(tmp->dado);
        tmp = tmp->prox;
    }
}

int tamanhoDaLista(Lista *lista){
    return lista->tamanho;
}

#endif
