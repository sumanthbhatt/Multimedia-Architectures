#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.141592654

#define BLOCK_SIZE 8

int main()
{
	int rowIndex,columnIndex,Array[BLOCK_SIZE][BLOCK_SIZE];
	int count1,count2;
	float coeff_U,coeff_V,Sum;
	float DCT[BLOCK_SIZE][BLOCK_SIZE];

	srand(time(NULL));
	printf("\n**************************************************************");
	printf("\nPrinting given matrix");
	for(rowIndex=0;rowIndex<BLOCK_SIZE;rowIndex++)
	{
		printf("\n");
		for(columnIndex=0;columnIndex<BLOCK_SIZE;columnIndex++)
		{
			Array[rowIndex][columnIndex] = rand() % 150 ;
			printf("%d\t",Array[rowIndex][columnIndex]);
		}
	}

	printf("\n**************************************************************");
	printf("\n DCT Matrix\n\n");

	for(rowIndex=0;rowIndex<BLOCK_SIZE;rowIndex++)
	{
		if(rowIndex==0)
			coeff_U = 1 / sqrt(2);
		else
			coeff_U = 1;
		for(columnIndex=0;columnIndex<BLOCK_SIZE;columnIndex++)
		{
			if(columnIndex==0)
				coeff_V = 1/sqrt(2);
			else
				coeff_V = 1;
			Sum = 0; //Reset
			for(count1=0;count1<8;count1++)
			{
				for(count2=0;count2<8;count2++)
				{
					Sum += (Array[count1][count2] * cos(PI * (2*count1 + 1) * (float)rowIndex/16) * cos (PI * (2*count2 + 1) * (float)columnIndex/16));
				}
			}

			DCT[rowIndex][columnIndex] = 0.25 * coeff_U * coeff_V * Sum;
		}
	}

	for(rowIndex=0;rowIndex<BLOCK_SIZE;rowIndex++)
	{
		printf("\n");
		for(columnIndex=0;columnIndex<BLOCK_SIZE;columnIndex++)
		{
			printf("%.2f\t",DCT[rowIndex][columnIndex]);
		}
	}
	printf("\n");
	printf("\n**************************************************************");
	printf("\n");
	printf("\n");
	return 0;
}



