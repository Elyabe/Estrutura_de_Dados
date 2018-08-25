/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS II
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação de Heap : Lista de prioridade com livros

CRIADO EM: 04/04/2016
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
	int chave;
	struct no *prox, *ant ;
} No;

void imprimir_lista( No *L );
No* excluir( No* L, int chave );
No* buscar( No* L, int chave );
No* inserir_ordenado( No* L, No* novo );
No* inserir_fim( No* L, No* Novo );
No* inserir_inicio( No* L, No* novo );
No* novo_no( int chave );
No* removeNElementos( No *L, int n );
No* criar_lista( int vetor[], int n);
No* desalocar( No *L );

int main()
{
	No *novo, *Lista = novo_no(4);
	if ( Lista )
	{
		novo = novo_no(16);
		Lista = inserir_ordenado(Lista,novo);
		imprimir_lista(Lista);
		novo = novo_no(-3);
		Lista = inserir_ordenado(Lista,novo);
		imprimir_lista(Lista);
		novo = novo_no(0);
		Lista = inserir_inicio(Lista,novo);
		imprimir_lista(Lista);
		novo = novo_no(7);
		Lista = inserir_fim(Lista,novo);
		imprimir_lista(Lista);
		
		//Questão 1
		printf("Q1\n");
		imprimir_lista(Lista);
		imprimir_lista(novo);

		//Questão 02
		printf("Q2\n");
		imprimir_lista(Lista);

		// Questão 03
		printf("Q3\n");
		//Lista = removeNElementos(Lista,2);
		//imprimir_lista(Lista);

		// Questão 04
		printf("Q4\n");
		imprimir_lista(Lista);
		imprimir_lista(novo);
		imprimir_lista(Lista);

		int vet[] = {1,2,3,4,5,6};
		No *l2 = criar_lista(vet,6);
		imprimir_lista(l2);

	}
}


// Aloca e retorna o ponteiro para um novo nó
// chave : Valor chave do novo nó
No* novo_no( int chave )
{
	No *novo = (No*)malloc(sizeof(No));
	
	if ( novo )
	{
		novo -> chave = chave;
		novo -> ant = novo -> prox = NULL;;
	} else
		printf(" Erro de alocação! \n");
	return novo;
}

// Insere elemento e retorna ponteiro para início da lista
// L : Ponteiro para lista
// novo : Ponteiro para novo elemento
No* inserir_inicio( No* L, No* novo )
{
	if ( L )
		novo->prox = L, L -> ant = novo;	
	
	return novo;
}

// Insere elemento no fim da lista e retorna ponteiro para início da lista
// L : Ponteiro para lista
// novo : Ponteiro para novo
No* inserir_fim( No* L, No* novo )
{
	No *aux = L;

	if (!aux) return novo;
	
	while ( aux -> prox != NULL )
		aux = aux -> prox;
	
	aux -> prox = novo , novo -> ant = aux ;
	return L;
}

// Insere ordenado numa lista 
// L : Ponteiro para lista
// novo : Ponteiro para novo elemento
No *inserir_ordenado( No* L, No* novo ) //[ok]
{
	No *aux = L;

	if ( aux == NULL ) return novo;
	
	while (aux -> prox != NULL && aux -> chave < novo -> chave )
		 aux = aux -> prox;
	
	if ( aux -> chave < novo -> chave )
	{
		novo -> ant = aux, novo -> prox = aux -> prox;
		aux -> prox  = novo ;
	} else {
				novo -> prox = aux;
				novo -> ant = aux -> ant;
				if ( aux -> ant != NULL )
					aux -> ant ->  prox = novo;
				else
					L = novo; 
			}
	aux -> ant = novo;
	
	return novo;
}

// Busca e retorna um ponteiro que aponta para o elemento buscardo, caso exista
// L : Ponteiro para lista
// chave : Valor a ser buscardo 
No* buscar( No* L, int chave )
{
	No *aux = L;
	
	while ( aux != NULL && aux -> chave != chave )
		aux = aux -> prox;

	if ( !aux ) printf("Error 404 - Not found :(\n");
	
	return aux;
}

// Exclui, caso exista, um elemento da lista 
// L : Ponteiro para lista
// chave : Valor chave a ser excluído
No* excluir( No* L, int chave )
{
	No *aux = buscar(L,chave);
	if ( aux )
	{
		if ( aux -> ant )
			aux -> ant -> prox = aux -> prox;
		else
			L = aux -> prox;
		
		if ( aux -> prox )
			aux -> prox -> ant = aux -> ant;

		free( aux );
	}
	return L;
}

// Imprime uma lista na tela
// L : Ponteiro para lista
void imprimir_lista( No *L )
{
	No *aux = L; 

	printf("L->");
	
	while ( aux )
		printf("[%d]-> ", aux -> chave ), aux = aux -> prox;
	
	printf("NULL \n");
}


// Desaloca a lista e libera sua memória
// L : Ponteiro para L
No* desalocar( No *L )
{
	No *aux = L;
	
	while ( aux )
		L = aux -> prox, free(aux), aux = L;
	
	return L;
}



// Cria uma lista a partir de um vetor de elementos
No* criar_lista( int vetor[], int n)
{
	No *L = NULL, *novo;
	int i;

	L = novo_no(vetor[0]);

	for ( i = 1; i < n; i++ )
	{
		novo = novo_no(vetor[i]);
		L = inserir_fim( L, novo ) ;
	}
	
	return L;
}