#include "ProgramOptions.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

typedef struct
{
	int x;
	int y;
	double elevation;
} Point;

Point* g_data_buffer;
int g_maxX, g_minX, g_maxY, g_minY;

void inline DataBufferInit(int size)
{
	g_data_buffer = (Point*)malloc(size*sizeof(Point));
}

void ReadFileData(char* filename)
{
	FILE* fp;
	int x, y;
	fp = fopen(filename, "r");
	if (!fp)
		perror("outliers:Couldn't Open File");


	fscanf(fp, "%d, %d\n", &g_maxX, &g_maxY);
	printf("x = %d; y = %d; x*y = %d\n", g_maxX, g_maxY, g_maxX*g_maxY);
	DataBufferInit(g_maxX*g_maxY);


	for (y = 0; y < g_maxY; y++)
	{
		for (x = 0; x < g_maxX; x++)
		{
			double elevation;
			Point* p = &g_data_buffer[(y*g_maxX+x)];
			fscanf(fp, "%lf\n", &elevation);
			p->x = x;
			p->y = y;
			p->elevation = elevation;
		}
	}

	fclose(fp);
}

void InitOCL()
{
#ifdef OPENCL
#endif //OPENCL
}

void DeInitOCL()
{
#ifdef OPENCL
#endif //OPENCL
}

void DataToGPU()
{
#ifdef OPENCL
#endif //OPENCL
}

void DataFromGPU()
{
#ifdef OPENCL
#endif //OPENCL
}


void DoCalculations()
{
	//for now, this will be a subtract by 1.0 function
#ifdef OPENCL
#else
	int i;
	for (i = 0; i < g_maxX*g_maxY; i++)
	{
		g_data_buffer[i].elevation = sqrt(g_data_buffer[i].elevation);
	}
#endif //OPENCL
}


void DisplayData()
{
	int x,y;
	for (y = 0; y < g_maxY; y++)
	{
		printf("%d\t", y);
		for (x = 0; x < g_maxX; x++)
		{
			printf("%lf\t", g_data_buffer[(y*g_maxX+x)].elevation);
		}
		printf("\n");
	}
}

int main(int argc, char** argv)
{
	time_t calcBeginTime = 0;
	time_t calcEndTime = 0;
	assert(argc >= 2);
	ReadFileData(argv[1]);
	printf("\nDone Reading\n");
	InitOCL();
	//DisplayData();

	//start timing
	{
		calcBeginTime = clock();

		DataToGPU();

		//do calculations
		DoCalculations();

		DataFromGPU();

		//end timing
		calcEndTime = clock();
	}

	printf("\nDone Calculating\n");
	//DisplayData();
	DeInitOCL();
	printf("timing: %d\n", (int)(calcEndTime - calcBeginTime));

	free(g_data_buffer);
	return 0;
}
