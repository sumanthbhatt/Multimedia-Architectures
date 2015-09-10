#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define R 0
#define G 1
#define B 2

#define Y 0
#define U 1
#define V 2

int main(int argv,char** args)
{
	FILE *fSource,*fNoisySource;
	unsigned char c;
	long int PSNR=0;
	float PSNR_db;
	int Sum,Temp;
	int rowIndex,columnIndex;
	int count;

	fSource = fopen(args[1],"r");
	fNoisySource=fopen(args[2],"r");

	if(fSource == NULL || fNoisySource == NULL)
	{
		printf("File Open error\n");
		exit(0);
	}	
	for(count=0;count<54;count++)
	{
		c = fgetc(fSource);
		c = fgetc(fNoisySource);
		c++;
	}

	for(rowIndex = 0 ;rowIndex<512;rowIndex++)
	{
		for(columnIndex = 0;columnIndex<512;columnIndex++)
		{
			Temp = 0;
			Sum = (fgetc(fSource) - fgetc(fNoisySource));
			Sum *= Sum ;
			Temp += Sum;	
			Sum = (fgetc(fSource) - fgetc(fNoisySource));
			Sum *= Sum ;
			Temp += Sum;	
			Sum = (fgetc(fSource) - fgetc(fNoisySource));
			Sum *= Sum ;
			Temp += Sum;	
			PSNR += Temp;
		}
	}
	
	PSNR_db = (float)PSNR / (3*512*512);
	if(PSNR>0)
	{
		PSNR_db = (float)((20*log10((double)255))-(10*log10((double)PSNR_db)));
		printf("\nPSNR = %f dB\n",PSNR_db);
	}
	else
		printf("\nPSNR = infinity\n");
	fclose(fSource);
	fclose(fNoisySource);
	return 0;
}
