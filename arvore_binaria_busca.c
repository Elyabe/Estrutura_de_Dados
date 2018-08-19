/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Arvore Binária de Busca - ABB

CRIADO EM: 06/11/2016
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no
{
	int chave,
	   altura;
	struct no *esq, *dir;
} No;

No* remover( No* raiz, int chave );
No *buscar( No *raiz, int chave );
No *alocar_no ( int chave );
No *inserir ( No *raiz, int chave );
void atualizar_altura ( No** raiz );
void altura_v2( No** pt );
void altura_v3 ( No **raiz );
int altura ( No* raiz );
void gerarABB ( No** myTree, int quantidade );
void imprimir ( No *raiz , int nivel );
void imprimirNo ( No *raiz );


int main()
{
	No *T = NULL;
	int qtd_nos;
	scanf("%d", &qtd_nos );
	
	gerarABB( &T, qtd_nos );
	imprimir( T, 0 );
	return 0;
}

// Aloca, seta os valores padroes e retorna ponteiro num nó
// chave : valor da chave a ser criada
No *alocar_no( int chave )
{
	No *novo;
	if ( novo = ( No* )calloc( 1, sizeof(No) ) )
	{
		novo -> esq = novo -> dir = NULL;
		novo -> chave = chave;
		novo -> altura = 1;
	}

	return novo;
}

// Insere um novo nó numa ávore de busca binária (ABB)
// raiz : Ponteiro para raíz da árvore
// chave : Novo valor a ser inserido
No *inserir( No *raiz, int chave )
{
	// Se a árvore é vazia, então aloque 
	if ( !raiz )
		{  return alocar_no( chave ); }
	else
	{
		// Realiza percurso até encontrar local certo para alocar
		if ( chave != raiz -> chave )
		{
			if ( chave > raiz -> chave )
				{ raiz -> dir = inserir( raiz -> dir, chave );}
			else
				{ raiz -> esq = inserir ( raiz -> esq, chave ); }
			atualizar_altura( &raiz );
		}
		return raiz;
	}
}

// Exibe dados de um nó
// raiz : Nó cujos dados deseja-se exibir
void imprimirNo( No *raiz )
{
	printf("[%d | h = %d ]\n", raiz -> chave, raiz -> altura );
}

// Imprime nós de árvore por nível
// raiz : Ponteiro para raíz da árvore
// nivel : Nível a ser impresso
void imprimir ( No *raiz , int nivel )
{
     int cont;
     // Se a árvore é não vazia
     if( raiz )
       {
	     for ( cont = 0; cont < nivel; cont++ )
	        printf("  ");

	    // Imprime a raiz e depois as subárvores à direita e à esquerda
	     imprimirNo( raiz );
	     imprimir  ( raiz -> esq , nivel + 1 );
	     imprimir  ( raiz -> dir , nivel + 1 ) ;
	    }
}

// Busca e retorna, se existir, ponteiro para nó; Caso contário retorna NULL
// raiz : Ponteiro para raiz da árvore na qual deseja-se realizar a busca
// chave : Chave do nó a ser buscada
No *buscar ( No *raiz, int chave )
{
	if ( ! raiz )
	 	return NULL; 
	if ( raiz -> chave != chave )
	{
		if ( chave > raiz -> chave )
			{ return buscar( raiz -> dir, chave ); }
		else
			{ return buscar( raiz -> esq, chave ); }
	}
	
	return raiz;
}

// Remove nó com chave de uma ABB
// raiz : Ponteiro para árvore da qual deseja-se remover o nó
// chave : Chave a ser removida
No* remover( No* raiz, int chave )
{
	// Se a árvore é não vazia
	if ( raiz )
	{
		// busca na subárvore à esquerda
		if ( raiz -> chave > chave )
		{ raiz -> esq = remover( raiz -> esq, chave ); } 
		else if ( raiz -> chave == chave )
		{
			// Encontrou a chave

			// Se for um nó folha
			if ( raiz -> esq == NULL && raiz -> dir == NULL )
			{	free( raiz ), raiz = NULL; 	}
			else
			{	
				if ( raiz -> esq == NULL )
				{ 
				  No *aux = raiz;
				  raiz = raiz -> dir, free( aux );
				}
				else
				{

					if ( raiz -> dir == NULL )
					{
						No *aux = raiz;
						raiz = raiz -> esq, free( aux );
					} else
					{
						// Tem os dois filhos
						No *pt = raiz -> dir;
						while ( pt -> esq != NULL )
						{ 	pt = pt -> esq; }
						
						// Troca de conteúdo e remove nó folha correspondente
						raiz -> chave = pt -> chave, pt -> chave = chave ;
						raiz -> dir = remover( raiz -> dir, chave );
					}
				}
			}
		} else 
		{ raiz -> dir = remover( raiz -> dir, chave ); }
	}	
	
	return raiz;
}

// Atualiza a altura de todos os nós na árvore
// raiz : Ponteiro para raiz da árvore
void atualizar_altura ( No** raiz )
{
	if ( (*raiz) -> esq )
		atualizar_altura( & ( (*raiz) -> esq ) );
	(*raiz) -> altura = altura( *raiz );
	if ( (*raiz) -> dir )
		atualizar_altura( & ( (*raiz) -> dir ) );
}

// Calcula e retorna a altura de uma ABB
// raiz: Ponteiro para raíz da árvore
int altura ( No* raiz ) 
{
   if ( !raiz ) 
      return 0; 
   else 
   {
      // Calcula alturas das subárvores e retorna a maior
      int hTe = altura ( raiz -> esq ), hTd = altura ( raiz -> dir );
      return ( hTd > hTe ) ?  hTd + 1 :  hTe + 1;
   }
}

// Versão alternativa
// Calcula e retorna a altura de uma ABB
// raiz: Ponteiro para raíz da árvore
void altura_v3 ( No **raiz )
{
	if ( raiz )
	 { 
	 	if ( (*raiz) -> esq == NULL && (*raiz) -> dir == NULL )
		 (*raiz) -> altura = 1;
		else
		{ 
			if ( (*raiz) -> esq && (*raiz) -> dir )
			{
				altura_v3( & ( (*raiz) -> esq ));
				altura_v3( & ( (*raiz) -> dir ));
				int hTd = (*raiz) -> esq -> altura, hTe = (*raiz) -> dir -> altura;
				(*raiz) -> altura  = ( hTd > hTe ) ? hTd + 1 : hTe + 1;
			} else
		 	{
		 		if ( (*raiz) -> esq )
		 		{ 
		 			altura_v3( & ( (*raiz) -> esq ));
		 			(*raiz) -> altura = (*raiz) -> esq -> altura + 1;
		 		} else 
		 			{
		 				altura_v3( & ( (*raiz) -> dir ));
		 				(*raiz) -> altura = (*raiz) -> dir -> altura + 1;
		 			}
			
		 	}
		}
	} 
}

// Determina altura de CADA nó da árvore
// pt : Ponteiro para raiz da árvore
void altura_v2 ( No** pt )
{
	if ( *pt )
	{
		// Calcula altura das subárvores
		altura_v2( &( (*pt) -> esq ) );
		altura_v2( &( (*pt) -> dir ) );

		// Se ambas as subárvores são não vazias
		if ( (*pt) -> esq && (*pt) -> dir )
			(*pt) -> altura = ( (*pt) -> esq -> altura > (*pt) -> dir -> altura ) ? (*pt) -> esq -> altura + 1: (*pt) -> dir -> altura + 1;
		else
		{
			if ( (*pt) -> esq || (*pt) -> dir )
				(*pt) -> altura = ( (*pt) -> esq != NULL ) ? (*pt) -> esq -> altura + 1: (*pt) -> dir -> altura + 1;
		}
	}
}

// Gera árvore binária de busca com quantidade de nós definida e valores pseudo-aleatórios
// myTree : Ponteiro para árvore 
// quantidade : quandidade de nós a serem criados
void gerarABB(  No** myTree, int quantidade )
{
	int cont;
	for ( cont = 0; cont < quantidade; cont++ )
	  *myTree = inserir( *myTree, (int)rand() % 100 ); 
}

