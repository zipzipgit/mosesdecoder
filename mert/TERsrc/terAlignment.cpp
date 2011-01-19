
#include "terAlignment.h"
using namespace std;
namespace TERCpp
{

    terAlignment::terAlignment()
    {
        numEdits=0;
        numWords=0;
        bestRef="";

        numIns=0;
        numDel=0;
        numSub=0;
        numSft=0;
        numWsf=0;
    }
    string terAlignment::toString()
    {
        stringstream s;
        s.str ( "" );
        s << "Original Ref: " << join ( " ", ref ) << endl;
        s << "Original Hyp: " << join ( " ", hyp ) <<endl;
        s << "Hyp After Shift: " << join ( " ", aftershift );
        s << endl;
        if ( ( int ) sizeof ( alignment ) >0 )
        {
            s << "Alignment: (";
            for ( int i = 0; i < ( int ) ( alignment.size() ); i++ )
            {
                s << alignment[i];
            }
            s << ")";
        }
        s << endl;
        if ( ( int ) allshifts.size() == 0 )
        {
            s << "NumShifts: 0";
        }
        else
        {
            s << "NumShifts: "<< ( int ) allshifts.size();
            for ( int i = 0; i < ( int ) allshifts.size(); i++ )
            {
                s << endl << "  " ;
                s << ( ( terShift ) allshifts[i] ).toString();
            }
        }
        s << endl << "Score: " << score() << " (" << numEdits << "/" << numWords << ")";
        return s.str();

    }
    string terAlignment::join ( string delim, vector<string> arr )
    {
        if ( ( int ) arr.size() == 0 ) return "";
        stringstream s;
        s.str ( "" );
        for ( int i = 0; i < ( int ) arr.size(); i++ )
        {
            if ( i == 0 )
            {
                s << arr.at ( i );
            }
            else
            {
                s << delim << arr.at ( i );
            }
        }
        return s.str();
    }
    double terAlignment::score()
    {
        if ( ( numWords <= 0.0 ) && ( numEdits > 0.0 ) )
        {
            return 1.0;
        }
        if ( numWords <= 0.0 )
        {
            return 0.0;
        }
        return ( double ) numEdits / numWords;
    }

  void terAlignment::scoreDetails() 
  {
	numIns = numDel = numSub = numWsf = numSft = 0;
	if((int)allshifts.size()>0) 
	{
	    for(int i = 0; i < (int)allshifts.size(); ++i)
	    {
		      numWsf += allshifts[i].size();
	    }
	    numSft = allshifts.size();
	}
		
	if((int)alignment.size()>0 ) 
	{
	  for(int i = 0; i < (int)alignment.size(); ++i) 
	  {
		switch (alignment[i]) 
		{
		  case 'S':
		  case 'T':
		    numSub++;
		    break;
		  case 'D':
		    numDel++;
		    break;
		  case 'I':
		    numIns++;
		    break;
		}		
	  }
	}
  }

}
