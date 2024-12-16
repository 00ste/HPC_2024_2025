#include <iostream>
#include <sstream>
#include <fstream>
#include <complex>
#include <chrono>
#include <omp.h>

// Ranges of the set
#define MIN_X -2
#define MAX_X 1
#define MIN_Y -1
#define MAX_Y 1

// Image ratio
#define RATIO_X (MAX_X - MIN_X)
#define RATIO_Y (MAX_Y - MIN_Y)

/*
// Image size
#define RESOLUTION 5000
#define WIDTH (RATIO_X * RESOLUTION)
#define HEIGHT (RATIO_Y * RESOLUTION)

#define STEP ((double)RATIO_X / WIDTH)
*/

#define DEGREE 2        // Degree of the polynomial
// #define ITERATIONS 300000 // Maximum number of iterations

using namespace std;

double project(int WIDTH, int HEIGHT, int STEP, int ITERATIONS)
{
    int *const image = new int[HEIGHT * WIDTH];

    const auto start = chrono::steady_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        cout << "Number of threads: " << omp_get_num_threads() << endl;

        #pragma omp for
        for (int pos = 0; pos < HEIGHT * WIDTH; pos++)
        {
            image[pos] = 0;

            const int row = pos / WIDTH;
            const int col = pos % WIDTH;
            const complex<double> c(col * STEP + MIN_X, row * STEP + MIN_Y);

            // z = z^2 + c
            complex<double> z(0, 0);
            int i;
            for (i = 1; i <= ITERATIONS; i++)
            {
                z = pow(z, 2) + c;

                // If it is convergent
                if (abs(z) >= 2)
                {
                    image[pos] = i;
                    break;
                }
            }
        }
    }
    const auto end = chrono::steady_clock::now();
    double executionTime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Time elapsed: " << executionTime << " ms." << endl;
    
    // Write the result to a file
    ofstream matrix_out;

    /*
    if (argc < 2)
    {
        cout << "Please specify the output file as a parameter." << endl;
        return -1;
    }
    */

    std::stringstream filename;
    filename << "result_" << WIDTH << "_" << HEIGHT << "_" << ITERATIONS << ".csv";
    matrix_out.open(/* argv[1] */ filename.str(), ios::trunc);
    if (!matrix_out.is_open())
    {
        cout << "Unable to open file." << endl;
        return -2;
    }

    const auto print_start = chrono::steady_clock::now();
    for (int row = 0; row < HEIGHT; row++)
    {
        for (int col = 0; col < WIDTH; col++)
        {
            matrix_out << image[row * WIDTH + col];

            if (col < WIDTH - 1)
                matrix_out << ',';
        }
        if (row < HEIGHT - 1)
            matrix_out << endl;
    }
    matrix_out.close();
    const auto print_end = chrono::steady_clock::now();
    cout << "Time elapsed: "
         << chrono::duration_cast<chrono::milliseconds>(print_end - print_start).count()
         << " seconds." << endl;

    delete[] image; // It's here for coding style, but useless
    return executionTime;
}

int main(int argc, char *argv[]) {
    int threads[8] = {1, 2, 5, 10, 20, 40, 60, 100};
    int threadsN = 8;
    int resolutions[3] = {10000, 15000, 18000};
    int resolutionsN = 3;
    int iterations[4] = {300000, 1000000, 2000000, 5000000};
    int iterationsN = 4;

    ofstream outputFile;

    int t, s, i;
    for (i = 0; i < iterationsN; i++) {
        std::stringstream filename;
        filename << "results" << iterations[i] << ".csv";
        outputFile.open(filename.str(), std::ios::out);

        for (t = 0; t < threadsN; t++) {
            omp_set_num_threads(threads[t]);
            for (s = 0; s < resolutionsN; s++) {
                int WIDTH = RATIO_X * resolutions[s];
                int HEIGHT = RATIO_Y * resolutions[s];
                int STEP = (double)RATIO_X / WIDTH;
                printf("Starting test with %d threads and %d resolution\n", threads[t], resolutions[s]);
                outputFile << project(WIDTH, HEIGHT, STEP, iterations[i]);
                if (s < resolutionsN - 1) outputFile << ";";
                }
                outputFile << std::endl;
        }

        outputFile.close();
    }

    return 0;
}

