/* 
UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação de algoritmos de ordenação de complexidade linear

PROFESSOR: Luciana Lee
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

#define alloc( size ) (int*)calloc( size, sizeof(int))

typedef struct vector
{
	int *data,
		size;
} Vector;

void countingSortAdapted ( Vector** A, int k, int col, int qtdDigit);
Vector* create_vector( int size );
Vector* countingSort ( Vector* A, int k );
int digit( int value, int qtdDigit, int digit );
void show_vector( Vector* myVector );
void radixSort ( Vector** A, int qtdDigit );
void createSequence( Vector** myVector );

// Função principal
int main()
{
	Vector *myVector = create_vector(14);
	int value, d;
	// Popula o vetor 
	createSequence( &myVector );
	// Exibe o vetor 
	show_vector( myVector );
	

	radixSort ( &myVector, 3 );
	
	show_vector( myVector );
	// scanf("%d", &value );
	// scanf("%d", &d );
	// printf("%d\n", digit( value, 2, d) );

	free( myVector -> data );
	free( myVector );
	return 1;
}


// Aloca e retorna vetor de inteiros
// size : Quantidade de elementos 
Vector* create_vector( int size )
{
	Vector *new = ( Vector*)calloc( sizeof( Vector), 1 );
	if ( new )
	{
		new -> data = alloc( size + 1 );
		new -> size = size;
	}
	return new;
}

// Ordena os elmentos de um vetor lexicograficamente
// A : Vetor a ser ordenado
// qtdDigit : Quantidade de dígitos dos números
// k maior elemento
Vector* countingSort ( Vector* A, int k )
{
	if ( A )
	{
		
		int *aux, *B = alloc ( A -> size + 1 ),
		*C = alloc( k + 1 ), i, n = A -> size;
		for ( i = 0; i < n; i++ )	
			C[ (A -> data)[i] ]++;

		for ( i = 2; i <= k; i++ )	
			C[ i ] += C[ i - 1 ];
			
		for ( i = n - 1; i >= 0 ; i-- )	
			B[ C[ (A -> data)[i] ] ] = C[ (A -> data)[i] ]--;
		
		aux = A -> data, A -> data = B;
		free ( aux ), free ( C );
	}
	return A;
}

// Preenche o vetor com elementos inteiros
// myVector : Vetor a ser ordenado
void createSequence( Vector** myVector )
{
	int i;
	for ( i = 0; i < (*myVector) -> size; i++ )
		((*myVector) -> data )[i] = (100 + rand() ) % 999 ;
}

// Ordena os elmentos de um vetor lexicograficamente
// A : Vetor a ser ordenado
// qtdDigit : Quantidade de dígitos dos números
void radixSort ( Vector** A, int qtdDigit )
{
	int w;
	for ( w = 1; w <= qtdDigit; w++ )
		countingSortAdapted( A,9, w, qtdDigit );
}

// Exibe os elementos do vetor 
// myVector : Vetor a ser exibido
void show_vector( Vector* myVector )
{
	int cont;
	printf("[");
	for ( cont = 0; cont <= myVector -> size; cont++ )
		printf("%d |", (myVector -> data)[cont]  );
	printf("]\n");
}

// Retorna o k-ésimo digito do número
// value : Número
// qtdDigit : Quantidade de dígitos do número
// digit : Posição do dígito a ser extraído
int digit( int value, int qtdDigit, int digit )
{
	int rest = value, dig = 0;
	while ( qtdDigit >= digit )
	{
		int pot = pow( 10, qtdDigit-1) ;
		if ( rest >= pot )
			dig = rest / pot, rest %= pot;
		else
			dig = 0;
		qtdDigit--;
	}
	return dig;
}

// Ordena o vetor de inteiros - CountingSort adaptado
// A : Vetor de inteiros a ser ordenado
// k : Maior valor do conjunto
// col : Coluna
// qtdDigit : Quantidade de dígitos das palavras
void countingSortAdapted ( Vector** A, int k, int col, int qtdDigit )
{
	if ( *A )
	{
		int n = (*A) -> size, *aux, *B = alloc ( n + 1 ), *C = alloc( k + 1 ), i;
		for ( i = 0; i < n; i++ )	
			C[ digit( ((*A) -> data)[i], qtdDigit, col ) ]++;

		for ( i = 1; i <= k; i++ )	
			C[ i ] += C[ i - 1 ];
			
		for ( i = n - 1; i >= 0 ; i-- )	
		{
			B[ C[ digit( ((*A) -> data)[i], qtdDigit, col ) ] -1 ] = ( (*A) -> data)[i];
			C[ digit( ((*A) -> data)[i], qtdDigit, col )   ]--;
		}
		
		aux = (*A) -> data, (*A) -> data = B;
		free ( aux ), free ( C );
	}
}

