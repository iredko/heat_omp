#include <stdio.h>
#include <stdlib.h>

#include <omp.h>
#ifdef _OPENMP
int main(int argc, char **argv)
{
	double start = omp_get_wtime();
	int N = 11;
	int M = 11;
	//double T = 0.1;
	int steps;
	int threads=2;
	double T1;
	double T2;
	if(argc>1){
		N=atoi(argv[1]);
		M=atoi(argv[2]);
		steps=atoi(argv[3]);
		threads=atoi(argv[4]);
		T1=atof(argv[5]);
		T2=atof(argv[6]);
		omp_set_num_threads(threads);
	}else{
		exit(125);
	}
	double *u[2];
	double h = 1.0;
	double dt = 0.03;
	
	int un = 1;
	
	double alpha=dt/(h*h);
	/* Выделение памяти. */
	u[0] = (double*)malloc(N*M*sizeof(double));
	u[1] = (double*)malloc(N*M*sizeof(double));
#pragma omp parallel for
	for(int i=0; i<N*M; i++){
	    u[0][i]=T1;
	    u[1][i]=T1;
	}
	
	
	/* Граничные условия. */
	for(int i=0;i<N;i++){
		u[0][i]=u[1][i]=u[0][(M-1)*N+i]=u[1][(M-1)*N+i]=T2;
	}
	for(int i=0;i<M;i++){
		u[0][N*i]=u[1][N*i]=u[0][N*i+N-1]=u[1][N*i+N-1]=T2;
	}

	int x,y;
	/* Цикл интегрирования. */
	
	for (int i = 0; i < steps; i++) {
#pragma omp parallel for private(x,y)
		for (int j = 0; j < (M-2)*(N-2); j++) {
			x=j%(N-2);
			y=j/(N-2);
			u[!un][x+1+(y+1)*N] = u[un][x+1+(y+1)*N] + alpha * (u[un][x+(y+1)*N] - 4.0 * u[un][x+1+(y+1)*N] + u[un][x+2+(y+1)*N]+u[un][x+1+(y)*N]  + u[un][x+1+(y+2)*N]);
		}
		un = !un;
	}
	double end = omp_get_wtime();
	printf("%i %lf\n",threads,end-start);
	FILE* out=fopen("data.out","w");
	for(int i = 0;i < M;i++){
		for(int j = 0; j<N ;j++){
			fprintf(out,"%lf ",u[un][i*N+j]);
		}
		fprintf(out,"\n");
	}
	fclose(out);
	free(u[0]);
	free(u[1]);
	
	return 0;
}


#endif