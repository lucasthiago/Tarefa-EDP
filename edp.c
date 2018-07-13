#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 100
#define err 1e-5

void contorno(double **M)
{
	int i, j;
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			M[i][j]=0;
			
			if(i==0)
				M[i][j]=200;
			if(j==0)
				M[i][j]=0;
			if(i==N-1)
				M[i][j]=0;
			if(j==N-1)
				M[i][j]=200;
		}
	}
}

double relaxamento(double **M)
{
	int i, j;
	double a, var=0;
	
	for(i=1; i<N-1; i++)
	{	
		
		for(j=1; j<N-1; j++)
		{
			a=M[i][j];
			M[i][j]=(M[i][j-1]+M[i-1][j]+M[i][j+1]+M[i+1][j])/4.;
			var=(fabs(a-M[i][j])>var)?fabs(a-M[i][j]):var;
		}
	}
	
	return var;
}

void imprime(double **M, int var){
	
	int i, j;
	
	for(i=0;i<var;i++) {
		for(j=0;j<var;j++) { 
			printf("%5.2lf\t",M[i][j]);
		}	  
		puts("");
	}
}

main()
{
	FILE *fp;
	double **M;
	double var;
	int i, j, b;
	
	M = malloc( N*sizeof(double *));
	for( i = 0 ; i < N ; i++ )
		M[i] = (double *) malloc(N*sizeof(double));
	
	fp=fopen("edp2.dat", "w");
	
	contorno(M);

	b=0;
	
	do
	{
		var=relaxamento(M);
		b++;
		
	}while(var>err);
	
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
			fprintf(fp, "%lf\t", M[i][j]);
		
		fprintf(fp, "\n");
	}
	
	printf("%d iterações %lf var\n\n", b, var);
}
