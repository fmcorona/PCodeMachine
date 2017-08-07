#ifndef READPCODE_H_INCLUDED
#define READPCODE_H_INCLUDED

#define INSTR_SIZE 3
#define MAX_ARG_SIZE 64

void fnCloseFile( );
void fnOpenFileToRead( char* strNameOfFile );

void fnGetChar( );

int fnHasInstr( );
int fnHasArg( );

void fnGetInstr( );
void fnGetArg( );

FILE *g_pFile;

extern char g_chCurrChar;

extern char g_strInstr[ INSTR_SIZE ];
extern char g_strArg[ MAX_ARG_SIZE ];

#endif // READPCODE_H_INCLUDED
