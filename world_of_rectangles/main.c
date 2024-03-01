/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//header referente a este módulo
#include "main.h"

//Entrada programa principal.
int main(){

    //declaração de variáveis e apontadores
    int i=0,j=0;

    //aloca em memória o espaço para poder gravar o comando lido
    COMANDO *cmd = (COMANDO*)malloc(sizeof(COMANDO));
    //aloca em memória o espaço para gravar o mundo
    MUNDO *mundo = (MUNDO*)malloc(sizeof(MUNDO));
    //aloca em memória o espaço para o primeiro retangulo
    RETANGULO *lista_retangulos = (RETANGULO*)malloc(sizeof(RETANGULO));
    //verifica se alocou memória
    if (cmd == NULL || mundo == NULL || lista_retangulos == NULL) {
        printf("Erro a alocar memoria.\n");
        return 1;
    }
    else{
        //valores por defeito da struct COMANDO
        cmd->tipo_comando = 0;
        cmd->x = 0;
        cmd->y = 0;
        cmd->l = 0;
        cmd->h = 0;
        cmd->p = 0;
        
        //valores por defeito do mundo
        for(i=0;i<MAX_Y;i++){
            for(j=0;j<MAX_X;j++){
                mundo->mundo[j][i]=0;
            }
        }
        mundo->qtde_retangulos=0;
        
        //cabeçalho inicial do programa
        printf("+----------------------------------------------------------------------+\n");
        printf("|                Laboratorio de programacao - E-folio B                |\n");
        printf("|                       Samuel Parente n.2104178                       |\n");
        printf("|                         Mundo dos retangulos                         |\n");
        printf("+----------------------------------------------------------------------+\n\n");
        
        while(1){

            printf("O mundo contem %d retangulo(s).\n\n",mundo->qtde_retangulos);
            menu();
            lerComando(cmd,mundo,lista_retangulos);
            mostraMundo(mundo);
            verificaEstabilidade(mundo,lista_retangulos);
        }
    }
}