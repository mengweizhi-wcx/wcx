#include<stdlib.h>
minfilter(double*dark, int wid, int hei, int mask)
{
	double*g_wid, *h_wid;
	int row;

	row = wid;
	if (wid%mask!=0)
		row = wid - wid%mask + mask;//g和h的width必须是mask的整数倍
	g_wid = (double*)malloc(row*sizeof(double));
	h_wid = (double*)malloc(row*sizeof(double));
	//min行
	for (int i = 0; i < hei; i++)
	{
		int rear;//每一个mask的尾部标记
		for (int j = 0; j < row; j++)
		{
			//（1）g_wid和h_wid初始化
			if (j < row - mask)//处理前row/mask*mask个值
			{
				if (j%mask == 0)
				{
					g_wid[j] = dark[i*wid+j];
					h_wid[j + mask - 1] = dark[i*wid + j + mask - 1];
					rear = j + mask - 1;
				}
				else
				{
					g_wid[j] = g_wid[j - 1] < dark[i*wid + j] ? g_wid[j - 1] : dark[i*wid + j];
					h_wid[rear - j%mask] = h_wid[rear - j%mask + 1] < dark[i*wid + rear - j%mask] ?
						h_wid[rear - j%mask + 1] : dark[i*wid + rear - j%mask];
				}
			}
			else
			{
				if (j<=wid-1)//处理row-mask和wid-1之间的值
				{
					if (j == row - mask)
					{
						g_wid[j] = dark[i*wid + j];
						h_wid[wid - 1] = dark[i*wid + wid - 1];
					}
					else
					{
						g_wid[j] = g_wid[j - 1] < dark[i*wid + j] ? g_wid[j - 1] : dark[i*wid + j];
						h_wid[wid - (j - rear)] = h_wid[wid - (j - rear) + 1] < dark[i*wid + wid - (j - rear)] ?
							h_wid[wid - (j - rear) + 1] : dark[i*wid + wid - (j - rear)];
					}
				}
				else//处理row-wid的值
				{
					g_wid[j] = g_wid[wid - 1];
					h_wid[j] = 255.0;
				}
			}
		}
		//（2）行取min值
		for (int x = 0; x < wid; x++)
		{
			if (x < mask / 2)
			{
				dark[i*wid + x] = g_wid[x + mask / 2];
			}
			else if (x >= mask / 2 && x <= row - 1 - mask / 2)
			{
				dark[i*wid + x] = g_wid[x + mask / 2] < h_wid[x - mask / 2] ?
					g_wid[x + mask / 2] : h_wid[x - mask / 2];
			}
			else
			{
				dark[i*wid + x] = h_wid[x - mask / 2];
			}
		}
	}
	free(g_wid);
	free(h_wid);




	//////////////////////////////////////////
	double*g_hei, *h_hei;
	int col;

	col = hei;
	if (hei%mask != 0)
		col = hei - hei%mask + mask;//g和h的height必须是mask的整数倍
	g_hei = (double*)malloc(col*sizeof(double));
	h_hei = (double*)malloc(col*sizeof(double));
	//min列
	for (int i = 0; i < wid; i++)
	{
		int rear;//每一个mask核的尾部标记
		for (int j = 0; j < col; j++)
		{
			//（1）g_hei和h_hei初始化
			if (j < col - mask)//处理前col/mask*mask个值
			{
				if (j%mask == 0)
				{
					g_hei[j] = dark[j*wid + i];
					h_hei[j + mask - 1] = dark[(j + mask - 1)*wid + i];
					rear = j + mask - 1;//rear标记的时h_hei的每个核的末位置
				}
				else
				{
					g_hei[j] = g_hei[j - 1] < dark[j*wid + i] ? g_hei[j - 1] : dark[j*wid + i];
					h_hei[rear - j%mask] = h_hei[rear - j%mask + 1] < dark[(rear - j%mask)*wid + i] ?
						h_hei[rear - j%mask + 1] : dark[(rear - j%mask)*wid + i];
				}
			}
			else
			{
				if (j <= hei - 1)//处理col-mask和hei-1之间的值（最后一个mask的前半部分）
				{
					if (j == col - mask)
					{
						g_hei[j] = dark[j*wid + i];
						h_hei[hei - 1] = dark[(hei - 1)*wid + i];
					}
					else
					{
						g_hei[j] = g_hei[j - 1] < dark[j*wid + i] ? g_hei[j - 1] : dark[j*wid + i];
						h_hei[hei - (j - rear)] = h_hei[hei - (j - rear) + 1] < dark[(hei - (j - rear))*wid + i] ?
							h_hei[hei - (j - rear) + 1] : dark[(hei - (j - rear))*wid + i];
					}
				}
				else//处理col-hei的值
				{
					g_hei[j] = g_hei[hei - 1];
					h_hei[j] = 255.0;
				}
			}
		}
		//（2）列取min值
		for (int x = 0; x < hei; x++)
		{
			if (x < mask / 2)
			{
				dark[x*wid + i] = g_hei[x + mask / 2];
			}
			else if (x >= mask / 2 && x <= col - 1 - mask / 2)
			{
				dark[x*wid + i] = g_hei[x + mask / 2] < h_hei[x - mask / 2] ?
					g_hei[x + mask / 2] : h_hei[x - mask / 2];
			}
			else
			{
				dark[x*wid + i] = h_hei[x - mask / 2];
			}
		}
	}
	free(g_hei);
	free(h_hei);

}