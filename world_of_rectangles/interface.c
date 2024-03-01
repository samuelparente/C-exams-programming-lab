/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//header referente a este módulo
#include "interface.h"

//função mostra menu
void menu(void){
  
    printf("Comando para criar um retangulo: create x,y+l,h\n");
    printf("Comando para mover o retangulo para a direita: moveright x,y+p\n");
    printf("Comando para mover o retangulo para a esquerda: moveleft x,y+p\n");
    printf("Comando para sair do programa: exit\n\n");
    printf("Insira o comando desejado: ");

}


//função ler comandos
void lerComando(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos){
    
    //declaração de variàveis e apontadores
    char entradaTemp[CMD_INPUT_LENGTH];
    int length=0;

    // limpar o buffer de entrada para evitar problemas a ler entrada do utilizador
    fflush(stdin);

    //ler e armazenar dados inseridos
    fgets(entradaTemp,CMD_INPUT_LENGTH,stdin);
    
    //ler comprimento da string
    length = strlen(entradaTemp);
    
    //Remove caracter \n adicionado pela função fgets e adiciona terminador nulo
    if (length > 0 && entradaTemp[length-1] == '\n') {
        entradaTemp[length-1] = '\0';
    }

    //selecção de funções conforme o comando após validação da entrada do utilizador
    if (validarComando(entradaTemp, cmd)) {

        switch(cmd->tipo_comando){
            //cria um retangulo
            case 1:
                criaRetangulo(cmd,mundo,lista_retangulos);
                break;
            //move um retangulo para a direita
            case 2:
                moveRetanguloDireita(cmd,mundo,lista_retangulos);
                break;
            //move um retangulo para a esquerda
            case 3:
                moveRetanguloEsquerda(cmd,mundo,lista_retangulos);
                break;
            //liberta a memória que foi alocada e encerra o programa
            case 4:
                free(mundo);
                free(lista_retangulos);
                free(cmd);
                printf("\nO programa vai encerrar em 5 segundos...\n\n");
                sleep(5);
                exit(0);
            default:
                printf("Ocorreu um erro inesperado.\n");
                printf("Nao foi possivel executar o comando.\n");
            break;
        }
    }
    else {   
    }  
}

//função validar formato dos comandos e armazena na struct os valores correspondentes
bool validarComando(const char* entradaTemp, COMANDO* cmd) {

    //declaração de variàveis e apontadores
    int x=0,y=0,l=0,h=0,p=0;
    char tipo_comando[CMD_INPUT_LENGTH];

    //verifica se o comando é create
    if (strstr(entradaTemp,"create ")!=NULL){ 

        //verifica os dados de entrada e armazena na struct para poder passar a outras funções os valores
        if(sscanf(entradaTemp, "%s %d,%d+%d,%d", &tipo_comando, &x, &y, &l, &h)){

             //valida máximos e mínimos dos valores
             if(x>=MIN_X && x<=MAX_X && y>=MIN_Y && y<=MAX_Y && l>=MIN_X && l<=MAX_X && h>=MIN_Y && h<=MAX_Y){
                
                cmd->x=x-1; //a coordenada mínima é 1 mas o vetor começa em 0
                cmd->y=y-1; //a coordenada mínima é 1 mas o vetor começa em 0
                cmd->l=l-1;
                cmd->h=h-1;
                cmd->p=-1; //indica que neste comando o parametro não é usado
                cmd->tipo_comando = COMMAND_1;

                return true; // Comando válido
             }
             else{
                printf("Valores fora de limites.\n");
                return false; // valores errados
             }
        }
        else{
            printf("Comando com formato errado.\n");
            return false; // Comando inválido
        }
    }
    //verifica se o comando é moveright
    else if(strstr(entradaTemp,"moveright ")!=NULL){
        
        //verifica os dados de entrada e armazena na struct para poder passar a outras funções os valores
        if(sscanf(entradaTemp, "%s %d,%d+%d", &tipo_comando, &x, &y, &p)){

            //valida máximos e mínimos dos valores
            if((x>=MIN_X && x<=MAX_X) && (y>=MIN_Y && y<=MAX_Y)  && (p>=MIN_P && p<=MAX_P)){
                
                cmd->x=x;
                cmd->y=y;
                cmd->p=p;
                cmd->h=-1;//indica que neste comando o parametro não é usado
                cmd->l=-1;//indica que neste comando o parametro não é usado
                cmd->tipo_comando = COMMAND_2;
               
                return true; // Comando válido
            }
            else{
                printf("Valores fora de limites.\n");
                return false; // valores errados
            }
        }
        else{
            printf("Comando com formato errado.\n");
            return false; // Comando inválido
        }
    }
    //verifica se o comando é moveleft
    else if(strstr(entradaTemp,"moveleft ")!=NULL){
        
         //verifica os dados de entrada e armazena na struct para poder passar a outras funções os valores
        if(sscanf(entradaTemp, "%s %d,%d+%d", &tipo_comando, &x, &y, &p)){
             
            //valida máximos e mínimos dos valores
            if((x>=MIN_X && x<=MAX_X) && (y>=MIN_Y && y<=MAX_Y)  && (p>=MIN_P && p<=MAX_P)){
                
                cmd->x=x;
                cmd->y=y;
                cmd->p=p;
                cmd->h=-1;//indica que neste comando o parametro não é usado
                cmd->l=-1;//indica que neste comando o parametro não é usado
                cmd->tipo_comando = COMMAND_3;
                
                return true; // Comando válido
            }
            else{
                printf("Valores fora de limites.\n");
                return false; // valores errados
            }
        }
    }
    //verifica se o comando é exit
    else if(strcmp(entradaTemp,"exit")==0){
        
        //apenas precisamos de gravar que o comando foi "exit"
        cmd->tipo_comando = COMMAND_4;
    }
    //erro na entrada do utilizador
    else{
        printf("Comando errado.\n");
        return false; // Comando inválido
    }
}