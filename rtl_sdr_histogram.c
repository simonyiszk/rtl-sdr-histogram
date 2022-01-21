#include <stdio.h>
#include <signal.h>

unsigned long SAMPLE_COUNT = (2048000>>2);		//adjust according to the rtl_sdr sampling rate (-s) and desired fps

int run = 0;

//handling plot window close event
void gnuplotClosingPipeEvent(int signal){
	if (signal==SIGPIPE){
    	run = 0;
	}
}

//usage: pipe rtl_sdr output into this, or specify the name of a raw file
int main(int argc, char **argv){

	FILE* data = stdin;
	signal(SIGPIPE, gnuplotClosingPipeEvent);
	
	if(argc==2){
		data = fopen(argv[1], "r");
		if(data==NULL){
			printf("Error opening file: %s\n", argv[1]);
			return -1;
		}
	}

	unsigned int I_samps[256] = {0};
	unsigned int Q_samps[256] = {0};

	//open and format gnuplot window
	FILE* gnuplot = popen("gnuplot -persistent", "w");	

	fprintf(gnuplot, "bind Close \"exit gnuplot\"\n");
	fprintf(gnuplot, "set terminal wxt title \"RTL-SDR histogram\"\n");
	fprintf(gnuplot, "set terminal wxt size 1300,600\n");
	fprintf(gnuplot, "set datafile separator ','\n");
	fprintf(gnuplot, "set xrange [0:255]\n");
	fprintf(gnuplot, "set grid\n");
	fprintf(gnuplot, "set ylabel \"Count\"\n");
	fprintf(gnuplot, "set xlabel \"Amplitude (byte)\"\n");
	fprintf(gnuplot, "set format x '0x%%02X'\n");	//hex format on x axis
	//fprintf(gnuplot, "set logscale y\n"); 		//for logarithmic y-scale

	if(data==stdin){
		run = 1;
	}else{
		fseek(data, 0, SEEK_END);
  		unsigned long samples_in_file = (ftell(data) >> 1);		//we will read 2 bytes each for I and Q
		rewind(data);

		if(samples_in_file<SAMPLE_COUNT){
			SAMPLE_COUNT = samples_in_file;
		}
	}

	do{
		//plot style
		fprintf(gnuplot,"plot '-' using 1 with lines lw 1.5 lt 6 title 'Amplitude distribution of in-phase components (I)', '' using 1 with lines lw 1.5 lt 7 title 'Amplitude distribution of quadrature components (Q)'\n");

		//read I and Q data
		for(int i=0; i<SAMPLE_COUNT; i++){
			I_samps[getc(data)]++;
			Q_samps[getc(data)]++;
		}

		//plot and clear bins
		for(int i=0; i<256; i++){
			fprintf(gnuplot, "%u\n", I_samps[i]);
			I_samps[i] = 0;
		}
		fprintf(gnuplot,"e\n");
		
		for(int i=0; i<256; i++){
			fprintf(gnuplot, "%u\n", Q_samps[i]);
			Q_samps[i] = 0;
		}
		fprintf(gnuplot,"e\n");	

		//refresh
		fflush(gnuplot);

	}while(run);
	
	//clean up
	pclose(gnuplot);

	if(data!=stdin){
		fclose(data);
	}	
	
	return 0;
}