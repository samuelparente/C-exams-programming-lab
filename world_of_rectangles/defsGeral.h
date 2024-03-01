/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//-------------------- header com definições e declarações comuns a todos os módulos --------------------

//Include guards
#ifndef DEFS_GERAL_H
#define DEFS_GERAL_H

//constantes
#define MAX_X 80 //x máximo do mundo é 80 mas em array vai até 79
#define MIN_X 1 //x mínimo do mundo é 1 mas o array começa em 0
#define MAX_Y 25 //y máximo do mundo é 25 mas em array vai até 24
#define MIN_Y 1 //y mínimo do mundo é 1 mas o array começa em 0
#define MIN_P 1 //para mover o retangulo o minimo é uma casa
#define MAX_P 78 //como x é 80 max, supondo retangulo minimo tem largura 1.
#define CMD_INPUT_LENGTH 24 // tamanho máximo do buffer de entrada para comandos
#define COMMAND_1 1 //comando create
#define COMMAND_2 2 //comando moveright
#define COMMAND_3 3 //comando moveleft
#define COMMAND_4 4 //comando exit
#define LIMITE_INSTABILIDADE 70.0
//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

//estrutura para armazenar um retangulo
typedef struct retangulo {
    int x;
    int y;
    int l;
    int h;
} RETANGULO;

//estrutura para armazenar os dados do mundo
typedef struct mundo{
    int qtde_retangulos;
    int mundo[MAX_X][MAX_Y];
} MUNDO;

//estrutura para armazenar os dados do comando dado pelo utilizador
typedef struct comando{
    int x;
    int y;
    int l;
    int h;
    int p;
    int tipo_comando;
} COMANDO;

#endif