/* Problem Generation for shop Cmax Problems*/
/* Include files  - Qsort is the sorting algorithm*/

#include <stdio.h>
#include <math.h>
#include "qsort.i"

/* Global Variables Definition */
int sequence[60][30];  /* Routing for the jobs */
int processtime[60][30]; /* Operation process times in the routings for jobs */

/* Main Program Start */
main()
{
	int iseed;  /* Starting Seed Value */
	int njobs, nmachines;  /* Number of jobs and Number of machines */
	float lowp,highp; /* Uniform[lowp,highp] for the processing times generation */
	int shopenvironment; /* Enter the shop environment */

	/* Initialization of parameter values */
	lowp = 1.0;
	highp = 200.0;	
	/* Initialization complete */

	/* Ask for various problem parameters and starting seed value  */

	printf("\t\tEnter seed value: ");
	scanf("%d",&iseed);
	printf("\t\t 1 - Classic Job Shop Environment \n");
	printf("\t\t 2 - Two Sets Job Shop Environment \n");
	printf("\t\t 3 - Flow Shop Environment \n");
	printf("\t\t Enter Shop Environment: ");
	scanf("%d",&shopenvironment);
	printf("\t\tEnter number of jobs: ");
	scanf("%d",&njobs);
	printf("\t\tEnter number of machines: ");
	scanf("%d",&nmachines);
	
	/* Generate the problem */
	if(shopenvironment == 1)	{
		generatejobshop(njobs,nmachines,lowp,highp,&iseed);
	}
	if(shopenvironment == 2)	{
		generatetwosets(njobs,nmachines,lowp,highp,&iseed);
	}
	if(shopenvironment == 3)	{
		generateflowshop(njobs,nmachines,lowp,highp,&iseed);
	}

	/* Print the information on Generated Problem */
	infoprint(njobs,nmachines);	
} /* Main Program End */
			
/* Random Number Generator */
float u16807d(iseed)
int *iseed;
{
	*iseed = (int) fmod(*iseed * 16807.0, 2147483647.);
	return( *iseed / 2147483648.);
} /* Random Number Generator End */

/* Generating Classic Job Shop Information */
generatejobshop(njobs,nmachines,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float lowp,highp;
{
	int i,j,seq[30];
	float rnumber[30];

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
	}
	
} /* End Generating Information for Classic Job Shop */	

/* Generating Two Sets Job Shop Information */
generatetwosets(njobs,nmachines,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float lowp,highp;
{
	int i,j,seq[30],firstset,secondset;
	float rnumber[30];

	firstset = nmachines / 2;
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
	}
	
} /* End Generating Information for Two Sets Job Shop */	

/* Generating Flow Shop Information */
generateflowshop(njobs,nmachines,lowp,highp,iseed)
int njobs,nmachines,*iseed;
float lowp,highp;
{
	int i,j,seq[30];
	float rnumber[30];

	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=nmachines;++j)	{
			seq[j] = j;
		}
		for(j=1;j<=nmachines;++j)	{
			sequence[i][j] = seq[j];
			processtime[i][j] = (int) (lowp + u16807d(iseed) * highp);
		}
	}
	
} /* End of Generating Flow Shop Information */	

/* Printing the Generated Information on the Screen */
infoprint(njobs,nmachines)
int njobs,nmachines;
{
	int i,j;
	
	printf("%d\t%d\n",njobs,nmachines);
	for(i=1;i<=njobs;++i)	{
		for(j=1;j<=nmachines;++j)	{
			printf("%2d %4d ",sequence[i][j],processtime[i][j]);
		}
		printf("\n");
	}

} /* End Printing the Information */		