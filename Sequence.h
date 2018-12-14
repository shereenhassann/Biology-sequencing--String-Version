#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>

using namespace std;

class Sequence
{
  	protected:
        string seq ;
        int len ;
    public:
 	 	// constructors and destructor
        Sequence();
        Sequence( int length );
        Sequence( Sequence& rhs );
        Sequence( string s);
        void setSeq( string seq );

        string getSeq() const;
        virtual ~Sequence();

        virtual void LoadSequenceFromFile(string filename) = 0; //pure virtual
        virtual void SaveSequenceToFile(string filename) = 0;		//pure virtual


 	 	// pure virtual function that should be overridden because every
        // type of sequence has its own details to be printed
        virtual void Print()= 0;
 	 	// friend function that will find the LCS (longest common
        // subsequence) between 2 sequences of any type, according to
        // polymorphism
        friend string Align( Sequence* s1 , Sequence* s2 );
        friend string LocalAlign( Sequence* s1 , Sequence* s2 );
};


#endif // SEQUENCE_H
