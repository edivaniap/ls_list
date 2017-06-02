#include "lslist.h"

int main( )
{
    ls::list< int > l;

    for( auto i(0) ; i < 10 ; ++i )
        l.push_back( i+1 );

    return 0;
}