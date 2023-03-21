/*
pl[0] = head
pl[1] = next node
pl[2] = last node
pl[3] = next node
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SIZE ( sizeof( int ) * 3 )
#define NAME_SIZE ( sizeof( char ) * 10 )
#define REGISTER_SIZE (NAME_SIZE + ( sizeof( int ) * 2 ) )

#define TRUE 1
#define FALSE 0
typedef int BOOL;

void* RESET();  // funcionando
void PUSH( void * pBuffer, void ** pL, int * size, int * i ); // tem q corrigir || funcionando para o primeiro elemento corretamente
// ^ precisa implementar a parte de ordem alfabética e da lista duplamente ligada
void* POP(); // precisa implementar
void PRINT( void * pBuffer ); // precisa implementar
BOOL EMPTY( void * head ); // funcionando
void MENU( int * option ); // funcionando

int main() {
    void * pBuffer = RESET();
    int * size;
    int * option;
    int * i;

    void ** pL;
    
    pL = ( void ** )malloc( sizeof( void * ) * 2 );
    pL[0] = ( void * )malloc( sizeof( void * ) );
    pL[1] = ( void * )malloc( sizeof( void * ) );
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
            
            break;
        case 3:
            // eh um bom caminho para listar os contatos, se eu resolver como fazer o push e o pop e conseguir fazer seguindo a minha primiera ideia, posso soh implementar essa lógica aq 
            for ( (*i) = 0 ; (*i) < (*size) ; (*i)++ ) {
                printf(" %s\n", ( char * ) pL[(*i)] );
                printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE ) );
                printf(" %d\n", *( int * ) ( pL[(*i)] + NAME_SIZE + sizeof( int ) ) );
            }      
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        }
    }

    return 0;
}

void *RESET() {
    void * pointer = ( void * )malloc( 3 * sizeof( int ) );

    *( int * )pointer = 0;                                  // size
    *( int * )( pointer + sizeof( int ) ) = 0;              // option
    *( int * )( pointer + ( sizeof( int ) * 2  ) ) = 1;     // i

    return pointer;
}

void PUSH( void * pBuffer, void ** pL, int * size, int * i ) {
    void * pointer = pBuffer;
    //void * hold = ( void * )malloc( sizeof( void *) );
    //char * name = ( char * )malloc( NAME_SIZE );

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

/*
    while ( pL[ *i ] ) {
        (*i) += 2;
    }
*/

    pointer = pBuffer + ( REGISTER_SIZE );
    pL[1] = pointer;

    scanf("%9[^\n]s", ( char * )pointer );
    pointer = pointer + NAME_SIZE;
    scanf("%d", ( int * )pointer );
    pointer = pointer + sizeof( int );
    scanf("%d", ( int * )pointer );

/*
    *i = 0;
    pL = ( void ** )realloc( pL, sizeof( pL ) + sizeof( void * ) * 2 );
    
    pointer = pL[*i];
    while( !(strcmp( (char *)pointer, name ) < 1) ) {
        *i += 2;
        pointer = pL[*i];
    }
    
    hold = pL[*i - 1];
    pL[*i - 1] = pointer;
    pL[ *i ] = pL[ *i - 4 ];
    pL[ *i + 1 ] = hold;
    pL[ *i + 2 ] = pointer;
*/
}

BOOL EMPTY( void * head ) {
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
