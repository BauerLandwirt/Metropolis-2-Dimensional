#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double targetDistrib(double x, double y){//Define target distribution up to a constant. 
	double rho=0;
	double z;
	z=exp(-1/(2*(1-rho*rho))*(x*x-2*rho*x*y+y*y));
return z;	
}

double proposalDistrib(double x){//Sample from a proposal distribution. I chose the uniform distribution U(x-1.5,x+1.5) using a pseudo-RNG.
	double y;
	y=rand()%3000000;
	y=y/1000000.0;
	y=x-1.5+y;
return y;
}

void SampleGenerator(double *initVal, int *Samplesize, double *Samplex, double *Sampley){//Generate samples from target distribution.
	double proposal[2];//Define proposal constant.
	double distribRatio;//Define the ratio of distributions (see below). This will be the acceptance probability for our proposal.
	double RandomNumb;//A (pseudo) random number between 0 and 1 that will help us decide if our proposal gets accepted.
	for(int i = 0;i<Samplesize[0];i++){
		proposal[0] = proposalDistrib(initVal[0]);//Generate proposal using the proposal distribution.
		proposal[1] = proposalDistrib(initVal[1]);
		if(targetDistrib(initVal[0], initVal[1])>0){//Do not divide by 0...
			distribRatio = targetDistrib(proposal[0], proposal[1])/targetDistrib(initVal[0], initVal[1]);//Generate acceptance probability for generated proposal.
		}
		else{
			distribRatio = 1;//Reject initial value if it has target probability 0.
		}
		RandomNumb = rand()%1000000;//generate random number between 0 and 1.
		RandomNumb = RandomNumb/1000000.0;//-''-
		if(distribRatio > RandomNumb){//Accept proposal.
			Samplex[i] = proposal[0];
			Sampley[i] = proposal[1];
			initVal[0] = proposal[0];
			initVal[1] = proposal[1];
		}
		else{
			Samplex[i] = initVal[0];//Reject proposal
			Sampley[i] = initVal[1];
		}
	}
}

int main(){
	int *Samplesize;//Defining variables and allocating storage.
	double *Samplex;
	double *Sampley;
	double *initVal;//Define initial value.)
	initVal = (double *) malloc(sizeof(double)*3);
	Samplesize = (int *) malloc(sizeof(int)+1);
	Samplesize[0] = 100000;//Define sample size
	Samplex = (double *) malloc(sizeof(double)*Samplesize[0]+1);
	Sampley = (double *) malloc(sizeof(double)*Samplesize[0]+1);
	SampleGenerator(initVal, Samplesize, Samplex, Sampley);
	initVal[0] = 1;
	initVal[1] = 1;
	FILE *fp;//create/open file and write sample values.
	fp = fopen("MetropolisSampleDim2.txt", "w");
	for(int j=0; j<Samplesize[0]; j++) {
		fprintf(fp, "%f    %f\n", Samplex[j], Sampley[j]);
	}
		fclose(fp);
}