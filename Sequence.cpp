#include "Sequence.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// constructors and destructor
Sequence::Sequence()
{

}
Sequence::Sequence( int length )
{
    (this -> seq )= "";
}
Sequence::Sequence( Sequence& rhs )
{
    string Array = rhs.getSeq();
    int len = ( rhs.getSeq() ).length();
    ( (this -> seq) = Array );
}
Sequence::~Sequence()
{

}

//setter function for sequence.
void Sequence:: setSeq( string s )
{
    int  len = ( s ).length();
    this -> seq =  s ;
}
//getter function for sequence
string Sequence:: getSeq() const
{
    return (seq);
}

// friend function that will find the LCS (longest common
// subsequence) between 2 sequences of any type, according to
// polymorphism
string Align( Sequence* s1 , Sequence* s2 )
{
    int** LCS = new int* [ ( s1 -> getSeq() ).length() + 1 ] ;
    for ( int i = 0 ; i < ( s1 -> getSeq() ).length() + 1 ; i++ )
    {
        LCS[ i ] = new int [ ( s2 -> getSeq() ).length() + 1 ];
    }
    for( int i = 0 ; i < ( s1 -> seq ).length() + 1 ; i++ )
    {
        for( int j = 0 ; j  < ( s2 -> seq ).length() + 1 ; j++ )
        {
             LCS[ i ][ j ] = 0;
        }

    }
    for( int i = 1  ; i <= ( s1 -> getSeq() ).length() ; i++ )
    {
        for( int j = 1  ; j <= ( s2 -> getSeq() ).length() ; j++)
        {
            if( s1 -> getSeq()[ i - 1 ] == s2 -> getSeq()[ j - 1 ] )
            {
                LCS[ i ][ j ] = 1 + LCS[ i - 1 ][ j - 1 ];
            }
            else
            {
                LCS[ i ][ j ] = max( LCS[ i - 1 ][ j ] , LCS[ i ][ j - 1 ] );
            }
        }
    }
    string result = "";
    int i = ( s1 -> getSeq() ).length() , j = ( s2 -> getSeq() ).length() , k = 0;
    while( i != 0 && j!= 0 )
    {
        if( LCS[ i - 1 ][ j ] == LCS [ i ][ j ] )
        {
            i--;
        }
        else if( LCS[ i ][ j - 1 ] == LCS[ i ][ j ] )
        {
             j--;
        }
        else if( LCS[ i - 1 ][ j - 1 ] < LCS[ i ][ j ] )
        {
            result[ k ] = s1 -> getSeq()[ i - 1 ];
            i--;
            j--;
            k++;
        }
    }

    for ( int i = 0 ; i < ( s1 -> getSeq() ).length() + 1 ; i++ )
    {
        delete[] LCS[ i ];
    }
    delete[] LCS;

    string temp = "";
    for( int n = ( result ).length() - 1 , m = 0 ; n >= 0 ; n-- , m++  )
    {
        temp += result[ n ];
    }
    result = temp;

    return result;
}

string LocalAlign( Sequence* s1 , Sequence* s2 )
{
    int gap = -7;
    int Mismatch = -5;
    int match = 10;
    int** LCS = new int* [ ( s1 -> getSeq() ).length() + 1 ] ;
    for ( int i = 0 ; i < ( s1 -> getSeq() ).length() + 1 ; i++ )
    {
        LCS[ i ] = new int [ ( s2 -> getSeq() ).length() + 1 ];
    }
    for( int i = 0 ; i < ( s1 -> seq ).length() + 1 ; i++ )
    {
        for( int j = 0 ; j  < ( s2 -> seq ).length() + 1 ; j++ )
        {
             LCS[ i ][ j ] = 0;
        }

    }

    for( int i = 1  ; i <= ( s1 -> getSeq() ).length() ; i++ )
    {
        for( int j = 1  ; j <= ( s2 -> getSeq() ).length() ; j++)
        {
            if( s1 -> getSeq()[ i - 1 ] == s2 -> getSeq()[ j - 1 ] )
            {
                LCS[ i ][ j ] = match + LCS[ i - 1 ][ j - 1 ];
            }
            else
            {
                LCS[ i ][ j ] = max( LCS[ i - 1 ][ j ] + gap , LCS[ i ][ j - 1 ]  + gap );
                int tmp = 0;
                tmp = max( LCS[ i ][ j ] , LCS[ i - 1 ][ j - 1 ] + Mismatch );
                tmp = max( tmp , 0 );
                LCS[ i ][ j ] = tmp;

            }
        }
    }
    int maxVal = 0;
    int iMax = 0;
    int jMax = 0;
     for( int i = 0 ; i < ( s1 -> seq ).length() + 1 ; i++ )
    {
        for( int j = 0 ; j  < ( s2 -> seq ).length() + 1 ; j++ )
        {
            int tmp = 0;
            tmp = max( LCS[ i ][ j ] , maxVal );
            tmp = max( tmp , 0 );
            maxVal = tmp;
        }
    }
    for( int i = 0 ; i < ( s1 -> seq ).length() + 1 ; i++ )
    {
        for( int j = 0 ; j  < ( s2 -> seq ).length() + 1 ; j++ )
        {
          if( LCS[ i ][ j ] == maxVal )
          {
                iMax = i;
                jMax = j;
                break;
          }
        }
    }
    int i = iMax , j = jMax , k = 0 , counter = 0;
    while( LCS[ i ][ j ] != 0 )
    {
        int tmp = 0;
        maxVal = max(LCS[ i - 1 ][ j - 1 ] , LCS[ i - 1 ][ j ]);
        tmp = max(maxVal , LCS[ i ][ j - 1 ] );
        maxVal = tmp;
        if( maxVal == LCS[ i - 1 ][ j - 1 ] )
        {
            counter++;
            i--;
            j--;
        }
        else if( maxVal == LCS [ i - 1 ][ j ] )
        {
            i--;
        }
        else if( maxVal == LCS[ i ][ j - 1] )
        {
            j--;
        }
    }
    string result = "";
    i = iMax , j = jMax , k = 0;
    while( LCS[ i ][ j ] != 0 )
    {
        int tmp = 0;
        maxVal = max(LCS[ i - 1 ][ j - 1 ] , LCS[ i - 1 ][ j ]);
        tmp = max(maxVal , LCS[ i ][ j - 1 ] );
        maxVal = tmp;
        if( maxVal == LCS[ i - 1 ][ j - 1 ] )
        {
            result[ k ] = s1 -> getSeq()[ i - 1 ];
            k++;
            i--;
            j--;
        }
        else if( maxVal == LCS [ i - 1 ][ j ] )
        {
            i--;
        }
        else if( maxVal == LCS[ i ][ j - 1] )
        {
            j--;
        }
    }
    for ( int i = 0 ; i < ( s1 -> getSeq() ).length() + 1 ; i++ )
    {
        delete[] LCS[ i ];
    }
    delete[] LCS;

    string temp = "";
    for( int n = ( result ).length() - 1 , m = 0 ; n >= 0 ; n-- , m++  )
    {
        temp += result[ n ];
    }
    result = temp;

    return result;
}
