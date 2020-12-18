//Some helper functions for computing relevant quantities
#include <string>
#include <vector>
#include <vector>

using namespace Pythia8;

int initLHEOutput(FILE *outfile)
{
	//Writing the inital tag of the file.
	fprintf(outfile, "<LesHouchesEvents>\n");
    return 0;
}



int writeLHEevent(FILE *outfile, Event &event) {

	//Writing initial tag of the event.
	fprintf(outfile, "<event>\n");

	//Writing the first line of the event.
	int eventSize = event.size();
	fprintf(outfile, " %d      1 1 1 1 1\n", eventSize);

    //LHE columns.
    for (int i = 0; i < event.size(); ++i) {
    	int id = event[i].id();
        int status = event[i].status();
    	int mother1 = event[i].mother1();
    	int mother2 = event[i].mother2();
    	int color1 = event[i].col();
    	int color2 = event[i].acol();
    	double p_1 = event[i].px();
    	double p_2 = event[i].py();
    	double p_3 = event[i].pz();
    	double p_0 = event[i].e();
    	double mass = event[i].m();
    	double prop_time = event[i].tau();
    	double spin = event[i].spinType();


        //Writing data into the file.
    	fprintf(outfile, "        %d ", id);
    	fprintf(outfile, "%d ", status);
    	fprintf(outfile, "%d ", mother1);
    	fprintf(outfile, "%d ", mother2);
    	fprintf(outfile, "%d ", color1);
    	fprintf(outfile, "%d ", color2);
    	fprintf(outfile, "%e ", p_1);
    	fprintf(outfile, "%e ", p_2);
    	fprintf(outfile, "%e ", p_3);
    	fprintf(outfile, "%e ", p_0);
    	fprintf(outfile, "%e ", mass);
    	fprintf(outfile, "%e ", prop_time);
    	fprintf(outfile, "%e\n", spin);
    }
	fprintf(outfile, "</event>\n");

    return 0;
}

int closeLHEOutput(FILE *outfile) {
	//Writing the final tag of the file.
	fprintf(outfile, "</LesHouchesEvents>\n");
    return 0;
}
