/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações do módulo operacoesProduto --------------------

//Include guards
#ifndef OPERACOES_PRODUTO_H
#define OPERACOES_PRODUTO_H

//includes
#include "defsGeral.h"
#include "funcoesGenericas.h"

//Protótipo da função para mostrar a lista de produtos carregada em memória
void mostraProdutos(PRODUTO *lista_produtos, int num_produtos);

//Protótipo da função para adicionar um produto à lista de produtos carregada em memória
void adicionaProduto(PRODUTO **lista_produtos, int *num_produtos);

//Protótipo da função para atualizar os dados de um produto da lista de produtos carregada em memória
void atualizaProduto(PRODUTO *lista_produtos, int num_produtos);

//Protótipo da função para remover um produto da lista de produtos carregada em memória
void removeProduto(PRODUTO **lista_produtos, int *num_produtos);

//Protótipo da função para procurar um produto na lista de produtos carregada em memória
void pesquisaProduto(PRODUTO *lista_produtos, int num_produtos);

//Protótipo da função para verificar a existência de um produto na lista de produtos carregada em memória
int verificaProduto(struct produto *lista_produtos, int num_produtos, int codigoLido);

#endif