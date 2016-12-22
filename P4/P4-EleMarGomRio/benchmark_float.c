/* benchmark_float.c
Para compilar usar (-lrt: real time library): gcc benchmark_float.c -o benchmark_float –lrt
Para ejecutar use: benchmark_float longitud
*/
#include <stdlib.h> // biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h> // biblioteca donde se encuentra la función printf()
#include <time.h> // biblioteca donde se encuentra la función clock_gettime()
#define VECTOR_GLOBAL	// descomentar para que los vectores sean variables ...
						// globales (su longitud no estará limitada por el ...
						// tamaño de la pila del programa)
#ifdef VECTOR_GLOBAL
#define MAX 1000//33554432 //=2^25
double M[MAX][MAX], v1[MAX], v2[MAX];
#endif
int main(int argc, char** argv){
	int k,i,j,suma;
	struct timespec cgt1,cgt2; double ncgt; //para tiempo de ejecución
	//Leer argumento de entrada (no de componentes del vector)
	if (argc<2){
		printf("Faltan nº componentes del vector\n");
		exit(-1);
	}
	unsigned int N = atoi(argv[1]); // Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
	#ifdef VECTOR_GLOBAL
		if (N>MAX) N=MAX;
	#endif
	//Inicializar vectores
	for(i=0; i<N; i++){
		for(j=0; j<N; j++)
			M[i][j] = N*0.23452345+i*0.7643456;
	}
	for(i=0; i<N; i++){
		v1[i] = N*0.1-i*0.1;// * (rand() % 50); //los valores dependen de N
		v2[i] = 0;
	}
	suma = 0;
	// Calculo de sumas con coma flotante
	clock_gettime(CLOCK_REALTIME,&cgt1);
		for(k = 0 ; k < 1000000 ; k++)
			for(i=0; i<N; i++){
				for(j=0; j<N; j++)
					v2[i]+=M[i][j]+v1[j]+2.8957015;
					suma++;
			}
	clock_gettime(CLOCK_REALTIME,&cgt2);
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	printf("SUM - Tiempo de ejecución= %2.11f - nº elementos = %d \t",ncgt,suma);
	printf("Primer comp= %2.3f \t",v2[0] );
	printf("Ultimo comp= %2.3f \n",v2[N-1] );
	suma = 0;
	// Calculo de multiplicaciones con coma flotante
	clock_gettime(CLOCK_REALTIME,&cgt1);
		for(k = 0 ; k < 1000000 ; k++)
			for(i=0; i<N; i++){
				for(j=0; j<N; j++)
					v2[i%N]+=M[i][j]*v1[j]*2.8957015;
					suma++;
			}
	clock_gettime(CLOCK_REALTIME,&cgt2);
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	printf("MUL - Tiempo de ejecución= %2.11f - nº elementos = %d \t",ncgt,suma);
	printf("Primer comp= %2.3f \t",v2[0] );
	printf("Ultimo comp= %2.3f \n",v2[N-1] );
	suma = 0;
	// Calculo de divisiones con coma flotante
	clock_gettime(CLOCK_REALTIME,&cgt1);
		for(k = 0 ; k < 1000000 ; k++)
			for(i=0; i<N; i++){
				for(j=0; j<N; j++)
					v2[i]+=M[i][j]/v1[j]/2.8957015;
					suma++;
			}
	clock_gettime(CLOCK_REALTIME,&cgt2);
	ncgt=(double) (cgt2.tv_sec-cgt1.tv_sec)+ (double) ((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));
	printf("DIV - Tiempo de ejecución= %2.11f - nº elementos = %d \t",ncgt,suma);
	printf("Primer comp= %2.3f \t",v2[0] );
	printf("Ultimo comp= %2.3f \n",v2[N-1] );
	return 0;
}
