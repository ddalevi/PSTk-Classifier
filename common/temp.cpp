//#include "SequenceGenerator.h"
//#include "Alphabet.h"
#include "StatisticalTables.h"
#include <iostream>
using namespace std;

int main()
{
  cout << "Half the 5% quantile, 3 d.o.f., of a Chi2 distribution is: " << 0.5*StatisticalTables::quantileChiSquare( 3, 0.05 ) << endl;
//   Alphabet* pAlp = new Alphabet();
//   pAlp->setAlphabet( Alphabet::DNA );
//   SequenceGenerator rGen( pAlp );
//   rGen.setGCnormal( 0.5, 0.15 );
//   rGen.setBase( 3 );
//   rGen.setRandomTransitions();
//   cout << rGen.getMixture( 50, 2, 0.5, 0 ) << endl;
  return 0;
}
