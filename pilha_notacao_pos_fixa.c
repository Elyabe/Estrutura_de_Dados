/* 
CENTRO UNIVERSTÁRIO NORTE DO ESPÍRITO SANTO - CEUNES/ UFES
ATIVIDADE DE LABORATÓRIO  DE ESTRUTURA DE DADOS I
AUTOR: ELYABE ALVES SANTOS
CURSO: CIÊNCIA DA COMPUTAÇÃO
MATRÍCULA: 2014203834
TURMA 1

OBJETIVO: CONVERTER EXPRESSÃO DE NOTAÇÃO ALGEBRICA PARA NOTACAO POLONESA REVERSA 
P.S.: Suporta apenas números com 1 algarismo : Uma leve modificação deve ser feita para suporte genérico

CRIADO EM: 21/05/2016
PROFESSOR: FRANCISCO S. SANTOS
--------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

typedef struct no 
{
    char dado;
    struct no *prox;
} No ;

typedef struct pilha 
{
    No *topo;
    int quant;
} Pilha ;

// OPERACOES GERAIS COM PILHA
Pilha* criar_pilha() ;
void empilhar( Pilha **pilha, char operador ) ;
char desempilhar( Pilha **pilha ) ;
char topo_pilha( Pilha **pilha) ;
void desalocar_pilha( Pilha **pilha );

// MODULOS DE CONVERSAO
int eh_operador( char c ) ; 
int precedencia( char auxPilha, char aux ) ; 
char* converter_not_pos_fixa( char notacaoAlg[], Pilha **pilha ) ; 


// Inicializa uma nova pilha
// pilha : Ponteiro para a pilha recém-criada
Pilha* criar_pilha(void) 
{
    Pilha *nova = (Pilha*)calloc( 1, sizeof(Pilha) );

    if ( nova )
    {
        nova -> topo = NULL;
        nova -> quant = 0;
    } else
        exit(0);

        // Para cada caracter da string
    return nova;
}


// Libera espaço ocupado pela pilha
// pilha : Ponteiro para pilha a ser desalocada
void desalocar_pilha( Pilha **pilha )
{
    while ( (*pilha) -> quant )
    {
        desempilhar( pilha );
    }
    *pilha = NULL;
}

// Empilha valor na pilha
// pilha : Ponteiro de ponteiro para pulha onde o elemento deve colocado
// valor : Novo valor a ser empilhado
void empilhar( Pilha **pilha, char valor ) 
{
    No *novo = ( No*) malloc (sizeof (No));
    // Adiciona os elementos baseados na sua precedência do que já está na pilha

    if ( novo )
    {
        novo -> dado = valor;
        novo -> prox  = NULL    ;

// Adiciona o restante dos elementos na nova expressão

       if ( (*pilha) -> quant )

            novo -> prox = (*pilha) -> topo; 

        (*pilha) -> topo = novo; 
        (*pilha) -> quant++;
    }
}

// Desempilha e retorna elemento do topo
// pilha : Ponteiro de ponteiro para pilha de onde o elemento será removido
char desempilhar( Pilha **pilha ) 
{
    char operador = '#';
    if ( ( *pilha ) -> quant  )
    {
        No *aux = ( *pilha ) -> topo ; 
        operador = aux -> dado; 

        ( *pilha ) -> topo  = aux -> prox; 
        free( aux ); 

        (*pilha) -> quant--;
    } else 
        { printf("PILHA VAZIA [FAILED] :( \n");}
    return operador;
}


char topo_pilha( Pilha **pilha) 
{
    return ( *pilha ) -> topo -> dado;
}


// Retorna 1 se um caracter é operador e 0 caso contrário
// c : Caracter a ser analisado
int eh_operador( char c ) 
{
     return (c == '+' || c == '-' || c == '*' || c == '/') ;
}

// Retorna inteiro representando a precedência entre dois operadores
// auxPilha, aux : Elementos a serem analisados
int precedencia( char auxPilha, char aux ) 
{

    int precedencia = 0;

    if ( auxPilha == '+' || auxPilha == '-') 
    {
        if (aux == '*' || aux == '/') 
            { precedencia = -1; }
    } else {
              if ( auxPilha == '*' || auxPilha == '/' ) 
                {
                    if ( aux == '+' || aux == '-' )   
                    { precedencia = 1; }
                } else
                   { precedencia = -1; }
            } 
    return precedencia ;
}


// Converte e retorna uma expressão na notação pos-fixa
// notacaoAlg : String contendo a expressão na notação in-fixa
// pilha : Ponteiro para pillha
char* converter_not_pos_fixa(char notacaoAlg[], Pilha **pilha ) 
{
    int i, j = 0;
    char aux, aux_pilha, *notacaoPR = (char*)malloc( 101 * sizeof(char) );

    // Para cada caracter da string
    for ( i = 0; i < strlen( notacaoAlg ) ; i++ ) 
    {
         aux = notacaoAlg[i];  
        
        if ( ! eh_operador( aux ) ) 
        {
           switch( aux )
            {
                case '(':
                    empilhar( pilha, aux );
                    break;
                case ')':
                     while( ( *pilha ) -> topo -> dado != '(' )
                        { notacaoPR[j] = desempilhar( pilha ), j++ ; }
                        desempilhar( pilha );
                    break;
                default:
                       notacaoPR[j] = aux, j++; 
            }
        } else
        {
            // Adiciona os elementos baseados na sua precedência do que já está na pilha
            while( ( *pilha ) -> quant != 0 && precedencia( ( *pilha ) -> topo -> dado, aux ) >= 0 )
                { notacaoPR[j] = desempilhar(pilha), j++; }
                empilhar( pilha, aux );
        }    
    }
    
    // Adiciona o restante dos elementos na nova expressão
    while( ( *pilha ) -> quant != 0)
    { notacaoPR[j] = desempilhar( pilha ), j++; }

return notacaoPR;
}

int main() 
{

    Pilha *pilha = criar_pilha();
    char expressao[MAX], notacaoPR[MAX];

    printf("DIGITE A EXPRESSAO NA FORMA ALGEBRICA:  ");
    // P.S.: Para melhor visualização digite os operandos e operadores separados por espaço 
    printf("Ex.: ( a + b ) * ( a - b) \n" );
    scanf("%[^\n]s", expressao );

    strcpy( notacaoPR, converter_not_pos_fixa( expressao, &pilha ) );

    printf("EXPRESSAO CORRESPONDENTE NA NOTACAO POLONESA REVERSA:\n ");
    printf("%s <=> %s \n ", expressao, notacaoPR );

    desalocar_pilha( &pilha );
    
    printf("\nDESALOCANDO PILHA ");
    if ( pilha )
        printf("[FAILED]\n");
    else
        printf("[OK]\n");

    return 0;
}

