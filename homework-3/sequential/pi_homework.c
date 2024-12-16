#include <stdio.h>
#include <time.h>
               
#define PI25DT 3.141592653589793238462643


int pi_Sec(int intervals_arg)
{
    long int i, intervals = intervals_arg;
    double x, dx, f, sum, pi;
    double time2;
    
    time_t time1 = clock();

    printf("Number of intervals: %ld\n", intervals);

    sum = 0.0;
    dx = 1.0 / (double) intervals;

    for (i = 1; i <= intervals; i++) {
        x = dx * ((double) (i - 0.5));
        f = 4.0 / (1.0 + x*x);
        sum = sum + f;
    }
         
    pi = dx*sum;

    time2 = (clock() - time1) / (double) CLOCKS_PER_SEC;

    printf("Computed PI %.24f\n", pi);
    printf("The true PI %.24f\n\n", PI25DT);
    printf("Elapsed time (s) = %.2lf\n", time2);

    return time2;
}

int main(int argc, char const *argv[])
{
    int intervals[5] = {1e6, 1e7, 1e8, 1e9, 1e10};
    int intervalsN = 5;

    FILE *fp;

    fp = fopen("results_sec.csv", "w");
    if (fp == NULL) return 1;

    int t;
    for (t = 0; t < intervalsN; t++) {
        printf("Starting test with %d intervals\n", intervals[t]);
        fprintf(fp, "%f;", pi_Sec(intervals[t]));
    }

    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}
