
/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações comuns a todos os módulos --------------------

//Include guards
#ifndef DEFS_GERAL_H
#define DEFS_GERAL_H

//constantes
#define MAX_DESIGNACAO_LENGTH 50
#define MAX_PRECO_LENGTH 9
#define MAX_CODIGO_LENGTH 9
#define MAX_QUANTIDADE_LENGTH 9
#define MAX_DATAVENDA_LENGTH 16
#define FICHEIRO_PRODUTOS "produtos.csv"
#define FICHEIRO_VENDAS "vendas.csv"
#define LINHA_MAX_LENGTH 128

//includes
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

//estrutura para um produto
typedef struct produto {
    int codigo;
    char designacao[MAX_DESIGNACAO_LENGTH];
    float preco;
} PRODUTO;

//estrutura para uma venda
typedef struct venda{
    int codigo;
    int quantidade;
    char dataVenda[MAX_DATAVENDA_LENGTH];
}VENDA;

#endif