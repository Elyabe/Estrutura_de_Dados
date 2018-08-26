/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS II
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Backtracking : Problema do Cavalo Xadrez

CRIADO EM: 
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

int dx[SIZE+1] = {0,2,1,-1,-2,-2,-1,1,2}, 
	dy[SIZE+1] = {0,1,2,2,1,-1,-2,-2,-1};

int m[SIZE+1][SIZE+1];

// Move o cavalo no tabuleiro 
// i : Número do movimento
// x0, y0 : Posição inicial
// s : Flag indicadora de sucesso no movimento
// matriz : Ponteiro para matriz/tabuleiro
// n : Dimensão do tabuleiro
void mover_cavalo( int i, int x0, int y0, int s, int** matriz, unsigned int n )
{
	
	int x, y, k = 0, sucesso = 0;
	
	do
	{
	 	k++;
	 	x = x0 + dx[k], y = y0 + dy[k];
	 	
	 	// Se as coordenadas são válidas e a célula não foi visitada
	 	if ( 1 <= x && x <= n && 1 <= y && y <= n && matriz[x][y] == 0 )
 			{
 				// Visita
 				matriz[x][y] = 1;
 				
 				
 				if ( i < n*n )
 				{
 					mover_cavalo( i+1, x, y, sucesso, matriz, n );
 					
 					if ( !sucesso ) matriz[x][y] = 0;
 				}

 			} else 
 				sucesso = 1;
	 } while ( !sucesso && k < SIZE );

	 s = sucesso;
}


int main()
{
	unsigned int n, a,b;
	printf("Valor de n :\n");
	scanf("%d", &n );
	
	// Aloca e seta para 0 a matriz
	int **matriz = (int**)calloc( n+1,sizeof(int*) );
	for ( a = 0; a <= n; a++ )
		matriz[a] = (int*)calloc( n+1,sizeof(int) );


	if ( matriz )
	{
		printf("Entre com a posição inicial (xo,yo), do cavalo. \n");
		scanf("%d%d", &a,&b);
		mover_cavalo( 0, a, b, 0, matriz, n );	
		
		for ( a = 1; a <= n; a++ ) 
			for ( b=1; b <= n; b++);
				printf("%d",matriz[a][b] );

	}
	
	return 0;
}