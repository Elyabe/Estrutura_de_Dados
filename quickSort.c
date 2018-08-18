/* 
UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação do QuickSort com diversas funções de particionamento
CRIADO EM: 06/08/2016

PROFESSOR: Luciana Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define alocar_vetor( tamanho ) ( int* )calloc( tamanho, sizeof( int ) )

void exibir_dados( int *v , int tam );
void preencher_vetor( int *v, int tam );
void trocar( int *v, int i, int k );
int pivo ( int *v, int p, int r );
int particionar( int *v, int p, int r );
int particionar2( int *v, int p, int r );
void quickSort( int *v, int p, int r );

// Função principal
int main()
{
	int tam_V1, *V_1;

	scanf("%d", &tam_V1 );
	
	V_1 = alocar_vetor( tam_V1 );

	if ( V_1 )
	{
		
		preencher_vetor( V_1, tam_V1 );
		exibir_dados( V_1, tam_V1 );
		
		//TESTE QuickSort
		quickSort( V_1, 0, tam_V1-1 );
		exibir_dados( V_1, tam_V1 );

		free( V_1 );
	} else 
			printf("OH oh \n");
	return 0;
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
	printf("]\n");
}

// Preenche e retorna um vetor com inteiros pseudo-aleatórios
// v : vetor de inteiros
// tam : quantidade de inteiros
void preencher_vetor( int *v, int tam )
{
	int i;
	for ( i = 0; i < tam; i++ )
		v[i] = rand() % 1000;	
}

// Troca elementos de posição no vetor
// v : Ponteiro para vetor 
// i, k : Posições dos elementos da troca
void trocar( int *v, int i, int k )
{
	int aux;
	aux = v[i], v[i] = v[k],  v[k] = aux; 
}

// Determina e retorna o índice do elemento pivô por mediana de 3 elementos
// v : Ponteiro para vetor de inteiros
// p, r : Limites dos índices v[ p, ... , r ]
int pivo ( int *v, int p, int r )
{
	int ind[3] = { p, (p+r)/2, r }, i, j;
	
	for ( i = 0; i < 2; i++ )
		for ( j = i + 1; j < 3; j++ )
		 	if ( v[ ind[i] ] > v [ ind[j] ] )
				trocar( ind, i, j );
	return ind[1];
}

// INCOMPLETA
// Particiona e retorna índice do particionamento de um vetor de inteiros
// v : Vetor a ser particionado
// p, r : Indices limites do vetor v[p, ..., r]
int particionar_v2( int *V, int p, int r )
{	
	trocar( V, pivo( V, p, r ), r );
	
	int i = p,  j = r - 1;

	// exibir_dados( v, r - p + 1 );
	
	// Enquanto não terminou a partição
	while ( i < j )
	{
		
		while ( V[i] <= V[r] ) i++;
		while ( V[j] > V[r] ) j--;
		
		// Se não terminou a partição
		if ( i < j )
			trocar( V, i++, j-- );	
	}
	
	// Reposiciona o pivô
		trocar( V, i, r );
	return i;
}



// INCOMPLETA - A IMPLEMENTAR - VERSÂO ELEMENTOS REPETIDOS
// Particiona e retorna índice do particionamento de um vetor de inteiros
// v : Vetor a ser particionado
// p, r : Indices limites do vetor v[p, ..., r]
int particionar_v3( int *V, int p, int r )
{
	trocar( V, pivo( V, p, r ) , r );
	int i, k, q, j;
	 i = k = p, j = q = r - 1;
	 exibir_dados( V, r - p + 1 );
	while ( i < j )
	{
		while ( V[i] < V[r] ) i++;
		while ( V[j] > V[r] ) j--;
		if ( i < j )
		{
			if ( V[i] == V[r] || V[j] == V[r] )
			{
				if ( V[i] == V[r] ) 
					trocar( V, i++, k++);
				else 
					trocar( V, j--, q-- );
			} else 
				 trocar( V, i++, j--);
		}	
	}
	 int w, aux = i++ ;
	 for ( w = k + 1; w <= i; w++ )
	 	trocar( V, p, w ), p++;
	 for ( w = q; w <= r; w++ )
	 	trocar( V, w, i ), i++;
	return aux;
}

// Particiona e retorna índice do particionamento de um vetor de inteiros
// v : Vetor a ser particionado
// p, r : Indices limites do vetor v[p, ..., r]
int particionar( int *V, int p, int r )
{
	int i = p, j = r - 1;
	
	// Enquanto não acabou de particionar
	while ( i <= j )
	{
		if ( V[i] <= V[r] ) i++;
		else if ( V[j] > V[r] ) j--;
		else 
			trocar( V, i++, j-- );
	}
	// Reposiciona o pivô em sua posição
	trocar( V, i, r );
	return i;
}


// Ordena vetor de inteiros 
// V : Vetor 
// p, r : Índices limites do vetor V[p, ..., r] 
void quickSort( int *V, int p, int r )
{
	int m;
	if ( p < r ) 
	{ 
		// Determina índice do pivô da partição e particiona
	  	m = particionar( V, p, r );
	  	// m = particionar_v2( V, p, r );
	  	quickSort( V, p, m-1 );
	  	quickSort( V, m+1, r );
	}
}
