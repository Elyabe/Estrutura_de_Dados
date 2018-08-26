/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS II
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação de pilha 

CRIADO EM: 12/05/2016
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
  	int valor;
	struct no *prox;
} No;

typedef struct pilha
{
    No *topo;
    int tamanho;
} Pilha;

No* pop( Pilha **pilha );
Pilha* push( Pilha *pilha, int valor );
Pilha* criar_pilha(void);
No* novo_no( int chave );
int esta_vazia( Pilha *pilha );
void imprimir_pilha( Pilha *pilha );
Pilha* desalocar( Pilha **pilha );

int main()
{
  
	Pilha *minha_pilha = criar_pilha();

	minha_pilha = push( minha_pilha, 1 );
	minha_pilha = push( minha_pilha, 5 );
	minha_pilha = push( minha_pilha, 15 );

	imprimir_pilha( minha_pilha );

	No *x = pop( &minha_pilha );
	printf("\n %d  desempilhado \n", x -> valor );

	imprimir_pilha( minha_pilha );

	desalocar( &minha_pilha );

	return 0;
}


No* novo_no( int chave )
{
	No *novo = (No*)malloc(sizeof(No));
	if ( novo )
	{
		novo -> valor = chave;
		novo -> prox = NULL;
	}

	return novo;
}

// Aloca, inicializa e retorna ponteiro para uma pilha
Pilha* criar_pilha(void)
{
	Pilha *pilha = (Pilha*)malloc( sizeof(Pilha) );
	if ( pilha )
	{	
		pilha -> topo = NULL;
		pilha -> tamanho = 0;
	} else {
				printf("Erro de alocação \n");
				exit(0);
			}

	return pilha;
}

// Retorna 1 se a pilha está vazia e 0 caso contrário
// pilha : Ponteiro para pilha a ser verificada
int esta_vazia( Pilha *pilha )
{
  return !( pilha -> topo ) ;
}

// Insere um novo elemento na pilha 
// pilha : Ponteiro para pilha
// valor : Chave a ser inserida
Pilha* push( Pilha *pilha, int valor )
{
	No *novo = novo_no( valor );
	
	novo -> prox = pilha -> topo;
	pilha -> topo = novo;
	pilha -> tamanho++;

	return pilha;
}

// Desempilha e retorna o elemento do topo
// pilha : Ponteiro para pilha
No* pop( Pilha **pilha )
{
	No* result = NULL;
	if ( !esta_vazia( *pilha ) )
	{
		result = (*pilha) -> topo;
		(*pilha) -> topo = (*pilha) -> topo -> prox;
		result -> prox = NULL;
		(*pilha) -> tamanho--;
	} else
		printf("Pilha vazia! \n");

	return result;
}

void imprimir_pilha( Pilha *pilha )
{
	No *aux = pilha -> topo;

	printf("\n");
	while ( aux )
	{
		printf("[\t %d \t ]\n", aux -> valor );
		aux = aux -> prox;
	}
}

Pilha* desalocar( Pilha **pilha )
{
	No *x = NULL;
	while ( !esta_vazia( *pilha ) )
	{
		x = pop( pilha );
		free( x );
	}
	return *pilha;
}
