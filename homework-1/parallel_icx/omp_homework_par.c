#include <omp.h>
#include "stdio.h"  // printf
#include "stdlib.h" // malloc and rand for instance. Rand not thread safe!
#include "time.h"   // time(0) to get random seed
#include "math.h"   // sine and cosine
#include "omp.h"    // openmp library like timing

// two pi
#define PI2 6.28318530718
#define R_ERROR 0.01

// omp threads
#define NUM_THREADS 4


int DFT(int idft, double *xr, double *xi, double *Xr_o, double *Xi_o, int N);
int fillInput(double *xr, double *xi, int N);
int setOutputZero(double *Xr_o, double *Xi_o, int N);
int checkResults(double *xr, double *xi, double *xr_check, double *xi_check, double *Xr_o, double *Xi_r, int N);
int printResults(double *xr, double *xi, int N);

double homework_1(int N)
{
  // Timestamps to measure performance 
  double dft_finish, idft_finish;

  // size of input array
  printf("DFTW calculation with N = %d \n", N);

  double *xr = (double *)malloc(N * sizeof(double));
  double *xi = (double *)malloc(N * sizeof(double));
  fillInput(xr, xi, N);

  double *xr_check = (double *)malloc(N * sizeof(double));
  double *xi_check = (double *)malloc(N * sizeof(double));
  setOutputZero(xr_check, xi_check, N);

  double *Xr_o = (double *)malloc(N * sizeof(double));
  double *Xi_o = (double *)malloc(N * sizeof(double));
  setOutputZero(Xr_o, Xi_o, N);

  // start timer
  double start_time = omp_get_wtime();

  // DFT
  int idft = 1;
  DFT(idft, xr, xi, Xr_o, Xi_o, N);
  dft_finish = omp_get_wtime();
  // IDFT
  //idft = -1;
  //DFT(idft, Xr_o, Xi_o, xr_check, xi_check, N);
  //idft_finish = omp_get_wtime();

  // stop timer
  /*
  double run_time = omp_get_wtime() - start_time;
  printf("DFTW computation in %f seconds\n", run_time);
  */
  // printf("DFT: %f, IDFT: %f, TOTAL: %f\n", dft_finish - start_time, idft_finish - dft_finish, idft_finish - start_time);

  // check the results: easy to make correctness errors with openMP
  // checkResults(xr, xi, xr_check, xi_check, Xr_o, Xi_o, N);

// print the results of the DFT
#ifdef DEBUG
  // printResults(Xr_o, Xi_o, N);
#endif

  // take out the garbage
  free(xr);
  free(xi);
  free(Xi_o);
  free(Xr_o);
  free(xr_check);
  free(xi_check);

  return dft_finish - start_time;
}

int main(int argc, char *argv[]) {
  int threads[8] = {1, 2, 5, 10, 20, 40, 60, 100};
  int sizes[4] = {100000, 200000, 300000, 500000};

  FILE *fp;

  fp = fopen("results.csv", "w");
  if (fp == NULL) return 1;

  int t, s;
  for (t = 0; t < 8; t++) {
    omp_set_num_threads(threads[t]);
    for (s = 0; s < 4; s++) {
      printf("Starting test with %d threads and %d size\n", threads[t], sizes[s]);
      fprintf(fp, "%f", homework_1(sizes[s]));
      if (s < 3) fprintf(fp, "; ");
    }
    fprintf(fp, "\n");
  }

  fclose(fp);

  return 0;
}

// DFT/IDFT routine
// idft: 1 direct DFT, -1 inverse IDFT (Inverse DFT)
int DFT(int idft, double *xr, double *xi, double *Xr_o, double *Xi_o, int N)
{
  int k, n;
  #pragma omp parallel
  {
    #pragma omp single
    printf("Using %d threads for main DFT operation\n", omp_get_num_threads());

    #pragma omp for private(n)
    { 
      for (k = 0; k < N; k++)
      {
        for (n = 0; n < N; n++)
        {
          // Real part of X[k]
          Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft * xi[n] * sin(n * k * PI2 / N);
          // Imaginary part of X[k]
          Xi_o[k] += -idft * xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
        }
      }
    }

    // normalize if you are doing IDFT
    if (idft == -1)
    {
      #pragma omp for
      for (n = 0; n < N; n++)
      {
        Xr_o[n] /= N;
        Xi_o[n] /= N;
      }
    }
  }
  return 1;
}

// set the initial signal
// be careful with this
// rand() is NOT thread safe in case
int fillInput(double *xr, double *xi, int N)
{
  int n;
  srand(time(0));
  for (n = 0; n < 100000; n++) // get some random number first
    rand();
  for (n = 0; n < N; n++)
  {
    // Generate random discrete-time signal x in range (-1,+1)
    xr[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
    xi[n] = ((double)(2.0 * rand()) / RAND_MAX) - 1.0;
    // constant real signal
    // xr[n] = 1.0;
    // xi[n] = 0.0;
  }
  return 1;
}

// set to zero the output vector
int setOutputZero(double *Xr_o, double *Xi_o, int N)
{
  int n;
  for (n = 0; n < N; n++)
  {
    Xr_o[n] = 0.0;
    Xi_o[n] = 0.0;
  }
  return 1;
}

// check if x = IDFT(DFT(x))
int checkResults(double *xr, double *xi, double *xr_check, double *xi_check, double *Xr_o, double *Xi_r, int N)
{
  int n;
  for (n = 0; n < N; n++)
  {
    if (fabs(xr[n] - xr_check[n]) > R_ERROR)
      printf("ERROR - xr[%d] = %f, inv(X)r[%d]=%f \n", n, xr[n], n, xr_check[n]);
    if (fabs(xi[n] - xi_check[n]) > R_ERROR)
      printf("ERROR - xi[%d] = %f, inv(X)i[%d]=%f \n", n, xi[n], n, xi_check[n]);
  }
  printf("Xre[0] = %f \n", Xr_o[0]);
  return 1;
}

// print the results of the DFT
int printResults(double *xr, double *xi, int N)
{
  int n;
  for (n = 0; n < N; n++)
    printf("Xre[%d] = %f, Xim[%d] = %f \n", n, xr[n], n, xi[n]);
  return 1;
}
