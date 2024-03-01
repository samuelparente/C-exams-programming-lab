/*
Laboratório de Programação - E-fólio B
Samuel Parente n.º2104178
Mundo dos retângulos
*/

//header referente a este módulo
#include "operacoesRetangulos.h"

//função para criar retângulos
void criaRetangulo(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos){

    //declaração de variàveis e apontadores
    int x=0,y=0,l=0,h=0,qtde_retangulos=0;

    //coordenadas sem a gravidade aplicada
    x = cmd->x;
    y = cmd->y;
    l = cmd->l;
    h = cmd->h;

    //verifica se o retangulo não é maior que o próprio mundo
    if(verificaLimitesMundo(x,y,l,h)){

        //aplica a gravidade e verifica colisões antes de gravar o retangulo
        if(aplicaGravidade(mundo,cmd)){

            //ler coordenadas com gravidade aplicada
            x = cmd->x;
            y = cmd->y;
            l = cmd->l;
            h = cmd->h;

            //ler quantidade de retângulos no mundo
            qtde_retangulos = mundo->qtde_retangulos;

            //ainda não existe nenhum retangulo em memoria.
            if(qtde_retangulos == 0){

                //grava o retangulo na struct
                (lista_retangulos)[qtde_retangulos].x = x;
                (lista_retangulos)[qtde_retangulos].y = y;
                (lista_retangulos)[qtde_retangulos].l = l;
                (lista_retangulos)[qtde_retangulos].h = h;

                //grava o retangulo no mundo
                marcaRetangulo(x,y,l,h,mundo,cmd);
                
                //grava o retangulo no contador
                mundo->qtde_retangulos = 1;

                printf("Retangulo criado com sucesso.\n\n");

            }
            //realoca espaço em memória para o novo retangulo bem como os existentes
            else if(qtde_retangulos > 0){
    
                lista_retangulos = (RETANGULO*)realloc(lista_retangulos, (qtde_retangulos+1) * sizeof(RETANGULO));
                
                //verifica se alocou memória
                if (lista_retangulos == NULL) {
                    printf("Erro a alocar memoria.Nao foi possivel adicionar o retangulo ao mundo.\n");
                }
                else{
                    //grava o retangulo na struct
                    (lista_retangulos)[qtde_retangulos].x = x;
                    (lista_retangulos)[qtde_retangulos].y = y;
                    (lista_retangulos)[qtde_retangulos].l = l;
                    (lista_retangulos)[qtde_retangulos].h = h;

                    //grava o retangulo no mundo
                    marcaRetangulo(x,y,l,h,mundo,cmd);
                    
                    //grava o retangulo no contador
                    mundo->qtde_retangulos = qtde_retangulos+1;

                    printf("Retangulo criado com sucesso.\n\n");
                }
            }
            else{
                printf("Ocorreu um erro inesperado.\n\n");
            }
        }
        //o retangulo colide com limites ou retangulos.
        else{
            printf("Nao existe espaco disponivel no mundo com as coordenadas fornecidas. O retangulo nao foi criado.\n\n");
        }
    }
    //o retângulo é maior que o mundo
    else{
        printf("O retangulo excede os limites do mundo e nao foi criado.\n\n");
    } 
}

//função para mover um retângulo para a direita
void moveRetanguloDireita(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos){

    //declaração de variàveis e apontadores
    int x=0,y=0,l=0,h=0,p=0,x_old=0,y_old=0,index_retangulo=0;

    //procurar se o x,y existe nas coordenadas dentro das lista dos retangulos. 999 indica que não encontrou.
    index_retangulo = procuraRetangulo(cmd,mundo,lista_retangulos);

    if(index_retangulo != 999){
    
        //"offset" no eixo x
        p = cmd->p;

        //coordenadas do retangulo original
        x = (lista_retangulos)[index_retangulo].x;
        y = (lista_retangulos)[index_retangulo].y;
        l = (lista_retangulos)[index_retangulo].l;
        h = (lista_retangulos)[index_retangulo].h;

        //guarda x e y originais
        x_old = x;
        y_old = y;
        //para mover o retangulo, adicionar o "offset" à coordenada x
        x=x+p;
        //atualiza struct comando para enviar as coordenadas corretas
        cmd->x = x;
        cmd->y = MAX_Y-h;
        cmd->l = l;
        cmd->h = h;

        //cabe no mundo ao mover?
        if(verificaLimitesMundo(x,y,l,h)){

            //elimina o retangulo original do mundo para poder mover e aplicar gravidade
            limpaRetanguloMundo(x_old,y_old,l,h,mundo);

            //aplica a gravidade e verifica colisões antes de mover o retangulo
            if(aplicaGravidade(mundo,cmd)){

                //ler coordenadas com gravidade aplicada
                x = cmd->x;
                y = cmd->y;
                l = cmd->l;
                h = cmd->h;

                //atualiza o retangulo na struct
                (lista_retangulos)[index_retangulo].x = x;
                (lista_retangulos)[index_retangulo].y = y;
                (lista_retangulos)[index_retangulo].l = l;
                (lista_retangulos)[index_retangulo].h = h;

                //grava o novo retangulo no mundo
                marcaRetangulo(x,y,l,h,mundo,cmd);

            }
            //o retangulo colide com limites ou retangulos.repõe o retangulo original no mundo porque não foi possível mover
            else{
                
                cmd->x = x_old;
                marcaRetangulo(x_old,y_old,l,h,mundo,cmd);
                printf("Nao existe espaco disponivel no mundo para o mover com as coordenadas fornecidas. O retangulo nao foi movido.\n\n");
            }
        }
        //o retângulo nao cabe no mundo ao mover.
        else{
            printf("O retangulo excede os limites do mundo ao mover para as novas coordenadas.\n\n");
        } 
    } 
    else{
        printf("O retangulo nao foi encontrado.\n");
    }
    //aplica gravidade no mundo para atualizar todos os retangulos após mover o retangulo
    aplicaGravidadeMundo(mundo,lista_retangulos,cmd);
}

//função para mover o retângulo para a esquerda
void moveRetanguloEsquerda(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos){

    //declaração de variàveis e apontadores
    int x=0,y=0,l=0,h=0,p=0,x_old=0,y_old=0,index_retangulo=0;

    //procurar se o x,y existe nas coordenadas dentro das lista dos retangulos. 999 significa que não encontrou.
    index_retangulo = procuraRetangulo(cmd,mundo,lista_retangulos);

    if(index_retangulo != 999){
    
        //"offset" no eixo x
        p = cmd->p;

        //coordenadas do retangulo original
        x = (lista_retangulos)[index_retangulo].x;
        y = (lista_retangulos)[index_retangulo].y;
        l = (lista_retangulos)[index_retangulo].l;
        h = (lista_retangulos)[index_retangulo].h;

        //guarda x e y originais
        x_old=x;
        y_old=y;
        //para mover o retangulo, adicionar o "offset" à coordenada x
        x=x-p;
        //atualiza struct comando para enviar as coordenadas corretas
        cmd->x = x;
        cmd->y = MAX_Y-h;
        cmd->l = l;
        cmd->h = h;

        //cabe no mundo ao mover?
        if(verificaLimitesMundo(x,y,l,h)){

            //elimina o retangulo original do mundo para poder mover e aplicar gravidade
            limpaRetanguloMundo(x_old,y_old,l,h,mundo);

            //aplica a gravidade e verifica colisões antes de mover o retangulo
            if(aplicaGravidade(mundo,cmd)){

                //ler coordenadas com gravidade aplicada
                x = cmd->x;
                y = cmd->y;
                l = cmd->l;
                h = cmd->h;

                //atualiza o retangulo na struct
                (lista_retangulos)[index_retangulo].x = x;
                (lista_retangulos)[index_retangulo].y = y;
                (lista_retangulos)[index_retangulo].l = l;
                (lista_retangulos)[index_retangulo].h = h;

                //grava o novo retangulo no mundo
                marcaRetangulo(x,y,l,h,mundo,cmd);

            }
            //o retangulo colide com limites ou retangulos.repõe o retangulo original no mundo porque não foi possível mover.
            else{

                cmd->x = x_old;
                marcaRetangulo(x_old,y_old,l,h,mundo,cmd);
                printf("Nao existe espaco disponivel no mundo para o mover com as coordenadas fornecidas. O retangulo nao foi movido.\n\n");
            }
        }
        //o retângulo nao cabe no mundo ao mover.
        else{
            printf("O retangulo excede os limites do mundo ao mover para as novas coordenadas.\n\n");
        } 
    } 
    else{
        printf("O retangulo nao foi encontrado.\n");
    }
    //aplica gravidade no mundo para atualizar todos os retangulos após mover o retangulo
    aplicaGravidadeMundo(mundo,lista_retangulos,cmd);
}

//função para procurar um retângulo
int procuraRetangulo(COMANDO* cmd, MUNDO* mundo, RETANGULO* lista_retangulos){

    //declaração de variáveis e apontadores
    int x=0,y=0,l=0,h=0,qtde_retangulos=0,i=0,j=0,find_x=0,find_y=0,index_returned=0;

    qtde_retangulos = mundo->qtde_retangulos;
    find_x = (cmd->x)-1;
    find_y = (cmd->y)-1;

    //só procura retangulos se o mundo não estiver vazio
    if(qtde_retangulos != 0){
     
        for (i = 0; i<qtde_retangulos; i++){
        
            x = (lista_retangulos)[i].x;
            y = (lista_retangulos)[i].y;
            l = (lista_retangulos)[i].l;
            h = (lista_retangulos)[i].h;
           
            if((find_x>=x) && (find_x<=x+l) && (find_y>=y) && (find_y<=y+h)){
                index_returned = i;
                break;
            }
            else{

                index_returned = 999;
            }
        } 
        return index_returned;
    }
    else{
        printf("O mundo esta vazio. Nao e possivel procurar o retangulo.\n");
        return 999;
    }
}

//função para gravar o retangulo no mapa do mundo
/*
XXXXXXXXXX  Primeira linha
X        X  Lateral
X        X  Lateral
XXXXXXXXXX  Ultima linha
*/
void marcaRetangulo(int x,int y,int l,int h,MUNDO* mundo, COMANDO* cmd){

    //declaração de variáveis e apontadores
    int x_temp=0,y_temp=0;
    
    x_temp=x;

    //grava primeira linha de X
    for(x;x<=l+x_temp;x++){    
        mundo->mundo[x][y] = 1;
    }

    x = cmd->x;
    x_temp=x;

    if(h!=0){
        y++;    
    }
    
    y_temp=y;

    //grava as laterais em X
    for(y;y<(y_temp+h)-1;y++){
        
        for(x;x<=l+x_temp;x++){
            if(x == x_temp || x==l+x_temp){
                mundo->mundo[x][y] = 1;   
            }
            else{
                mundo->mundo[x][y] = 0;    
            } 
        }
        x = cmd->x;
        x_temp = x;
    }

    x = cmd->x;
    x_temp=x;

    //grava a ultima linha em X
    for(x;x<=l+x_temp;x++){
        mundo->mundo[x][y] = 1;
    }
}

//apaga um retangulo do mundo
void limpaRetanguloMundo(int x,int y,int l,int h,MUNDO* mundo){

    //declaração de variáveis e apontadores
    int x_temp=0,y_temp=0,x_temp2=0,y_temp2=0;
    
    x_temp=x;
    x_temp2=x;

    for(x;x<=l+x_temp;x++){    
        mundo->mundo[x][y] = 0;
    }

    x=x_temp2;
    x_temp=x;
    y++;
    y_temp=y;
    y_temp2=y;

    for(y;y<(y_temp+h)-1;y++){
        
        for(x;x<=l+x_temp;x++){
            mundo->mundo[x][y] = 0;    
        }
        x=x_temp2;
        x_temp=x;
    }

    x=x_temp2;
    
    for(x;x<=l+x_temp;x++){
        mundo->mundo[x][y] = 0;
    }
}

//função para "desenhar" o mundo no ecrã
void mostraMundo(MUNDO* mundo){

    //declaração de variáveis e apontadores
    int i=0,j=0;

    printf("Y ^\n"); //nome do eixo

    for(i=MAX_Y-1;i>=0;i--){
        printf("%-2d|",i+1); //eixo y

        for(j=0;j<MAX_X;j++){
            if(mundo->mundo[j][i]==0){
                printf(" ");
            }
            else{
                printf("x");
            }
        }
        
        printf("\n");
    }
    printf("   ");
    for(i=0;i<MAX_X;i++){
        printf("-"); //eixo x
    }
    //nome do eixo e numeração das coordenadas
    printf("> X\n"); 
    printf("   00000000011111111112222222222333333333344444444445555555555666666666677777777778\n");
    printf("   12345678901234567890123456789012345678901234567890123456789012345678901234567890\n");
    printf("\n\n");
}

//função para verificar colisões com limites do mapa do mundo
bool verificaLimitesMundo(int x, int y, int l, int h){

    if((x+l>MAX_X-1) || (y+h>MAX_Y-1)){
        return false;
    }
    else if(x<MIN_X-1 || y<MIN_Y-1){
        return false;
    }
    else{
    return true;    
    }
}

//função aplica gravidade e verifica colisoes
bool aplicaGravidade(MUNDO* mundo, COMANDO* cmd){

    //declaração de variáveis e apontadores
    int y=0,x=0,l=0,h=0,i=0,j=0,colisao=0,y_bottom=0,y_bottom_original=0;

    y = cmd->y;
    x = cmd->x;
    l = cmd->l;
    h = cmd->h;

    y_bottom = y;
    y_bottom_original = y_bottom; //auxiliar para verificar se é a primeira iteração e se colide antes de aplicar gravidade

        while(y_bottom>=MIN_Y-1){
        
            for (j=x;j<=x+l;j++) {
               
                if (mundo->mundo[j][y_bottom]==1) {
                    colisao = 1;
                    break;
                }
            }

            if(colisao == 1 && y_bottom_original != y_bottom){
                y=y_bottom+1; //repoe coordenada 1 posicao antes da colisao
                cmd->y = y;
                return true;
            }
            else if(colisao == 1 && y_bottom_original == y_bottom){
                printf("O retangulo colide com outro retangulo\n");
                return false; //sem atuar a gravidade,as coordenadas inseridas entram em colisão
            }
            else if(colisao == 0 && y_bottom_original == y_bottom && y_bottom==0){
                return true; 
            }

            else{
               y_bottom--; 
            }
           
        }
        if(y_bottom<0){
            y_bottom=0;
        }
    cmd->y = y_bottom;
    return true;
}

//função auxiliar para aplicar gravidade ao mundo inteiro após mover um retângulo
void aplicaGravidadeMundo(MUNDO* mundo, RETANGULO* lista_retangulos, COMANDO* cmd){

    //declaração de variáveis e apontadores
    int qtde_retangulos=0,i=0,x=0,y=0,l=0,h=0,x_old=0,y_old=0;

    qtde_retangulos = mundo->qtde_retangulos;

    for(i=0;i<qtde_retangulos;i++){

        x = (lista_retangulos)[i].x;
        y = (lista_retangulos)[i].y;
        l = (lista_retangulos)[i].l;
        h = (lista_retangulos)[i].h;

        x_old=x;
        y_old=y;

        cmd->y = y;
        cmd->x = x;
        cmd->l = l;
        cmd->h = h;

        //elimina o retangulo original do mundo para poder mover e aplicar gravidade
        limpaRetanguloMundo(x_old,y_old,l,h,mundo);

        if(aplicaGravidade(mundo,cmd)){
       
            //ler coordenadas com gravidade aplicada
            x = cmd->x;
            y = cmd->y;
            l = cmd->l;
            h = cmd->h;

            //atualiza o retangulo na struct
            (lista_retangulos)[i].x = x;
            (lista_retangulos)[i].y = y;
            (lista_retangulos)[i].l = l;
            (lista_retangulos)[i].h = h;

            //grava o retangulo no mundo com as novas coordenadas
            marcaRetangulo(x,y,l,h,mundo,cmd); 
        }
        else{
            //repõe o retangulo original no mundo porque não foi possível atualizar posição com a gravidade
            cmd->x = x_old;
            cmd->y = y_old;
            marcaRetangulo(x_old,y_old,l,h,mundo,cmd);

        }   
    }
}

//função para medir a estabilidade do mundo
void verificaEstabilidade(MUNDO* mundo, RETANGULO* lista_retangulos){

    //declaração de variáveis e apontadores
    int qtde_retangulos_total=0,P_na=0,P_a=0,qtde_retangulos_risco=0,i=0,x=0,x_temp=0,y=0,l=0,temp=0;
    float instabilidade=0.0,P_na_acumulado=0.0,percentagem_P_na=0.0;

    qtde_retangulos_total = mundo->qtde_retangulos;

    //corre todos os retangulos
    if(qtde_retangulos_total>0){
       
        for(i=0;i<qtde_retangulos_total;i++){

            x = (lista_retangulos)[i].x;
            y = (lista_retangulos)[i].y;
            l = (lista_retangulos)[i].l;
            x_temp=x;

            if(y==0){ //retangulo apoiado no eixo nao corre risco de cair
                P_na=0;
                P_a=x+l;
            }
            else{
                P_na=0;
                P_a=0;

                for(x;x<x_temp+l;x++){ //corre a base em x

                    temp = mundo->mundo[x][y-1]; //verifica se tem apoio por baixo
                    
                    if(temp==1){ //tem apoio
                        P_a++;
                    }
                    else{ //não tem apoio
                        P_na++;
                    }
                }
            }

            //adiciona ou não o retangulo à lista dos instáveis 
            if(P_na>P_a){
                qtde_retangulos_risco++; //quantidade total de retangulos em risco de cair
                percentagem_P_na=(100*P_na)/(l); //calcula percentagem do comprimento que não está apoiado
                P_na_acumulado=P_na_acumulado+percentagem_P_na;
            }                                      
            else{
                ;
            }
            
        }
        
        //calcula instabilidade
        instabilidade = P_na_acumulado/qtde_retangulos_risco;
        
        //alerta o utilizador que a instabilidade é igual ou superior a 70%
        if(instabilidade>=LIMITE_INSTABILIDADE){
            printf("********** A INSTABILIDADE DO MUNDO E IGUAL OU SUPERIOR A %.2f%% **********\n\n",LIMITE_INSTABILIDADE);
        }

            //evita mostrar Nan no output quando divide por 0.
            if(isnan(instabilidade)){
                instabilidade = 0.0;
            }
        //mostra sempre a taxa atual de instabilidade do mundo
        printf("Taxa de instabilidade do mundo:%.2f%%\n",instabilidade);
    }
    else{
        printf("Taxa de instabilidade do mundo: Nao e possivel calcular porque o mundo esta vazio.\n\n");
    }
}

