/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//-------------------- header com definições e declarações do módulo operacoesRetangulos.c --------------------

//Include guards
#ifndef OPERACOES_RETANGULOS
#define OPERACOES_RETANGULOS

//Outros headers necessários
#include "defsGeral.h"

//Protótipos das funções
void criaRetangulo(COMANDO* cmd, MUNDO* mundo,RETANGULO* lista_retangulos);
void moveRetanguloDireita(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos);
void moveRetanguloEsquerda(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos);
void marcaRetangulo(int x,int y,int l,int h,MUNDO* mundo, COMANDO* cmd);
void mostraMundo(MUNDO* mundo);
bool verificaLimitesMundo(int x, int y, int l, int h);
bool aplicaGravidade(MUNDO* mundo, COMANDO* cmd);
int procuraRetangulo(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos);
void limpaRetanguloMundo(int x,int y,int l,int h,MUNDO* mundo);
void aplicaGravidadeMundo(MUNDO* mundo, RETANGULO* lista_retangulos, COMANDO* cmd);
void verificaEstabilidade(MUNDO* mundo, RETANGULO* lista_retangulos);

#endif