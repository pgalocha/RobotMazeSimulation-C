#include "func.h"

/** Função que representa o menu inicial ao utilizador , disponiblizando apenas 3 opções que irão conduzir ao segundo menu.
*     @param char** pplab Labirinto criado previamente,no caso da primeira vez, recebe um pplab=NULL
*
*/

void menu(char** pplab)
{

    int i=0;
    int linhas,colunas;
    printf(" *********MENU*******\n");
    printf("1:Importar Labiritno\n");
    printf("2:Criar Labiritno\n");
    printf("3:Continuar(Escolha esta se ja tiver um labirinto de trás:\n");
    printf("4:EXIT\n");
    printf("\nQue deseja fazer?:");
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        pplab=importalab(&linhas,&colunas);
        menu2(pplab,linhas,colunas);
        break;
    case 2:
        criatulab();
        break;

     case 3:
        if(pplab==NULL){
            printf("Nao tem lab de trás, tente outra vez! \n");
            menu(pplab);
        }else{
        menu2(pplab,linhas,colunas);
        }
        return;


    case 4:
        printf("GoodBye!\n");
        return;
    }
}

/**
* Função que é acionada quando o utilizador deseja criar um Labirinto em vez de importa-lo. Permite a construção Manual ou aleatória do Labirinto.
*/
void criatulab()
{

    char** ppointer=NULL;
    int linhas,colunas;
    char c;


    printf("Quantas linhas?:\n");
    scanf("%d",&linhas);

    printf("\n Quantas colunas?:\n");
    scanf("%d",&colunas);

    if(colunas==2 && linhas==2)
    {
        printf("Insira novamente!!!!\n");
        criatulab();
    }

    ppointer=initmatriz(ppointer,linhas,colunas);
    startmatriz(ppointer,linhas,colunas);
    printmatriz(ppointer,linhas,colunas);
    getchar();
    printf("Como deseja criar o seu labirinto?(M-manual,A-aleatorio:\n");
    c=getchar();
    switch(c)
    {

    case 'A':
        preenchematriz(ppointer,linhas,colunas);
        printmatriz(ppointer,linhas,colunas);
        getchar();
        break;

    case 'M':
        preenchetumatriz(ppointer,linhas,colunas);
        colocarobot(ppointer,linhas,colunas);
        printmatriz(ppointer,linhas,colunas);
        getchar();
        break;

    }
    menu2(ppointer,linhas,colunas);

}


/** O nosso segundo Menu, que já disponibliza e tem como pré requisito receber um Labirinto já criado e preenchido e que permite ao utilizador realizar os requerimentos dos projeto
*     @param char** ppointer labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/
void menu2(char** ppointer,int linhas,int colunas){
    printf("Que deseja fazer ao Labirinto?:\n");
    printf("P- Permutar sem repeticoes?:\n");
    printf("T- Inserir Codigos:\n");
    printf("U- Criar a sua propria matriz de permutaçoes:\n");
    printf("S- Guardar em ficheiro .txt:\n");
    printf("A- Alterar/editar Labirinto:\n");
    printf("B- Export to binaryFile:\n");
    printf("L- Codigo a Codigo:\n");
    printf("I- Autonomia:\n");
   char c=getchar();
    switch(c)
    {

    case 'P':
        permuta(ppointer,linhas,colunas);
        break;

    case 'T':
        executacodigo(ppointer,linhas,colunas);
        break;
    case 'U':
        tuapermuta(ppointer,linhas,colunas);
        break;
        case 'S':
        exportalab(ppointer,linhas,colunas);
        break;
         case 'A':
        alteralab(ppointer,linhas,colunas);
        break;
          case 'B':
        txt();
        break;
          case 'L':
            //codigo(ppointer,linhas,colunas);
            matrizdecodigos(ppointer,linhas,colunas);
        break;

        case 'I':

            autonomia(ppointer,linhas,colunas);
        break;
    }
}


/** Função que simula a autonomia do robot e procesa quatro movimentos, 00, 300,900,66, ou seja percorrer duas casas
nas quatro direcções. Vai percorrer esses 4 códigos até que a str auxiliar chegue a um tamanho de códigos superior a 20.
assim que chegar a 20 ele interrompe o ciclo while final. Baseia-se em 4 movimentos acima referidos, no final cada movimento
tem a sua pontuação. Dessa pontuação vai ser escolhida a maior pela função escolhemaior que devolve o maior inteiro de um array estatico
passado. esse i corresponde à maior pont. assim como corresponde ao i da string no array de strings que tem o codigo que obtem maior pontuacao para
posicao x , y e orientacao. No final executamos esse codigo no lab original(copia do original) e concatena mos a string que originou essa pnt.
na str que faz cond do ciclo principal. Resetamos as variaveis e fazemos novamente apartir do original modificado.
*     @param char** pplab labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/

void autonomia(char** pplab,int linhas,int colunas){
    int pont[4]={0,0,0,0};
    int ncasas=0;
    char ** ppcopialabirinto=NULL;
    char maxcomando[20]="";
    char** ppcomandos=(char**)malloc(sizeof(char*)*4);
    char * teste;
    char** ppcodigosautonomia=preenchetumatrizcodigos(ppcomandos,4,4);
    int i=0,pontuacao=0,j=0,z=0,p=0;
    int posx,posy;
    char orie;
    int maior=0;
    char** ppaux=NULL;
    printmatriz(ppcodigosautonomia,4,4);
    printf(" %d \n",strlen(maxcomando));
    teste=*(ppcodigosautonomia+0);
    printf(" %s \n",teste);
    //pplab Labirinto original    ppcopia é uma copia do original
    ppcopialabirinto=copialabirinto(pplab,linhas,colunas);
    int posx2,posy2;
    char orien2;
    while(strlen(maxcomando)< 20){
        i=0;


    while(i<4){
            ppaux=copialabirinto(ppcopialabirinto,linhas,colunas);
            getpos(&posx,&posy,ppcopialabirinto,colunas,linhas,&orie);
        while(*(teste+j)!='\0'){
            if(*(teste+j)=='0'){
                   pontuacao=foward(&posx,&posy,ppaux,linhas,colunas,pontuacao,&orie);

               }else if(*(teste+j)=='6'){
                   pontuacao=back(&posx,&posy,ppaux,linhas,colunas,pontuacao,&orie);

               }else if(*(teste+j)=='3'){
               rotate_right(&orie,posx,posy,ppaux);
               }else if(*(teste+j)=='9'){
               rotate_left(&orie,posx,posy,ppaux);
               }
               j++;

        }
        j=0;
        pont[i]=pontuacao;
        printf(" \n ARRAY %d \n",pont[i]);
        pontuacao=0;
        i++;
        teste=*(ppcodigosautonomia+i);


    }
    maior=escolheomaior(4,pont);
    printf(" MAIOR:%d \n",maior);
    for(z=0;z<4;z++){
        if(maior==pont[z]){
            goto label;
        }


    }
    label:
        printf("Entramos aqui na LABEL\n");
        teste=*(ppcodigosautonomia+z);
        strcat(maxcomando,teste);
        getpos(&posx2,&posy2,ppcopialabirinto,linhas,colunas,&orien2);
        while(*(teste+p)!='\0'){
                 if(*(teste+p)=='0'){
                   pontuacao=foward(&posx2,&posy2,ppcopialabirinto,linhas,colunas,pontuacao,&orien2);

               }else if(*(teste+p)=='6'){
                   pontuacao=back(&posx2,&posy2,ppcopialabirinto,linhas,colunas,pontuacao,&orien2);

               }else if(*(teste+p)=='3'){
               rotate_right(&orien2,posx2,posy2,ppcopialabirinto);
               }else if(*(teste+p)=='9'){
               rotate_left(&orien2,posx2,posy2,ppcopialabirinto);
               }
               p++;
        }
        ;
        i=0;
        j=0;
        p=0;
        z=0;
        printmatriz(ppcopialabirinto,linhas,colunas);
    }

    printf("\nCOMANDO FINAL DISTO TUDO QUE OBTEM MAIOR PONTUAÇAO : \n%s \n",maxcomando);
    menu(pplab);

}

int escolheomaior(int size,int a[size]){
    int maior,i=0;

    for(i=0;i<size;i++){
        if(a[i]>maior){
            maior=a[i];
        }

    }
    return maior;

}




void matrizdecodigos(char** ppointer,int linhas,int colunas){
    char** aux=NULL;
    char** ppmatriz=NULL;
    char c='Y';
    char *pcodigo=NULL;
    int i=0;
    int posx,posy;
    char orie;
    int pontuacao=0;
    int size=0;
    int n=0;
    int *pontuacoes=NULL;
    char str[150];
    while(c!='N'){
    aux=copialabirinto(ppointer,linhas,colunas);
    getpos(&posx,&posy,ppointer,colunas,linhas,&orie);
    getchar();
     if(i==size){
        ppmatriz=initmatrizcodigo(ppmatriz,&size);
        pontuacoes=initpontucoes(pontuacoes,size);
    }
    printf("\nInsira código a testar:\n");
    fgets(str,150,stdin);
    pcodigo=mandaendereco(str,strlen(str));
    printf("%s %d \n",pcodigo,strlen(str));
    printf("%d ",size);
    while(n<strlen(str)){
            if(*(pcodigo+n)=='0'){
                   pontuacao=foward(&posx,&posy,aux,linhas,colunas,pontuacao,&orie);

               }else if(*(pcodigo+n)=='6'){
                   pontuacao=back(&posx,&posy,aux,linhas,colunas,pontuacao,&orie);

               }else if(*(pcodigo+n)=='3'){
               rotate_right(&orie,posx,posy,aux);
               }else if(*(pcodigo+n)=='9'){
               rotate_left(&orie,posx,posy,aux);
               }
               n++;
    }
    ppmatriz=metenamatriz(ppmatriz,pontuacao,pcodigo,i);
    pontuacoes=guardapontuacao(pontuacoes,pontuacao,i);
    n=0;
    i++;
    pontuacao=0;
    strcpy(str,"");
    printf("Deseja continuar?:Y/N");
    scanf("%c",&c);
    }
    getchar();
    char simnao;
    printf("Deseja exportar o seu ficheiro de pontuaçoes e codigos?!\n");
    scanf("%c",&simnao);

    if(simnao=='Y'){
            escrevepontuacoes(ppmatriz,pontuacoes,i);
    }


}

void escrevepontuacoes(char** ppmatriz,int* pontuacoes,int i){
    FILE * fp=NULL;
    fp=fopen("Tabeladepontuacoes.txt","w");
    int j=0;
    fprintf(fp,"*************ScoreBoard**************\n");

    for(j=0;j<i;j++){
            fprintf(fp,"CODIGO:%s PONTUACAO:%d",*(ppmatriz+j),*(pontuacoes+j));
            fprintf(fp,"\n");
    }
    fprintf(fp,"*************ScoreBoard**************\n");

    fclose(fp);

}





int *guardapontuacao(int*pontuacoes,int pontuacao,int i){
    *(pontuacoes+i)=pontuacao;
    printf(" PONTUAÇAO %d \n",*(pontuacoes+i));
    return pontuacoes;

}

char** metenamatriz(char** ppmatriz,int pontuacao,char* pcodigo,int i){
    int tamanho=strlen(pcodigo);

    *(ppmatriz+i)=(char*)malloc(sizeof(char)*tamanho);

    strcpy(*(ppmatriz+i),pcodigo);

    return ppmatriz;
}


int* initpontucoes(int* pontuacoes,int size){
    int i=0;
    int* paux=NULL;
    printf("Entrei AQUI! \n");

    if(pontuacoes==NULL){
            paux=(int*)malloc(sizeof(int)*size);
             for(i=0;i<size;i++){
               // *(paux+i)=0;

        }

    }else{
      paux=(int*)malloc(sizeof(int)*size);
        for(i=0;i<size/2;i++){
                *(paux+i)=*(pontuacoes+i);

        }
        for(i=size/2;i<size;i++){
*(paux+i)=0;
        }

    }

    return paux;

}


char** initmatrizcodigo(char**ppmatriz,int * size){
    char** ppaux=NULL;
    int i=0;
    if(ppmatriz==NULL){
            printf("Entrou aqui!\n");
            *(size)=5;
    ppaux=(char**)malloc(sizeof(char*)*(*size));

    }else{
        *(size)=*(size)*2;
        ppaux=(char**)malloc(sizeof(char*)*(*size));
        for(i=0;i<*(size)/2;i++){
                *(ppaux+i)=*(ppmatriz+i);

        }

    }


return ppaux;


}
char* mandaendereco(char* str,int tamanho){
    char* paux;
    paux=(char*)malloc(sizeof(char)*tamanho);
    strcpy(paux,str);
    return paux;

}

char** guardacodigosimples(char** matrizcomandos,char* pcodigo,int pontuacao,int*size,int tamanho,int i){
    char** aux=NULL;
    int z=0,j=0;
    if(matrizcomandos==NULL){
            *(size)=5;
            matrizcomandos=(char**)malloc(sizeof(char*)*(*size));
            *(matrizcomandos+i)=(char*)malloc(sizeof(char)*tamanho);
            strcpy(*(matrizcomandos+i),pcodigo);
            printf("Primeira Ocasião!\n");
            printf("%s %s %d %d --\n",*(matrizcomandos+0),pcodigo,*(size),i);
            return matrizcomandos;
    }else if(i==*(size)-1){
        printf("Entrou!");
        *(size)=*(size)*2;
        *(matrizcomandos+i)=(char*)malloc(sizeof(char)*tamanho);
         strcpy(*(matrizcomandos+i),pcodigo);
         aux=(char**)malloc(sizeof(char*)*(*size));
         for(z=0;z<*(size)/2;z++){
                strcpy(*(aux+z),*(matrizcomandos+z));
         }
         for(j=*(size)/2;j<(*size);j++){
                strcpy(*(aux+j),"");
         }
          printf("Primeira Ocasião!\n");
            printf("%s %s %d %d --\n",*(matrizcomandos+i),pcodigo,*(size),i);
         return aux;
    }
     printf("Primeira Ocasião!\n");
            printf("%s %s %d %d --\n",*(matrizcomandos+i),pcodigo,*(size),i);
     strcpy(*(matrizcomandos+i),pcodigo);
        return matrizcomandos;
}



/** Função que permite editar uma determinada célula do nosso Labirinto.
*     @param char** ppointer labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/

void alteralab(char** ppointer,int linhas,int colunas){
    printmatriz(ppointer,linhas,colunas);
    char c;
    int xlinha=0,xcoluna=0;
    getchar();
    printf("Cordenadas em x a alterar:\n");
    scanf("%d",&xcoluna);
    printf("Cordenadas em y a alterar:\n");
    scanf("%d",&xlinha);
    *(*(ppointer+xlinha)+xcoluna)=c;

    printf(" \n Conteudo atual dessa celula %c %d %d \n",c,xcoluna,xlinha);
    getchar();
    printf("Que deseja inserir nessa célula?:\n");
    scanf("%c",&c);

   *(*(ppointer+xlinha)+xcoluna)=c;

   printf("\n Nova célula inserida com sucesso! \n");
   printmatriz(ppointer,linhas,colunas);
   getchar();
   menu2(ppointer,linhas,colunas);

}

/** Função que permite ao utilizador criar a tabela de permutações com repetições e o preenchimento da mesma fica por conta do utilizador
*     @param char** ppointer labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/

void tuapermuta(char**pplab,int linhas,int colunas){
     int colunascomandos=0;
    int ncomandos=0;
    char** ppcomandos=NULL;
    printf("\n");
    printf("Nrº de Dígitos do comando: \n");
    scanf("%d",&colunascomandos);
    printf("Quantos códigos pretende inserir?: \n");
    scanf("%d",&ncomandos);
    ppcomandos=comandos(ncomandos,colunascomandos);
    printf("ppcomandos criado!");
    startmatriz(ppcomandos,ncomandos,colunascomandos);
    printmatriz(ppcomandos,ncomandos,colunascomandos);
    ppcomandos=preenchetumatrizcodigos(ppcomandos,ncomandos,colunascomandos);
    printmatriz(ppcomandos,ncomandos,colunascomandos);
    printf("ppcomandos feito! %d \n",ncomandos);
    int** matrix=NULL;
    matrix=fazerumatrix(ncomandos);
    printmatrix(matrix,(fatorial(ncomandos)),ncomandos);
    getchar();
    testacodigo(ppcomandos,pplab,matrix,linhas,colunas,ncomandos,colunascomandos);

}

/** Função que receb o array de strings referentes aos comandos guardados e a matriz dos comandos a executar pela ordem que esta mesma impõe
*     @param int n representa o numero de comandos inseridos pelo utilizador, que será usado para calculo do numero de linhas da matriz de permutas.
*      @return int** retorna o endereço de um apontador para matriz preenchida manualmente pelo nosso utilizador
*/
int** fazerumatrix(int n){
    int ** matrix=(int**)malloc(sizeof(int*)*(fatorial(n)));
    int i=0,j=0;
    int valor=0;

    for(i=0;i<(fatorial(n));i++){
        *(matrix+i)=(int*)malloc(sizeof(int)*n);
    }

    printf("Preencha a matriz com valores de %d a %d !!!\n",0,n-1);

      for(i=0;i<(fatorial(n));i++){
             for(j=0;j<n;j++){
                printf("Valor [%d][%d] :\n",i,j);
             scanf("%d",&valor);
                 *(*(matrix+i)+j)=valor;

    }

    }
    printmatrix(matrix,fatorial(n),n);
    return matrix;
}


/** Função que recebe o labirinto e permite ao utilizador interagir usando a tabela de códigos possiveis para movimentar o nosso robot e ir verificando a pontuação acumulada
*     @param char** pplabirinto labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/
void executacodigo(char** pplabirinto,int linhas,int colunas)
{
    int posx,posy;
    int c;
    char** ppaux=NULL;
    char posicao;
    int pontuacao=0;
    getpos(&posx,&posy,pplabirinto,colunas,linhas,&posicao);
    ppaux=copialabirinto(pplabirinto,linhas,colunas);
    while(c!=-1)
    {
        printf("Codigo a executar?\n");
        scanf("%d",&c);
        if(c==-1)
        {
            return;
        }
        else
        {
            if(c==0)
            {
                pontuacao=foward(&posx,&posy,ppaux,linhas,colunas,pontuacao,&posicao);
            }
            else if(c==6)
            {
                pontuacao=back(&posx,&posy,ppaux,linhas,colunas,pontuacao,&posicao);
            }
            else if(c==3)
            {
                rotate_right(&posicao,posx,posy,ppaux);
            }
            else if(c==9)
            {
                rotate_left(&posicao,posx,posy,ppaux);
            }
        }
        printmatriz(ppaux,linhas,colunas);
        printf("Pontuaçao atual : %d \n",pontuacao);
    }

}


/** Função que cria a matriz e a preenche-a com as várias permutações sem repetições . Chama a função testacódigo que irá realizar os vários comandos de cada linha
*     @param char** ppointer labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*/

void permuta(char**ppointer,int linhas,int colunas)
{
    int colunascomandos=0;
    int ncomandos=0;
    char** ppcomandos=NULL;

    printf("\n");
    printf("Nrº de Dígitos do comando: \n");
    scanf("%d",&colunascomandos);
    printf("Quantos códigos pretende inserir?: \n");
    scanf("%d",&ncomandos);
    ppcomandos=comandos(ncomandos,colunascomandos);
    printf("ppcomandos criado!");
    startmatriz(ppcomandos,ncomandos,colunascomandos);
    printmatriz(ppcomandos,ncomandos,colunascomandos);
    ppcomandos=preenchetumatrizcodigos(ppcomandos,ncomandos,colunascomandos);
    printmatriz(ppcomandos,ncomandos,colunascomandos);
    printf("ppcomandos feito! %d \n",ncomandos);
    // int matrizpermuta[linhasmatriz][colunasmatriz];
    // printf(" Linhas:%d colunas: %d \n",linhasmatriz,ncomandos);
    int** matrix=NULL;
    matrix=fazermatrix(ncomandos);
    printmatrix(matrix,(fatorial(ncomandos)),ncomandos);
    getchar();
    // int a[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
    printf("Entrou aqui %d %d CUCUCUCU !!!",ncomandos,(fatorial(ncomandos)));
    testacodigo(ppcomandos,ppointer,matrix,linhas,colunas,ncomandos,colunascomandos);
    free(matrix);
    menu(NULL);
}

/**variável global**/
int iterations=0;

/** Função que troca valores de dois apontadores
*     @param int* y
*     @param int* x
*/
void swap(int *x, int *y)
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
            swap((a+l), (a+i));
            permute(a, l+1, r, size,matrix,linhas,colunas);
            swap((a+l), (a+i)); //backtrack
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

/* Driver program to test above functions */

/** Função que receb o array de strings referentes aos comandos guardados e a matriz dos comandos a executar pela ordem que esta mesma impõe
*     @param int n numero de comandos(colunas) da matriz
*      @return int** retorna o endereço que aponta para uma matriz vazia criada pronta a ser preenchida
*
*/
int** fazermatrix(int n)
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

/** Função que receb o array de strings referentes aos comandos guardados e a matriz dos comandos a executar pela ordem que esta mesma impõe
*     @param char** ppcomandos array strings dos codigos
*     @param char** ppointer labirinto
*     @param int** a a nossa matriz com os comandos com a sua ordem comutativa a ser executada
*     @param int linhas linhas
*     @param int colunas colunas
*     @param int ncomandos linhas de comandos
*     @param int colunascomandos colunas dos comandos
*/
int testacodigo(char** ppcomandos,char** ppointer,int** a,int linhas,int colunas,int ncomandos,int colunascomandos)
{
    int posx,posy;
    int i=0,j=0,z=0;
    char** ppaux=NULL;
    int score[fatorial(ncomandos)];
    char posicao;
    int pontuacao=0;
//    printf("%d COLUNASCOMANDOS %d LINHAS\n",colunascomandos,linhas);
//    printf("%d ncomandos \n",ncomandos);
    getpos(&posx,&posy,ppointer,colunas,linhas,&posicao);
//    printf(" %d %d %c ---- x y\n",posx,posy,posicao);
//    printf(" String copiada: %s \n",*(ppcomandos+0));
    // int x=0;
//     printf(" %d %d x y\n",posx,posy);
    int teste=0;
    printmatrix(a,(fatorial(ncomandos)),ncomandos);
    getchar();
    for(i=0; i<(fatorial(ncomandos)); i++)
    {
        pontuacao=0;
        printf(" TESTE: %d\n",teste);
        teste++;
        ppaux=copialabirinto(ppointer,linhas,colunas);
        // printmatriz(ppaux,linhas,colunas);
        for(j=0; j<ncomandos; j++)
        {
            printf(" TESTE: %d\n",teste);
            for(z=0; z<colunascomandos; z++)
            {
                if(*(*(ppcomandos+*(*(a+i)+j))+z)=='0')
                {
                    pontuacao=foward(&posx,&posy,ppaux,linhas,colunas,pontuacao,&posicao);
                }
                else if(*(*(ppcomandos+*(*(a+i)+j))+z)=='6')
                {
                    pontuacao=back(&posx,&posy,ppaux,linhas,colunas,pontuacao,&posicao);
                }
                else if(*(*(ppcomandos+*(*(a+i)+j))+z)=='3')
                {
                    rotate_right(&posicao,posx,posy,ppaux);
                }
                else if(*(*(ppcomandos+*(*(a+i)+j))+z)=='9')
                {
                    rotate_left(&posicao,posx,posy,ppaux);
                }
            }
        }
        score[i]=pontuacao;
    }

    for(i=0; i<(fatorial(ncomandos)); i++)
    {
        printf(" %d ,",score[i]);
    }
    return 0;

}

/** Função que recebe o endereço do nosso labirinto original e cria na memoria um lab igual com endereço diferente. Retorna esse endereço
*     @param char** ppointer labirinto
*     @param int linhas linhas
*     @param int colunas colunas
*     @return char** retorna o endereço apontador de uma copia do nosso labirinto original
*/
char**copialabirinto(char**ppointer,int linhas,int colunas)
{
    int i=0,j=0;
    char ** ppaux=(char**)malloc(sizeof(char*)*linhas);

    for(i=0; i<linhas; i++)
    {
        *(ppaux+i)=(char*)malloc(sizeof(char)*colunas);
    }

    for(i=0; i<linhas; i++)
    {

        for(j=0; j<colunas; j++)
        {

            *(*(ppaux+i)+j)=*(*(ppointer+i)+j);
        }

    }

    printf(" COPIA DO ORIGINAL \n");
    printmatriz(ppaux,linhas,colunas);
    return ppaux;

}




/** Função que vair procurar o x e o y do nosso Robot bem como a sua orientação, e atualiza as variáveis
*    @param int* posx endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*@param int* posy endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*   @param  char** ppointer o nosso labirinto
*    @param int colunas
*    @param int linhas
* @param char* posicao o endereço da posiçao do nosso robot
* */
void getpos(int * posx, int* posy,char** ppointer,int colunas,int linhas,char * posicao)
{
    int i=0;
    int j=0;
    printf("Entrou aqui---- %d %d!!!",linhas,colunas);
    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
        {
            if(*(*(ppointer+i)+j)=='N' || *(*(ppointer+i)+j)=='E'|| *(*(ppointer+i)+j)=='S' || *(*(ppointer+i)+j)=='O')
            {
                *(posx)=j;
                *(posy)=i;
                *(posicao)=*(*(ppointer+(*posy))+(*posx));

            }
        }
    }
}

//recebe a matriz dos comandos com o indice do comando pretendido para exec
/** Função que vair executar o comando de back, conforme a sua orientaçao o back ira atuar.
*    @param int* posx endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*@param int* posy endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*   @param  char** labirinto o nosso labirinto
*    @param int colunas
*    @param int linhas
* @param char* orien o endereço da orientaçao do nosso robot
* @param int pontuacao a pontuacao que tem naquele momento
* @return int retorna a pontuaçao depois de executado aquele código
* */

int back(int* posx,int* posy,char** labirinto,int linhas,int colunas,int pontuacao,char* orien)
{
    int x=(*posx);
    int y=(*posy);
    if(*(orien)=='N')
    {
        if(*(posy)<colunas-1)
        {

            printf("Entrou aqui! Orientaçao == N Comando: BACK\n");
            printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y+1))+x)=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                pontuacao=pontuacao+10;
                *(posy)=*(posy)+1;
                *(*(labirinto+(y+1))+x)='N';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                pontuacao=pontuacao;
                *(posy)=*(posy)+1;
                *(*(labirinto+(y+1))+x)='N';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if(pontuacao>0)
                {
                    pontuacao=pontuacao-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if(pontuacao>=5)
                {
                    pontuacao=pontuacao-5;
                    *(*(labirinto+(y+1))+x)='N';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",pontuacao);
            }
        }
    }
    else if(*(orien)=='S')
    {
        if(*(posy)>0)
        {
            printf("Entrou aqui! Orientaçao == S \n");
            printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y-1))+x)=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                pontuacao=pontuacao+10;
                *(posy)=*(posy)-1;
                *(*(labirinto+(y-1))+x)='S';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                pontuacao=pontuacao;
                *(posy)=*(posy)-1;
                *(*(labirinto+(y-1))+x)='S';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if(pontuacao>0)
                {
                    pontuacao=pontuacao-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if(pontuacao>=5)
                {
                    pontuacao=pontuacao-5;
                    *(posy)=*(posy)-1;
                    *(*(labirinto+(y-1))+x)='S';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
    }
    else if(*(orien)=='O')
    {
        if(*(posx)<colunas-1)
        {
            printf("Entrou aqui! Orientaçao == O \n");
            //printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y))+(x+1))=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                pontuacao=pontuacao+10;
                *(posx)=*(posx)+1;
                *(*(labirinto+y)+(x+1))='O';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",pontuacao);
            }
            else if(*(*(labirinto+y)+(x+1))=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                pontuacao=pontuacao;
                *(posx)=*(posx)+1;
                *(*(labirinto+y)+(x+1))='O';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",pontuacao);
            }
            else if(*(*(labirinto+y)+(x+1))=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if(pontuacao>0)
                {
                    pontuacao=pontuacao-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",pontuacao);
            }
            else if(*(*(labirinto+y)+(x+1))=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+y)+(x+1))='O';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
    }
    else if(*(orien)=='E')
    {
        if(*(posx)>0)
        {
            printf("Entrou aqui! Orientaçao == E \n");
            //printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y))+(x-1))=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                pontuacao=(pontuacao)+10;
                *(posx)=*(posx)-1;
                *(*(labirinto+y)+(x-1))='E';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                pontuacao=(pontuacao);
                *(posx)=*(posx)-1;
                *(*(labirinto+y)+(x-1))='E';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if((pontuacao)>0)
                {
                    (pontuacao)=(pontuacao)-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+y)+(x-1))='E';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
    }

    return pontuacao;


}

/** Função que vair fazer o rotate right do nosso robot e alterar a sua orientaçao
*    @param int* posx endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*@param int* posy endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*   @param  char** ppaux o nosso labirinto
* @param char* posicao o endereço da posiçao do nosso robot
* */

void rotate_right(char * posicao,int posx,int posy,char** ppaux)
{
    printf(" %c Orientacao Antes da conversão\n",*(posicao));
    int i=posy;
    int j=posx;
    if(*(posicao)=='N')
    {
        *(posicao)='E';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='E')
    {
        *(posicao)='S';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='S')
    {
        *(posicao)='O';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='O')
    {
        *(posicao)='N';
         *(*(ppaux+i)+j)=*(posicao);
    }

    printf(" %c Orientacao depois do rotate right\n",*(posicao));

}


/** Função que vair fazer o rotate left do nosso robot e alterar a sua orientaçao
*    @param int* posx endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*@param int* posy endereço da posiçao em x. Possivel de ser alterado e ficar guardado sem precisar de retorno
*   @param  char** ppaux o nosso labirinto
* @param char* posicao o endereço da posiçao do nosso robot
* */
void rotate_left(char * posicao,int posx,int posy,char** ppaux)
{
    int i=posy;
    int j=posx;
    printf(" %c Orientacao Antes da conversão\n",*(posicao));

    if(*(posicao)=='N')
    {
        *(posicao)='O';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='O')
    {
        *(posicao)='S';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='S')
    {
        *(posicao)='E';
         *(*(ppaux+i)+j)=*(posicao);
    }
    else if(*(posicao)=='E')
    {
        *(posicao)='N';
         *(*(ppaux+i)+j)=*(posicao);
    }

    printf(" %c Orientacao depois do rotate right\n",*(posicao));

}

//chamada desta funcao caso seja encontrado um 0 no indice da str do comando da matriz

/**
*  Função que é chamada sempre que se insere no código um zero (0).
*  @param int* posx posição em X do Robot
*  @param int* posy posição em Y do Robot
*  @param char** labirinto a nossa matriz de caracteres correspondetes ao labirinto
*  @param int linhas numero de linhas do nosso labirinto
*  @param int colunas numero de colunas do nosso labirinto
*  @param int* pontuacao endereco da nossa pontuacao
*  @param char* orien apontador para o endereco contendo a orientaçao do nosso robot
*/
int foward(int* posx,int* posy,char** labirinto,int linhas,int colunas,int pontuacao,char* orien)
{
    int x=(*posx);
    int y=(*posy);
    if(*(orien)=='N')
    {
        if(*(posy)>0)
        {
            printf("Entrou aqui! Orientaçao == N \n");
            printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y-1))+x)=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                (pontuacao)=(pontuacao)+10;
                *(posy)=*(posy)-1;
                *(*(labirinto+(y-1))+x)='N';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                (pontuacao)=(pontuacao);
                *(posy)=*(posy)-1;
                *(*(labirinto+(y-1))+x)='N';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if((pontuacao)>0)
                {
                    (pontuacao)=(pontuacao)-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y-1))+x)=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+(y-1))+x)='N';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
        else
        {
            printf("Está num Limite do labirinto!!!");
        }
    }
    else if(*(orien)=='S')
    {
        if(*(posy)<linhas-1)
        {
            printf("Entrou aqui! Orientaçao == S COMANDO:FOWARD\n");
            if(*(*(labirinto+(y+1))+x)=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                (pontuacao)=(pontuacao)+10;
                *(posy)=*(posy)+1;
                *(*(labirinto+(y+1))+x)='S';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                (pontuacao)=(pontuacao);
                *(posy)=*(posy)+1;
                *(*(labirinto+(y+1))+x)='S';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if((pontuacao)>0)
                {
                    (pontuacao)=(pontuacao)-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+(y+1))+x)=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    *(posy)=*(posy)+1;
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+(y+1))+x)='S';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
        else
        {
            printf("Está num Limite do labirinto!!!");
        }
    }
    else if(*(orien)=='O')
    {
        if(*(posx)>0)
        {
            printf("Entrou aqui! Orientaçao == O \n");
            //printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y))+(x-1))=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                (pontuacao)=(pontuacao)+10;
                *(posx)=*(posx)-1;
                *(*(labirinto+y)+(x-1))='O';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                (pontuacao)=(pontuacao);
                *(posx)=*(posx)-1;
                *(*(labirinto+y)+(x-1))='O';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if((pontuacao)>0)
                {
                    (pontuacao)=(pontuacao)-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x-1))=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    *(posx)=*(posx)-1;
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+y)+(x-1))='O';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
        else
        {
            printf("Está num Limite do labirinto!!!");
        }
    }
    else if(*(orien)=='E')
    {
        if(*(posx)<colunas-1)
        {
            printf("Entrou aqui! Orientaçao == O \n");
            //printf(" \n y-1 = %c \n",*(*(labirinto+(3))+x));
            if(*(*(labirinto+(y))+(x+1))=='$')
            {
                printf("Entrou aqui! Casa da frente é um dolar! \n");
                (pontuacao)=(pontuacao)+10;
                *(posx)=*(posx)+1;
                *(*(labirinto+y)+(x+1))='E';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x+1))=='0')
            {
                printf("Entrou aqui!Casa da frente é um zero!! \n");
                (pontuacao)=(pontuacao);
                *(posx)=*(posx)+1;
                *(*(labirinto+y)+(x+1))='E';
                *(*(labirinto+y)+x)='0';
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x+1))=='W')
            {
                printf("Entrou aqui!Casa da frente é uma parede!! \n");
                if((pontuacao)>0)
                {
                    (pontuacao)=(pontuacao)-1;
                }
                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }
            else if(*(*(labirinto+y)+(x+1))=='B')
            {
                printf("Entrou aqui!Casa da frente é uma Bomba!! \n");
                if((pontuacao)>=5)
                {
                    (pontuacao)=(pontuacao)-5;
                    *(*(labirinto+y)+(x+1))='E';
                    *(*(labirinto+y)+x)='0';
                }
                else printf(" Não tem pontuação suficiente para caminhar sobre a bomba!!\n");

                printmatriz(labirinto,linhas,colunas);
                printf(" Pontuaçao %d \n",(pontuacao));
            }

        }
        else
        {
            printf("Está num Limite do labirinto!!!");
        }
    }
    return pontuacao;

}


/** Função que vair guardar um dado comando na nossa matriz de comandos
*    @param int* comandos endereço da variavel que contem a linha onde o comando vai ser inserido na matriz de comandos
*@param int padrao numero de elementos desse mesmo comando
*   @param  char** ppcomandos matriz de comandos
* @param char str[] comando em si
* */


//guarda o comando enviado na matriz de comandos criada
void guardacomando(char** ppcomandos,char str[],int* comandos,int padrao)
{
    int i=0;
    //int len=strlen(str);
    while(str[i]!='\0')
    {
        *(*(ppcomandos+(*comandos))+i)=str[i];
        i++;

    }


    *(comandos)=*(comandos)+1;

}


/** Função que vair criar a nossa matriz de comandos e retornar o seu endereço
*    @param int colunas
*    @param int linhas
*    @return char** retorna o endereço da matriz de comandos criada
* */
//cria matriz de 100 linhas por 4 colunas com comandos prontos a serem inseridos
char** comandos(int linhas,int colunas)
{
    int i=0;
    char** ppcomandos=NULL;
    ppcomandos=(char**)malloc(sizeof(char*)*linhas);
    for(i=0; i<linhas; i++)
    {
        *(ppcomandos+i)=(char*)malloc(sizeof(char)*colunas);
    }
    return ppcomandos;
}

/** Função que vair inicializar uma matriz
*    @param char** ppointer recebe um ppointer a NULL
*    @param int colunas
*    @param int linhas
*    @return char** retorna o endereço da matriz (Labirinto) ou matriz de comandos
* */
char** initmatriz(char**ppointer,int linhas,int colunas)
{
    int i=0;

    //Mete o ppointer a apontar para um array de apontadores de tamanho = linhas
    ppointer=(char**)malloc(sizeof(char*)*linhas);

    //Vai percorrer o array de apontadores e dentro de cada value para o indice i vai colocar o endereço que vai dar acesso às colunas
    for(i=0; i<linhas; i++)
    {
        *(ppointer+i)=(char*)malloc(sizeof(char)*colunas);
    }

    return ppointer;
}

//INICIA TODOS OS VALORES DA MATRIZ A 0
void startmatriz(char** ppointer,int linhas,int colunas)
{
    int i=0,j=0;

    for(i=0; i<linhas; i++)
    {

        for(j=0; j<colunas; j++)
        {

            *(*(ppointer+i)+j)='0';


        }
    }


}

//IMPRIME MATRIZ FEITA
void printmatriz(char** ppointer,int linhas,int colunas)
{
    int i=0,j=0;

    for(i=0; i<linhas; i++)
    {

        for(j=0; j<colunas; j++)
        {

            printf(" %c",*(*(ppointer+i)+j));

        }
        printf("\n");
    }

}
//Preenchimento da nossa matriz com símbolos random e com limitação de cada tipo de símbolos
void preenchematriz(char** ppointer,int linhas,int colunas)
{
    int i=0,j=0;
    int value=0;
    //int x,y;
    int countA=5,countB=5;
    char aux[]="WB$0";


    for(i=0; i<linhas; i++)
    {

        for(j=0; j<colunas; j++)
        {
            value=rand() %4 ;
            if(value==0 && countA > 0)
            {
                countA--;
                *(*(ppointer+i)+j)=aux[value];
            }
            else if(value==1 && countB > 0)
            {
                countB--;
                *(*(ppointer+i)+j)=aux[value];

            }
            else if(value != 0 && value != 1)
            {
                *(*(ppointer+i)+j)=aux[value];

            }
            else
            {
                j--;
            }

        }
    }

    colocarobot(ppointer,linhas,colunas);
}

void colocarobot(char** ppointer,int linhas,int colunas)
{

    printmatriz(ppointer,linhas,colunas);

    char orientacao[]="NSEO";
    char virado;
    int posx=0,posy=0;
    int opcao=0;
    int x,y;
    printf(" Como deseja inserir o robot?  1 Manual 2 Alea: \n");
    scanf("%d",&opcao);
    switch(opcao)
    {
    case 1:
        getchar();
        printf("\nDiga a orientação do robot:\n");
        virado=getchar();
        printf("\nCoordenadas em x:\n");
        scanf("%d",&posx);
        printf("\n Coordenadas em y:\n");
        scanf("%d",&posy);
        *(*(ppointer+posy)+posx)=virado;;
        break;
    case 2:
        x=rand()%colunas;
        y=rand()%linhas;
        *(*(ppointer+y)+x)=orientacao[rand()%4];
        break;

    }

}


void preenchetumatriz(char** ppointer,int linhas,int colunas)
{

    int i=0,j=0;
    for(i=0; i<linhas; i++)
    {

        for(j=0; j<colunas; j++)
        {
            getchar();
            printf("Símbolo na célula de coordenadas (%d:x,%d:y):\n",j,i);
            scanf("%c",*(ppointer+i)+j);

        }
    }

    printmatriz(ppointer,linhas,colunas);

    // colocarobot(ppointer,linhas,colunas);

}

char** preenchetumatrizcodigos(char** ppcomandos,int linhas,int colunas)
{
    getchar();
    int i=0;
    char** pstr=(char**)malloc(sizeof(char*)*linhas);

    for(i=0; i<linhas; i++)
    {
        *(pstr+i)=(char*)malloc(sizeof(char)*colunas);
    }

    for(i=0; i<linhas; i++)
    {
        printf("Insira codigo nª %d:\n",i);
        fgets(*(pstr+i),10,stdin);

    }



    return pstr;
}

void exportalab(char**pplab,int linhas,int colunas)
{
    getchar();
    char strmax[150];
    printf("\n Nome do ficheiro txt. a exportar?\n");
    gets(strmax);
    printf("%s .txt criado!\n",strmax);
    printf(" %d %d ****\n",linhas,colunas);
    int i=0,j;
    FILE*fp=NULL;
    strcat(strmax,".txt");
    fp=fopen(strmax,"w");

    fprintf(fp,"%d %d\n",linhas,colunas);

    for(i=0; i<linhas; i++)
    {
        for(j=0; j<colunas; j++)
            fprintf(fp,"%c",*(*(pplab+i)+j));
        fprintf(fp,"\n");
    }

    printf("Ficheiro Exportado!!! \n");
    fclose(fp);
}


char** importalab(int* linhas,int* colunas)
{
    getchar();
    char nome[150];
    printf("Nome do ficheiro a abrir?\n");
    gets(nome);
    FILE* fp=NULL;
    char** pplab=NULL;
    int i=0;
    strcat(nome,".txt");
//    char str[MAX];
//    printf("Nome do ficheiro a abrir?:\n");
//    fgets(str,MAX,stdin);
//
//
//    printf("%s \n",str);

    fp=fopen(nome,"r");


    if(fp==NULL)
    {
        printf("Ficheiro inexistente!!!\n");
    }
    else
    {
        fscanf(fp,"%d %d",linhas,colunas);
        printf("%d %d\n",*(linhas),*(colunas));


        pplab=(char**)malloc(sizeof(char*)*(*linhas));

        for(i=0; i<(*linhas); i++)
        {
            *(pplab+i)=(char*)malloc(sizeof(char)*(*colunas));
        }
        for(i=0; i<(*linhas); i++)
        {
            fscanf(fp,"%s",*(pplab+i));
            printf(" %s \n",*(pplab+i));
        }
    }
    fclose(fp);
    return pplab;
}

void txt()
	{
		int counter;
		FILE *ptr_myfile;
		struct rec my_record;

		ptr_myfile=fopen("test.bin","wb");
		if (!ptr_myfile)
		{
			printf("Unable to open file!");
			return ;
		}
		for ( counter=1; counter <= 10; counter++)
		{
			my_record.x= counter;
			fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
		}
		fclose(ptr_myfile);
		return ;
	}
