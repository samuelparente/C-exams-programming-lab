/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//header referente ao módulo
#include "relatorios.h"

//função para gerar um relatório com quantidade vendida por produto, preço total de venda por produto,
//total de quantidade vendida dos produtos e total arrecadado com as vendas.Não retorna nada.
void geraRelatorioVendas(VENDA *lista_vendas, int num_vendas, PRODUTO *lista_produtos, int num_produtos) {
    
    //variáveis e apontadores
    int i = 0; //variável genérica para as iterações
    int j = 0; //variável genérica para as iterações
    float total_arrecadado = 0; //variável para armazenar a totalidade do valor de vendas nas iterações
    int total_unidades_vendidas = 0; // variavel para armazenar a totalidades de produtos vendidos nas iterações
    int codigo_produto = 0; //variável para armazenar o código nas iterações
    int quantidade_vendida = 0; //variável para armazenar a quantidade vendida por produto nas iterações
    float valor_venda = 0; //variável para armazenar o total de venda por produto nas iterações
    float preco_unitario = 0; //variável para armazenar o preço unitário nas iterações
    char designacao[50]; //variável para armazenar a designação do produto nas iterações

    printf("+-----------+------------------------------------------------------+----------------+--------------------+-------------+\n");
    printf("|  Codigo   | Designacao                                           | Preco unitario | Quantidade vendida | Valor total |\n");
    printf("+-----------+------------------------------------------------------+----------------+--------------------+-------------+\n");

    //percorre a lista de produtos
    for (i = 0; i < num_produtos; i++) {
        codigo_produto = lista_produtos[i].codigo;
        preco_unitario = lista_produtos[i].preco;
        strcpy(designacao, lista_produtos[i].designacao);
        quantidade_vendida = 0;
        valor_venda = 0;

        //percorre lista de vendas para obter as vendas
        for (j = 0; j < num_vendas; j++) {
            if (lista_vendas[j].codigo == codigo_produto) {
                quantidade_vendida += lista_vendas[j].quantidade;
                valor_venda += (float)lista_vendas[j].quantidade * lista_produtos[i].preco;
            }
        }
        //verifica se tem vendas para mostrar os totais por produto
        if (quantidade_vendida > 0) {
            printf("| %-9d | %-52s | %14.2f | %-18d | %11.2f |\n", codigo_produto, designacao, preco_unitario, quantidade_vendida, valor_venda);
            total_arrecadado += valor_venda;
            total_unidades_vendidas += quantidade_vendida;
        }
    }
    //mostra os totais globais de quantidade vendida de produtos e total arrecadado com as vendas
    printf("+-----------+------------------------------------------------------+----------------+--------------------+-------------+\n");
    printf("| Total de unidades vendidas: %-17d | Total de vendas: %-16.2f |\n", total_unidades_vendidas, total_arrecadado);
    printf("+-----------------------------------------------------------------------------------+\n\n");
}
