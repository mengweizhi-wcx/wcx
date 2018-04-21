#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"minfilter.h"
#define HEI 12
#define WID 20

int main()
{
	//为什么来回进行类型转换
	/*char a = 60;
	double b = 60;
	printf("%c,%c",a,(char)b);*/
	//unsigned char输出格式:%hhu
	//unsigned char c = 128+40;
	//printf("%c,%u,%hhu,%d", c, c, c,c);
	unsigned char*in,*out;
	double*dark;
	FILE*fin,*fout;
	int radius=3;

	in = (unsigned char*)malloc(HEI * WID * sizeof(unsigned char));
	out = (unsigned char*)malloc(HEI * WID * sizeof(unsigned char));
	dark = (double*)malloc(HEI * WID * sizeof(double));
	

	if ((fin = fopen("in.txt", "r")) == NULL)
	{
		printf("Do not open this file!\n");
		exit(0);
	}
	for (int i = 0; i < HEI * WID; i++)
	{
		fscanf(fin, "%hhu", &in[i]);
	}
	fclose(fin);
	for (int i = 0; i < HEI * WID; i++)
	{
		dark[i] = (double)in[i];//将数据从uchar转换为double
	}
	minfilter(dark, WID,  HEI,  2*radius+1);
	for (int i = 0; i < HEI * WID; i++)
	{
		out[i] = (unsigned char)dark[i];//将数据从double转换为uchar
	}
	if ((fout = fopen("out.txt", "w")) == NULL)
	{
		printf("Do not open this file!\n");
		exit(0);
	}
	for (int i = 0; i < HEI; i++)//输出矩阵到out.txt
		for (int j = 0; j < WID; j++)
			if (j==WID-1)
				fprintf(fout, "%hhu\n", out[i*WID+j]);
			else
				fprintf(fout, "%hhu\t", out[i*WID+j]);
	fclose(fout);
		
	
	



	free(in);
	free(out);
	free(dark);
	/*system("pause");*/
	return 0;
}