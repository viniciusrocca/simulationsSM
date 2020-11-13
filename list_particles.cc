// main30.cc is a part of the PYTHIA event generator.
// Copyright (C) 2017 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.
// Author: Steve Mrenna.

// Example how to create a copy of the event record, where the original one
// is translated to another format, to meet various analysis needs.
// In this specific case the idea is to set up the history information
// of the underlying hard process to be close to the PYTHIA 6 structure.

#include "Pythia8/Pythia.h"
using namespace Pythia8;

//--------------------------------------------------------------------------

int run(const string & outputfile)
{

  // Generator. Shorthand for the event.
  Pythia pythia("",false); //Set printBanner to false

  // ParticleData ParticleData();
  pythia.particleData.listXML(outfile);
  return 0;

}

//--------------------------------------------------------------------------



void help( const char * name )
{
	  cout << "Prints out the particle data in XML format. Syntax: " << name << " [-h]  [-o <output file>] " << endl;
	  cout << "        -o <output file>:  output filename  [particles.xml]" << endl;
  exit( 0 );
};

int main( int argc, const char * argv[] ) {
  string outfile = "particles.xml";
  for ( int i=1; i!=argc ; ++i )
  {
    string s = argv[i];
    if ( s== "-h" )
    {
      help ( argv[0] );
    }

    if ( s== "-o" )
    {
      if ( argc < i+2 ) help ( argv[0] );
      outfile = argv[i+1];
      i++;
      continue;
    }



    cout << "Error. Argument " << argv[i] << " unknown." << endl;
    help ( argv[0] );
  };

  int r = run(outfile);

  return 0;
}
