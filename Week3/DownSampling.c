#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define R 0
#define G 1
#define B 2

#define Y 0
#define U 1
#define V 2

int main()
{
	unsigned char Buffer[512][512][3],YUV_Image[512][512][3];	
	FILE *fp,*fTransformed,*fRGB;
	unsigned char c;
	int temp,p1,p2,p3;
	int rowIndex,columnIndex;
	int count;

	fp=fopen("Lenna.bmp","r");
	if(fp==NULL)
	{
		printf("\nError opening file");
		exit(0);
	}

	fTransformed = fopen("Transformed.bmp","w+");
	fRGB = fopen("DownSampled420.bmp","w+");

	for(count=0;count<54;count++)
	{
		c = fgetc(fp);
		fputc(c,fTransformed);
		fputc(c,fRGB);
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
			p1 = Buffer[rowIndex][columnIndex][B];
			p2 = Buffer[rowIndex][columnIndex][G];
			p3 = Buffer[rowIndex][columnIndex][R];

			
				temp = (int)((0.299* (float)p3)+(0.587*(float)p2)+(0.114*(float)p1));	
				if(temp<0)temp=0;
				if(temp>255)temp=255;
				YUV_Image[rowIndex][columnIndex][Y]=(unsigned char)temp;

			if(columnIndex%2==0 && rowIndex%2==0)
			{	
				temp = (int)((-0.168736*(float)p3)+(-0.331265*(float)p2)+(0.500002*(float)p1)) + 128;
				if(temp<0)temp=0;
				if(temp>255)temp=255;
				YUV_Image[rowIndex][columnIndex][U]=(unsigned char)temp;

				temp = (int)((0.5*(float)p3)+(-0.418688*(float)p2)+(-0.081312*(float)p1)) + 128;
				if(temp<0)temp=0;
				if(temp>255)temp=255;
				YUV_Image[rowIndex][columnIndex][V]=(unsigned char)temp;
			}

			else
			{
				if(columnIndex%2 != 0)
				{
					YUV_Image[rowIndex][columnIndex][V]=YUV_Image[rowIndex][columnIndex-1][V];
					YUV_Image[rowIndex][columnIndex][U]=YUV_Image[rowIndex][columnIndex-1][U];
				}
				if(rowIndex%2 != 0)
				{
					YUV_Image[rowIndex][columnIndex][V]=YUV_Image[rowIndex-1][columnIndex][V];
					YUV_Image[rowIndex][columnIndex][U]=YUV_Image[rowIndex-1][columnIndex][U];
				}
			}		
			fputc(YUV_Image[rowIndex][columnIndex][V],fTransformed);
			fputc(YUV_Image[rowIndex][columnIndex][U],fTransformed);
			fputc(YUV_Image[rowIndex][columnIndex][Y],fTransformed);
		}
	}

	fclose(fTransformed);

	for(rowIndex=0;rowIndex<512;rowIndex++)
	{
		for(columnIndex=0;columnIndex<512;columnIndex++)
		{
			p1 = YUV_Image[rowIndex][columnIndex][V]-128;
			p2 = YUV_Image[rowIndex][columnIndex][U]-128;
			p3 = YUV_Image[rowIndex][columnIndex][Y];

			temp = (int)(((float)p3)+(1.4021*(float)p1));	
			if(temp<0)temp=0;
			if(temp>255)temp=255;
			Buffer[rowIndex][columnIndex][R]=(unsigned char)temp;

			temp = (int)(((float)p3)+(-0.34414*(float)p2)+(-0.71414*(float)p1));
			if(temp<0)temp=0;
			if(temp>255)temp=255;
			Buffer[rowIndex][columnIndex][G]=(unsigned char)temp;

			temp = (int)(((float)p3)+(1.7718*(float)p2));
			if(temp<0)temp=0;
			if(temp>255)temp=255;
			Buffer[rowIndex][columnIndex][B]=(unsigned char)temp;

			fputc(Buffer[rowIndex][columnIndex][B],fRGB);
			fputc(Buffer[rowIndex][columnIndex][G],fRGB);
			fputc(Buffer[rowIndex][columnIndex][R],fRGB);
		}
	}
	fclose(fRGB);
	return 0;
}
