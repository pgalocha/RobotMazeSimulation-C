#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.c"
/** Parte Dinamica de Lp1(LISTAS LIGADAS)
*   Trabalho realizado por: Pedro Galocha nr 25999
*
*
*@author Pedro Miguel Veiga Galocha
*/

int main()
{
    int choice=0;
    printf("Como deseja iniciar?\n");
    printf("1- Criar:\n");
    printf("2- Importar:\n");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            menu();
            break;

    case 2:
        importlab();
        break;
    }
return 0;
}





