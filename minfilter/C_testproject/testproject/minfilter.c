#include<stdlib.h>
minfilter(double*dark, int wid, int hei, int mask)
{
	double*g_wid, *h_wid;
	int row;

	row = wid;
	if (wid%mask!=0)
		row = wid - wid%mask + mask;//g��h��width������mask��������
	g_wid = (double*)malloc(row*sizeof(double));
	h_wid = (double*)malloc(row*sizeof(double));
	//min��
	for (int i = 0; i < hei; i++)
	{
		int rear;//ÿһ��mask��β�����
		for (int j = 0; j < row; j++)
		{
			//��1��g_wid��h_wid��ʼ��
			if (j < row - mask)//����ǰrow/mask*mask��ֵ
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
				if (j<=wid-1)//����row-mask��wid-1֮���ֵ
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
				else//����row-wid��ֵ
				{
					g_wid[j] = g_wid[wid - 1];
					h_wid[j] = 255.0;
				}
			}
		}
		//��2����ȡminֵ
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
		col = hei - hei%mask + mask;//g��h��height������mask��������
	g_hei = (double*)malloc(col*sizeof(double));
	h_hei = (double*)malloc(col*sizeof(double));
	//min��
	for (int i = 0; i < wid; i++)
	{
		int rear;//ÿһ��mask�˵�β�����
		for (int j = 0; j < col; j++)
		{
			//��1��g_hei��h_hei��ʼ��
			if (j < col - mask)//����ǰcol/mask*mask��ֵ
			{
				if (j%mask == 0)
				{
					g_hei[j] = dark[j*wid + i];
					h_hei[j + mask - 1] = dark[(j + mask - 1)*wid + i];
					rear = j + mask - 1;//rear��ǵ�ʱh_hei��ÿ���˵�ĩλ��
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
				if (j <= hei - 1)//����col-mask��hei-1֮���ֵ�����һ��mask��ǰ�벿�֣�
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
				else//����col-hei��ֵ
				{
					g_hei[j] = g_hei[hei - 1];
					h_hei[j] = 255.0;
				}
			}
		}
		//��2����ȡminֵ
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