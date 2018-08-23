/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I - EDI20161
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação de Lista simplesmente encadeada

CRIADO EM: 2016/1
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


typedef struct no
{
	int chave;
	struct no *prox;
} No;

void imprimeLista( No *L );
No* excluiElemento( No* L, int chave );
No* busca( No* L, int chave );
No *inserir_ordenado( No* L, No* Novo );
No* inserir_fim( No* L, No* Novo );
No* inserir_inicio( No* L, No* Novo );
No* novo_no( int chave );
No* divide( No* L, int n );
No* concatena( No* L1, No* L2 );
No* removeNElementos( No *L, int n );
No* intercala( No *L1, No* L2 );
No* criar_lista( int vetor[], int n);
No* deletar_lista( No *L );

int main()
{
	No *Novo, *Lista = novo_no(4);
	
	if ( Lista )
	{
		Lista = inserir_ordenado( Lista, novo_no( 16 ) );
		imprimeLista( Lista );
		Lista = inserir_ordenado( Lista, novo_no( -3 ) );
		imprimeLista( Lista );
		Lista = inserir_inicio( Lista, novo_no( 0 ) );
		imprimeLista( Lista );
		Lista = inserir_fim(Lista,novo_no( 7 ));
		imprimeLista( Lista );
		
		//Questão 1
		printf("Q1\n");
		Novo = divide(Lista, 4);
		imprimeLista(Lista);
		imprimeLista(Novo);

		//Questão 02
		printf("Q2\n");
		Lista = concatena(Lista, Novo);
		imprimeLista(Lista);

		// Questão 03
		printf("Q3\n");
		//Lista = removeNElementos(Lista,2);
		//imprimeLista(Lista);

		// Questão 04
		printf("Q4\n");
		Novo = divide(Lista,4);
		imprimeLista(Lista);
		imprimeLista(Novo);
		Lista = intercala(Lista, Novo);
		imprimeLista(Lista);

		int vet[] = {1,2,3,4,5,6};
		No *l2 = criar_lista(vet,6);
		imprimeLista(l2);

		// Libera memória
		Lista = deletar_lista( Lista );
		l2 = deletar_lista( l2 );
		Novo = deletar_lista( Novo );
	}
	
	return 0;
}


// Aloca e retorna um ponteiro para novo no 
// chave : Valor chave do nó
No* novo_no( int chave )
{
	No *novo = (No*)malloc(sizeof(No));
	
	if ( novo )
	{
		novo -> chave = chave;
		novo -> prox = NULL;
	} else
		printf(" Erro de alocação! \n");
	return novo;
}

// Insere um novo nó no início da lista 
// L : Ponteiro para lista
// novo : Ponteiro para novo nó
No* inserir_inicio( No* L, No* novo )
{
	novo -> prox = L;
	return novo;
}

// Insere um novo nó no fim da lista
// L : Ponteiro para lista 
// novo : Ponteiro para novo elemento
No* inserir_fim( No* L, No* novo )
{
	No *aux = L;
	// Lista vazia
	if (!aux) return novo;
	
	// Determina fim da lista
	while ( aux -> prox != NULL )
		aux = aux -> prox;

	aux -> prox = novo ; 
	
	return L;
}

// Insere novo elemento ordenado na lista
// L : Ponteiro para lista
// novo : Ponteiro para novo elemento
No *inserir_ordenado( No* L, No* novo )
{
	No *ant = NULL, *aux = L;

	while (aux != NULL && aux -> chave < novo -> chave )
		ant  = aux , aux = aux -> prox;
	
	novo -> prox = aux;
	
	if ( ant )
	{
		ant -> prox = novo ;
		return L;
	}

	return novo;
}

// Busca e retorna ponteiro para elemento buscado
// L : Ponteiro para lista 
// chave : Valor chave a ser buscado
No* busca( No* L, int chave )
{
	No *aux = L;
	while ( aux != NULL && aux -> chave != chave )
		aux = aux -> prox;
	return aux;
}

// Remove elemento e retorna lista modificada 
// L : Ponteiro para lista 
// chave : Valor chave a ser removido (1a ocorrência)
No* excluiElemento( No* L, int chave )
{
	No *aux = L, *ant = NULL;

	while ( aux != NULL && aux -> chave != chave )
		ant = aux, aux = aux -> prox;

	if ( aux )
	{
		if ( ant )
			ant -> prox = aux -> prox;
		else
			L = aux -> prox;
		free( aux );
	}
	return L;
}

// Exibe lista na tela 
// L : Ponteiro para lista 
void imprimeLista( No *L )
{
	No *aux = L;

	printf("L->");
	while ( aux )
	{
		printf("[%d]-> ", aux -> chave );
		aux = aux -> prox;
	}
	printf("NULL \n");
}

// Divide uma lista em duas a partir da primeira ocorrência de um valor 
// L : Ponteiro para lista original
// n : Valor chave a partir do qual a lista será dividida
No* divide( No* L, int n )
{
	No *aux = L, *novaL = NULL;

	while ( aux && n != aux -> chave )
		aux = aux -> prox ;

	if ( aux )
	{	
		novaL = aux -> prox, 
		aux -> prox = NULL;
	}
	return novaL;
}

// Concatena e retorna duas listas 
// L1, L2 : Ponteiros para listas a serem encadeadas
No* concatena( No* L1, No* L2 )
{
	if ( !L1 ) return L2;
	if ( !L2 ) return L1;
	No *aux = L1;
	while ( aux -> prox != NULL )
		aux  = aux -> prox;
	aux -> prox  = L2;
	return L1;
}

// Remove e retorna os n primeiros elementos da lista
// L : Ponteiro para lista
// n : Quantidade de elementos a serem removidas
No* removeNElementos( No *L, int n )
{
	No *aux = L;
	while ( aux && n > 0 )
	{
		L = aux -> prox;
		free(aux);
		aux = L, n--;
	}
	return L;
}

// Cria e retorna uma nova lista resultado da intercalação de duas listas
// L1, L2 : Ponteiros para listas a serem intercaladas
No* intercala( No *L1, No* L2 ) //enxugar codigo
{
	No *aux1 = L1, *aux2 = L2, *temp, *temp2;
	
	// Uma das listas vazias
	if ( !aux1 ) return aux2;
	if ( !aux2 ) return aux1;

	// Quando chegar ao final de uma das duas listas
	while ( aux1 != NULL && aux2 != NULL )
	{
		temp = aux1, temp2 = aux2;
		aux1 = aux1 -> prox, aux2 = aux2 -> prox;
		temp -> prox = temp2;
		temp2 -> prox = aux1;
	}

	if ( aux1 == NULL )
		aux1 -> prox = aux2;
	else
		temp2 -> prox = aux1;	
	return L1;
}

// Cria uma lista a partir de um vetor com n elementos
// V : Vetor de inteiros 
// n : Quantidade de números no vetor
No* criar_lista( int V[], int n )
{
	No *L = NULL;
	int i;

	for ( i = 0; i < n; i++ )
		L = inserir_fim( L, novo_no( V[i] ) ) ;

	return L;
}

// Deleta lista e libera área de memória
// L : Ponteiro para lista
No* deletar_lista( No *L )
{
	No *aux;
	
	while ( L )
	{
		aux = L;
		L = L -> prox;
		free( aux );
	}

	return L;
}


