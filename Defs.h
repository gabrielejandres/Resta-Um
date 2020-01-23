/*

* Programa: Jogo Resta Um em linguagem C
* Autores: Gabriele Jandres, Maria Carolina Esteves e Victor Cardoso
* Universidade Federal do Rio de Janeiro
* Descrição: *********
	
	-> Definição de tipos
	-> Definição de macros

*/

#ifndef DEFS_H
#define DEFS_H

/* DECLARAÇÕES DE MACROS */

#define DIM 7

/* DECLARAÇÕES DE TIPOS */

// Estrutura para armazenar os dados de um jogador que posteriormente serão guardados em um arquivo
typedef struct{
    char nome[60];
    float tempo;
    int op;
} Jogador;

#endif