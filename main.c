/*
pl[0] = head
pl[1] = next node
pl[2] = last node
pl[3] = next node
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SIZE ( sizeof( int ) * 3 )                        // TAMANHO DOS 3 INTEIROS DO COMECO 
#define NAME_SIZE ( sizeof( char ) * 10 )                       // TAMANHO DOS NOMES
#define REGISTER_SIZE (NAME_SIZE + ( sizeof( int ) * 2 ) )      // TAMANHO DE UM CONTATO INTEIRO

#define TRUE 1
#define FALSE 0
typedef int BOOL;

// dando problema pra armazenar 10 contatos -- muito provavelmente pro causa da lógica usada nos ponteiros
void* RESET();  // funcionando
void PUSH( void * pBuffer, void ** Last, void ** Next , int * size, int * i ); // tem q implementar a ordem alfabetica
void* POP( void * pBuffer, void ** Last, void ** Next, int * size, int * i); // precisa retirar do meio e do começo não sendo contato unico
void PRINT( void ** Last, void ** Next, int * size, int * i ); // funcionando
BOOL EMPTY( void * head ); // funcionando
void MENU( int * option ); // funcionando
void CLEAR( void * pBuffer, void ** Last, void ** Next ); // funcionando
void FIND( void ** Last, void ** Next, int * size, int * i ); // funcionando

int main() {
    void * pBuffer = RESET();

    int * size;
    int * option;
    int * i;

    void ** pLast = ( void ** )malloc( sizeof( void * ) );
    void ** pNext = ( void ** )malloc( sizeof( void * ) );

    pLast[0] = NULL;
    pNext[0] = NULL;

    size = ( int * )pBuffer;
    option = ( int * )( pBuffer + sizeof( int ) );
    i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );

    while( TRUE ) {
        MENU( option );
        switch ( *option ) {
        case 1:
            (*size)++;
            if ( EMPTY( pLast[0] ) )
                pBuffer = ( void * )realloc( pBuffer, START_SIZE + REGISTER_SIZE );
            else
                pBuffer = ( void * )realloc( pBuffer, ( START_SIZE + REGISTER_SIZE ) * ( *size) );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            PUSH( (pBuffer + START_SIZE ), pLast, pNext, size, i );
            break;
        case 2:
            (*size)--;
            pBuffer = POP( pBuffer, pLast, pNext, size, i );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            if ( (*i) == 0 && (*size) == 0 ) {
                pLast = ( void ** )malloc( sizeof( void * ) );
                pNext = ( void ** )malloc( sizeof( void * ) );
                pLast[0] = NULL;
                pNext[0] = NULL;
            }
            break;
        case 3:
            if ( (*size) == 0 )
                printf("Lista vazia\n");
            else
                PRINT( pLast, pNext, size, i );  
            break;
        case 4:
            FIND( pLast, pNext, size, i );
            break;
        case 5:
            CLEAR( pBuffer, pLast, pNext );
            exit(1);
            break;
        }
        if ( (*size) == 0 )
            *i = 0;
        else
            *i = (*size) - 1;
    }

    return 0;
}

void *RESET() {
    void * pointer = ( void * )malloc( 3 * sizeof( int ) );

    *( int * )pointer = 0;                                  // size
    *( int * )( pointer + sizeof( int ) ) = 0;              // option
    *( int * )( pointer + ( sizeof( int ) * 2  ) ) = 0;     // i

    return pointer;
}

void PUSH( void * pBuffer, void ** Last, void ** Next, int * size, int * i ) {
    void * pointer = pBuffer;
    void ** newLast = realloc( Last, sizeof( void * ) * (*size) );
    void ** newNext = realloc( Last, sizeof( void * ) * (*size) );

    getchar();
    if ( EMPTY( Last[0] ) ) { // TESTA SE EH O PRIMEIRO DA LISTA
        scanf("%9[^\n]s", ( char * )pointer );
        pointer = pointer + NAME_SIZE;
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        scanf("%d", ( int * )pointer );
        Last[0] = pBuffer;
        return;
    }

    for ( (*i) = 0 ; *i < (*size) - 1 ; (*i)++ ) {
        newLast[*i] = Last[*i];
        newNext[*i] = Next[*i];
    }
    Last = newLast;
    Next = newNext;

    // LE OS PROXIMOS VALORES DA LISTA E ARRUMA OS PONTEIROS
    pointer = pBuffer + ( REGISTER_SIZE * ( (*size) - 1 ) );
    Next[ (* i) - 1] = pointer;                         //  head->next = first
    Last[ (* i) ] = pointer - REGISTER_SIZE;            //  first->last = head
    Next[ (* i) ] = NULL;                               //  first->next = NULL;

    scanf("%9[^\n]s", ( char * )pointer );
    pointer = pointer + NAME_SIZE;
    scanf("%d", ( int * )pointer );
    pointer = pointer + sizeof( int );
    scanf("%d", ( int * )pointer );


}

void* POP(void * pBuffer, void ** Last, void ** Next, int * size, int * i) {
    void * newBuffer = ( void * )realloc( pBuffer, START_SIZE + ( REGISTER_SIZE * (*size) ) );
    void ** newLast = realloc( Last, sizeof( void * ) * (*size) );
    void ** newNext = realloc( Last, sizeof( void * ) * (*size) );
    //void * p1;
    //void * p2;
    char * name = ( char * )malloc( NAME_SIZE );

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    *i = 0;
    if ( !strcmp( (char *)Last[ 0 ], name  ) ) 
        ;
    else 
        while ( strcmp((char *)Next[(*i)], name) && ( *i < ( ( (* size) ) - 1 ) ) )
            (*i)++;

    // CASO O ULTIMO SEJA O PRIMEIRO TB -- UM UNICO CONTATO NA AGENDA
    if ( (*i) == 0 && (*size) == 0 ) {
        CLEAR( pBuffer, Last, Next );
        newBuffer = RESET();
        return newBuffer;
    }
    
    if ( *i < ( ( (* size) * 2 ) - 2 ) ) { 
        // CASO SEJA O ULTIMO A SER REMOVIDO
        for ( (*i) = 0 ; *i < (*size) - 1 ; (*i)++ )
            if ( (*i)%2 == 0 ) 
                newLast[*i] = Last[*i];
            else
                newNext[*i] = Next[*i];
        newLast[ *i ] = Last[ *i ];
        newNext[ *i ] = NULL;
        Last = newLast;
        Next = newNext;
        return newBuffer; 
    }
    
    return newBuffer;
}

void PRINT( void ** Last, void ** Next, int * size, int * i ) {
    printf(" %s\n", ( char * ) Last[(0)] );
    printf(" %d\n", *( int * ) ( Last[(0)] + NAME_SIZE ) );
    printf(" %d\n", *( int * ) ( Last[(0)] + NAME_SIZE + sizeof( int ) ) );

    if ( (*size) == 1 )
        return;
 
    for ( (*i) = 0 ; (*i) < (*size) ; (*i)++ ) {
        // NAO PERMITE PRINTAR O ULTIMO->NEXT, QUE ESTA APONTANDO PRA NULL
        if ( (* i) != (*size) - 1 ) { 
            printf(" %s\n", ( char * ) Next[(*i)] );
            printf(" %d\n", *( int * ) ( Next[(*i)] + NAME_SIZE ) );
            printf(" %d\n", *( int * ) ( Next[(*i)] + NAME_SIZE + sizeof( int ) ) );
        }  
    }
}

BOOL EMPTY(void *head)
{
    if ( head == NULL ) {
        return TRUE;
    }

    return FALSE;
}

void MENU(int *option)
{

    printf("+----- MENU -----+\n");
    printf(" 1.Adicionar Nome\n");
    printf(" 2.Apagar Nome\n");
    printf(" 3.Listar Contatos\n");
    printf(" 4.Acessar Contato\n");
    printf(" 5.Sair\n");
    scanf("%d", option);
    while( *option < 1 || (*option) > 5 ) {
        printf("Opcao invalida, informe outra: ");
        scanf("%d", option);
    }
}

void CLEAR( void * pBuffer, void ** Last, void ** Next ) {
    free( pBuffer );
    free( Last );
    free( Next );
}

void FIND( void ** Last, void ** Next, int * size, int * i ) {
    char * name = ( char * )malloc( NAME_SIZE );

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    if ( !strcmp( (char *)Last[ 0 ], name  ) ) {
        printf(" %s\n", ( char * ) Last[(0)] );
        printf(" %d\n", *( int * ) ( Last[(0)] + NAME_SIZE ) );
        printf(" %d\n", *( int * ) ( Last[(0)] + NAME_SIZE + sizeof( int ) ) );

        return ;
    }

    for ( (*i) = 0 ; (*i) < ( *size ) - 1 ; (*i)++ ) {
        if ( !strcmp( (char *)Next[(* i)], name  ) ) {
            printf(" %s\n", ( char * ) Next[(*i)] );
            printf(" %d\n", *( int * ) ( Next[(*i)] + NAME_SIZE ) );
            printf(" %d\n", *( int * ) ( Next[(*i)] + NAME_SIZE + sizeof( int ) ) );
            return ;
        }
    }

    printf("Nome nao encontrado\n");
}
