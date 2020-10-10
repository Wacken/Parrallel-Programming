#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <pthread.h>

#include "mandelbrot_set.h"

struct pthread_args
{
	int i; int j;
	double x; double y;
	int max_iter;
	int x_stepsize; int y_stepsize;
	int palette_shift;
	unsigned char (*image)[][3];
	complex double C;
};


void* kernel(void* args);

void mandelbrot_draw(int x_resolution, int y_resolution, int max_iter,
	                double view_x0, double view_x1, double view_y0, double view_y1,
	                double x_stepsize, double y_stepsize,
	                int palette_shift, unsigned char (*image)[x_resolution][3],
						 int num_threads) {
	
	double y;
	double x;

	complex double Z;
	complex double C;

	int k;

	pthread_t *threads = (pthread_t*) malloc(num_threads *sizeof(pthread_t));
	struct pthread_args* args = (struct pthread_args*) malloc(num_threads* sizeof(struct pthread_args));
	for(int i = 0; i < num_threads; ++i)
	{
		args[0].i = i;
		args[]  
		pthread_create(&threads, NULL, kernel, args+i);
	}
	// for(int i = 0; i < num_threads; ++i)
	// {
	// 	pthread_join(threads, NULL);
	// }

	// free(threads); free(args);

	for (int i = 0; i < y_resolution; i++)
	{
		for (int j = 0; j < x_resolution; j++)
		{
			y = view_y1 - i * y_stepsize;
			x = view_x0 + j * x_stepsize;

			Z = 0 + 0 * I;
			C = x + y * I;

			k = 0;

			do
			{
				Z = Z * Z + C;
				k++;
			} while (cabs(Z) < 2 && k < max_iter);

			if (k == max_iter)
			{
				memcpy(image[i][j], "\0\0\0", 3);
			}
			else
			{
				int index = (k + palette_shift)
				            % (sizeof(colors) / sizeof(colors[0]));
				memcpy(image[i][j], colors[index], 3);
			}
		}
	}
}

void* kernel(void* args)
{
	
}
