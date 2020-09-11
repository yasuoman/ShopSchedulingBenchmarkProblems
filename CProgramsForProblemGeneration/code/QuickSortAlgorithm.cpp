/* Program to Sort using Quick Sort Algorithm */


/* Function Declarations */

void qsort(); 
int numcmp(); 
void swap(); 
void swapfloat(); 

/* Function for sorting Multiple Arrays */

void qsort(rnumber,seq,left,right)
int *seq,left,right;
float *rnumber;
{
	int i,j,last;

	if(left >= right)
		return;
	swapfloat(rnumber,left,(left+right)/2);
    swap(seq,left,(left+right)/2);
	last = left;
	for(i = left+1; i<= right; i++) 	{
		if(numcmp(rnumber[i],rnumber[left]) < 0)	{
			++last;
			swapfloat(rnumber, last, i);
			swap(seq, last, i);
		}
	}
	swapfloat(rnumber,left,last);
	swap(seq,left,last);
	qsort(rnumber,seq,left,last-1);
	qsort(rnumber,seq,last+1,right);
}

int numcmp(v1,v2)
float v1,v2;
{
	if(v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(v,i,j)
int *v,i,j;
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void swapfloat(v,i,j)
int i,j;
float *v;
{
	float temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}