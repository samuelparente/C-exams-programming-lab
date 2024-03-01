/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações do módulo operacoesCsv --------------------

//Include guards
#ifndef OPERACOES_FICHEIRO_CSV_H
#define OPERACOES_FICHEIRO_CSV_H

//includes
#include "defsGeral.h"
#include "funcoesGenericas.h"

//protótipo da função para ler o ficheiro com os dados dos produtos e carregar para a memória
PRODUTO *lerCsvProdutos(const char *ficheiro,int *num_produtos);

//protótipo da função para gravar os dados alocados em memória no ficheiro dos dados dos produtos
void gravarCsvProdutos(const char *ficheiro, PRODUTO* lista_produtos, int num_produtos);

//protótipo da função para ler o ficheiro com os dados das vendas e carregar para a memória
VENDA *lerCsvVendas(const char *ficheiro,int *num_vendas);

//protótipo da função para gravar os dados alocados em memória no ficheiro dos dados das vendas
void gravarCsvVendas(const char *ficheiro, VENDA* lista_vendas, int num_vendas);

#endif