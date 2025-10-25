#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

#define _USE_MATH_DEFINES
#define N 4

void sinx_taylor(int num_elements, int terms, double *x, double *result)
{
    int pipes[num_elements][2];
    pid_t pids[num_elements];

    for (int i = 0; i < num_elements; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe error");
            exit(1);
        }

        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork error");
            exit(1);
        }
        else if (pids[i] == 0) {
            close(pipes[i][0]);

            double value = x[i];
            double numer = x[i] * x[i] * x[i];
            double denom = 6.0;
            int sign = -1;

            for (int j = 1; j < terms; j++) {
                value += (double)sign * numer / denom;
                numer *= x[i] * x[i];
                denom *= (2.0 * j + 2.0) * (2.0 * j + 3.0);
                sign *= -1;
            }

            write(pipes[i][1], &value, sizeof(double));
            close(pipes[i][1]);
            exit(0);
        }
        else {
            close(pipes[i][1]);
        }
    }

    for (int i = 0; i < num_elements; i++) {
        read(pipes[i][0], &result[i], sizeof(double));
        close(pipes[i][0]);
        wait(NULL);
    }
}

int main()
{
    double x[N] = {0, M_PI / 6., M_PI / 3., 0.134};
    double res[N];

    sinx_taylor(N, 3, x, res);

    for (int i = 0; i < N; i++) {
        printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
        printf("sin(%.2f) by math.h       = %f\n\n", x[i], sin(x[i]));
    }

    return 0;
}

