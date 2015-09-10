#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define R 0
#define G 1
#define B 2

int main(int argv,char** args)
{
	unsigned char Buffer[512][512][3];	
	FILE *fp;
	int R_hist[256],G_hist[256],B_hist[256],Full_hist[256];
	int rowIndex,columnIndex;
	int count;
	float R_ent,G_ent,B_ent,Full_ent;
	float Pi;
	
	fp=fopen(args[1],"r");
	if(fp==NULL)
	{
		printf("\nError opening file");
		exit(0);
	}

	for(count=0;count<54;count++)
	{
		fgetc(fp);
	}

	for(count = 0; count <256; count++)
	{
		R_hist[count]=0;
		G_hist[count]=0;
		B_hist[count]=0;
		Full_hist[count]=0;
	}

	for(rowIndex=0;rowIndex<512;rowIndex++)
	{
		for(columnIndex=0;columnIndex<512;columnIndex++)
		{
			Buffer[rowIndex][columnIndex][B]=fgetc(fp);
			Buffer[rowIndex][columnIndex][G]=fgetc(fp);
			Buffer[rowIndex][columnIndex][R]=fgetc(fp);			
		}
	}

	fclose(fp);

	for(rowIndex=0;rowIndex<512;rowIndex++)
	{
		for(columnIndex=0;columnIndex<512;columnIndex++)
		{
			B_hist[(unsigned char)Buffer[rowIndex][columnIndex][B]]++;
			G_hist[(unsigned char)Buffer[rowIndex][columnIndex][G]]++;
			R_hist[(unsigned char)Buffer[rowIndex][columnIndex][R]]++;
			Full_hist[(unsigned char)Buffer[rowIndex][columnIndex][B]]++;
			Full_hist[(unsigned char)Buffer[rowIndex][columnIndex][G]]++;
			Full_hist[(unsigned char)Buffer[rowIndex][columnIndex][R]]++;
		}
	}

	R_ent = 0;
	G_ent = 0;
	B_ent = 0;
	for(count = 0; count<256;count++)
	{
		Pi = (float)R_hist[count] / (512*512);
		if(Pi!=0)
		{
			R_ent += (Pi*(log((1/Pi))/log((2))));
		}

		Pi = (float)G_hist[count] / (512*512);
		if(Pi!=0)
		{
			G_ent += (Pi*(log((1/Pi))/log((2))));
		}
	
		Pi = (float)B_hist[count] / (512*512);
		if(Pi!=0)
		{
			B_ent += (Pi*(log(1/Pi)/log(2)));
		}

		Pi = (float)Full_hist[count] / (3*512*512);
		if(Pi!=0)
		{
			Full_ent += (Pi*(log(1/Pi)/log(2)));
		}
	}
	printf("\nR_entropy = %f bits",R_ent);
	printf("\nG_entropy = %f bits",G_ent);
	printf("\nB_entropy = %f bits\n",B_ent);
	printf("\nFull Entropy = %f bits\n",Full_ent);
	return 0;
}

