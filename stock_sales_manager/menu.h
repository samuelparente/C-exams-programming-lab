/*
Programa para gerir vendas e produtos de uma loja.
Desenvolvido por Samuel Parente, aluno 2104178
Para a disciplina de Laboratórios de Programação - Programação modular
*/

//-------------------- header com definições e declarações do módulo menu --------------------

//Include guards
#ifndef MENU_H
#define MENU_H

//Includes
#include "defsGeral.h"
#include "operacoesProduto.h"
#include "operacoesVendas.h"
#include "operacoesCsv.h"
#include "relatorios.h"
#include "funcoesGenericas.h"

//protótipo da função menu
void menu(PRODUTO **lista_produtos, int *num_produtos,VENDA **lista_vendas, int *num_vendas);

#endif