#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

#include "listClientes.h"
#include "listRegistros.h"
#include "model.h"

int menu(){
    setlocale(LC_ALL, "portuguese");
    int op;
    printf("\n---------- LISTA DE CLIENTES E REGISTROS ----------\n");
    printf("1 - Listar Clientes\n");
    printf("2 - Inserir Cliente\n");
    printf("3 - Deletar um Cliente\n");
    printf("4 - Buscar um Cliente\n");
    printf("5 - Listar Registros\n");
    printf("6 - Inserir Registro\n");
    printf("7 - Deletar um Registro\n");
    printf("8 - Buscar um Registro\n");
    printf("0 - Sair\n");
    scanf("%d", &op);
    
    return op;
}

int main(){
    setlocale(LC_ALL, "portuguese");
    int op = 1, cod;
    char cpf[11];
    Cliente cliente, aux_cliente;
    Registro registro;
    Lista listaRegistros;
    ListaClientes listaClientes;
    GuardRegistro guardRegistro;
    GuardCliente guardCliente;
    criaLista(&listaRegistros);
    criaListaClientes(&listaClientes);
    
    do
    {
        op = menu();
        switch (op) {
            case 1:
                imprimirListaCliente(&listaClientes);
                break;
            case 2:
                cliente = criaCliente();
                if(!adicionarCliente(&listaClientes, cliente)){
                    printf("Cliente já existe.");
                }
                break;
            case 3:
                printf("Digite o CPF do cliente que deseja deletar:\n");
                scanf("%s", cpf);
                deletarCliente(&listaClientes, cpf);
                break;
            case 4:
                printf("Digite o CPF do cliente:\n");
                scanf("%s", cpf);
                guardCliente = *buscarCliente(&listaClientes, cpf);
                if (guardCliente.valido == 1) {
                    imprimirCliente(*guardCliente.cliente);
                } else {
                    printf("Cliente não encontrado.");
                }
                break;
            case 5:
                imprimirListaRegistros(&listaRegistros);
                break;
            case 6:
                printf("Digite o CPF do cliente:\n");
                scanf("%s", cpf);
                guardCliente = *buscarCliente(&listaClientes, cpf);
                if (guardCliente.cliente->status == 1) {
                    registro = criaRegistro(&aux_cliente, tamanhoDaLista(&listaRegistros));
                    adicionarRegistro(&listaRegistros, registro);
                    atualizaCliente(&listaClientes, registro.cliente.cpf, registro.cliente);
                } else {
                    printf("Cliente inativo. Impossível criar registro de venda.");
                }
                break;
            case 7:
                printf("Digite o código do registro de compra que deseja deletar:\n");
                scanf("%d", &cod);
                deletarRegistro(&listaRegistros, cod);
                break;
            case 8:
                printf("Digite o código da compra:\n");
                scanf("%d", &cod);
                guardRegistro = buscarRegistro(&listaRegistros, cod);
                if (guardRegistro.valid == 1){
                    imprimirRegistro(guardRegistro.registro);
                } else {
                    printf("Registro não encontrado.");
                }
                break;
            default:
                break;
        }
    } while (op != 0);
    
    return 0;
}
