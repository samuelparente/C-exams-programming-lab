/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//-------------------- header com definições e declarações do módulo interface.c --------------------

//Include guards
#ifndef INTERFACE_H
#define INTERFACE_H

//outros headers necessários
#include "defsGeral.h"
#include "operacoesRetangulos.h"

//Protótipos das funções
void menu(void);
void lerComando(COMANDO *cmd,MUNDO* mundo,RETANGULO* lista_retangulos);
bool validarComando(const char* entradaTemp, COMANDO* cmd);

#endif