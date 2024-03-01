/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações do módulo operacoesVendas --------------------

//Include guards
#ifndef OPERACOES_VENDAS_H
#define OPERACOES_VENDAS_H

//includes
#include "defsGeral.h"
#include "operacoesProduto.h"
#include "funcoesGenericas.h"

//Protótipo da função para mostrar a lista de vendas efetuadas carregada em memória
void mostraVendas(VENDA *lista_vendas, int num_vendas);

//Protótipo da função para efetuar uma venda ao cliente e adicionar a venda à lista carregada em memória
void adicionaVenda(VENDA **lista_vendas, int *num_vendas, PRODUTO *lista_produtos, int num_produtos);

#endif