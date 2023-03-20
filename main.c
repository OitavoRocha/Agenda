#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE (sizeof( char ) * 10)
#define REGISTER_SIZE (NAME_SIZE + ( sizeof( int ) * 2 ) )

#define TRUE 1
#define FALSE 0
typedef int BOOL;

void* RESET( int * size );
void PUSH( void * pBuffer, void ** pL, int * size );
void* POP();
void PRINT();
BOOL EMPTY( void * head );
void MENU( int * option );

int main() {
    int * option = ( int * )malloc( sizeof( int ) );
    int * size = ( int * )malloc( sizeof( int ) );

    void * pBuffer = RESET( size );
    void ** pL;

    pL = ( void ** )malloc( sizeof( void * ) * 2 );
    pL[0] = ( void * )malloc( 1 );
    pL[1] = ( void * )malloc( 1 );
    pL[0] = NULL;
    pL[1] = NULL;

    while( TRUE ) {
        MENU( option );
        switch ( *option ) {
        case 1:
            PUSH( pBuffer, pL, size );
            break;
        case 2:
            
            break;
        case 3:
            printf("%s\n", ( char * ) pBuffer);
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        }
    }

    return 0;
}

void *RESET( int * size ) {
    void * pointer = ( void * )malloc( 1 );

    *size = 0;

    return pointer;
}

void PUSH( void * pBuffer, void ** pL, int * size ) {
    void * pointer;

    (*size)++;

    getchar();
    if ( EMPTY( pL[0] ) ) { // TESTA SE EH O PRIMEIRO DA LISTA
        pointer = ( void * )realloc(pBuffer, REGISTER_SIZE );
        pBuffer = ( void * )realloc(pBuffer, REGISTER_SIZE );
        scanf("%9[^\n]s", ( char * )pointer );
        pointer = pointer + NAME_SIZE;
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        scanf("%d", ( int * )pointer );

        return;
    }


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
