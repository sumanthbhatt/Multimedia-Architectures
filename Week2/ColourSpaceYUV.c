//---------------------------------------------------------------------------------------------------------------------------------------------
// Author     : Nirmalkumar D
// Institution: IIITB
// Semester   : Third
// Assignment : 2.1
// Program    : To Convert RGB colour space to YUV
// Details    : -Take a 512x512 .bmp image 
//              -Convert RGB to YUV
//		-Task 1: Convert back from YUV to RGB
//			 Store in a file as bmp
//		-Task 2: Convert back to RGB using only Y Component				
//			 Store in a file as bmp
//		-Task 3: Convert back to RGB using only U Component				
//			 Store in a file as bmp
//		-Task 4: Convert back to RGB using only V Component				
//			 Store in a file as bmp
//		-Task 5: Quantization of Y,U and V components seperately				
//			 Store in a file as bmp
//---------------------------------------------------------------------------------------------------------------------------------------------

//File inclusions
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

//Macros and Global defnitions
#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER
{
	uint16_t bfType;  //specifies the file type
	uint32_t bfSize;  //specifies the size in bytes of the bitmap file
	uint16_t bfReserved1;  //reserved; must be 0
	uint16_t bfReserved2;  //reserved; must be 0
	uint32_t bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER
{
	uint32_t biSize;  //specifies the number of bytes required by the struct
	int biWidth;  //specifies width in pixels
	int biHeight;  //species height in pixels
	uint16_t biPlanes; //specifies the number of color planes, must be 1
	uint16_t biBitCount; //specifies the number of bit per pixel
	uint32_t biCompression;//spcifies the type of compression
	uint32_t biSizeImage;  //size of image in bytes
	int biXPelsPerMeter;  //number of pixels per meter in x axis
	int biYPelsPerMeter;  //number of pixels per meter in y axis
	uint32_t biClrUsed;  //number of colors used by th ebitmap
	uint32_t biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;
#pragma pack(pop)


//Function Defnitions


//Main part of the program
int main()
{
	FILE *fImagePtr, *fImageYUV; //Pointer to image file
	BITMAPINFOHEADER bitmapInfoHeader; // To get header information
	unsigned int uiHeaderOffset; // Stores the header offset value to get a data
	unsigned char *pcbitmapBGR, *pcbitmapBGR_Original; //To store RGB values
	unsigned char *pcbitmapYUV; // To store YUV values
	unsigned int iH; //To keep track of each element of .bmp
	unsigned char buffer[100];// To copy headers
	unsigned int iOption;// For one of the task selection
	unsigned int iUQuant, iVQuant, temp;// To quantize the given image	
	unsigned char iULevel, iVLevel;// To quantize the given image

	//Open the image
	fImagePtr = fopen("LenaRGB.bmp","rb");

	//Check how much of Header Offset to be done to get actual image data
	fseek(fImagePtr, 14, SEEK_SET);
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fImagePtr);
	uiHeaderOffset = 14 + bitmapInfoHeader.biSize;

	//Dynamic memory allocation
	pcbitmapBGR = (unsigned char *)malloc(bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3 * sizeof(unsigned char ));
	pcbitmapBGR_Original = (unsigned char *)malloc(bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3 * sizeof(unsigned char ));
	pcbitmapYUV = (unsigned char *)malloc(bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3 * sizeof(unsigned char ));
	if(pcbitmapBGR == NULL)
	{
		printf("\nCouldnot allocate memory for RGB array ");
		free(pcbitmapBGR);
		return 1;
	} 
	if(pcbitmapBGR_Original == NULL)
	{
		printf("\nCouldnot allocate memory for RGB array ");
		free(pcbitmapBGR);
		return 1;
	} 
	if(pcbitmapYUV == NULL)
	{
		printf("\nCouldnot allocate memory for YUV array");
		free(pcbitmapYUV);
		return 1;
	} 

	//Get bitmap data
	fseek(fImagePtr, uiHeaderOffset, SEEK_SET);
	fread(pcbitmapBGR_Original, 1, (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3), fImagePtr);
	if(pcbitmapBGR_Original == NULL)
	{
		printf("Image data copying was unsuccessful\n");
		fclose(fImagePtr);
		free(pcbitmapBGR_Original);
		free(pcbitmapBGR);
		free(pcbitmapYUV);
		return 1;
	}

	//Convert RGB to YUV
	for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3); iH+=3)
	{
		pcbitmapYUV[iH] = (unsigned char)((float)pcbitmapBGR_Original[iH] * 0.114 + (float)pcbitmapBGR_Original[iH+1] * 0.487 + (float)pcbitmapBGR_Original[iH+2] * 0.299) ; 
		if(pcbitmapYUV[iH] > 255) pcbitmapYUV[iH] = 255;
		else if(pcbitmapYUV[iH] < 0) pcbitmapYUV[iH] = 0; 
		pcbitmapYUV[iH+1] = (unsigned char)((float)pcbitmapBGR_Original[iH] * (0.500002) + (float)pcbitmapBGR_Original[iH+1] * (-0.331264) + (float)pcbitmapBGR_Original[iH+2] * (-0.168736)) + 128; 
		if(pcbitmapYUV[iH+1] > 255) pcbitmapYUV[iH+1] = 255;
		else if(pcbitmapYUV[iH+1] < 0) pcbitmapYUV[iH+1] = 0; 
		pcbitmapYUV[iH+2] = (unsigned char)((float)pcbitmapBGR_Original[iH] * (-0.081312) + (float)pcbitmapBGR_Original[iH+1] * (-0.418688) + (float)pcbitmapBGR_Original[iH+2] * 0.5) + 128; 
		if(pcbitmapYUV[iH+2] > 255) pcbitmapYUV[iH+2] = 255;
		else if(pcbitmapYUV[iH+2] < 0) pcbitmapYUV[iH+2] = 0; 
	} 

	printf("\n Choose the Task\n1. Convert back to RGB\n2. Convert back to RGB with only Y\n3. Convert back to RGB with only U\n4. Convert back to RGB with only V\n5. Quantization: Sending U and V by defined number of bits to\n");
	scanf("%u", &iOption);
	switch(iOption)
	{
		case 1:
		//Task 1: Converting back to RGB
		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3) ; iH+=3)
		{
			pcbitmapBGR[iH] = (unsigned char)((float)pcbitmapYUV[iH] + (float)(pcbitmapYUV[iH+1] - 128) * 1.77180);
			if(pcbitmapBGR[iH] > 255) pcbitmapBGR[iH] = 255;
			else if(pcbitmapBGR[iH] < 0) pcbitmapBGR[iH] = 0; 
			pcbitmapBGR[iH+1] = (unsigned char)((float)pcbitmapYUV[iH] + (float)(pcbitmapYUV[iH+1] - 128) * (-0.34414) +(float)(pcbitmapYUV[iH+2]-128) *(-0.71414));
			if(pcbitmapBGR[iH+1] > 255) pcbitmapBGR[iH+1] = 255;
			else if(pcbitmapBGR[iH+1] < 0) pcbitmapBGR[iH+1] = 0; 
			pcbitmapBGR[iH+2] = (unsigned char)((float)pcbitmapYUV[iH] + (float)(pcbitmapYUV[iH+2]-128) * 1.40210);
			if(pcbitmapBGR[iH+2] > 255) pcbitmapBGR[iH+2] = 255;
			else if(pcbitmapBGR[iH+2] < 0) pcbitmapBGR[iH+2] = 0; 
		}
		printf("Converted back to RGB\n");
		break;

		case 2:
		//Task 2: Converting back to RGB with only Y component
		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3) ; iH+=3)
		{
			pcbitmapBGR[iH] = pcbitmapYUV[iH];
			pcbitmapBGR[iH+1] = pcbitmapYUV[iH];
			pcbitmapBGR[iH+2] = pcbitmapYUV[iH];
		}
		printf("Converted back to RGB with only Y\n");
		break;

		case 3:
		//Task 3: Converting back to RGB with only U component
		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3) ; iH+=3)
		{
			pcbitmapBGR[iH] = (unsigned char)((float)(pcbitmapYUV[iH+1] - 128) * 1.77180);
			if(pcbitmapBGR[iH] > 255) pcbitmapBGR[iH] = 255;
			else if(pcbitmapBGR[iH] < 0) pcbitmapBGR[iH] = 0; 
			pcbitmapBGR[iH+1] = (unsigned char)((float)(pcbitmapYUV[iH+1] - 128) * (-0.34414));
			if(pcbitmapBGR[iH+1] > 255) pcbitmapBGR[iH+1] = 255;
			else if(pcbitmapBGR[iH+1] < 0) pcbitmapBGR[iH+1] = 0; 
			pcbitmapBGR[iH+2] = (unsigned char)0;
		}
		printf("Converted back to RGB with only U\n");
		break;

		case 4:
		//Task 4: Converting back to RGB with only V component
		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3) ; iH+=3)
		{
			pcbitmapBGR[iH] = (unsigned char)0;
			pcbitmapBGR[iH+1] = (unsigned char)((float)(pcbitmapYUV[iH+2]-128) *(-0.71414));
			if(pcbitmapBGR[iH+1] > 255) pcbitmapBGR[iH+1] = 255;
			else if(pcbitmapBGR[iH+1] < 0) pcbitmapBGR[iH+1] = 0; 
			pcbitmapBGR[iH+2] = (unsigned char)((float)(pcbitmapYUV[iH+2]-128) * 1.40210);
			if(pcbitmapBGR[iH+2] > 255) pcbitmapBGR[iH+2] = 255;
			else if(pcbitmapBGR[iH+2] < 0) pcbitmapBGR[iH+2] = 0; 
		}
		printf("Converting back to RGB with only V\n");
		break;
		case 5:
		//Task 5: Quantization of Y, U and V components
		printf("Enter the quantization levels (Number of bits - Not more than 8) for U V: ");
		scanf("%d %d", &iUQuant, &iVQuant);
		printf("\n");
		temp = 0;
		iULevel = 0;
		while(temp != iUQuant)
		{
			iULevel = ( (iULevel >> 1) | 0x80) ; 
			temp += 1;
		}
		printf("iULevel = 0x%x\n", iULevel);
		temp = 0;
		iVLevel = 0;
		while(temp != iVQuant)
		{
			iVLevel = ( (iVLevel >> 1) | 0x80) ; 
			temp += 1;
		}
		printf("iVLevel = 0x%x\n", iVLevel);

		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3); iH += 3)
		{
			pcbitmapBGR[iH] = pcbitmapYUV[iH] + (unsigned char)((float)((pcbitmapYUV[iH+1] & iULevel) - 128) * 1.77180);
			if(pcbitmapBGR[iH] > 255) pcbitmapBGR[iH] = 255;
			else if(pcbitmapBGR[iH] < 0) pcbitmapBGR[iH] = 0; 
			pcbitmapBGR[iH+1] = (unsigned char)((float)pcbitmapYUV[iH] + (float)((pcbitmapYUV[iH+1] & iULevel) - 128) * (-0.34414) +(float)((pcbitmapYUV[iH+2] & iVLevel) - 128) *(-0.71414));
			if(pcbitmapBGR[iH+1] > 255) pcbitmapBGR[iH+1] = 255;
			else if(pcbitmapBGR[iH+1] < 0) pcbitmapBGR[iH+1] = 0; 
			pcbitmapBGR[iH+2] = (unsigned char)((float)pcbitmapYUV[iH] + (float)((pcbitmapYUV[iH+2] & iVLevel) - 128)  * 1.40210);
			if(pcbitmapBGR[iH+2] > 255) pcbitmapBGR[iH+2] = 255;
			else if(pcbitmapBGR[iH+2] < 0) pcbitmapBGR[iH+2] = 0; 
		}
/*		//PSNR Calculation	
		iMSE = 0;
		iMaxConverted = 0;	
		for(iH = 0; iH < (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3); iH += 3)
		{
			iOriginalPixel = (unsigned int)pcbitmapBGR_Original[iH] << 16 + (unsigned int)pcbitmapBGR_Original[iH+1] << 8 + (unsigned int)pcbitmapBGR_Original[iH+2];
			iConvertedPixel = (unsigned int)pcbitmapBGR[iH] << 16 + (unsigned int)pcbitmapBGR[iH+1] << 8 + (unsigned int)pcbitmapBGR[iH+2];
			itempMSE = itempMSE + (unsigned int)pow((iConvertedPixel - iOriginalPixel), 2);
			//Get Maximum value of the pixels
			if(iMaxConverted < iConvertedPixcel)
				iMaxConverted = iConvertedPixel;
		}
		fMSE = (float)itempMSE / (float)(bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight); 
		fPSNR = 20 * log10(iMaxConverted) - 10 * log10(fMSE) ;
		printf("PSNR is %6.4fdb\n", fPSNR); */
		break;
	}

	//Copying the YUV values to .bmp file
	fImageYUV = fopen("LenaYUV.bmp","wb");
	fseek(fImagePtr, 0, SEEK_SET);
	fread(buffer,uiHeaderOffset, 1, fImagePtr);
	fwrite(buffer,uiHeaderOffset, 1, fImageYUV);

	//Copying YUV values to .bmp
	fseek(fImageYUV, uiHeaderOffset, SEEK_SET);
	fwrite(pcbitmapBGR, 1, (bitmapInfoHeader.biHeight * bitmapInfoHeader.biWidth * 3), fImageYUV);

	//Freeing up the memory space and closing the files
	free(pcbitmapBGR);
	free(pcbitmapBGR_Original);
	free(pcbitmapYUV);
	fclose(fImagePtr);
	fclose(fImageYUV);
	return 1;
}
