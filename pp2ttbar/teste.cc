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
	
  FILE* arquivo4 = fopen("saida.txt", "w");
  fprintf(arquivo4, "<LesHouchesEvents>\n");
  fclose(arquivo4);
	
  for (int iEvent = 0; iEvent < 100; ++iEvent) {
    if (!pythia.next()) continue;
	  
	//Writing the <event> tag.
	FILE* arquivo = fopen("saida.txt", "a+");
	fprintf(arquivo, "<event>\n");
	
	fclose(arquivo);
	
	  
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
	}
	//Writing the </event> tag.
	FILE* arquivo2 = fopen("saida.txt", "a+");
	fprintf(arquivo2, "</event>\n");
	fclose(arquivo2);
  // End of event loop. Statistics. Histogram. Done.
    
  }
	
  FILE* arquivo3 = fopen("saida.txt", "a+");
  fprintf(arquivo3, "</LesHouchesEvents>\n");
  fclose(arquivo3);
	
  pythia.stat();
  cout << mult;
  return 0;
  
}