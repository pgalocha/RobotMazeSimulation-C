#include "funcs.h"


/** Função que tem como objetivo principal iniciar o nosso labirinto e permitir ao utilizador decidir como deseja
* fazer a inicializacao do seu labirinto por listas ligadas
*
*
**/
void menu()
{
    LAB first= {"lab",0,0,NULL};
    LAB* pfirst= &first;
    printf("Quantas linhas?\n");
    scanf("%d",&(pfirst->linhas));
    printf("Quantas colunas?\n");
    scanf("%d",&(pfirst->colunas));
    printf(" %d %d \n",pfirst->linhas,pfirst->colunas);
    int choice=0;

    printf("Como deseja iniciar o seu lab?\n");
    printf("1- Manualmente:\n");
    printf("2- Aleatoriamente\n");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        pfirst->array=initlabmanually(pfirst); //Iniciar manualmente
        printlab(pfirst);
        menuRobot(pfirst);
        menu4(pfirst);
        break;
    case 2:
        pfirst->array=initlabautomatically(pfirst); // Inicio automático
        printlab(pfirst);
        menuRobot(pfirst);
        menu4(pfirst);
        break;
    }

}

/**Função para importar de um ficheiro txt um labirinto. Começa por ler o numero de colunas e de linhas
* para criar o array de nlinhas do tipo CELL* , para depois cada CELL* desse array ter uma LL de CELLS*
*/
void importlab(){
    LAB importado={NULL,0,0,NULL};
    LAB *pplab=&importado;
    CELL* ppaux=NULL;
    int linhas, colunas;
    char str[100]="";
    int i=0,j=0,idx=0;
    getchar();
    char strmax[150];
    printf("\n Nome do ficheiro txt. a importar?\n");
    gets(strmax);
    printf("%s .txt importado!\n",strmax);
    FILE*fp=NULL;
    strcat(strmax,".txt");
    fp=fopen(strmax,"r");
    if(fp==NULL){
        printf("Falhou ao abrir ficheiro!");
    }else{
        fscanf(fp,"%s",str);
        fscanf(fp,"%d %d",&colunas,&linhas);
        pplab->colunas=colunas;
        pplab->linhas=linhas;
        pplab->array=(CELL*)malloc(sizeof(CELL)*pplab->linhas);
        ppaux=pplab->array;

        //insere o numero de celulas consoante o numero de colunas introduzidas.
  while(ppaux < pplab->array + pplab->linhas)
    {

        idx++;
        //  printf(" %d \n",ppaux->index);
        for(j=1; j<pplab->colunas; j++)
        {
            insertcell(ppaux,i,j,idx);
            idx++;

        }
        //printlinha(ppaux);
        printf("\n");
        i++;
        j=0;
        ppaux++;
        ppaux->index=idx;
        ppaux->x=j;
        ppaux->y=i;
    }
}
    //cria array dinamico de strings

     char ** ppointer=(char**)malloc(sizeof(char*)*pplab->linhas);

     for(i=0;i<pplab->linhas;i++){
       *(ppointer+i)=(char*)malloc(sizeof(char)*pplab->colunas);
     }

     //copia para o array dinamico de strings cada linha do ficheiro txt.
      for(i=0;i<pplab->linhas;i++){
            fscanf(fp,"%s",*(ppointer+i));
      }
printf(" LABIRINTO IMPORTADO!\n");
   i=0;
   j=0;
    CELL* pparray=pplab->array;
   while(pparray < pplab->array + pplab->linhas)
        {
        j=0;
        CELL* paux=pparray;
       while(paux!=NULL)
       {
            paux->simbolo=*(*(ppointer+i)+j);//faz a atribuição de cada elemento lido e presente no array de strings para dentro do lab crio por LL
            paux=paux->proximo;
            j++;
        }
        i++;
        pparray++;
    }
    printlab(pplab);//imprime o lab
    menu4(pplab);//vai para o menu 4

}
/** para entrar neste menu é necessário já ter um lab criado e preenchido.
* tem uma func que vai buscar automaticamente a localização do robot para que depois seja possivel aplicar-lhe
* os comandos pelo requisito proposto.
* @param LAB* pplab labirinto já criado e preenchido anteriormente nos outros menus.
*/
void menu4(LAB* pplab){
    ROBOT robot={NULL,0,0,'c'};
    ROBOT* probot=&robot;
    getrobot(pplab,probot);
    printf("\n Robot colocado em %d %d %c\n",probot->posx,probot->posy,probot->orien);
    printf("Menu de Requisitos ParteDinamica:\n");
    printf("1-Executar Pedaço de Codigo:\n");
    printf("2-Permutaçoes s/ repeticaço\n");
    int choice=0;
    int n;
   // getchar();
    scanf("%d",&choice);
    switch(choice){
    case 1:
        codigoexecuta(pplab,probot);//chamada da funcao para executar um codigo em LL naquele labirinto
        break;
    case 2:

        printf("Quantos codigos pretende inserir?\n");
        scanf("%d",&n);
        fazermatrix(n,pplab);
        break;
    }

}

/**Func que respeita o requisito número 3 , permitir executar uma sequencia de movimentos.
* cada movimento corresponde a um simbolo de uma struct do tipo CODIGO que contem um pnext e um char simbolo.
* a inserçao do pnext é feita sempre na cauda da LL.
*  @param LAB* pplab labirinto
*  @param ROBOT* probot apontador para a struct do nosso robot criado
*/
void codigoexecuta(LAB*pplab,ROBOT* probot){
    printf("\n****LAB ORIGINAL****\n");
    printlab(pplab);
    char c;
    //getchar();
    CODIGO* pfirst=NULL;
    //int i=0;
    printf(" Insira o seu código a executar , para sair insira 'E'\n");
    scanf("%c",&c);
    pfirst=(CODIGO*)malloc(sizeof(CODIGO));
    pfirst->simbolo=c;
    pfirst->pnext=NULL;
    while(c!='E'){ //paramos de inserir simbolos na LL quando escrevemos E
    scanf("%c",&c);
    if(c=='E'){
            insercodigo(pfirst,'E');
        break;
    }
    insercodigo(pfirst,c); //Inserção do código/simbolo na cauda
    }
    printcodigo(pfirst); //mostra todo o codigo inserido
    CODIGO* paux=pfirst; //auxiliar que está posicionada no primeiro elemento da LL
    int pont=0;
    while(paux->simbolo!='E'){
            if(paux->simbolo=='0'){
                pont=foward(pplab,probot,pont);
//            }else if(paux->simbolo=='6'){
//                pont=back(pplab,probot);
//            }else if(paux->simbolo=='3'){
//                rotateright(pplab,probot);
//            }else if(paux->simbolo=='9'){
//                rotateleft(pplab,probot);
            }else if(paux->simbolo=='6'){
            pont=back(pplab,probot,pont);

            }else if(paux->simbolo=='3'){
            turnright(pplab,probot);

            }else if(paux->simbolo=='9'){
            turnleft(pplab,probot);

            }
            paux=paux->pnext;
    }
    printcodigo(pfirst);
    printf("Pontuação do código acima referido : %d \n",pont);
    exportacodigopont(pfirst,pont);//exporta para pdf o codigo inserido(LL) e a pont máx obtida

}

/**Func que vai exportar a lista ligada com os códigos digitados no requesito acima e que vai guardar em ficheiro txt
* a pontuação máxima.
* @param CODIGO* pcodigo apontador para o primeiro elemento struct CODIGO
* @param int pont a nossa pontuacao maxima
*/
void exportacodigopont(CODIGO* pcodigo,int pont){
    FILE* fp=fopen("ExecutaCodigo.txt","w");
    fprintf(fp,"CodigoExecutado no Lab:\n");
    while(pcodigo!=NULL){
            fprintf(fp,"%c",pcodigo->simbolo);
            pcodigo=pcodigo->pnext;
    }
    fprintf(fp,"Pontuacao Final = %d PONTOS\n",pont);
    fprintf(fp,"******************************\n");
    fclose(fp);
}

/** Fun para virar à direita no lab e actualizar na struct do Robot
* @param LAB* pplab o nosso labirinto
* @param ROBOT* probot o nosso robot
*/

void turnright(LAB*pplab,ROBOT*probot){
    printf("\n Entrou aqui , Orien = %c \n",probot->orien);
    char orien=probot->orien;
    if(orien=='N'){//Atualiza a variavel do Robot apos rotate
        orien='E';

    }else if(orien=='S'){
    orien='E';
    }else if(orien=='O'){
    orien='S';
    }else if(orien=='E'){
    orien='N';
    }
    probot->orien=orien;
    printf(" Nova Orien %c \n",probot->orien);
    CELL* ppaux=pplab->array;
    CELL* pll=NULL;
    while(ppaux < pplab->array + pplab->linhas){ //vai procurar o robot no Lab e mudar pela nova variavel
            pll=ppaux;
    while(pll!=NULL){
        if(pll->x==probot->posx && pll->y == probot->posy){
            pll->simbolo=probot->orien;
        }
        pll=pll->proximo;
    }
    ppaux++;
    }

    printlab(pplab);
}
/**Faz o oposto da rotate right mas com o mesmo raciocinio, para melhor descrição
* ver rotate right
*/
void turnleft(LAB*pplab,ROBOT*probot){
    printf("\n Entrou aqui , Orien = %c \n",probot->orien);
    char orien=probot->orien;
    if(orien=='N'){
        orien='O';

    }else if(orien=='S'){
    orien='O';
    }else if(orien=='O'){
    orien='N';
    }else if(orien=='E'){
    orien='S';
    }
    probot->orien=orien;
    printf(" Nova Orien %c \n",probot->orien);
    CELL* ppaux=pplab->array;
    CELL* pll=NULL;
    while(ppaux < pplab->array + pplab->linhas){
            pll=ppaux;
    while(pll!=NULL){
        if(pll->x==probot->posx && pll->y == probot->posy){
            pll->simbolo=probot->orien;
        }
        pll=pll->proximo;
    }
    ppaux++;
    }

    printlab(pplab);
}

/**Func que é executada quando introduzimos um 0 no codigo
* @param LAB* pplab o nosso labirinto criado
* @param ROBOT* probot o nosso robot
* @param int pont a pontuacao actual do robot
*/

int foward(LAB*pplab,ROBOT*probot,int pont){
    printf("Entrou aqui\n");
    int idx;
    char clab;
    int idxtroca;
    printf(" %d %d",probot->posx,probot->posy);
    if(probot->orien=='N'){
         if(probot->posy > 0){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas); //calcula o idx atual do robot
        clab=getconteudo(idx-pplab->colunas,pplab,&idxtroca);// verifica o conteudo na celula para onde vai o robot e atualiza o idxtroca dessa mesma celula
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posy=probot->posy-1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posy=probot->posy-1;

            }
        }else   if(clab=='W'){
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posy=probot->posy-1;
        }
    }
    }else if(probot->orien=='S'){
         if(probot->posy < pplab->linhas-1){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx+pplab->colunas,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posy=probot->posy+1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posy=probot->posy+1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posy=probot->posy+1;
        }
    }
    }else if(probot->orien=='E'){
         if(probot->posx < pplab->colunas-1){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx+1,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posx=probot->posx+1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posx=probot->posx+1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posx=probot->posx+1;
        }
    }
    }else if(probot->orien=='O'){
         if(probot->posx > 0){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx-1,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posx=probot->posx-1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posx=probot->posx-1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posx=probot->posx-1;
        }
    }
    }
    printlab(pplab);
    printf(" %d %d",probot->posx,probot->posy);
    printf("\nErrou \n");
    return pont;
    }
/**Faz o contrário que o Foward, mas o raciocinio é o mesmo
* para melhor explicação ver Foward.
*/
int back(LAB*pplab,ROBOT*probot,int pont){
    printf("Entrou aqui\n");
    int idx;
    char clab;
    int idxtroca;
    printf(" %d %d",probot->posx,probot->posy);
    if(probot->orien=='N'){
         if(probot->posy < pplab->linhas-1){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx+pplab->colunas,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posy=probot->posy+1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posy=probot->posy+1;

            }
        }else   if(clab=='W'){
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posy=probot->posy+1;
        }
    }
    }else if(probot->orien=='S'){
         if(probot->posy > 0){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx-pplab->colunas,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posy=probot->posy-1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posy=probot->posy-1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posy=probot->posy-1;
        }
    }
    }else if(probot->orien=='E'){
         if(probot->posx > 0){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx-1,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posx=probot->posx-1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posx=probot->posx-1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posx=probot->posx-1;
        }
    }
    }else if(probot->orien=='O'){
         if(probot->posx < pplab->colunas-1){
        idx=calculaidx(probot->posx,probot->posy,pplab->colunas);
        clab=getconteudo(idx+1,pplab,&idxtroca);
        printf(" %c %d %d",clab,idx,idxtroca);
        if(clab=='$'){
                swap(idx,idxtroca,pplab);
                pont=pont+10;
                probot->posx=probot->posx+1;
        }else   if(clab=='B'){
            if(pont>=5){
                swap(idx,idxtroca,pplab);
                pont=pont-5;
                probot->posx=probot->posx+1;

            }
        }else   if(clab=='W'){
            printf("É uma Parede!!\n");
            if(pont>=1){
                printf("É uma Parede!!\n");
                pont=pont-1;
            }
        }else   if(clab=='0'){
            swap(idx,idxtroca,pplab);
            probot->posx=probot->posx+1;
        }
    }
    }
    printlab(pplab);
    printf(" %d %d",probot->posx,probot->posy);
    printf("\nErrou \n");
    return pont;
    }

/** Fun que recebe dois indíces , recebe o labirinto e vai garantir que vai ser efuada a troca dos seus simbolos
*
*@param int idxrobot indice do robot
*@param int troca indice pelo qual vai trocar
*@param LAB* pplab onde vão ser feitas as alteraçoes
*/
void swap(int idxrobot,int troca,LAB* pplab){
    printf("Entrou aqui! \n");
    char c;
    CELL* ppaux=pplab->array;
    CELL* pll=NULL;
    while(ppaux < pplab->array + pplab->linhas){
            pll=ppaux;
    while(pll!=NULL){
        if(pll->index==idxrobot){
            c=pll->simbolo;
            pll->simbolo='0';
        }
        pll=pll->proximo;
    }
    ppaux++;
    }
    ppaux=pplab->array;
    while(ppaux < pplab->array + pplab->linhas){
            pll=ppaux;
    while(pll!=NULL){
        if(pll->index==troca){
            pll->simbolo=c;
        }
         pll=pll->proximo;
    }
    ppaux++;
    }

}

/**Func que vai procurar o conteudo pelo qual o robot vai trocar através do eu idx,atualiza o endereço que recebeu para saber por qual indxtroca vai trocar
*@param int idx indice do robot
*@param LAB* pplab lab onde vai ser feita a procura
*@param int* idxtroca apontador para o inteiro onde está o indxtroca que queremos trocar
* @return char o char dentro da casa para onde vai ser trocado o robot
* Devolver o caracter dentro ca celula pela qual ele vai trocar.*/
char getconteudo(int idx,LAB*pplab,int * idxtroca){
    CELL* ppaux=pplab->array;
    CELL* ppone=NULL;
    char c;
    while(ppaux < pplab->array + pplab->linhas){
        ppone=ppaux;
        while(ppone!=NULL){
                if(ppone->index==idx){
                    c=ppone->simbolo;
                    *(idxtroca)=ppone->index;
                    }
                ppone=ppone->proximo;
        }
        ppaux++;
    }

    return c;

}

/** Imprime toda a Lista Ligada de codigo para ser executado no lab
* @param CODIGO* pfirst apontador para a primeira struct do codigo a executar
*
*/
void printcodigo(CODIGO* pfirst){
    while(pfirst!=NULL){
        printf("%c",pfirst->simbolo);
        pfirst=pfirst->pnext;
    }

}

/** Insere na cauda da lista ligada de codigos o proximo codigo
* @param CODIGO* pfirst apontador para a primeira struct do codigo a executar
* @param char c caracter a ser inserido
*/
void insercodigo(CODIGO*pfirst,char c){
    CODIGO*pnew=(CODIGO*)malloc(sizeof(CODIGO));
    pnew->simbolo=c;
    while(pfirst->pnext!=NULL){
            pfirst=pfirst->pnext;
    }
    pfirst->pnext=pnew;
    pnew->pnext=NULL;
}

/** Percorre o Lab até encontrar o robot, assim que é encontrado atualiza os valores do apontador recebido
* @param LAB* pplab o nosso lab
* @param ROBOT* robot o apontador para a nossa struct robot que queremos atualizar com os valores encontrados
*/
void getrobot(LAB* pplab,ROBOT* robot){
      CELL* pparray=pplab->array;
   while(pparray < pplab->array + pplab->linhas)
        {
        CELL* paux=pparray;
       while(paux!=NULL)
       {
           if(paux->simbolo=='N' ||paux->simbolo=='S' ||paux->simbolo=='E' ||paux->simbolo=='O'){
                robot->orien=paux->simbolo;
           robot->posx=paux->x;
           robot->posy=paux->y;
           return;
           }
            paux=paux->proximo;

        }

        pparray++;
    }
}



/**Menu que nos permite decidir como queremos fazer a inserçao do Robot se manualmente ou automaticamente
*@param LAB* plab
*/
void menuRobot(LAB* plab)
{
    int choice=0;
    ROBOT p1= {NULL,0,0,'0'};
    ROBOT * pp1=&p1;
    printf("Como deseja inserir o seu Robot?\n");
    printf("1-Aleatoriamente\n");
    printf("2-Manualmente\n");
    getchar();
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        pp1=insererobot(plab);
        printlab(plab);
        menu3(plab,pp1);
        break;
    case 2:
        pp1=insereturobot(plab);
        printf("%d %d %c \n",pp1->posx,pp1->posy,pp1->orien);
        printlab(plab);
        menu3(plab,pp1);
        break;

    }

}

/** Menu que é automaticamente executado apos criar mos um novo labirinto já com o robot introduzido*
*@param LAB* plab o nosso lab
*@param ROBOT* probot o nosso robot
*/
void menu3(LAB* plab,ROBOT* probot)
{
    int choice=0;
    printf("Que deseja fazer ao seu lab?\n");
    printf("1-Exportar para txt.\n");


    scanf("%d",&choice);

    switch(choice)
    {
    case 1:
        exportfortxt(plab);
        break;

    }


}

/**Func que vai exportar para ficheiro txt o nosso labirinto criado até ao momento.
* Exporta o numero de colunas e o numero de linhas seguido do conteudo do Lab.
*@param LAB* plab
*
*/
void exportfortxt(LAB* plab)
{
    getchar();
    char strmax[150];
    printf("\n Nome do ficheiro txt. a exportar?\n");
    gets(strmax);
    printf("%s .txt criado!\n",strmax);
    FILE*fp=NULL;
    strcat(strmax,".txt");
    fp=fopen(strmax,"w");

    fprintf(fp,"Labirinto:\n");
    fprintf(fp,"%d %d\n",plab->colunas,plab->linhas);

    CELL* pparray=plab->array;
    while(pparray < plab->array + plab->linhas)
    {
        CELL* paux=pparray;
        while(paux!=NULL)
        {
            fprintf(fp,"%c",paux->simbolo);
            paux=paux->proximo;
        }
        pparray++;
        fprintf(fp,"\n");
    }
    fclose(fp);
    printf("\nFicheiro Criado com sucesso!!!!\n");
}

/**Insercao automatica do robot
*@param LAB* plab o nosso lab
*@return ROBOT* retorna um apontador para um tipo struct robot , que representa a localizaçao do nosso robot
*
*/
ROBOT* insererobot(LAB* plab)
{
    ROBOT p1= {NULL,0,0,'0'};
    ROBOT * pp1=&p1;
    char str[5]="NSEO";
    int n=rand()% 4;
    char c=str[n];
    int indice;
    int posx=rand()% plab->colunas,posy=rand() % plab->linhas;
    printf(" \n %d COLUNA %d LINHA %c ORIEN\n",posx,posy,c);
    pp1->orien=c;
    pp1->posx=posx;
    pp1->posy=posy;
    indice=calculaidx(posx,posy,plab->colunas);

    CELL* pparray=plab->array;
    while(pparray < plab->array + plab->linhas)
    {
        CELL* paux=pparray;
        while(paux!=NULL)
        {
            if(paux->index==indice)
            {
                paux->simbolo=c;
                return pp1;
            }
            paux=paux->proximo;
        }
        pparray++;
        printf("\n");
    }

    return pp1;


}

/**Insercao manual do robot
*@param LAB* plab o nosso lab
*@return ROBOT* retorna um apontador para um tipo struct robot , que representa a localizaçao do nosso robot
*
*/
ROBOT* insereturobot(LAB* plab)
{
    ROBOT p1= {"Robot",0,0,'0'};
    ROBOT * pp1=&p1;
    char orien;
    int posx,posy;
    getchar();
    printf("Orientacao do Robot?\n");
    scanf("%c",&orien);
    pp1->orien=orien;
    printf("Insira as coordenadas y e x do Robot com um espaço entre elas:\n");
    scanf("%d %d",&posx,&posy);
    pp1->posx=posx;
    pp1->posy=posy;
    //printf("%d %d %c \n",pp1->posx,pp1->posy,pp1->orien);
    int indice;
    indice=calculaidx(posx,posy,plab->colunas);

    CELL* pparray=plab->array;
    while(pparray < plab->array + plab->linhas)
    {
        CELL* paux=pparray;
        while(paux!=NULL)
        {
            if(paux->index==indice)
            {
                paux->simbolo=orien;
                return pp1;
            }
            paux=paux->proximo;
        }
        pparray++;
        printf("\n");
    }


    return pp1;
}

/**Func matemática que calcula o idx dado um x , y e o numero de colunas do lab
*@param int posx a posiçao em x
*@param int posy a posicao em y
*@param int colunas o numero de colunas
* @return int o nosso indice
*/
int calculaidx(int posx,int posy,int colunas)
{
    return (colunas*posy)+posx;
}
void printlab(LAB* plab)
{
    CELL* pparray=plab->array;
    while(pparray < plab->array + plab->linhas)
    {
        CELL* paux=pparray;
        while(paux!=NULL)
        {
            printf("%c ",paux->simbolo);
            paux=paux->proximo;
        }
        pparray++;
        printf("\n");
    }
}

/**Iniciar manualmente o nosso labirinto, vai ser retornado o endereço para o 1 elemento do array de listas ligadas do lab
*@param LAB* pplab o nosso labirinto
*@return CELL* o apontador para o primeiro elemento de um array de listas ligadas
*
*
*/
CELL* initlabmanually(LAB* pplab)
{
    CELL* ppaux=NULL;
    CELL* pfinal=NULL;
    int i=0,j=0;
    int idx=0;
    char c;
    printf(" Labirinto criado Manualmente com %d Linhas e %d Colunas\n",pplab->linhas,pplab->colunas);
    ppaux=pplab->array;
    ppaux=(CELL*)malloc(sizeof(CELL)*pplab->linhas);
    pfinal=ppaux;
    ppaux->index=idx;
    ppaux->x=i;
    ppaux->y=j;
    getchar();
    printf("Insira o caracter para as coordenadas x:%d y:%d idx:%d \n",ppaux->x,ppaux->y,ppaux->index);
    scanf("%c",&c);
    ppaux->simbolo=c;
    while(ppaux < pfinal + pplab->linhas)
    {
        idx++;
        for(j=1; j<pplab->colunas; j++)
        {
            insertcellmanualmente(ppaux,i,j,idx);
            idx++;
        }
        printlinha(ppaux);
        printf("\n");
        i++;
        j=0;
        ppaux++;
        ppaux->index=idx;
        ppaux->x=j;
        ppaux->y=i;
        getchar();
        printf("Insira o caracter para as coordenadas x:%d y:%d idx:%d \n",ppaux->x,ppaux->y,ppaux->index);
        scanf("%c",&c);
        ppaux->simbolo=c;

    }
    return (ppaux-pplab->linhas);
}


/**Iniciar automaticamente o nosso labirinto, vai ser retornado o endereço para o 1 elemento do array de listas ligadas do lab
*@param LAB* pplab o nosso labirinto
*@return CELL* o apontador para o primeiro elemento de um array de listas ligadas
*
*
*/

CELL* initlabautomatically(LAB* pplab)
{
    CELL* ppaux=NULL;
    CELL* pfinal=NULL;
    int i=0,j=0;
    int idx=0;
    char str[5]="0$WB";
    int n=0;
    char c;
    printf(" Labirinto criado Automaticamente com %d Linhas e %d Colunas\n",pplab->linhas,pplab->colunas);
    ppaux=pplab->array;
    ppaux=(CELL*)malloc(sizeof(CELL)*pplab->linhas);
    pfinal=ppaux;
    ppaux->index=idx;
    //printf(" %p \n",ppaux);
    ppaux->x=i;
    ppaux->y=j;
    n=rand()% 4;
    c=str[n];
    ppaux->simbolo=c;
    while(ppaux < pfinal + pplab->linhas)
    {

        idx++;
        //  printf(" %d \n",ppaux->index);
        for(j=1; j<pplab->colunas; j++)
        {
            insertcell(ppaux,i,j,idx);
            idx++;

        }
        printlinha(ppaux);
        printf("\n");
        i++;
        j=0;
        ppaux++;
        ppaux->index=idx;
        ppaux->x=j;
        ppaux->y=i;
        n=rand()% 4;
        c=str[n];
        ppaux->simbolo=c;
    }
    // printf(" %p FINAL\n",(ppaux-pplab->linhas));
    return (ppaux-pplab->linhas);
}

/**Func para imprimir uma linha , por exemplo, do primeiro elemento do array de listas ligadas
*@param CELL* pfirst elemento do array, que desejamos imprimir a sua Lista Ligada
*
*/
void printlinha(CELL* pfirst)
{
    CELL* paux=pfirst;
    while(paux!=NULL)
    {
        printf("%c ",paux->simbolo);
        paux=paux->proximo;
    }
}

/** Func para inserir uma celula na cauda de um lab com um elemento random dentro dos que são possiveis de inserir
*@param CELL* pfirst recebe o pfirst e vai inserir na cauda
*@param int y a sua posicao no lab em y
*@param int x a sua posicao no lab em x
*@param int idx o seu idx no lab
*/
void insertcell(CELL* pfirst,int y,int x,int idx)
{
    CELL* paux= pfirst;
    CELL* pnew=(CELL*)malloc(sizeof(CELL));
    char str[5]="0$WB";
    int n=0;
    char c;
    n=rand()% 4;
    c=str[n];
    pnew->anterior=NULL;
    pnew->baixo=NULL;
    pnew->cima=NULL;
    pnew->proximo=NULL;
    pnew->index=idx;
    pnew->x=x;
    pnew->y=y;
    pnew->simbolo=c;
    while(paux->proximo!=NULL)
    {
        paux=paux->proximo;
    }

    paux->proximo=pnew;
    pnew->anterior=paux;

}

/** Func para inserir uma celula na cauda de um lab com um elemento escolhido manualmente dentro dos que são possiveis de inserir
*@param CELL* pfirst recebe o pfirst e vai inserir na cauda
*@param int y a sua posicao no lab em y
*@param int x a sua posicao no lab em x
*@param int idx o seu idx no lab
*/

void insertcellmanualmente(CELL* pfirst,int y,int x,int idx)
{
    CELL* paux= pfirst;
    CELL* pnew=(CELL*)malloc(sizeof(CELL));
    char c;
    pnew->anterior=NULL;
    pnew->baixo=NULL;
    pnew->cima=NULL;
    pnew->proximo=NULL;
    pnew->index=idx;
    pnew->x=x;
    pnew->y=y;
    getchar();
    printf("Insira o caracter para as coordenadas x:%d y:%d idx:%d \n",pnew->x,pnew->y,pnew->index);
    scanf("%c",&c);
    pnew->simbolo=c;
    while(paux->proximo!=NULL)
    {
        paux=paux->proximo;
    }

    paux->proximo=pnew;
    pnew->anterior=paux;

}


/**variável global**/
int iterations=0;

/** Função que troca valores de dois apontadores
*     @param int* y
*     @param int* x
*/
void swapint(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/** Função que origina as permutações por linha da nossa matriz
*     @param int* a array de elementos
*     @param int l elemento mais pequeno
*     @param int r numero de elementos
*     @param int size tamanho
*     @param int** matrix a matriz criada e para ir sendo preenchida linha  a linha
*     @param int linhas
*     @param int colunas
*/
void permute(int *a, int l, int r, int size,int ** matrix,int linhas,int colunas)
{
    int i;
    if (l == r)
    {
        printArr(a,size,matrix,iterations);
        iterations++;
    }
    else
    {
        for (i = l; i <= r; i++)
        {
            swapint((a+l), (a+i));
            permute(a, l+1, r, size,matrix,linhas,colunas);
            swapint((a+l), (a+i)); //backtrack
        }
    }
}


/** Função que recebe a matriz e a linha dessa matriz e a imprime
*     @param int** matrix matriz de permutas
*     @param int size tamanho
*     @param int* a o nosso array de elementos, ordenado segundo essa linha da matriz
*     @param int vai a linha em que vai ser preenchida a nossa matriz
**/

void printArr(int* a, int size,int ** matrix,int vai)
{
    int i=0;
    for(i=0; i<size; i++)
    {
        *(*(matrix+(vai))+i)=a[i];
        // printf("%d",a[i]);
        //printf("%d",*(*(matrix+(vai))+i));
    }

//    printf("\n");
//    printf(" VAI :%d \n",(vai));
}

void insertvalor(CELULAM* parray,int n){
    CELULAM* pnovo=(CELULAM*)malloc(sizeof(CELULAM));
    pnovo->valor=n;
    while(parray->pnext!=NULL){
        parray=parray->pnext;
    }
    parray->pnext=pnovo;
}


/* Driver program to test above functions */

/** Função que receb o array de strings referentes aos comandos guardados e a matriz dos comandos a executar pela ordem que esta mesma impõe
*     @param int n numero de comandos(colunas) da matriz
*      @return int** retorna o endereço que aponta para uma matriz vazia criada pronta a ser preenchida
*
*/
void fazermatrix(int n,LAB* plab)
{
    ROBOT p1={NULL,0,0,'0'};
    ROBOT* ppr=&p1;
    getrobot(plab,ppr);
    int** matrix=NULL;
    matrix=fazerumamatrix(n);
    int i=0,j=0;
    int arr[n];
    for(i=0; i<n; i++)
    {
        arr[i]=i;
    }
    int linhas=fatorial(n);
    MATRIZ matriz={NULL};
    MATRIZ* pmatriz=&matriz;
    pmatriz->pfirst=(CELULAM*)malloc(sizeof(CELULAM)*linhas);
    CELULAM* paux=pmatriz->pfirst;
    i=0;
    j=0;
    while(paux < pmatriz->pfirst + linhas){
            paux->x=j;
            paux->y=i;
            printf("%d %d %d\n",paux->y,paux->x,*(*(matrix+i)+j));
            for(j=1;j<n;j++){
                    printf("%d %d %d\n",i,j,*(*(matrix+i)+j));
                    insertmatrizcell(paux,i,j,*(*(matrix+i)+j));
            }
            j=0;
            i++;
            paux++;
    }
    CELULAM* pnovo=pmatriz->pfirst;
    CELULAM* pmanja=NULL;
    while(pnovo < pmatriz->pfirst + linhas){
            pmanja=pnovo;
    while(pmanja!=NULL){
            printf("\n %dx %dy ",pmanja->x,pmanja->y);
            pmanja=pmanja->pnext;
    }
    pnovo++;

    }
    printf("%d\n", iterations);
    char str[5]="";
    char ** ppointer=NULL;
    ppointer=(char**)malloc(sizeof(char*)*n);
    for(i=0;i<n;i++){
            getchar();
        printf("Digite Codigo nr %d \n",i);
        fgets(str,5,stdin);
            *(ppointer+i)=(char*)malloc(sizeof(char)*5);
            strcpy(*(ppointer+i),str);
    }

     for(i=0;i<n;i++){

            printf("%s \n",*(ppointer+i));

    }
    int pont;
    int apont[linhas];
    j=0;
    i=0;
    CELULAM* corre=pmatriz->pfirst;
    CELULAM* phelp=NULL;

    while(corre < pmatriz->pfirst + linhas){
            while(*(*(matrix+corre->valor)+j)!='/0'){
                if(*(*(matrix+corre->valor)+j)=='0'){
                    pont=foward(plab,ppr,pont);
                }else if(*(*(matrix+corre->valor)+j)=='6'){
                    pont=foward(plab,ppr,pont);
                }else if(*(*(matrix+corre->valor)+j)=='3'){
                    turnright(plab,ppr);
                }else if(*(*(matrix+corre->valor)+j)=='9'){
                    turnleft(plab,ppr);
                }
                j++;
            }
            phelp=corre->pnext;
            j=0;
            while(phelp!=NULL){
                    while(*(*(matrix+phelp->valor)+j)!='/0'){
                if(*(*(matrix+phelp->valor)+j)=='0'){
                    pont=foward(plab,ppr,pont);
                }else if(*(*(matrix+phelp->valor)+j)=='6'){
                    pont=foward(plab,ppr,pont);
                }else if(*(*(matrix+phelp->valor)+j)=='3'){
                    turnright(plab,ppr);
                }else if(*(*(matrix+phelp->valor)+j)=='9'){
                    turnleft(plab,ppr);
                }
                j++;
            }
            phelp=phelp->pnext;
            j=0;
            }
            apont[i]=pont;
            pont=0;
            corre++;
            i++;
    }
    printf(" \n ");
    for(i=0;i<linhas;i++){
        printf(" %d ",apont[i]);
    }


}

int** fazerumamatrix(int n)
{


    int i=0;
    int arr[n];
    for(i=0; i<n; i++)
    {
        arr[i]=i;
    }
    int linhas=fatorial(n);
    int** matrix=(int**)malloc(sizeof(int*)*linhas);
    for(i=0; i<linhas; i++)
    {
        *(matrix+i)=(int*)malloc(sizeof(int)*n);
    }

    permute(arr,0,n-1, n,matrix,linhas,n);

    //printf("URSO%d",*(*(matrix+0)+0));

    printmatrix(matrix,linhas,n);
//    permute(str, 0, n-1);
//permute(n);
    printf("%d\n", iterations);

    return matrix;

}

/** Função que recebe a matriz com as suas espec. e a imprime ao utilizador
*     @param int** matrix a nossa matriz
*     @param int linhas linhas
*     @param int colunas colunas
*/
void printmatrix(int** matrix,int linhas,int colunas)
{
    int i=0,j=0;
    printf(" %d LINHAS %d COLUNAS \n",linhas,colunas);
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            printf("%d",*(*(matrix+i)+j));
        }
        printf("\n");
    }

}

void insertmatrizcell(CELULAM* paux,int y,int x,int valor){
    CELULAM* pnovo=NULL;
    pnovo=(CELULAM*)malloc(sizeof(CELULAM));
    pnovo->x=x;
    pnovo->y=y;
    pnovo->valor=valor;
    while(paux->pnext!=NULL){
        paux=paux->pnext;
    }
    paux->pnext=pnovo;
}

/** Função que recebe o numero de elementos e calcula o seu fatorial
*    @param int n numero de elementos
* @return int retorna um int. que representa o fatorial do numero de elementos
*/
int fatorial(int n)
{
    int resultado=1,i=0;
    for(i=n; i>0; i--)
    {
        resultado=resultado*i;
    }
    return resultado;
}
