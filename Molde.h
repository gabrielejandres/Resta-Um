/*

* Programa: Jogo Resta Um em linguagem C
* Autores: Gabriele Jandres, Maria Carolina Esteves e Victor Cardoso
* Universidade Federal do Rio de Janeiro
* Descrição: *********
* Arquivo de interface do módulo

	-> Alusoes de variaveis globais 
	-> Alusoes de funcoes globais 

*/
#include "Defs.h"
#ifndef MOLDE_H
#define MOLDE_H

/* ALUSÕES DE VARIÁVEIS GLOBAIS */

extern int movimentos;

/* ALUSÕES DE FUNÇÕES GLOBAIS */

void menu_inicial(char nome[], int * op);
int menu(char *nome);
void imprime_tabuleiro(char **tab);
char **tradicional();
char **piramide();
char **flecha();
int verifica_movimento(char **p, int l1, int c1, int l2, int c2);
void realiza_movimento(char **p, int l1, int c1, int l2, int c2, int validacao);
int verifica_fim(char **p);
void mostra_ranking(Jogador *vetor, int n);

#endif