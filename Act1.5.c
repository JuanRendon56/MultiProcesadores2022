#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <malloc.h>
FILE *fptr;
double** tab1;
double** tab2;
double** tab3;
double** tab4;
double** tab5;
double** tab6;

#define NUM_THREADS 6

double** euler_method(int N)
{
    printf("Numero de pasos:%d Atendido por thread:%d\n", N,omp_get_thread_num());
    double w0=0.5,a=0,b=2;
    int i;
    double** data = malloc(sizeof(double*) * 2);
    double* w = malloc(sizeof(double) * N);
    double* t = malloc(sizeof(double) * N);
    double h,ab;

    h=(b-a)/N;
    w[0] = w0;
    t[0] = a;
    for(i=0;i<N;i++)
    {
        t[i]=a+(h*i);
        w[i]=cosh(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1])); //Operaciones matematicas
    }
    *(data) = t;
    *(data+1) = w;
    return data;
}

void writeArr(double** arr, FILE *fp){
    int size = sizeof(*arr)/sizeof arr[0][0];
    printf("%d\n", size);
    fprintf(fp, "Datos que encuentra el metodo de Euler:\nN\t\tX\t\t\t  Y\n");
    for(int j = 0; j < size; j++){
      fprintf(fp, "%03i\t%.4lf\t%.4lf\n",j, arr[0][j], arr[1][j]);
    }
}

int main(){
  omp_set_num_threads(NUM_THREADS); //TIEMPO RAM
  const double startTime = omp_get_wtime();
  #pragma omp parallel
  {
      #pragma omp sections
    {
      #pragma omp section
      tab1 = euler_method(185529);
      #pragma omp section
      tab2 = euler_method(183674);
      #pragma omp section
      tab3 = euler_method(164190);
      #pragma omp section
      tab4 = euler_method(121522);
      #pragma omp section
      tab5 = euler_method(119667);
      #pragma omp section
      tab6 = euler_method(225418);
    }
  }
  const double endTime = omp_get_wtime();
  printf("En un tiempo total de (%lf)\n", (endTime - startTime));
  
  fptr=fopen("Euler_n_0.txt","w");
  writeArr(tab1,fptr);
  fclose(fptr);
  
  fptr=fopen("Euler_n_1.txt","w");
  writeArr(tab2,fptr);
  fclose(fptr);
  
  fptr=fopen("Euler_n_2.txt","w");
  writeArr(tab3,fptr);
  fclose(fptr);
  
  fptr=fopen("Euler_n_3.txt","w");
  writeArr(tab4,fptr);
  fclose(fptr);
  
  fptr=fopen("Euler_n_4.txt","w");
  writeArr(tab5,fptr);
  fclose(fptr);
  
  fptr=fopen("Euler_n_5.txt","w");
  writeArr(tab6,fptr);
  fclose(fptr);

}
