/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE COMPLEMENTAR DE ESTRUTURA DE DADOS II
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: Implementação de Heap : Lista de prioridade com livros

CRIADO EM: 29/09/2016
PROFESSOR: Luciana Lee
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct book
{
	char title[255],
		 author[255];
	long isbn;
	int priority;
} Book;

typedef struct heap
{
	Book **vetBooks;
	int size, space;
} Heap;


Book* criar_livro ( char title[], char author[], long isbn, int priority );
Heap* criar_vetor ( FILE *ptr, int space );
void trocar( Book** heap, int j, int k );
void subir ( Heap** myHeap, int pos );
void descer ( Heap** myHeap, int pos );
void criar_heap ( Heap** myHeap );
void criar_heap_subir ( Heap** myHeap );
void imprimir_livro ( Book *book );
void imprimir_heap ( Heap* myHeap );
void alterar_prioridade ( Heap** myHeap, int pos, int newPriority );
void inserir_livro ( Heap** myHeap, Book* newBook );
void remover_livro_prioritario ( Heap** myHeap );
void exibir_chaves( Heap* myHeap );
void liberar_memoria ( Heap** myHeap );
void realocar_heap ( Heap** myHeap );
void gravar_arquivo( FILE* ptr, Heap* myHeap );


int main( int argc, char *args[] )
{
	long aux, aux2; char string[20], string2[20], url[20];
	FILE *ptr;
	Heap *myHeap = NULL, *resulBusca = NULL ;
		
	printf("Hello, Welcome !: D \n");
	printf("Enter witch a name of archive: \n");
	scanf("%[^\n]s", url );
	ptr = fopen( url, "r+");

	if ( ptr )
	{
		myHeap = criar_vetor( ptr, 12 );
		fclose( ptr );
		do 
		{			
			printf("---------------------------------------------------\n");
			printf("LIST OF PRIORITIES\n CHOOISE A OPTION:\n");
			printf("1 : Show me the book of the biggest priority:\n");
			printf("2 : Show me heap full \n");
			printf("3 : Heap-Ar\n");
			printf("4 : Show Heap-keys \n");
			printf("5 : Alter number of copy of book the biggest priority\n");
			printf("6 : Insert new book \n");
			printf("7 : Delete the book the biggest priority \n");
			printf("0 : Quit \n");
			printf("---------------------------------------------------\n");
			printf("InfoHeap: Size: %d\n Space: %d\n", myHeap -> size, myHeap -> space );
			scanf("%ld", &aux );

			
			switch ( aux )
			{
			 	case 1: 
			 		if ( myHeap && myHeap -> size > 1)
			 			imprimir_livro( ( myHeap -> vetBooks)[1] );
			 		else
			 			printf("Oh oh \n Heap empty :C\n");
			 		break;
			 	case 2:
					// printf("Insert data of book \n");
					// scanf("%d", &chave );
					imprimir_heap( myHeap );
			 		break;
			 	case 3: 
			 		criar_heap_subir( &myHeap );
			 		break;
			 	case 4:
			 		exibir_chaves( myHeap );
			 		break;
			 	case 5:
			 		printf("Insert position of element: \n");
			 		scanf( "%ld", &aux2 );
					printf("Insert the new priority: \n");			 		
			 		scanf( "%ld", &aux );
			 		alterar_prioridade ( &myHeap, aux2, aux );
			 		break;
			 	case 6:
			 		printf("Insert a info of new book: \n");
			 		printf("Title : \n");
			 		scanf("%s", string );
			 		printf("Author(s) : \n");
			 		scanf("%s", string2 );
			 		printf("ISNB : \n");
			 		scanf("%ld", &aux2 );
			 		printf("Priority : \n");
			 		scanf("%ld", &aux);
			 		inserir_livro ( &myHeap, criar_livro( string, string2, aux2, aux ) );
			 		break;
			 	case 7:
			 		remover_livro_prioritario ( &myHeap );
			 		break;
			 	case 0: 
			 		strcpy( url, "heap.txt" );
			 		ptr = fopen( url, "w+");
			 		gravar_arquivo( ptr, myHeap );
			 		fclose( ptr );
			 		liberar_memoria( &myHeap );
			 		exit(0);
			 		break;
			 	default:
			 		printf(" Oh Oh Choise not available! :C\n");
			}

		} while ( aux );
	} else
		printf("Ops Error in the Conexion! \n");
}

// Cria e retorna ponteiro para um novo livro com os dados passados
// title : Título 
// author : Autor 
// isbn : Número de inscrição
// priority : Prioridade do livro na lista
Book* criar_livro ( char title[], char author[], long isbn, int priority )
{
	Book *novo = (Book*)calloc( 1, sizeof(Book) );
	if ( novo )
	{
		strcpy( novo -> title, title );
		strcpy( novo -> author, author);
		novo -> priority = priority;
		novo -> isbn = isbn;
	}
	return novo;
}

// Aloca e retorna ponteiro para espaço de memória do vetor no qual será implementado o heap
// ptr : Ponteiro para o arquivo fonte das informações dos livros 
// space : Quantidade inicial de livros ssubirortada pelo livro
Heap* criar_vetor ( FILE *ptr, int space )
{
	char author[255], title[255];
	long isbn; int priority, i;

	Heap *myHeap = (Heap*)calloc( 1, sizeof(Heap) );
	
	if ( myHeap )
	{
		myHeap -> space = space;
		myHeap -> vetBooks = (Book**)calloc( sizeof( Book* ), space + 1 );
		
		// Seta ponteiros do vetor todos para NULL
		for ( i = 0; i < myHeap -> space; i++ )
			myHeap -> vetBooks[i] = NULL;

		// Lê o arquivo e carrega os livros no Heap
		while ( !feof( ptr ) )
		{
			fscanf( ptr, "%s : %s : %ld : %d;\n", title, author, &isbn, &priority );
			realocar_heap( &myHeap );
			( myHeap -> vetBooks)[ 1 + myHeap -> size ] = criar_livro( title, author, isbn, priority );
			myHeap -> size++;
		}
	}
	
	return myHeap;
}


// Realiza troca entre os eleentos num vetor heap
// heap : Ponteiro para o heap
// j, k : Posições dos elementos no heap a serem trocados
void trocar( Book** heap, int j, int k )
{
	Book *aux = heap[j];
	heap[j] = heap[k], heap[k] = aux;
}

// Procedimento subir no heap
// myHeap : Ponteiro para o heap a ser alterado
// pos : Posição do elemento a subir na estrutura
void subir( Heap** myHeap, int pos )
{
	int j = pos/2;	
	Book **heap = (*myHeap) -> vetBooks;
	
	if ( j > 0 )
	{
		if ( heap[pos] -> priority > heap[j] -> priority )
		{
			trocar( heap, pos, j );
			subir( myHeap, j );
		}
	}
}

// Procedimento descer no heap
// myHeap : Ponteiro para a estrutra do heap
// pos : Posição do elemento a subir
void descer( Heap** myHeap, int pos )
{
	int j = 2*pos;

	Book **heap = (*myHeap) -> vetBooks;
	
	if ( j <= (*myHeap) -> size )
	{
		if ( j < (*myHeap) -> size && heap[j+1] -> priority > heap[j] -> priority  ) j++;
		if ( heap[pos] -> priority < heap[j] -> priority )
		{
			trocar( heap, pos, j );
			descer ( myHeap, pos );
		}
	}
}

// Cria a estrutura do heap num vetor utilizando o procedimento DESCER
// myHeap : Ponteiro para o vetor a ser estruturado
void criar_heap( Heap** myHeap )
{
	int j;
	( (*myHeap) -> vetBooks )[ 0 ] = NULL;
	for ( j = ((*myHeap) -> size - 1)/2; j > 0; j-- ) 
	{
		descer( myHeap, j );
	}
}

// Cria a estrutura do heap num vetor utilizando o procedimento subir
// myHeap : Ponteiro para a estrutura heap
void criar_heap_subir( Heap** myHeap )
{
	int j;
	for ( j = 1; j <= (*myHeap) -> size ; j++ )
	{
		subir ( myHeap, j );
	}
}

// Exibe as informações de um livro
// book : Ponteiro para o livro cujos dados devem ser exibidos
void imprimir_livro ( Book *book )
{
	printf("Title : %s \n Author(s) : %s \n ISNB: %ld \n Priority : %d \n", book -> title, book -> author, book -> isbn, book -> priority );
}

// Exibe o heap full na tela
// myHeap : Ponteiro para a estrutura do heap a ser impressa
void imprimir_heap ( Heap* myHeap )
{
	int cont;
	for ( cont = 1; cont <= myHeap -> size; cont++ )
	{
		imprimir_livro( (myHeap -> vetBooks)[cont] );
		printf("\n");
	}
}


// Altera a prioridade de um livro no heap
// myHeap : Ponteiro para a estrutura heap 
// pos : Posição do livro a ser modificado
// newPriority : Nova prioridade do livro no heap
void alterar_prioridade ( Heap** myHeap, int pos, int newPriority )
{
	if ( pos <= (*myHeap) -> size )
	{
		( (*myHeap) -> vetBooks )[ pos ] -> priority = newPriority;
		descer ( myHeap, pos );
	}
}


// Insere um novo livro no heap
// myHeap : Ponteiro para o heap no qual será inserido o livro
// newBook : Ponteiro para o novo livro a ser inserido
void inserir_livro ( Heap** myHeap, Book* newBook )
{
	realocar_heap( myHeap );
	( (*myHeap) -> vetBooks )[ ++(*myHeap)->size ] = newBook ;
	subir ( myHeap, (*myHeap) -> size );
}

// Remove o livro de maior prioridade do heap
// myHeap : Ponteiro para a estrutura do heap
void remover_livro_prioritario ( Heap** myHeap )
{
	if ( (*myHeap) -> size > 0)
		{ 
			// Book *temp = ( (*myHeap) -> vetBooks )[ 1 ];
			// ( (*myHeap) -> vetBooks )[ 1 ] = ((*myHeap) -> vetBooks )[ (*myHeap) -> size-- ];
			trocar( (*myHeap) -> vetBooks, 1, (*myHeap) -> size );
			if ( (*myHeap) -> size > 1 )
				descer ( myHeap, 1 );
			free ( ( (*myHeap) -> vetBooks )[ (*myHeap) -> size-- ] );
			
		}
}

// Exibe as chaves armazenadas num heap no formato de vetor
// myHeap : Ponteiro para o heap
void exibir_chaves( Heap* myHeap )
{
	int cont;
	printf("[");
	for ( cont = 1; cont <= myHeap -> size; cont++ )
	{
		printf("%d |", (myHeap -> vetBooks)[ cont ] -> priority );
	}
	printf("]\n");
}

// Libera a memória ocsubirada pela estrutura completo do heap
// myHeap : Ponteiro para o Heap
void liberar_memoria ( Heap** myHeap )
{
	while ( (*myHeap) -> size )
	{
		free ( ( (*myHeap) -> vetBooks )[ (*myHeap) -> size-- ] );
	}
	*myHeap = NULL;
}

// Verifica a quantidade de espaço disponível e realoca se necessário
// myHeap : Ponteiro para o heap
void realocar_heap ( Heap** myHeap )
{
	if ( (*myHeap) -> space - 1 < (*myHeap) -> size + 1 )
	{
		(*myHeap) -> vetBooks = (Book**)realloc( (*myHeap) -> vetBooks, (int)(sizeof(Book*)*(*myHeap) -> space * 1.5) );
		(*myHeap) -> space *=  1.5;

		int i; 

		// for( i = (*myHeap) -> size + 1; i < (*myHeap) -> space; i++ )
		// 	(*myHeap) -> vetBooks[i] = NULL;

	}
}

// Persiste o heap num arquivo de texto
// ptr : Ponteiro para arquivo de saída
// myHeap : Ponteiro para o heap a ser gravado
void gravar_arquivo( FILE* ptr, Heap* myHeap )
{
 	int cont;
 	Book *book;
 	for ( cont = 1; cont <= myHeap -> size; cont++ )
 		{
 			book = ( myHeap -> vetBooks )[ cont ];
 			fprintf( ptr, "%s : %s : %ld : %d;\n", book -> title, book -> author, book -> isbn, book -> priority );
 		}
}

