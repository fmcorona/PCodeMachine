#include <stdio.h>
#include <string.h>
#include "../includes/readpcode.h"
#include "../includes/stack.h"
#include "../includes/list.h"
#include "../includes/codegen.h"

void fnInitListOfTemporaries( stList* L );

void fnGenCode( )
{
    char strReg0[ 4 ], strReg1[ 4 ], strReg2[ 4 ], strCondBranche[ 4 ];
    stStack* stackOfPMachine;
    stList* listOfTemporaries;

    stackOfPMachine = fnInitStack( );
    listOfTemporaries = fnInitList( );

    fnInitListOfTemporaries( listOfTemporaries );

    while( fnHasInstr( ) )
    {
        fnGetInstr( );

        if ( fnInstrMatch( "ent" ) )
        {
            fnGetArg( );
            printf( "%s:\n", g_strArg );
        }
        else if ( fnInstrMatch( "lda" ) )
        {
            fnGetArg( );

            strcpy( strReg0, fnGetLast( listOfTemporaries ) );
            fnRemoveLast( listOfTemporaries );

            printf( " la %s, %s\n", strReg0, g_strArg );

            fnPush( stackOfPMachine, strReg0 );
        }
        else if ( fnInstrMatch( "ldc" ) )
        {
            fnGetArg( );

            strcpy( strReg0, fnGetLast( listOfTemporaries ) );
            fnRemoveLast( listOfTemporaries );

            printf( " li %s, %s\n", strReg0, g_strArg );

            fnPush( stackOfPMachine, strReg0 );
        }
        else if ( fnInstrMatch( "lod" ) )
        {
            fnGetArg( );

            strcpy( strReg0, fnGetLast( listOfTemporaries ) );
            fnRemoveLast( listOfTemporaries );

            printf( " lw %s, %s\n", strReg0, g_strArg );

            fnPush( stackOfPMachine, strReg0 );
        }
        else if ( fnInstrMatch( "stn" ) )
        {
            if ( strcmp( fnPeek( stackOfPMachine ), "Hi" ) == 0 )
            {
                strcpy( strReg0, fnGetLast( listOfTemporaries ) );
                fnPop( stackOfPMachine ); // Se bota Hi

                printf( " mfhi %s\n", strReg0 );

                strcpy( strReg1, fnPop( stackOfPMachine ) );

                printf( " sw %s, 0(%s)\n", strReg0, strReg1 );
            }
            else if( strcmp( fnPeek( stackOfPMachine ), "Lo" ) == 0 )
            {
                strcpy( strReg0, fnGetLast( listOfTemporaries ) );
                fnPop( stackOfPMachine ); // Se bota Lo

                printf( " mflo %s\n", strReg0 );

                strcpy( strReg1, fnPop( stackOfPMachine ) );

                printf( " sw %s, 0(%s)\n", strReg0, strReg1 );
            }
            else
            {
                strcpy( strReg0, fnPop( stackOfPMachine ) );
                strcpy( strReg1, fnPop( stackOfPMachine ) );

                fnInsertInPlace( listOfTemporaries, strReg0 );
                fnInsertInPlace( listOfTemporaries, strReg1 );

                printf( " sw %s, 0(%s)\n", strReg0, strReg1 );
            }
        }
        else if ( fnInstrMatch( "adi" ) )
        {
            strcpy( strReg2, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg2 );

            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            strcpy( strReg0, fnGetLast( listOfTemporaries ) );

            fnRemoveLast( listOfTemporaries );

            printf( " add %s, %s, %s\n", strReg0, strReg1, strReg2 );

            fnPush( stackOfPMachine, strReg0 );
        }
        else if ( fnInstrMatch( "sbi" ) )
        {
            strcpy( strReg2, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg2 );

            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            strcpy( strReg0, fnGetLast( listOfTemporaries ) );

            fnRemoveLast( listOfTemporaries );

            printf( " sub %s, %s, %s\n", strReg0, strReg1, strReg2 );

            fnPush( stackOfPMachine, strReg0 );
        }
        else if ( fnInstrMatch( "mpi" ) )
        {
            strcpy( strReg0, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg0 );

            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            printf( " mult %s, %s\n", strReg0, strReg1 );

            fnPush( stackOfPMachine, "Hi" );
        }
        else if ( fnInstrMatch( "dvi" ) )
        {

            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            strcpy( strReg0, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg0 );

            printf( " div %s, %s\n", strReg0, strReg1 );

            fnPush( stackOfPMachine, "Lo" );
        }
        else if ( fnInstrMatch( "mod" ) )
        {
            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            strcpy( strReg0, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg0 );

            printf( " div %s, %s\n", strReg0, strReg1 );

            fnPush( stackOfPMachine, "Hi" );
        }
        else if ( fnInstrMatch( "les" ) )
        {
            fnPush( stackOfPMachine, "bge" );
        }
        else if ( fnInstrMatch( "leq" ) )
        {
            fnPush( stackOfPMachine, "bgt" );
        }
        else if ( fnInstrMatch( "equ" ) )
        {
            fnPush( stackOfPMachine, "bne" );
        }
        else if ( fnInstrMatch( "grt" ) )
        {
            fnPush( stackOfPMachine, "ble" );
        }
        else if ( fnInstrMatch( "geq" ) )
        {
            fnPush( stackOfPMachine, "blt" );
        }
        else if ( fnInstrMatch( "neq" ) )
        {
            fnPush( stackOfPMachine, "beq" );
        }
        else if ( fnInstrMatch( "fjp" ) )
        {
            fnGetArg( );
            strcpy( strCondBranche, fnPop( stackOfPMachine ) );

            strcpy( strReg1, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg1 );

            strcpy( strReg0, fnPop( stackOfPMachine ) );
            fnInsertInPlace( listOfTemporaries, strReg0 );

            printf( " %s %s, %s, %s\n", strCondBranche, strReg0, strReg1, g_strArg );
        }
        else if ( fnInstrMatch( "ujp" ) )
        {
            fnGetArg( );

            printf( " j %s\n", g_strArg );
        }
        else if ( fnInstrMatch( "lab" ) )
        {
            fnGetArg( );

            printf( " %s:\n", g_strArg );
        }
        else if ( fnInstrMatch( "stp" ) )
        {
            // No
            /* printf( " li $v0, 10\n" );
            printf( " syscall\n" );*/

            //Lo correcto es
            printf( " jr $ra\n" );
        }
    }

    fnDestroyList( listOfTemporaries );
    fnDestroyStack( stackOfPMachine );
}

int fnInstrMatch( char* strInstr )
{
    if( strcmp( g_strInstr, strInstr ) == 0 )
        return 1;

    return 0;
}

void fnInitListOfTemporaries( stList* L )
{
    fnInsertInPlace( L, "$t7" );
    fnInsertInPlace( L, "$t6" );
    fnInsertInPlace( L, "$t5" );
    fnInsertInPlace( L, "$t4" );
    fnInsertInPlace( L, "$t3" );
    fnInsertInPlace( L, "$t2" );
    fnInsertInPlace( L, "$t1" );
    fnInsertInPlace( L, "$t0" );
}
