#include "MultiLane.h"
//ֻ������7~9
//[11]=0,��ȫ
//[11]=1,����ƫ
//[11]=2,����ƫ
void LDWS(short hough_record[][30],short hough_line_record[][1000],int width,int height)
{
	short i,j,lane_middle=999;	
	static short LDWS_L_count=0,LDWS_R_count=0,LDWS_L_en=0,LDWS_R_en=0,LDWS_L_right=0,LDWS_R_right=0;
	static short lock=0;
	short left_coordinate=999,right_coordinate=999;

	
	
	if (!hough_line_record[1][sampling_v_inside_position]) right_coordinate=video_h_right_limit;
	else right_coordinate=hough_line_record[1][sampling_v_inside_position];
	if (!hough_line_record[0][sampling_v_inside_position]) left_coordinate=video_h_left_limit;
	else left_coordinate=hough_line_record[0][sampling_v_inside_position];
	lane_middle=((right_coordinate-left_coordinate)>>1)+left_coordinate;

	if ( ((lane_middle-LDWS_car_middle)>LDWS_L_enable)&&(!LDWS_R_en) )		//����ƫ�ƣ���
	{
		if (LDWS_L_count>3) 
		{
			hough_record[0][5]=1;
			LDWS_L_en=1;
		}
		else LDWS_L_count++;
	}
	else	//�����ع�����
	{
		if (LDWS_L_count==0)	
		{
			LDWS_L_en=0;
			hough_record[0][5]=0;
		}
		else LDWS_L_count--;
	}

	if ( ((LDWS_car_middle-lane_middle) > LDWS_L_enable)&&(!LDWS_L_en))	//����ƫ�ƣ��ң�
	{
		if (LDWS_R_count>3) 
		{
			LDWS_R_en=1;
			lock=1;
			hough_record[1][5]=1;
		}
		else LDWS_R_count++;
	}
	else	//���D�^�k����
	{
		if (LDWS_R_count==0)	
		{
			LDWS_R_en=0;
			hough_record[1][5]=0;
		}
		else LDWS_R_count--;
	}
	

	//if ((!LDWS_R_en) && (lock)) //�V�k������A�ˬd�O�_�ݭn��_���u�]�m
	//{
	//	lock=0;
	//	hough_record[0][2]=0;
	//	hough_record[1][2]=0;
	//	hough_record[2][2]=0;
	//	hough_record[3][2]=0;
	//	hough_record[4][2]=0;
	//	hough_record[5][2]=0;
	//	hough_record[6][2]=0;
	//	hough_record[7][2]=0;
	//	hough_record[8][2]=0;
	//	hough_record[9][2]=0;
	//}	
}