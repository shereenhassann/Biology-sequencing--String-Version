#include "RNA.h"
#include "DNA.h"
#include "Protein.h"
#include "CodonsTable.h"
#include "Sequence.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

using namespace std;

void RNA::Print()   ///print RNA
{
    cout << "Sequence is: " << seq << endl;
	cout << "Type is: ";
	getTypeChar();
}
/*void RNA :: operator = ( RNA rna )
{
    this -> seq = rna.seq;
    this -> type = rna.type;
}*/

RNA::RNA() : Sequence() /// default constructor
{
    type = mRNA;
}

RNA::~RNA() ///destructor
{

}
//Parameterized constructor
RNA::RNA( string seq , RNA_Type atype )
{
    this -> seq = seq;
	type = atype;
}


//Copy constructor
RNA::RNA( RNA& rhs )
{
	string Array = rhs.getSeq();
    int len = ( rhs.getSeq() ).length();
    this -> seq = Array ;
    this -> type = rhs.type;
}

bool RNA :: operator == ( RNA& rna )    // check equality
{
    if( ( ( this -> seq ).length() == ( rna.seq ).length() ) && ( this -> getType() == rna.getType() ) )
    {
        for( int i = 0 ; i < ( this -> seq ).length() ; i++ )
        {
            if( this -> seq[ i ] != rna.seq[ i ] )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool RNA :: operator != ( RNA& rna )    //check not equal
{
    if( ( *this ) == rna )
        return false;
    return true;
}

RNA RNA :: operator + ( RNA& rna )  //add 2 RNAs
{
    RNA result;
    string seq1 = "";
    for( int i = 0 ; i < ( this -> seq ).length() ; i++ )
    {
        seq1 += this -> seq[ i ];
    }
    for( int i = ( this -> seq ).length() , j = 0 ; i < ( rna.seq ).length() + ( this -> seq ).length() ; i++ , j++ )
    {
        seq1 +=  rna.seq[ j ];
    }
    result.setSeq( seq1 );
    result.setType(this -> getType());
    RNA r(result);
    return r;
}

Protein RNA::ConvertToProtein()
{
	Protein p;
	CodonsTable table;
	table.LoadCodonsFromFile( "RNA_codon_table.txt" );  ///loads from codon file
	string seq = "";
	string result = "";

	for ( int i = 0 , j = 0 ; i < ( this -> seq ).length() ; i += 3 , j++ )
    {
        seq[ 0 ] = this -> seq[ i ];
        seq[ 1 ] = this -> seq[ i + 1 ];
        seq[ 2 ] = this -> seq[ i + 2 ];
        result[ j ] = table.getAminoAcid( seq ).AminoAcid;  //changes into protein

    }
    p.setSeq( result );

	return p;
}

DNA RNA::ConvertToDNA()
{
	DNA dna;
	string temp = this -> seq;
	for (int i = 0 ; i < ( this -> seq ).length() ; i++)
	{
		if ( this -> seq[ i ] == 'U' )
		{
			temp[ i ] = 'T';
		}
	}
	dna.setSeq( temp );
	dna.setType(0);
	return dna;
}

void RNA::setType( int type )   //set type of DNA by using integer
{
	switch ( type )
	{
	case 0:
		this -> type = mRNA;
		break;

	case 1:
		this -> type = pre_mRNA;
		break;

	case 2:
		this -> type = mRNA_exon;
		break;

	case 3:
		this -> type = mRNA_intron;
		break;

	default:
		cout << "\nInvalid input.\n";
		break;
	}
}

int RNA::getType()
{
	return this -> type;
}
void RNA::getTypeChar() ///get the type in its string form
{
    switch( getType() )
    {
    case 0:
        cout << "mRNA" << endl;
        break;
    case 1:
        cout << "pre_mRNA" << endl;
        break;
    case 2:
        cout << "mRNA_exon" << endl;
        break;
    case 3:
        cout << "mRNA_intron" << endl;
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}
void RNA::LoadSequenceFromFile(string filename) ///load what is inside the file
{
	ifstream file;
	file.open(filename);
	if (file.fail())
	{
		cout << "\nError opening file.\n";
		return;
	}
    else{
        string line;
        while (!file.eof())
        {
            getline(file, line);
            cout << line << endl;
        }
        file.close();
    }
}

void RNA::SaveSequenceToFile(string filename)   //save the input into a file
{
	string line;

	ofstream file;
	file.open(filename, ios_base::app);

	if (file.fail())
	{
		cout << "\nError opening file. \n";
		return;
	}

	file << "RNA :\n";
    switch (getType())
	{
	case 0:
		file << "Type: mRNA\n";
		break;
	case 1:
		file << "Type: pre-mRNA\n";
		break;
	case 2:
		file << "Type: mRNA_exon\n";
		break;
	case 3:
		file << "Type: mRNA_intron";
		break;
	}
    file << "RNA sequence : ";
    file << this -> getSeq();
    file <<"\n\n";
}
void validRNASeq( string seq )   //check sequence validity
{
    int check = 0;
    for( int i = 0 ; i < ( seq ).length() ; i++ )
    {
        if( seq[ i ] == 'A' || seq[ i ] == 'C' || seq[ i ] == 'G' || seq[ i ] == 'U' )
        {
            check++;
        }
    }
    int len = seq.length();
    if( check < len )
    {
        throw 1 ;
    }
}
void validRNAChoice( char choice )  //check choice validity
{
    if( choice != '1' && choice != '2' && choice != '3' && choice != '4' )
    {
        throw 2;
    }
}
istream& operator >> ( istream& in , RNA& rna ) //input RNA
{
    char choice;
    cout << "Please choose the type of the RNA : \n\n1-mRNA.\n2-pre_mRNA.\n3-mRNA_exon.\n4-mRNA_intron.\n>> ";
    in >> choice;
    bool flag = false;
    do
    {
        try
        {
            validRNAChoice( choice );
            flag = false;
        }
        catch ( int n )
        {
            flag = true;
            cout << "Invalid input. Please choose 1, 2, 3, or 4 : \n>> ";
            in >> choice;
        }

    }while( flag );
    int choosen = int( choice  - '0' );
    rna.setType( choosen - 1 );
    cout << "Please enter the RNA strand : ";
    string str;
    in >> str;
    for( int i = 0 ; i < str.length() ; i++ )
    {
        str[ i ] = toupper( str[ i ] );
    }

    flag = false;
    //Checking input validity using try and catch
    do
    {
        try
        {
            validRNASeq( str );
            flag = false;
        }
        catch (int n )
        {
            flag = true;
            cout << "Invalid input. Please enter a valid strand : \n>> ";
            in >> str;
            for( int i = 0 ; i < str.length() ; i++ )
            {
                str[ i ] = toupper( str[ i ] );
            }

        }
    }while( flag );
    rna.setSeq( str );
	return in;
}
ostream& operator << ( ostream& out , RNA& rna )       //print RNA
{
    out << "The type of your RNA is : ";
    rna.getTypeChar();
    out << "RNA Sequence is: " << rna.getSeq() << endl;
    return out;
}
