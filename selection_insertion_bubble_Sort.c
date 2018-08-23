/* 
UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Revisão e Implementação de métodos simples de ordenação 

CRIADO EM: 
PROFESSOR: Luciana Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alocar_vetor( tamanho ) ( int* )calloc( tamanho, sizeof( int ) )

void exibir_dados( int *v , int tam );
void preencher_vetor( int *v, int tam );
void trocar( int *v, int i, int k );
void bubbleSort( int *V, int tam );
void selectionSort( int *V, int tam );
void insertionSort( int *V, int tam );

int main()
{
	int tam_V1, *V_1;

	scanf("%d", &tam_V1 );
	
	V_1 = alocar_vetor( tam_V1 );

	if ( V_1 )
	{
		
		preencher_vetor( V_1, tam_V1 );
		exibir_dados( V_1, tam_V1 );
		
		// bubbleSort( V_1, tam_V1 );
		// insertionSort( V_1, tam_V1 );
		selectionSort( V_1, tam_V1 );
		exibir_dados( V_1, tam_V1 );

		free( V_1 );
	} else 
			printf("OH oh \n");
	return 0;
}

// Ordena o vetor de inteiros pelo método da bolha
// V : Ponteiro para vetor a ser ordenado
// tam : Quantidade de elementos do vetor 
void bubbleSort( int *V, int tam )
{
	int j = tam, i ;

	while ( j > 1 )
	{
		for ( i = 0; i < j - 1; i++  )
		{
			if ( V[i] > V[i+1] )
				trocar( V, i, i+1 );
		}
		j--;
	}
}


// Ordena os elementos de um vetor de inteiros pelo método da inserção
// V : Ponteiro para vetor a ser ordenado
// tam : Quantidade de elementos do vetor
void insertionSort( int *V, int tam )
{
	int i, j, chave;

	for ( j = 1; j < tam; j++ )
	{
		chave = V[j];
		// Desloca os elementos de V maiores do que a chave e a insere na posição correta
		for ( i = j - 1; i >= 0 && V[i] > chave ; i-- )
			trocar( V, i, i+1 );
		V[i+1] = chave;
	}

}

// Ordena um vetor de inteiros pelo método da seleção
// V : Ponteiro para vetor a ser ordenado
// tam : Quantidade de elementos do vetor
void selectionSort( int *V, int tam )
{
	int i, j, i_min;

	for ( i = 0; i < tam - 1; i++ )
	{
		i_min = i;
		for ( j = i + 1; j < tam; j++ )
		{
			if ( V[j] < V[i_min] )
				i_min = j;
		}

		trocar( V, i_min, i );
	}
}

// Exibe na tela os inteiros de um vetor 
// v : Vetor de inteiros
// tam : Quantiade de inteiros  
void exibir_dados( int *v , int tam )
{
	int i;
	printf("[ ");
	for ( i = 0; i < tam; i++ )
		printf("%d |", v[i] );
	printf("]\n\n");
}

// Preenche e retorna um vetor com inteiros pseudo-aleatórios
// v : vetor de inteiros
// tam : quantidade de inteiros
void preencher_vetor( int *v, int tam )
{
	int i;
	for ( i = 0; i < tam; i++ )
		v[i] = rand() % 100;	
}

// Troca elementos de posição no vetor
// v : Ponteiro para vetor 
// i, k : Posições dos elementos da troca
void trocar( int *v, int i, int k )
{
	int aux;
	aux = v[i], v[i] = v[ k ],  v[k] = aux; 
}
