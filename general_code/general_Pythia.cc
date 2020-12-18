//A general code to run Pythia.

#include "Pythia8/Pythia.h"
#include <stdio.h>
#include <string>
#include "lheEventWriter.h"

using namespace Pythia8;

int run(const string & infile, int nevents, const string & cfgfile, const string & outputfile)
{
	Pythia pythia;
	std::srand(500);
	string outname;

	//Setting the output name
	if (outputfile == "") {
		size_t lastindex = infile.find_last_of(".");
		outname = infile.substr(0, lastindex)+".out";
	}
	else{outname = outputfile;}

	//Avoiding negative number of events
	if ( nevents < 0) {
    	nevents = 100;
    	cout << "Negative number of events for SLHA input. Setting nevents to " << nevents << endl;
    }

	//Reading the configuration file
	pythia.readFile(cfgfile);

	//Setting the frame type
	pythia.readString("Beams:frameType = 4");

	//Reading the input .lhe file
    pythia.readString("Beams:LHEF = " + infile);

	//Initialize
	pythia.init();

	int nPass = 0;
	int iAbort = 0;

	//Opening the output file:
	FILE* OutputFile = fopen(outname.c_str(), "w");
	int a = initLHEOutput(OutputFile);


	// Begin event loop.
	int iEvent = 0;

	while (iEvent < nevents or nevents < 0) {

		 // If failure because reached end of file then exit event loop.
		 if (pythia.info.atEndOfFile()) break;

		 // Generate events. Quit if failure.
		 if (!pythia.next()) {
			 if (++iAbort < 10) continue;
			 cout << " Event generation aborted prematurely, owing to error!\n";
			 break;
		 }


		a =  writeLHEevent(OutputFile, pythia.event);

		 ++iEvent;

	}
	// End of event loop.

	//Closing the output file:
	a = closeLHEOutput(OutputFile);
	fclose(OutputFile);


}
void help( const char * name )
{
	  cout << "syntax: " << name << " [-h] [-f <input file>] [-o <output file>] [-n <number of events>] [-c <pythia cfg file>]" << endl;
	  cout << "        -f <input file>:  pythia input LHE file" << endl;
	  cout << "        -c <pythia config file>:  pythia config file [pythia8_stau.cfg]" << endl;
	  cout << "        -o <output file>:  output filename for naming the output file and histograms [<input file>.lhe]" << endl;
	  cout << "        -n <number of events>:  Number of events to be generated [100]. If n < 0, it will run over all events in the LHE file" << endl;
  exit( 0 );
};

int main( int argc, const char * argv[] ) {
	float weight = 1.;
	int nevents = -1;
	double width = 0.;
	string cfgfile = "pythia8_stau.cfg";
	string outfile = "";
	string infile = "";
	for ( int i=1; i!=argc ; ++i )
	{
		string s = argv[i];
		if ( s== "-h" )
		{
			help ( argv[0] );
		}

		if ( s== "-c" )
		{
			if ( argc < i+2 ) help ( argv[0] );
			cfgfile = argv[i+1];
			i++;
			continue;
		}


		if ( s== "-n" )
		{
			if ( argc < i+2 ) help ( argv[0] );
			nevents = atoi(argv[i+1]);
			i++;
			continue;
		}

		if ( s== "-o" )
		{
			if ( argc < i+2 ) help ( argv[0] );
			outfile = argv[i+1];
			i++;
			continue;
		}


		if ( s== "-f" )
		{
			if ( argc < i+2 ) help ( argv[0] );
			infile = argv[i+1];
			i++;
			continue;
		}



		cout << "Error. Argument " << argv[i] << " unknown." << endl;
		help ( argv[0] );
	};

	int r = run(infile, nevents, cfgfile, outfile );




	return 0;
}
