/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações do módulo relatorios --------------------

//Include guards
#ifndef RELATORIOS_H
#define RELATORIOS_H

//includes
#include "defsGeral.h"

//Protótipo da função que gera um relatório de vendas
void geraRelatorioVendas(VENDA *lista_vendas, int num_vendas, PRODUTO *lista_produtos, int num_produtos);

#endif