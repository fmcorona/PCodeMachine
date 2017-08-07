#include <stdio.h>
#include <stdlib.h>
#include "includes/readpcode.h"
#include "includes/codegen.h"

int main( )
{
	fnOpenFileToRead( "test//test3.txt" );
	fnGenCode( );
	fnCloseFile( );

    return 0;
}
