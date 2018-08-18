/* 
UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO - UFES
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação do MergeSort com diversas funções de intercalação

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
static void  intercalar( int *v, int p, int q, int r );
static void  intercalar_in_loco_v1( int *v, int p, int q, int r );
static void  intercalar_in_loco_v2( int *v, int p, int q, int r );
static void  intercalar_in_loco_v3( int *v, int p, int q, int r );
void mergeSort( int *v, int p, int r );
void intercalar_vetores_recursiva( int *v1, int *v2, int indV1,  int tv1, int indV2, int tv2, int **result, int k );

int main()
{
	int tam_V1, *V_1;

	scanf("%d", &tam_V1 );
	
	V_1 = alocar_vetor( tam_V1 );

	if ( V_1 )
	{
		
		preencher_vetor( V_1, tam_V1 );
		exibir_dados( V_1, tam_V1 );
		
		//TESTE mergeSort
		mergeSort( V_1, 0, tam_V1 );
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

// Inverte os elementos num vetor de inteiros
// v : Vetor de inteiros
// n : Quantidade de elementos de v
void inverter( int *v, int n  )
{
	int i;
	for ( i = 0; i < n/2 ; i++ )
		trocar( v, i, n-i-1 );
}

// Intercala vetor utilizando espaço auxiliar
// v : Vetor de inteiros
// p, q, r : Índices do vetor : v[p, ..., q, ... , r-1 ]
static void  intercalar( int *v, int p, int q, int r ) 
{
   int i, j, k, *w;                        
 
   w = alocar_vetor( r - p );
   i = p; j = q;                           
   k = 0;                                  

   // Enquanto existem elementos a serem comparados nos dois vetores 
   while ( i < q && j < r ) 
      w[k++] = ( v[i] <= v[j] ) ? v[i++] : v[j++];
   
   while (i < q)  w[k++] = v[i++];         
   while (j < r)  w[k++] = v[j++];         

   memcpy( &(v[p]) , w,  sizeof( int )*( r - p ) );
   free (w);                               
}

// Alternativas de intercalação em teste ==============================================
// Alternativas de intercalacao in loco
// Intercala vetor com subvetores SEM usar memória auxiliar versão 1
// v : Vetor a ser intercalado
// p, q, r : Índices dos subvetores v[p, ..., q, ... , r-1 ]
static void  intercalar_in_loco_v1( int *v,int p, int q, int r ) 
{
   int i = p, x, k;                        
   
   while ( i < q && q < r) 
   {
	   if ( v[i] >= v[q] ) 
	   {
	      x = v[q];
	      for ( k = q - 1; k >= i; k-- ) 
	         v[k+1] = v[k];
	      v[i] = x;
	      q++; 
	  	}
	   i++; 
	}                       
}


// Intercala os elementos de um vetor SEM usar memória auxiliar versão 2
// v : Vetor de inteiros
// p, q, r : Índices do vetor v[p, ..., q, ... , r-1 ]
static void  intercalar_in_loco_v2( int *v, int p, int q, int r ) 
{
    int i , x, k;                        
    while ( q < r ) 
	{
      	x = v[q];
      	for ( i = q - 1; i >= p && v[i] > x; i-- ) 
          v[i+1] = v[i];
      	v[i+1] = x;
   	 q++; 
	}
}


// Intercala os elementos de um vetor SEM usar memória auxiliar versão 3
// v : Vetor de inteiros
// p, q, r : Índices do vetor v[p, ..., q, ... , r-1 ]
static void  intercalar_in_loco_v3( int *v, int p, int q, int r ) 
{
   int i, j, k, *w;

   inverter( v, r - q );

   i = 0; j = r-p-1;
   
   for ( k = p; k < r; k++ )
      ( v[i] <= v[j] ) ? trocar( v, k, i++ ) : trocar( v, k, j-- );
}

// Mergesort : Ordena os elementos com complexidade O( nlg(n))
// v : Ponteiro para vetor a ser ordenado
// p, r : Índice de início e fim, respectivamente do subvetor v[ p, ..., r ]
void mergeSort( int *V, int p, int r )
{
   // Se existe mais do que 1 elemento no subVetor
   if ( p < r-1 ) 
   {                 
    // Calcula metade e ordena primeira metade
    int q = (p + r)/2;          
    mergeSort (V, p, q );    
    mergeSort (V, q, r );  
    // Intercala as duas metades ordenadas
    intercalar( V, p, q, r );
    // intercalar_in_loco_v1( V, p, q, r ); 
    // intercalar_in_loco_v2( V, p, q, r ); 
    // intercalar_in_loco_v3( V, p, q, r );  
   }
}

// Atividade de implementação ==========================================================================================
// Intercala dois vetores disjuntos retornando um ponteiro para o resultado
// v1, v2 : Ponteiros para vetores disjuntos
// tv1, tv2 : Quantidades de elementos dos vetores 1 e 2, respectivamente
int* intercalar_vetores( int *v1, int *v2, int tv1, int tv2 )
{
	int *result = alocar_vetor( tv1 + tv2 ), i, j, k;
	i = j = k = 0;
	
	if ( result )
	{
		while ( i < tv1 && j < tv2 )
		{
			result[k++] = ( v1[i] < v2[j] ) ? v1[i++] : v2[j++];
		}

		while( i < tv1 ) { result[k++] = v1[i++]; }
		while( j < tv2 ) { result[k++] = v2[j++]; }
	}
	return result;
}

// Intercala elementos de vetores versão recursiva 
// v1, v2 : Ponteiros para vetores disjuntos
// tv1, tv2 : Quantidades de elementos dos vetores 1 e 2, respectivamente
// indV1, indV2 : Índices dos vetores na recursão
// result : ponteiro de ponteiro para resultado da intercalação
//  k : Índice do vetor no resultado da intercalação (em result)
void intercalar_vetores_recursiva( int *v1, int *v2, int indV1,  int tv1, int indV2, int tv2, int **result, int k )
{
	int i = indV1, j = indV2;
	if ( *result )
	{
		if ( i < tv1 && j < tv2 )
		{
			(*result)[k++]  =  ( v1[i] <= v2[j] ) ? v1[i++] : v2[j++]; 
			 intercalar_vetores_recursiva( v1, v2, i, tv1, j, tv2, result, k );
		} else 
		{
		  while ( i < tv1 ) (*result)[k++] = v1[i++];
		  while ( j < tv2 ) (*result)[k++] = v2[j++];
		}
	}
}