#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START_SIZE ( sizeof( int ) * 3 )                        // TAMANHO DOS 3 INTEIROS DO COMECO 
#define NAME_SIZE ( sizeof( char ) * 10 )                       // TAMANHO DOS NOMES
#define REGISTER_SIZE (NAME_SIZE + ( sizeof( int ) * 2 ) )      // TAMANHO DE UM CONTATO INTEIRO

#define TRUE 1
#define FALSE 0
typedef int BOOL;

void * RESET();  // funcionando
void PUSH( void * pBuffer, int * size, int * i ); // funcionando
void * POP( void * pBuffer, int * size, int * i); // funcionando
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
            if ( EMPTY( size ) )
                pBuffer = ( void * )realloc( pBuffer, START_SIZE + REGISTER_SIZE );
            else
                pBuffer = ( void * )realloc( pBuffer, ( START_SIZE + REGISTER_SIZE ) * ( ( *size) + 1 ) );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2  ) );
            PUSH( ( pBuffer + START_SIZE ), size, i );
            break;
        case 2:
            if ( (*size) == 0 ) {
                printf("Lista vazia\n");
                break;
            }
            pBuffer = POP( pBuffer, size, i );
            size = ( int * )pBuffer;
            option = ( int * )( pBuffer + sizeof( int ) );
            i = ( int * )( pBuffer + ( sizeof( int ) * 2 ) );
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
            return 0;
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
    void * pointer2 = pBuffer + REGISTER_SIZE;
    char * name;

    getchar();
    if ( EMPTY( size ) ) { // TESTA SE EH O PRIMEIRO DA LISTA
        printf(" -Nome: ");
        scanf("%9[^\n]s", ( char * )pointer );
        pointer = pointer + NAME_SIZE;
        printf(" -Idade: ");
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        printf(" -Telefone: ");
        scanf("%d", ( int * )pointer );
        *size += 1;
        return;
    }

    name = (char *)malloc( NAME_SIZE );
    printf(" -Nome: ");
    scanf("%9[^\n]s", name );

    // PROCURA O LOCAL A SER COLOCADO ALFABETICAMENTE
    *i = 0;
    while( ( strcmp( (char *)pointer, name ) < 1 ) && ( *i < (*size) ) ) {
        *i += 1;
        if ( *i < *size )
            pointer += REGISTER_SIZE;
    }

    // TESTA SE EH O ULTIMO
    if ( *i == *size ) {
        pointer += REGISTER_SIZE;
        strcpy((char *)pointer, name);
        pointer = pointer + NAME_SIZE;
        printf(" -Idade: ");
        scanf("%d", ( int * )pointer );
        pointer = pointer + sizeof( int );
        printf(" -Telefone: ");
        scanf("%d", ( int * )pointer );
        *size += 1;
        free( name );
        return ;
    }

    *size += 1;
    pointer2 = pointer + REGISTER_SIZE;
    memmove( pointer2, pointer, REGISTER_SIZE * ( (*size) - (*i) ) );
    strcpy( (char *)pointer, name );
    pointer = pointer + NAME_SIZE;
    printf(" -Idade: ");
    scanf("%d", ( int * )pointer );
    pointer = pointer + sizeof( int );
    printf(" -Telefone: ");
    scanf("%d", ( int * )pointer );
    free( name );

}

void * POP( void * pBuffer, int * size, int * i ) {
    char * name = ( char * )malloc( NAME_SIZE );
    void * p1 = pBuffer + START_SIZE;
    void * p2;

    getchar();
    printf("Informe o nome a ser encontrado: ");
    scanf("%9[^\n]s", name);

    // PROCURA O CONTATO
    *i = 0;
    while( ( strcmp( (char *)p1, name ) != 0 ) && ( *i <= (*size) ) ) {
        *i += 1;
        if ( *i < *size )
            p1 += REGISTER_SIZE;
    }

    free( name );
    // NAO ENCONTRA
    if ( *i > *size ) {
        printf("Nome nao encontrado\n");
        return pBuffer;
    }

    // ELEMENTO UNICO
    if ( (*i) == 0 && ((*size) - 1) == 0 ) {
        CLEAR( pBuffer );
        return RESET();
    }

    (*size)--;
    // ULTIMO ELEMENTO
    if ( *i == *size ) {
        return ( void * )realloc(pBuffer, START_SIZE + ( REGISTER_SIZE * (*size) ) );
    }

    // COPIA A PARTIR DO PROX CONTATO LOGO DPS DO ENCONTRADO E REALLOCA MEMORIA PRA SIZE - 1;
    p2 = p1 + REGISTER_SIZE;
    memmove( p1, p2, REGISTER_SIZE * ( (*size) - (*i) ) );
    return ( void * )realloc(pBuffer, START_SIZE + ( REGISTER_SIZE * (*size) ) );
}

void PRINT( void * pBuffer , int * size, int * i ) {
    void * pointer = pBuffer;
    
    printf("+-------------------+\n");
    for ( (*i) = 0 ; (*i) < (*size) ; (*i)++ ) {
        printf("Nome: %s\n", ( char * ) pointer );
        pointer += NAME_SIZE;
        printf("Idade: %d\n", *( int * ) pointer );
        pointer += sizeof( int );
        printf("Telefone: %d\n", *( int * ) pointer );
        pointer += sizeof( int );
        printf("+-------------------+\n");
    }
}

BOOL EMPTY( int * size ) {
    if ( (*size) == 0 ) {
        return TRUE;
    }

    return FALSE;
}

void MENU( int *option ) {

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
            printf("+-------------------+\n");
            printf(" Nome: %s\n", ( char * ) pointer );
            pointer += NAME_SIZE;
            printf(" Idade: %d\n", *( int * ) pointer );
            pointer += sizeof( int );
            printf(" Telefone: %d\n", *( int * ) pointer );
            pointer += sizeof( int );
            printf("+-------------------+\n");
            free( name );
            return ;
        }
        pointer += REGISTER_SIZE;
    }

    free( name );
    printf("Nome nao encontrado\n");
}
