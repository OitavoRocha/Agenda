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
void PUSH( void * pBuffer, void ** pL, int * size, int * i ); // tem q implementar a ordem alfabetica
void* POP( void * pBuffer, void **pL, int * size, int * i); // precisa retirar do meio e do começo não sendo contato unico
void PRINT( void ** pL, int * size, int * i ); // funcionando
BOOL EMPTY( void * head ); // funcionando
void MENU( int * option ); // funcionando
void CLEAR( void * pBuffer, void ** pL ); // funcionando
void FIND( void ** pL, int * size, int * i ); // funcionando

int main() {
    void * pBuffer = RESET();

    int * size;
    int * option;
    int * i;

    void ** pL;
    
    pL = ( void ** ) malloc( sizeof( void * ) * 2 );
    pL[0] = NULL;
    pL[1] = NULL;

    size = ( int * )pBuffer;
    option = ( int * )( pBuffer + sizeof( int ) );
    i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );

    while( TRUE ) {
        MENU( option );
        switch ( *option ) {
        case 1:
            (*size)++;
            if ( EMPTY( pL[0] ) )
                pBuffer = ( void * )realloc( pBuffer, START_SIZE + REGISTER_SIZE );
            else
                pBuffer = ( void * )realloc( pBuffer, ( START_SIZE + REGISTER_SIZE ) * ( *size) );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            PUSH( (pBuffer + START_SIZE ), pL, size, i );
            break;
        case 2:
            (*size)--;
            pBuffer = POP( pBuffer, pL, size, i );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            if ( (*i) == 0 && (*size) == 0 ) {
                pL = (void ** ) malloc( sizeof( void * ) * 2 );
                pL[0] = NULL;
                pL[1] = NULL;
            }
            break;
        case 3:
            if ( (*size) == 0 )
                printf("Lista vazia\n");
            else
                PRINT( pL, size, i );  
            break;
        case 4:
            FIND( pL, size, i );
            break;
        case 5:
            CLEAR( pBuffer, pL );
            exit(1);
            break;
        }
        if ( (*size) == 0 )
            *i = 0;
        else
            *i = ( (*size) * 2 ) - 1;
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

void PUSH( void * pBuffer, void ** pL, int * size, int * i ) {
    void * pointer = pBuffer;
    void ** newPL = realloc( pL, sizeof( void * ) * 2 * (*size) );

    getchar();
    if ( EMPTY( pL[0] ) ) { // TESTA SE EH O PRIMEIRO DA LISTA
        scanf("%9[^\n]s", ( char * )pointer );
        pointer = pointer + NAME_SIZE;
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        scanf("%d", ( int * )pointer );
        pL[0] = pBuffer;
        return;
    }

    for ( (*i) = 0 ; *i < ((*size) - 1) * 2 ; (*i)++ ) 
        newPL[*i] = pL[*i];
    pL = newPL;
    (*i)--;

    // LE OS PROXIMOS VALORES DA LISTA E ARRUMA OS PONTEIROS
    pointer = pBuffer + ( REGISTER_SIZE * ( (*size) - 1 ) );
    pL[ (* i) ] = pointer;          // *i = 1 -- head->next = first
    pL[ (* i) + 1 ] = pointer - REGISTER_SIZE;  // *i = 2 -- first->last = head
    (*i) += 2;
    pL[ (* i) ] = NULL;             // *i = 3 -- first->next = NULL;

    scanf("%9[^\n]s", ( char * )pointer );
    pointer = pointer + NAME_SIZE;
    scanf("%d", ( int * )pointer );
    pointer = pointer + sizeof( int );
    scanf("%d", ( int * )pointer );

}

void* POP(void * pBuffer, void ** pL, int * size, int * i) {
    void * newBuffer = ( void * )realloc( pBuffer, START_SIZE + ( REGISTER_SIZE * (*size) ) );
    void ** newPL = realloc( pL, sizeof( void * ) * 2 * (*size) );
    void * p1;
    void * p2;
    char * name = ( char * )malloc( NAME_SIZE );

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    *i = 0;
    if ( !strcmp( (char *)pL[ 0 ], name  ) ) 
        ;
    else 
        while ( strcmp((char *)pL[(*i) + 1], name) && ( *i < ( ( (* size) * 2 ) - 2 ) ) )
            *i += 2;

    // CASO O ULTIMO SEJA O PRIMEIRO TB -- UM UNICO CONTATO NA AGENDA
    if ( (*i) == 0 && (*size) == 0 ) {
        CLEAR( pBuffer, pL  );
        newBuffer = RESET();
        return newBuffer;
    }
    
    if ( *i < ( ( (* size) * 2 ) - 2 ) ) { 
        
        // CASO SEJA O ULTIMO A SER REMOVIDO
        for ( (*i) = 0 ; *i < ((*size) - 1) * 2 ; (*i)++ ) 
            newPL[*i] = pL[*i];
        newPL[*i] = NULL;
        pL = newPL;
        return newBuffer;
    }
    
    return newBuffer;
}

void PRINT( void ** pL, int * size, int * i ) {
    printf(" %s\n", ( char * ) pL[(0)] );
    printf(" %d\n", *( int * ) ( pL[(0)] + NAME_SIZE ) );
    printf(" %d\n", *( int * ) ( pL[(0)] + NAME_SIZE + sizeof( int ) ) );

    if ( (*size) == 1 )
        return;
 
    for ( (*i) = 1 ; (*i) < (*size) * 2 ; (*i) += 2 ) {
        if ( (* i) != ((*size) * 2) - 1 ) {
            printf(" %s\n", ( char * ) pL[(*i)] );
            printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE ) );
            printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE + sizeof( int ) ) );
        }  
    }

    (*i) = ( (*size) * 2 ) - 1;
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

void CLEAR( void * pBuffer, void ** pL ) {
    free( pBuffer );
    free( pL );
}

void FIND(void ** pL, int * size, int * i ) {
    char * name = ( char * )malloc( NAME_SIZE );

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    if ( !strcmp( (char *)pL[ 0 ], name  ) ) {
        printf(" %s\n", ( char * ) pL[(0)] );
        printf(" %d\n", *( int * ) ( pL[(0)] + NAME_SIZE ) );
        printf(" %d\n", *( int * ) ( pL[(0)] + NAME_SIZE + sizeof( int ) ) );

        return ;
    }

    for ( (*i) = 1 ; (*i) < ( (*size) * 2 ) - 1 ; (*i) += 2 ) {
        if ( !strcmp( (char *)pL[(* i)], name  ) ) {
            printf(" %s\n", ( char * ) pL[(*i)] );
            printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE ) );
            printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE + sizeof( int ) ) );
            *i = (*size) - 1; 
            return ;
        }
    }

    printf("Nome nao encontrado\n");
}
