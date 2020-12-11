// main01.cc is a part of the PYTHIA event generator.
// Copyright (C) 2020 Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Keywords: basic usage; charged multiplicity;

// This is a simple test program. It fits on one slide in a talk.
// It studies the charged multiplicity distribution at the LHC.

#include "Pythia8/Pythia.h"
#include <stdio.h>

using namespace Pythia8;
int main() {
  // Generator. Process selection. LHC initialization. Histogram.
  Pythia pythia;
  pythia.readString("Beams:eCM = 8000.");
  pythia.readString("HardQCD:all = on");
  pythia.readString("PhaseSpace:pTHatMin = 20.");
  pythia.init();
  Hist mult("charged multiplicity", 100, -0.5, 799.5);
  // Begin event loop. Generate event. Skip if error. List first one.
	
  FILE* arquivo = fopen("pp_2_ttbar.lhe", "w");
  fprintf(arquivo, "<LesHouchesEvents>\n");
  
	
  for (int iEvent = 0; iEvent < 100; ++iEvent) {
    if (!pythia.next()) continue;
	  
	//Writing the <event> tag.
	fprintf(arquivo, "<event>\n");
	int eventSize = pythia.event.size();
	fprintf(arquivo, " %d      1 1 1 1 1\n", eventSize);
		
	
	
	  
    for (int i = 0; i < pythia.event.size(); ++i) {
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
    
     
      
    
      //Writing data into the file.
      fprintf(arquivo, "        %d ", id); 
	  fprintf(arquivo, "%d ", status);
	  fprintf(arquivo, "%d ", mother1);
	  fprintf(arquivo, "%d ", mother2);
	  fprintf(arquivo, "%d ", color1);
	  fprintf(arquivo, "%d ", color2);
	  fprintf(arquivo, "%e ", p_1);
	  fprintf(arquivo, "%e ", p_2);
	  fprintf(arquivo, "%e ", p_3);
	  fprintf(arquivo, "%e ", p_0);
	  fprintf(arquivo, "%e ", mass);
	  fprintf(arquivo, "%e ", prop_time);
	  fprintf(arquivo, "%e\n", spin);
    
     
      
	}
	//Writing the </event> tag.
	
	fprintf(arquivo, "</event>\n");
	
  // End of event loop
    
  }
	
  
  fprintf(arquivo, "</LesHouchesEvents>\n");
  fclose(arquivo);
	
  pythia.stat();
  cout << mult;
  return 0;
  
}