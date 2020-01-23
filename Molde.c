/*

* Programa: Jogo Resta Um em linguagem C
* Autores: Gabriele Jandres, Maria Carolina Esteves e Victor Cardoso
* Universidade Federal do Rio de Janeiro
* Descrição: *********
* Arquivo de implementação do módulo

	-> Definicoes de variaveis locais e globais do modulo 
	-> Definicoes de funcoes locais e globais do modulo

*/
#include "Molde.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h> //essa linha deverá ser comentada para rodar no linux
#include <conio.h> //essa linha deverá ser comentada para rodar no linux
#include <string.h>
#include <math.h>
#include <ctype.h>

/* DEFINIÇÕES DE VARIÁVEIS GLOBAIS */

//variável global para controlar a quantidade de movimentos
int movimentos = 0;

/* DEFINIÇÕES DE FUNÇÕES GLOBAIS */

// Função para printar um menu inicial ao usuário
void menu_inicial(char nome[], int * op){
  SetConsoleTitle("Resta Um");
  system("color 0F");
  printf("                                                          \033[96m>\033[32m>\033[93m>\033[95m>\033[31m>\033[94m>\033[91m>\033[0m Resta Um \033[96m<\033[32m<\033[93m<\033[95m<\033[31m<\033[94m<\033[91m<\033[0m \n ");
  printf("\n");

  printf("\033[94m>\033[91m>\033[0m Ola, usuario!! Antes de iniciarmos, por favor, entre com seu nome: \n");
  do{
  	scanf("%s", nome); 
  	setbuf(stdin, NULL);
  	if(strlen(nome) == 0) 
  		printf("\033[31m Nome invalido. Por favor, digite um nome valido: \033[0m \n");
  } while(strlen(nome) == 0);

  printf("\n");
  printf("\033[94m>\033[91m>\033[0m Bem-vindo, %s! O que voce deseja fazer? \n", nome);
  do{
  	  printf("\n");
	  printf("\t\033[91m1\033[0m - Jogar \n" );
	  printf("\t\033[91m2\033[0m - Consultar ranking \n" );
	  printf("\t\033[91m3\033[0m - Sair \n" );

	  scanf("%d", op);
	  setbuf(stdin, NULL);

	  if(*op != 1 && *op != 2 && *op != 3)
	  	printf("\033[31m Opcao invalida. Digite uma opcao valida: \033[0m\n");

  } while(*op != 1 && *op != 2 && *op != 3);
}

// Função para printar um menu secundario ao usuário
int menu(char *nome){
  int op;

  printf("\n");
  printf("\033[94m>\033[91m>\033[0m Escolha um dos niveis de dificuldade abaixo para iniciar o jogo: \n", nome);
  printf("\n" );
  printf("\t\033[91m1\033[0m - Facil - Tabuleiro piramide \n" );
  printf("\t\033[91m2\033[0m - Medio - Tabuleiro flecha \n" );
  printf("\t\033[91m3\033[0m - Dificil - Tabuleiro tradicional \n" );

  do{
    printf("\n" );
    scanf("%d", &op);
    setbuf(stdin, NULL); //limpar o buffer de leitura do teclado

    if(op != 1 && op != 2 && op != 3)
	  	printf("\033[31m Opcao invalida. Digite uma opcao valida: \033[0m\n");

  } while(op != 1 && op != 2 && op != 3);

  return op;
}

// Função para criar um tabuleiro com desenho tradicional
void imprime_tabuleiro(char **tab){
    int i, j;

    printf("\n");
    //Impressão dos índices da coluna
    printf("   ");
    for(i = 0; i < DIM; i++){
      printf("\033[91m%d \033[0m ", i);
    }
    printf("\n");

    for (i = 0; i < DIM; i++) {
        for (j = -1; j < DIM; j++){
            if(j == -1) { //Impressão dos índices da linha
              printf("\033[91m%d \033[0m ", i);
              continue;
            }
            if(*(*(tab + i) + j) == '1')
              printf("\033[94m%c\033[0m",*(*(tab + i) + j));
            else if(*(*(tab + i) + j) == '*')
              printf("\033[37m%c\033[0m",*(*(tab + i) + j));
            else printf("\033[93m%c\033[0m",*(*(tab + i) + j));
            printf("  ");
        }
        printf("\n");
    }
}

// Função para criar um tabuleiro com desenho tradicional
char **tradicional(){
    int i, j;
    char **tab;

    tab = (char **) malloc(DIM * sizeof(char *));

    if(!tab){
      printf("Erro ao alocar memoria\n");
      return NULL;
    }

    for (i = 0; i < DIM; i++) {
      *(tab + i) = (char *) malloc(DIM * sizeof(char));
      if(! *(tab + i)){
        printf("Erro ao alocar memoria\n");
        return NULL;
      }

      for(j = 0; j < DIM; j++){
        if((i < 2 && j < 2) || (i < 2 && j > 4) || (i > 4 && j < 2) || (i > 4 && j > 4) )
          *(*(tab + i) + j) = '*';
        else if (i == 3 && j == 3){
          *(*(tab + i) + j) = '0';
        }
        else{
          *(*(tab + i) + j) = '1';
        }
      }
    }

    return tab;
}

// Função para criar um tabuleiro com desenho de pirâmide
char **piramide(){
    int i, j;

    char **tab;
    tab = (char **) malloc(DIM * sizeof(char *));

    if(!tab){
      printf("Erro ao alocar memoria\n");
      return NULL;
    }

    for (i = 0; i < DIM; i++) {
      *(tab + i) = (char *) malloc(DIM * sizeof(char));
      if(! *(tab + i)){
        printf("Erro ao alocar memoria\n");
        return NULL;
      }

      for(j = 0; j < DIM; j++){
        if((i < 2 && j < 2) || (i < 2 && j > 4) || (i > 4 && j < 2) || (i > 4 && j > 4) )
          *(*(tab + i) + j) = '*';
        else if (i > 0 && i < 5 && j <= 3 + i - 1 && j >= 3 - (i - 1)){
          *(*(tab + i) + j) = '1';
        }
        else{
          *(*(tab + i) + j) = '0';
        }
      }
    }

    return tab;
}

// Função para criar um tabuleiro com desenho de flecha
char **flecha(){ 
    int i, j;

    char **tab;
    tab = (char **) malloc(DIM * sizeof(char *));

    if(!tab){
      printf("Erro ao alocar memoria\n");
      return NULL;
    }

    for (i = 0; i < DIM; i++) {
      *(tab + i) = (char *) malloc(DIM * sizeof(char));
      if(! *(tab + i)){
        printf("Erro ao alocar memoria\n");
        return NULL;
      }

      for(j = 0; j < DIM; j++){
        if((i < 2 && j < 2) || (i < 2 && j > 4) || (i > 4 && j < 2) || (i > 4 && j > 4) )
          *(*(tab + i) + j) = '*';
        else if (i < 3 && j <= 3 + i && (j >= 3 - i) || ((i == 3 || i == 4) && j == 3) || (i > 4 && j > 1 && j < 5)){
          *(*(tab + i) + j) = '1';
        }
        else{
          *(*(tab + i) + j) = '0';
        }
      }
    }

    return tab;
}

// Função para pegar as coordenadas e verificar um movimento
int verifica_movimento(char **p, int l1, int c1, int l2, int c2){
  /*
    1 - movimento válido na vertical
    2 - movimento válido na horizontal
    0 - movimento inválido
  */
  
  	if(l1 > 6 || l2 > 6 || c1 > 6 || c2 > 6) 
  		return 0;
    else if((*(*(p + l1) + c1) != '1') || (*(*(p + l2) + c2) != '0')){ //movimento inválido porque só posso mexer em peças e só posso ir para lugar vazio
      	return 0;
    }
    //movimentos na horizontal
    else if(abs(c2 - c1) == 2 && l1 == l2){
        if(c1 != 6 && c1 != 0){ //nos extremos não posso comparar peças
          if(*(*(p + l1) + (c1+1) ) == '1' || *(*(p + l1) + (c1-1)) == '1'){
            return 2;
          }
        }
        else if(c1 == 6){
          if(*(*(p + l1) + (c1-1)) == '1')
            return 2;
        }
        else{
          if(*(*(p + l1) + (c1+1)) == '1')
            return 2;
        }
    }

    //movimentos na vertical
     else if(abs(l2 - l1) == 2 && c2 == c1){
        if(l1 != 6 && l1 != 0){ //nos extremos não posso comparar peças
          if(*(*(p + l1+1) + (c1) ) == '1' || *(*(p + l1-1) + (c1)) == '1'){
            return 1;
          }
        }
        else if(l1 == 6){
          if(*(*(p + l1-1) + (c1)) == '1')
            return 1;
        }
        else{
          if(*(*(p + l1+1) + (c1)) == '1')
            return 1;
        }
    }

    else{
      return 0;
    }
        
}

// Função para pegar as coordenadas e realizar um movimento
void realiza_movimento(char **p, int l1, int c1, int l2, int c2, int validacao){
    int i, j;
    char **v = p;

    switch(validacao){
      case 0:
        printf("\n");
        printf("\033[31m Movimento invalido. Tente outro par de coordenadas! \033[0m\n");
        break;

      case 1:
        *(*(p + l1) + (c1)) = '0'; //!(*(*(p + l1) + (c1))) casa origem

        if(l2 > l1)
            *(*(p + l1+1) + (c1)) = '0'; //!(*(*(p + l1) + (c1)))
        else
            *(*(p + l1-1) + (c1)) = '0';

        *(*(p + l2) + (c2)) = '1'; //*(*(p + l2) + (c2)) casa destino
        movimentos++;
        break;

      default: //case 2
        *(*(p + l1) + (c1)) = '0'; //!(*(*(p + l1) + (c1))) casa origem

        if(c2 > c1)
            *(*(p + l1) + (c1+1)) = '0'; //!(*(*(p + l1) + (c1)))
        else
            *(*(p + l1) + (c1-1)) = '0'; //!(*(*(p + l1) + (c1)))

        *(*(p + l2) + (c2)) = '1'; //*(*(p + l2) + (c2)) casa destino
        movimentos++;
    }
}

int verifica_fim(char **p){
  /*Função retorna 0 se não há mais movimentos possíveis e 1 se ainda existem*/
    int i, j, check = 0; //check é variável de checagem se existem movimentos possíveis

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++){

          //verificação se o índice não extrapola os limites
          if(i+2 < DIM){ 
            if(verifica_movimento(p, i, j, i+2, j) == 1){
                check = 1;
                break;
            }
          }

          if(j+2 < DIM){ 
            if(verifica_movimento(p, i, j, i, j+2) == 2 ){
                check = 1;
                break;
            }
          }

          if(i-2 >= 0){ 
            if(verifica_movimento(p, i, j, i-2, j) == 1 ){
                check = 1;
                break;
            }
          }

          if(j-2 >= 0){ 
            if(verifica_movimento(p, i, j, i, j-2) == 2 ){
                check = 1;
                break;
            }
          }

        }

        if(check == 1) break;
    }

    return check;
}

//Função para ordenar as estruturas por tempo de jogo
void mostra_ranking(Jogador *vetor, int n){
	int k, j;
	Jogador aux;

	//bubble sort para ordenar 
	for(k = 1; k < n; k++){

		for(j = 0; j < n - 1; j++){
			if((vetor + j)->tempo > (vetor + j + 1)->tempo){
				aux = *(vetor + j);
				*(vetor + j) = *(vetor+j+1);
				*(vetor+j+1) = aux;
			}

		}
	}

	for(k = 0; k < n; k++){
		switch((vetor + k)->op){
			case 1:
				printf("\033[32m %d lugar \033[0m - %s com %.2f minutos - nivel facil \n", k+1, (vetor + k)->nome, (vetor + k)->tempo);
				break;
			case 2:
				printf("\033[32m %d lugar \033[0m - %s com %.2f minutos - nivel medio \n", k+1, (vetor + k)->nome, (vetor + k)->tempo);
				break;
			default:
				printf("\033[32m %d lugar \033[0m - %s com %.2f minutos - nivel dificil \n", k+1, (vetor + k)->nome, (vetor + k)->tempo);
		}
		
	}

}