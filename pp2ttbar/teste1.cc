// main11.cc is a part of the PYTHIA event generator.
// Copyright (C) 2020 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Keywords: basic usage; LHE file;

// This is a simple test program.
// It illustrates how Les Houches Event File input can be used in Pythia8.
// It uses the ttsample.lhe(.gz) input file, the latter only with 100 events.

#include "Pythia8/Pythia.h"
using namespace Pythia8;
int main() {

  // You can always read an plain LHE file,
  // but if you ran "./configure --with-gzip" before "make"
  // then you can also read a gzipped LHE file.
#ifdef GZIP
  bool useGzip = true;
#else
  bool useGzip = false;
#endif
  cout << " useGzip = " << useGzip << endl;

  // Generator. We here stick with default values, but changes
  // could be inserted with readString or readFile.
  Pythia pythia;

  // Initialize Les Houches Event File run. List initialization information.
  pythia.readString("Beams:frameType = 4");
  pythia.readString("Beams:LHEF = pp2ttbar.lhe");
  pythia.init();
  
  // Allow for possibility of a few faulty events.
  int nAbort = 10;
  int iAbort = 0;


  // Begin event loop; generate until none left in input file.
  for (int iEvent = 0;  ; ++iEvent) {
	 

    // Generate events, and check whether generation failed.
    if (!pythia.next()) {

      // If failure because reached end of file then exit event loop.
      if (pythia.info.atEndOfFile()) break;

      // First few failures write off as "acceptable" errors, then quit.
      if (++iAbort < nAbort) continue;
      break;
    }

   
    FILE* arquivo4 = fopen("saida.txt", "w");
    fprintf(arquivo4, "<LesHouchesEvents>\n");
	fprintf(arquivo4, "<event>\n");
    fclose(arquivo4);  

    // Sum up final charged multiplicity and fill in histogram.
    
    for (int i = 0; i < pythia.event.size(); ++i){
    //LHE columns.
      int id = pythia.event[i].id();
      int status = pythia.event[i].status();
	  int mother1 = pythia.event[i].mother1();
	  int mother2 = pythia.event[i].mother2();
	  int color1 = pythia.event[i].col();
	  int color2 = pythia.event[i].acol();
	  double p_1 = pythia.event[i].px();
	  double p_2 = pythia.event[i].py();
	  double p_3 = pythia.event[i].pz();
	  double p_0 = pythia.event[i].e();
	  double mass = pythia.event[i].m();
	  double prop_time = pythia.event[i].tau();
	  double spin = pythia.event[i].pol();
    
      //Opening the file.
      FILE* arquivo1 = fopen("saida.txt", "a+");
    
      //Writing into the file.
      fprintf(arquivo1, "%d ", id); 
	  fprintf(arquivo1, "%d ", status);
	  fprintf(arquivo1, "%d ", mother1);
	  fprintf(arquivo1, "%d ", mother2);
	  fprintf(arquivo1, "%d ", color1);
	  fprintf(arquivo1, "%d ", color2);
	  fprintf(arquivo1, "%e ", p_1);
	  fprintf(arquivo1, "%e ", p_2);
	  fprintf(arquivo1, "%e ", p_3);
	  fprintf(arquivo1, "%e ", p_0);
	  fprintf(arquivo1, "%e ", mass);
	  fprintf(arquivo1, "%e ", prop_time);
	  fprintf(arquivo1, "%e\n", spin);
    
      //Closing the file.
      fclose(arquivo1);
	  
	  

  // End of event loop.
  }
  //Writing the </event> tag.
  FILE* arquivo2 = fopen("saida.txt", "a+");
  fprintf(arquivo2, "</event>\n");
  fclose(arquivo2);
  }
 
  
   FILE* arquivo5 = fopen("saida.txt", "a+");
  fprintf(arquivo5, "</LesHouchesEvents>\n");
  fclose(arquivo5);

  // Done.
  return 0;
}