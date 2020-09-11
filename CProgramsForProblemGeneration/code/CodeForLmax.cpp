/* Prgroam for Lmax Problems Generation */

/* Include Files - qsort.i is for sorting values */
#include <stdio.h>
#include <math.h>
#include "qsort.i"

/* Global Variables Information */
int sequence[60][30]; /* Routing for the jobs */
int processtime[60][30]; /* Operation Processing Times */
int duedate[60]; /* Job Due Dates */
int dmin,dmax; /*  Minimum and Maximum Duedate values */ /* Uniform[dmin,dmax] */

/* Main Program Start */
main()
{
	int iseed; /* Starting Seed Value */
	int njobs, nmachines; /* Number of Jobs and Number of Machines */
	float rvalue,tau; /* R and T values */
	float lowp,highp; /* lower and higher processing time values */
	int shopenvironment; /* Shop Routing Configuration */	

	/* Initialization of parameter values */
	lowp = 1.0;
	highp = 200.0;

	/* Ask for the parameter values */
	printf("\t\tEnter seed value: ");
	scanf("%d",&iseed); 

	printf("\t\t 1 - Classic Job Shop Environment\n"); 
	printf("\t\t 2 - Two Sets Job Shop Environment\n"); 
	printf("\t\t 3 - Flow Shop Environment\n"); 
	printf("\t\t Enter the Shop Configuration: ");
	scanf("%d",&shopenvironment);
	
	printf("\t\tEnter number of jobs: ");
	scanf("%d",&njobs);

	printf("\t\tEnter number of machines: ");
	scanf("%d",&nmachines);

	printf("\t\tEnter tau value: ");
	scanf("%f",&tau);

	printf("\t\tEnter R value: ");
	scanf("%f",&rvalue);

	/* Generate the Problem Information Based on parameter Values */
	if(shopenvironment == 1)
		generatejobshop(njobs,nmachines,tau,rvalue,lowp,highp,&iseed);
	if(shopenvironment == 2)
		generatetwosets(njobs,nmachines,tau,rvalue,lowp,highp,&iseed);
	if(shopenvironment == 3)
		generateflowshop(njobs,nmachines,tau,rvalue,lowp,highp,&iseed);

	/* Print the Generated Information */
	infoprint(njobs,nmachines);	
}
			
/* Function for Random Numbers Generation */
float u16807d(iseed)
int *iseed;
{
	*iseed = (int) fmod(*iseed * 16807.0, 2147483647.);
	return( *iseed / 2147483648.);
}

/* Function for Classic Job Shop Problems Information Generation */
generatejobshop(njobs,nmachines,tau,rvalue,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float tau,rvalue,lowp,highp;
{
	int i,j,seq[30];
	float rnumber[30];
	float dmin,dmax,makespan,mean;

	makespan = njobs * ((lowp+highp)/2.0);
	mean = (1.0 - tau) * makespan;
	dmin = mean - (mean * rvalue /2.0);
	dmax = mean + (mean * rvalue /2.0);
	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=nmachines;++j)	{
			rnumber[j] = u16807d(iseed);
			seq[j] = j;
		}
		qsort(rnumber,seq,1,nmachines);
		for(j=1;j<=nmachines;++j)	{
			sequence[i][j] = seq[j];
			processtime[i][j] = (int) (lowp + u16807d(iseed) * highp);
		}
		duedate[i] = (int) (dmin + u16807d(iseed) * (dmax - dmin + 1));
	}
	
}	

/* Function for Two Sets Job Shop Problems Information Generation */
generatetwosets(njobs,nmachines,tau,rvalue,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float tau,rvalue,lowp,highp;
{
	int i,j,seq[30],firstset,secondset;
	float rnumber[30];
	float dmin,dmax,makespan,mean;

	firstset = nmachines / 2;
	makespan = njobs * ((lowp+highp)/2.0);
	mean = (1.0 - tau) * makespan;
	dmin = mean - (mean * rvalue /2.0);
	dmax = mean + (mean * rvalue /2.0);
	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=firstset;++j)	{
			rnumber[j] = u16807d(iseed);
			seq[j] = j;
		}
		qsort(rnumber,seq,1,firstset);
		for(j=firstset+1;j<=nmachines;++j)	{
			rnumber[j] = u16807d(iseed);
			seq[j] = j;
		}
		qsort(rnumber,seq,firstset+1,nmachines);
		for(j=1;j<=nmachines;++j)	{
			sequence[i][j] = seq[j];
			processtime[i][j] = (int) (lowp + u16807d(iseed) * highp);
		}
		duedate[i] = (int) (dmin + u16807d(iseed) * (dmax - dmin + 1));
	}
	
}	

/* Function for Flow Shop Problems Information Generation */
generateflowshop(njobs,nmachines,tau,rvalue,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float tau,rvalue,lowp,highp;
{
	int i,j,seq[30];
	float rnumber[30];
	float dmin,dmax,makespan,mean;

	makespan = njobs * ((lowp+highp)/2.0);
	mean = (1.0 - tau) * makespan;
	dmin = mean - (mean * rvalue /2.0);
	dmax = mean + (mean * rvalue /2.0);
	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=nmachines;++j)	{
			seq[j] = j;
		}
		for(j=1;j<=nmachines;++j)	{
			sequence[i][j] = seq[j];
			processtime[i][j] = (int) (lowp + u16807d(iseed) * highp);
		}
		duedate[i] = (int) (dmin + u16807d(iseed) * (dmax - dmin + 1));
	}
	
}	

/* Function for Printing the Shop Scheduling Problem Information  - on Screen*/
infoprint(njobs,nmachines)
int njobs,nmachines;
{
	int i,j;

	printf("%d\t%d\n",njobs,nmachines);
	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=nmachines;++j)	{
			printf("%2d %4d ",sequence[i][j],processtime[i][j]);
		}
		printf("%4d\n",duedate[i]);
	}
}		