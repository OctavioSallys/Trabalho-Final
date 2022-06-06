#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Cliente
{
    char cpf[11];
    char nome[100];
    int status;
    double totalGasto;
} Cliente;

enum Combustivel
{
    Gasolina = 0,
    Diesel,
    Etanol,
};

typedef struct Registro
{
    enum Combustivel tipo;
    char ultimaModificacao[10];
    char dataDaVenda[10];
    char responsavel[100];
    double quantidade;
    double valorLitro;
    int codVenda;
    Cliente cliente;
} Registro;

void imprimirRegistro(Registro registro)
{
    setlocale(LC_ALL, "portuguese");
    char combustivel[9];
    switch (registro.tipo)
    {
        case Gasolina:
            strcpy(combustivel, "Gasolina");
            break;
        case Etanol:
            strcpy(combustivel, "Etanol");
            break;
        case Diesel:
            strcpy(combustivel, "Diesel");
            break;
        default:
            break;
    }
    printf("Data da compra: %s, CPF: %s, Nome: %s, Combustivel: %s, Quantidade: %f, Responsável: %s\n", registro.dataDaVenda, registro.cliente.cpf, registro.cliente.nome, combustivel, registro.quantidade, registro.responsavel);
}

void imprimirCliente(Cliente cliente)
{
    setlocale(LC_ALL, "portuguese");
    char status[9];
    switch (cliente.status)
    {
        case 1:
            strcpy(status, "Ativo");
            break;
        case 0:
            strcpy(status, "Inativo");
            break;
        default:
            break;
    }
    printf("CPF: %s, Nome: %s, Status: %s, Total de Compras: %.2f\n", cliente.cpf, cliente.nome, status, cliente.totalGasto);
}

Registro criaRegistro(Cliente *cliente, int CodVenda)
{
    Registro registro;
    double valorBase = 5;
    if (cliente->status != 0)
    {
        printf("Digite a última modificação do valor do combustível:\n");
        scanf("%s", registro.ultimaModificacao);
        printf("Data da venda:\n");
        scanf("%s", registro.dataDaVenda);
        printf("Digite o nome do responsável pela venda:\n");
        scanf("%[^\n]%*c", registro.responsavel);
        printf("Escolha o combustível:\n");
        printf("Digite 0 para Gasolina\nDigite 1 para Diesel\nDigite 2 para Etanol:\n");
        scanf("%d", &registro.tipo);
        printf("Digite a quantidade de combustível:\n");
        scanf("%lf", &registro.quantidade);
        
        switch (registro.tipo)
        {
            case Gasolina:
                registro.valorLitro = valorBase * 1.55;
                break;
            case Etanol:
                registro.valorLitro = valorBase * 1.15;
                break;
            case Diesel:
                registro.valorLitro = valorBase * 1.75;
                break;
            default:
                break;
        }
        double valorTotal;
        valorTotal = registro.valorLitro * registro.quantidade;
        cliente->totalGasto += valorTotal;
        printf("Valor total da compra: %.2f \n", valorTotal);
        
        registro.cliente = *cliente;
        registro.codVenda = CodVenda;
        printf("Registro criado com sucesso! Código do registro: %d \n", CodVenda);
        return registro;
    }
    else {
        return registro;
    }
}

Cliente criaCliente(){
    Cliente cliente;
    double totalGasto;
    printf("Digite o CPF do cliente:\n");
    scanf("%s", cliente.cpf);
    printf("Digite o Nome do cliente:\n");
    scanf("%s", cliente.nome);
    printf("Digite o Status do cliente:\n");
    printf("Digite 0 para inativo e 1 para ativo:\n");
    scanf("%d", &cliente.status);
    totalGasto = 0;
    
    cliente.totalGasto = totalGasto;
    return cliente;
}

void trocarStatus(Cliente *cliente) {
    if (cliente->status == 0)
    {
        cliente->status = 1;
    } else {
        cliente->status = 0;
    }
}

#endif
