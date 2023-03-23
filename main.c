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

void* RESET();  // funcionando
void PUSH( void * pBuffer, int * size, int * i ); // tem q implementar a ordem alfabetica
void POP( void * pBuffer, int * size, int * i); // precisa retirar do meio e do começo não sendo contato unico -- arrumar a logica de passagem do pbuffer
void PRINT( void * pBuffer, int * size, int * i ); // funcionando
BOOL EMPTY( int * size ); // funcionando
void MENU( int * option ); // funcionando
void CLEAR( void * pBuffer ); // funcionando
void FIND( void * pBuffer, int * size, int * i ); // funcionando

int main() {
    void * pBuffer = RESET();

    int * size;
    int * option;
    int * i;

    size = ( int * )pBuffer;
    option = ( int * )( pBuffer + sizeof( int ) );
    i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );

    while( TRUE ) {
        MENU( option );
        switch ( *option ) {
        case 1:
            (*size)++;
            if ( EMPTY( size ) )
                pBuffer = ( void * )realloc( pBuffer, START_SIZE + REGISTER_SIZE );
            else
                pBuffer = ( void * )realloc( pBuffer, ( START_SIZE + REGISTER_SIZE ) * ( *size) );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            PUSH( (pBuffer + START_SIZE ), size, i );
            break;
        case 2:
            if ( (*size) == 0 ) {
                printf("Lista vazia\n");
                break;
            }
            (*size)--;
            POP( pBuffer, size, i );
            option = ( int * )( pBuffer + sizeof( int ) );
            break;
        case 3:
            if ( (*size) == 0 )
                printf("Lista vazia\n");
            else
                PRINT( pBuffer + START_SIZE, size, i );  
            break;
        case 4:
            if ( (*size) == 0 )
                printf("Lista vazia\n");
            else
                FIND( pBuffer + START_SIZE, size, i );
            break;
        case 5:
            CLEAR( pBuffer );
            exit(1);
            break;
        }
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

void PUSH( void * pBuffer, int * size, int * i ) {
    void * pointer = pBuffer;

    getchar();
    if ( EMPTY( size ) ) { // TESTA SE EH O PRIMEIRO DA LISTA
        scanf("%9[^\n]s", ( char * )pointer );
        pointer = pointer + NAME_SIZE;
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        scanf("%d", ( int * )pointer );
        return;
    }

    pointer = pBuffer + ( REGISTER_SIZE * ( (*size) - 1 ) ); 
    scanf("%9[^\n]s", ( char * )pointer );
    pointer = pointer + NAME_SIZE;
    scanf("%d", ( int * )pointer );
    pointer = pointer + sizeof( int );
    scanf("%d", ( int * )pointer );

}

void POP(void * pBuffer, int * size, int * i) {
    void * newBuffer;
    char * name = ( char * )malloc( NAME_SIZE );
    void * p1 = pBuffer + START_SIZE;
    void * p2;

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    *i = 0;
    while( ( strcmp( (char *)p1, name ) != 0 ) && ( *i <=(*size) + 1 ) ) {
        *i += 1;
        p1 += REGISTER_SIZE;
    }

    // NAO ENCONTRA
    if ( *i > (*size) + 1 ) {
        printf("Nome nao encontrado\n");
        size = ( int * )pBuffer;
        i = ( int * )( pBuffer + ( sizeof( int ) * 2 ) );
        (*size)++;
        return ;
    }

    newBuffer = ( void * )realloc( pBuffer, START_SIZE + ( REGISTER_SIZE * (*size) ) );
    size = ( int * )newBuffer;
    i = ( int * )( newBuffer + ( sizeof( int ) * 2 ) );

    // ELEMENTO UNICO
    if ( (*i) == 0 && (*size) == 0 ) {
        CLEAR( pBuffer );
        newBuffer = RESET();
        pBuffer = newBuffer;
    }

    // ULTIMO ELEMENTO
    if ( *i == (*size) + 1 ) 
        pBuffer = newBuffer;

    p1 = pBuffer + START_SIZE + ( REGISTER_SIZE * (*i) );
    p2 = newBuffer + START_SIZE;
    while ( *i < *size ) {
        strcpy( (char *)p2, (char *)p1 );
        p1 += NAME_SIZE;
        p2 += NAME_SIZE;
        *( int * )p2 = *( int * )p1;
        p1 += sizeof( int );
        p2 += sizeof( int );
        *( int * )p2 = *( int * )p1;
        p1 += sizeof( int );
        p2 += sizeof( int );
        *i += 1;
    }
    
    pBuffer = newBuffer;
}

void PRINT( void * pBuffer , int * size, int * i ) {
    void * pointer = pBuffer;

    for ( (*i) = 0 ; (*i) < (*size) * 2 ; (*i) += 2 ) {
        printf(" %s\n", ( char * ) pointer );
        pointer += NAME_SIZE;
        printf(" %d\n", *( int * ) pointer );
        pointer += sizeof( int );
        printf(" %d\n", *( int * ) pointer );
        pointer += sizeof( int );
    }
}

BOOL EMPTY( int * size ) {
    if ( (*size) - 1 == 0 ) {
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

void CLEAR( void * pBuffer ) {
    free( pBuffer );
}

void FIND( void * pBuffer, int * size, int * i ) {
    char * name = ( char * )malloc( NAME_SIZE );
    void * pointer = pBuffer;

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    for ( *i = 0 ; *i < *size ; *i += 1 ) {
        if ( !strcmp( (char *)pointer, name  ) ) {
            printf(" %s\n", ( char * ) pointer );
            pointer += NAME_SIZE;
            printf(" %d\n", *( int * ) pointer );
            pointer += sizeof( int );
            printf(" %d\n", *( int * ) pointer );
            pointer += sizeof( int );
            return ;
        }
        pointer += REGISTER_SIZE;
    }

    printf("Nome nao encontrado\n");
}