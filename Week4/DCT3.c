#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.141592654

#define BLOCK_SIZE 8

int main(int argv,char** args)
{
	int rowIndex,columnIndex,Array_R[BLOCK_SIZE][BLOCK_SIZE];
	int Array_G[BLOCK_SIZE][BLOCK_SIZE];
	int Array_B[BLOCK_SIZE][BLOCK_SIZE];
	int count1,count2;
	FILE *fp;
	int g_rI,g_cI;
	float coeff_U,coeff_V,Sum;
	float DCT[BLOCK_SIZE][BLOCK_SIZE];

	sscanf(args[2],"%d",&g_rI);
	sscanf(args[3],"%d",&g_cI);

	fp = fopen(args[1],"r");
	if(fp==NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}

	for(count1 = 0; count1 < 54;count1++)
		fgetc(fp);
	
	for(count1 = 0 ; count1 < 3*(g_rI*512 + g_cI);count1++)
		fgetc(fp);
	
	for(rowIndex=0;rowIndex<8;rowIndex++)
	{
		for(columnIndex=0;columnIndex<8;columnIndex++)
		{
			Array_B[rowIndex][columnIndex] = (unsigned char)fgetc(fp);
			Array_G[rowIndex][columnIndex] = (unsigned char)fgetc(fp);
			Array_R[rowIndex][columnIndex] = (unsigned char)fgetc(fp);
		}
	}
	printf("\n**************************************************************");
	printf("\nPrinting given matrix");
	for(rowIndex=0;rowIndex<BLOCK_SIZE;rowIndex++)
	{
		printf("\n");
		for(columnIndex=0;columnIndex<BLOCK_SIZE;columnIndex++)
		{
			printf("%d\t",Array_B[rowIndex][columnIndex]);
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
					Sum += (Array_B[count1][count2] * cos(PI * (2*count1 + 1) * (float)rowIndex/16) * cos (PI * (2*count2 + 1) * (float)columnIndex/16));
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



