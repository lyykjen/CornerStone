#include "MultiLane.h"
#include <math.h>
#include <stdio.h>
#include <memory.h>
/*hough_record
[0][]=>储存前一张r
[1][]=>储存前一张角度
[2][]=>计算是否连续三张找错车道线
[3][]=>计算是否连续三张找不到车道线
[4][]=>存放车道交错点位置高度
[5][]=>LDWS [0]=>R [1]=>L
[6][]=>存放车道交错点位置宽度
[7][]=>判断任意一条曲线是否选择直线
[8][]=>前一张画面距离（for 车底阴影）
[9][]=>白天、夜晚判断（1 夜晚 0 白天）
[10][]=>前一张画面距离（for 车尾灯）
[11][]=>.
[12][]=>判断车道线连续性，0代表没有连续性，1代表虚线，2代表实线
[13][]=>
[14][]=>三张做一次counter
*/
short hough_combine(unsigned char * lane,short hough_record[][30],short hough_line_record[][1000],short *hough_r,unsigned char *hough_angle,int width,int height)
{
	short i,j;
	short r,angle;
	short max_r[4]={0},max_angle[4]={0};
	short temp_max[4]={10,10,10,10},lock[4]={0};
	static short r_queue[3][4]={0};
	static short r_queue_count_l=0,r_queue_count_r=0,r_queue_count_lo=0,r_queue_count_ro=0;
	short lane_inside_position[6]={999,999,999,999,999,999};
	int hough_result[video_width+video_height][180]={0};
	
	for (j=video_v_higher;j<video_v_lower;j++)
	{
		for (i=video_h_left_limit;i<video_h_right_limit;i++)
		{
			if (lane[j*width+i]==255)
			{
				if (i<width>>1)
				{
					/*for (angle=1 ; angle < 30 ; angle+=3)				
					{
						r=cos_matrix[angle*cos_matrix_width+i]+cos_matrix[(90-angle)*cos_matrix_width+j];
						hough_result[r][angle]+=1;
					}*/

					for (angle=30 ; angle < 90 ; angle+=2)				
					{
						r=cos_matrix[angle*cos_matrix_width+i]+cos_matrix[(90-angle)*cos_matrix_width+j];
						hough_result[r][angle]+=1;
					}
				}
				else
				{					
					for (angle=91 ; angle < 150 ; angle+=2)					
					{
						r=cos_matrix[angle*cos_matrix_width+i]+cos_matrix[(angle-90)*cos_matrix_width+j]+width;
						hough_result[r][angle]+=1;
					}

					/*for (angle=150 ; angle < 180 ; angle+=3)					
					{
						r=cos_matrix[angle*cos_matrix_width+i]+cos_matrix[(angle-90)*cos_matrix_width+j]+width;
						hough_result[r][angle]+=1;
					}*/					
				}
			}			
		}
	}

	//----------------------------------------------找出现次数最多-------------------------------------
	for (r=hough_r[0];r<=hough_r[1];r++)	
	{
		//for (angle=1 ; angle < 30 ; angle+=3)
		//{
		//	if (hough_result[r][angle]>=temp_max[0])		//left_lane_inside
		//	{
		//		temp_max[0] = hough_result[r][angle];				
		//		max_angle[0]=angle;
		//		max_r[0]=r;				
		//	}
		//}

		for (angle=30 ; angle < 70 ; angle+=2)					
		{
			if (hough_result[r][angle]>=temp_max[0])		
			{
				temp_max[0] = hough_result[r][angle];				
				max_angle[0]=angle;
				max_r[0]=r;				
			}
		}
	}

	for (r=hough_r[4];r<=hough_r[5];r++)	
	{
		for (angle=113 ; angle < 150 ; angle+=2)					
		{
			if (hough_result[r][angle]>=temp_max[1])		//right_lane_inside
			{
				temp_max[1] = hough_result[r][angle];				
				max_angle[1]=angle;
				max_r[1]=r;				
			}
		}

		/*for (angle=150 ; angle < 180 ; angle+=3)					
		{
			if (hough_result[r][angle]>=temp_max[1])		
			{
				temp_max[1] = hough_result[r][angle];				
				max_angle[1]=angle;
				max_r[1]=r;				
			}
		}*/			
	}

	for (r=hough_r[2];r<=hough_r[3];r++)	
	{
		//for (angle=1 ; angle < 30 ; angle+=3)
		//{
		//	if (hough_result[r][angle]>=temp_max[2])		//left_lane_outside
		//	{
		//		temp_max[2] = hough_result[r][angle];				
		//		max_angle[2]=angle;
		//		max_r[2]=r;						
		//	}
		//}

		for (angle=70 ; angle < 90 ; angle+=2)					
		{
			if (hough_result[r][angle]>=temp_max[2])		
			{
				temp_max[2] = hough_result[r][angle];				
				max_angle[2]=angle;
				max_r[2]=r;					
			}
		}		
	}

	for (r=hough_r[6];r<=hough_r[7];r++)	
	{
		for (angle=91 ; angle < 130 ; angle+=2)					
		{
			if (hough_result[r][angle]>=temp_max[3])		//right_lane_outside
			{
				temp_max[3] = hough_result[r][angle];				
				max_angle[3]=angle;
				max_r[3]=r;				
			}
		}

		//for (angle=150 ; angle < 180 ; angle+=3)					
		//{
		//	if (hough_result[r][angle]>=temp_max[3])		//right_lane_outside
		//	{
		//		temp_max[3] = hough_result[r][angle];				
		//		max_angle[3]=angle;
		//		max_r[3]=r;				
		//	}
		//}			
	}
	//----------------------------------------------找出现次数最多-------------------------------------
	//hough_record[0][2]=max_r[2];
	//hough_record[1][2]=max_angle[2];
	/*hough_record[0][3]=max_r[3];
	hough_record[1][3]=max_angle[3];*/

		//找车道线位置差异，用作判断找错的依据,sampling_v_inside_position取样
		if (((max_angle[0]) && (max_r[0])) && ((max_angle[1]) && (max_r[1])))
		{
			short r1,r2,tmp[2]={999};
			for (i=video_h_left_limit;i<video_h_right_limit;i++)
			{
				r1=cos_matrix[max_angle[0]*cos_matrix_width+i]+cos_matrix[(90-max_angle[0])*cos_matrix_width+sampling_v_inside_position];
				r2=cos_matrix[max_angle[1]*cos_matrix_width+i]+cos_matrix[(max_angle[1]-90)*cos_matrix_width+sampling_v_inside_position]+width;					
				if (r1==max_r[0]) tmp[0]=i;
				if (r2==max_r[1]) tmp[1]=i;										
			}
			lane_inside_position[0]=tmp[0];
			lane_inside_position[1]=tmp[1];
		}

		if ((max_angle[0]) && (max_r[0]) &&(max_angle[2]) && (max_r[2]))
		{
			short r1,r3,tmp[2]={999};
			for (j=video_v_higher;j<video_v_lower;j++)
			{
				r1=cos_matrix[max_angle[0]*cos_matrix_width+sampling_hl_outside_position]+cos_matrix[(90-max_angle[0])*cos_matrix_width+j];
				r3=cos_matrix[max_angle[2]*cos_matrix_width+sampling_hl_outside_position]+cos_matrix[(90-max_angle[2])*cos_matrix_width+j];
				if (r1==max_r[0]) tmp[0]=j;
				if (r3==max_r[2]) tmp[1]=j;
			}
			lane_inside_position[4]=tmp[0];
			lane_inside_position[2]=tmp[1];
		}

		if ((max_angle[3]) && (max_r[3]) && (max_angle[1]) && (max_r[1]))
		{
			short r2,r4,tmp[2]={999};
			for (j=video_v_higher;j<video_v_lower;j++)
			{
				r2=cos_matrix[max_angle[1]*cos_matrix_width+sampling_hr_outside_position]+cos_matrix[(max_angle[1]-90)*cos_matrix_width+j]+width;					
				r4=cos_matrix[max_angle[3]*cos_matrix_width+sampling_hr_outside_position]+cos_matrix[(max_angle[3]-90)*cos_matrix_width+j]+width;				
				if (r2==max_r[1]) tmp[0]=j;
				if (r4==max_r[3]) tmp[1]=j;	
			}			
			lane_inside_position[5]=tmp[1];
			lane_inside_position[3]=tmp[0];			
		}

	//---------------------------------------修补------------------------------------------------------
		//-----------------------------------host left lane------------------------------------------------
		if ( (!hough_record[0][0]) && (!hough_record[0][1]) ) //等待累计三张正确
		{
			if (r_queue_count_l<2)
			{
				if (max_r[0] || max_angle[0]) r_queue[r_queue_count_l++][0]=max_r[0];
			}
			else if (r_queue_count_l==2)
			{			
				if ( (abs(max_r[0]-r_queue[0][0])<10) && (abs(max_r[0]-r_queue[1][0])<10) && (abs(r_queue[0][0]-r_queue[1][0])<10) )
				{
					if ((lane_inside_position[1]-lane_inside_position[0]>250) && (lane_inside_position[1]-lane_inside_position[0]<380) && (lane_inside_position[1]!=999) && (lane_inside_position[0]!=999))
					{
						hough_record[0][0]=max_r[0];
						hough_record[0][1]=max_angle[0];
						r_queue[0][0]=0;
						r_queue[1][0]=0;
						r_queue[2][0]=0;
						r_queue_count_l=0;
					}
					else
					{
						if (max_r[0] || max_angle[0])
						{
							max_r[0]=0;
							max_angle[0]=0;
						}
					}
				}
				else
				{
					r_queue[0][0]=r_queue[1][0];
					r_queue[1][0]=max_r[0];
				}
			}
		}
		else if ((hough_record[0][2]>2) || (hough_record[0][3]>2))  //判断是否连续错三张或三张找不到
		{
			if (r_queue_count_l<2)
			{
				if (max_r[0] || max_angle[0]) r_queue[r_queue_count_l++][0]=max_r[0];
				max_r[0]=hough_record[0][0];
				max_angle[0]=hough_record[0][1];
			}
			else if (r_queue_count_l==2)
			{	
				if ( (abs(max_r[0]-r_queue[0][0])<=10) && (abs(max_r[0]-r_queue[1][0])<=10) && (abs(r_queue[0][0]-r_queue[1][0])<=10) )
				{
					if ((lane_inside_position[1]-lane_inside_position[0]>250) && (lane_inside_position[1]-lane_inside_position[0]<380) && (lane_inside_position[1]!=999) && (lane_inside_position[0]!=999))
					{
						hough_record[0][0]=max_r[0];
						hough_record[0][1]=max_angle[0];
						hough_record[0][2]=0;
						hough_record[0][3]=0;
						r_queue[0][0]=0;
						r_queue[1][0]=0;
						r_queue[2][0]=0;
						r_queue_count_l=0;
					}
					else
					{
						if (max_r[0] || max_angle[0])
						{
							max_r[0]=hough_record[0][0];
							max_angle[0]=hough_record[0][1];
						}
					}
				}
				else
				{
					r_queue[0][0]=r_queue[1][0];
					r_queue[1][0]=max_r[0];
					max_r[0]=hough_record[0][0];
					max_angle[0]=hough_record[0][1];
				}
			}
		}
		else
		{
			if ((max_r[0]) && (max_angle[0]))
			{
				if ( (abs(hough_record[0][0]-max_r[0])>10) || (abs(hough_record[0][1]-max_angle[0])>8) )
				{
					hough_record[0][2]+=1;
					max_r[0]=hough_record[0][0];
					max_angle[0]=hough_record[0][1];
				}
				else //临⊿ó笵糴ぃ
				{
					hough_record[0][0]=max_r[0];
					hough_record[0][1]=max_angle[0];
					hough_record[0][2]=0;
					hough_record[0][3]=0;
				}
			}
			else
			{
				hough_record[0][3]+=1;
				max_r[0]=hough_record[0][0];
				max_angle[0]=hough_record[0][1];
			}
		}
		//-----------------------------------host left lane------------------------------------------------
	//-----------------------------------host right lane------------------------------------------------
	if ( (!hough_record[1][0]) && (!hough_record[1][1]) ) //单仓璸眎タ絋
	{
		if (r_queue_count_r<2)
		{
			if (max_r[1] || max_angle[1]) r_queue[r_queue_count_r++][1]=max_r[1];
		}
		else if (r_queue_count_r==2)
		{			

			if ( (abs(max_r[1]-r_queue[0][1])<10) && (abs(max_r[1]-r_queue[1][1])<10) && (abs(r_queue[0][1]-r_queue[1][1])<10) )
			{
				if ((lane_inside_position[1]-lane_inside_position[0]>250) && (lane_inside_position[1]-lane_inside_position[0]<380) && (lane_inside_position[1]!=999) && (lane_inside_position[0]!=999))
				{
					hough_record[1][0]=max_r[1];
					hough_record[1][1]=max_angle[1];
					r_queue[0][1]=0;
					r_queue[1][1]=0;
					r_queue[2][1]=0;
					r_queue_count_r=0;
				}
				else
				{
					if (max_r[1] || max_angle[1])
					{
						max_r[1]=0;
						max_angle[1]=0;
					}
				}
			}
			else
			{
				r_queue[0][1]=r_queue[1][1];
				r_queue[1][1]=max_r[1];
			}
		}
	}
	else if ((hough_record[1][2]>2) || (hough_record[1][3]>2))  //判断是否连续错三张或三张找不到
	{
		if (r_queue_count_r<2)
		{
			if (max_r[1] || max_angle[1]) r_queue[r_queue_count_r++][1]=max_r[1];
			max_r[1]=hough_record[1][0];
			max_angle[1]=hough_record[1][1];
		}
		else if (r_queue_count_r==2)
		{	
			if ( (abs(max_r[1]-r_queue[0][1])<=10) && (abs(max_r[1]-r_queue[1][1])<=10) && (abs(r_queue[0][1]-r_queue[1][1])<=10) )
			{
				if ((lane_inside_position[1]-lane_inside_position[0]>250) && (lane_inside_position[1]-lane_inside_position[0]<380) && (lane_inside_position[1]!=999) && (lane_inside_position[0]!=999))
				{
					hough_record[1][0]=max_r[1];
					hough_record[1][1]=max_angle[1];
					hough_record[1][2]=0;
					hough_record[1][3]=0;
					r_queue[0][1]=0;
					r_queue[1][1]=0;
					r_queue[2][1]=0;
					r_queue_count_r=0;
				}
				else
				{
					if (max_r[1] || max_angle[1])
					{
						max_r[1]=hough_record[1][0];
						max_angle[1]=hough_record[1][1];
					}
				}
			}
			else
			{
				r_queue[0][1]=r_queue[1][1];
				r_queue[1][1]=max_r[1];
				max_r[1]=hough_record[1][0];
				max_angle[1]=hough_record[1][1];
			}
		}
	}
	else
	{
		if ((max_r[1]) && (max_angle[1]))
		{
			if ( (abs(hough_record[1][0]-max_r[1])>10) || (abs(hough_record[1][1]-max_angle[1])>8) )
			{
				hough_record[1][2]+=1;
				max_r[1]=hough_record[1][0];
				max_angle[1]=hough_record[1][1];
			}
			else //临⊿ó笵糴ぃ
			{
				hough_record[1][0]=max_r[1];
				hough_record[1][1]=max_angle[1];
				hough_record[1][2]=0;
				hough_record[1][3]=0;
			}
		}
		else
		{
			hough_record[1][3]+=1;
			max_r[1]=hough_record[1][0];
			max_angle[1]=hough_record[1][1];
		}
	}
	//-----------------------------------host right lane------------------------------------------------
		//-----------------------------------outside left lane------------------------------------------------
		if ( (!hough_record[2][0]) && (!hough_record[2][1]) ) //单仓璸眎タ絋
		{
			if (r_queue_count_lo<2)
			{
				if (max_r[2] || max_angle[2]) r_queue[r_queue_count_lo++][2]=max_r[2];
			}
			else if (r_queue_count_lo==2)
			{			

				if ( (abs(max_r[2]-r_queue[0][2])<10) && (abs(max_r[2]-r_queue[1][2])<10) && (abs(r_queue[0][2]-r_queue[1][2])<10) )
				{
					if ((lane_inside_position[4]-lane_inside_position[2]>30) && (lane_inside_position[4]-lane_inside_position[2]<85) && (lane_inside_position[2]!=999) && (lane_inside_position[4]!=999))
					{
						hough_record[2][0]=max_r[2];
						hough_record[2][1]=max_angle[2];
						r_queue[0][2]=0;
						r_queue[1][2]=0;
						r_queue[2][2]=0;
						r_queue_count_lo=0;
					}
					else
					{
						max_r[2]=0;
						max_angle[2]=0;
					}
				}
				else
				{
					if (max_r[2] || max_angle[2])
					{
						r_queue[0][2]=r_queue[1][2];
						r_queue[1][2]=max_r[2];
					}
				}
			}
		}
		else if ((hough_record[2][2]>2) || (hough_record[2][3]>2))  //耞琌硈尿岿眎OR硈尿眎тぃ
		{
			if (r_queue_count_lo<2)
			{
				if (max_r[2] || max_angle[2]) r_queue[r_queue_count_lo++][2]=max_r[2];
				max_r[2]=hough_record[2][0];
				max_angle[2]=hough_record[2][1];
			}
			else if (r_queue_count_lo==2)
			{	
				if ( (abs(max_r[2]-r_queue[0][2])<=10) && (abs(max_r[2]-r_queue[1][2])<=10) && (abs(r_queue[0][2]-r_queue[1][2])<=10) )
				{
					if ((lane_inside_position[4]-lane_inside_position[2]>30) && (lane_inside_position[4]-lane_inside_position[2]<85) && (lane_inside_position[2]!=999) && (lane_inside_position[4]!=999))
					{
						hough_record[2][0]=max_r[2];
						hough_record[2][1]=max_angle[2];
						hough_record[2][2]=0;
						hough_record[2][3]=0;
						r_queue[0][2]=0;
						r_queue[1][2]=0;
						r_queue[2][2]=0;
						r_queue_count_lo=0;
					}
					else
					{
						if (max_r[2] || max_angle[2])
						{
							max_r[2]=hough_record[2][0];
							max_angle[2]=hough_record[2][1];
						}
					}
				}
				else
				{
					r_queue[0][2]=r_queue[1][2];
					r_queue[1][2]=max_r[2];
					max_r[2]=hough_record[2][0];
					max_angle[2]=hough_record[2][1];
				}
			}
		}
		else
		{
			if ((max_r[2]) && (max_angle[2]))
			{
				if ( (abs(hough_record[2][0]-max_r[2])>10) || (abs(hough_record[2][1]-max_angle[2])>8) )
				{
					hough_record[2][2]+=1;
					max_r[2]=hough_record[2][0];
					max_angle[2]=hough_record[2][1];
				}
				else //临⊿ó笵糴ぃ
				{
					hough_record[2][0]=max_r[2];
					hough_record[2][1]=max_angle[2];
					hough_record[2][2]=0;
					hough_record[2][3]=0;
				}
			}
			else
			{
				hough_record[2][3]+=1;
				max_r[2]=hough_record[2][0];
				max_angle[2]=hough_record[2][1];
			}
		}
		//-----------------------------------outside left lane------------------------------------------------
	//-----------------------------------outside right lane------------------------------------------------
	if ( (!hough_record[3][0]) && (!hough_record[3][1]) ) //单仓璸眎タ絋
	{
		if (r_queue_count_ro<2)
		{
			if (max_r[3] || max_angle[3]) r_queue[r_queue_count_ro++][3]=max_r[3];
		}
		else if (r_queue_count_ro==2)
		{			

			if ( (abs(max_r[3]-r_queue[0][3])<10) && (abs(max_r[3]-r_queue[1][3])<10) && (abs(r_queue[0][3]-r_queue[1][3])<10) )
			{
				if ((lane_inside_position[3]-lane_inside_position[5]>30) && (lane_inside_position[3]-lane_inside_position[5]<70) && (lane_inside_position[5]!=999) && (lane_inside_position[3]!=999))
				{
					hough_record[3][0]=max_r[3];
					hough_record[3][1]=max_angle[3];
					r_queue[0][3]=0;
					r_queue[1][3]=0;
					r_queue[2][3]=0;
					r_queue_count_ro=0;
				}
				else
				{
					max_r[3]=0;
					max_angle[3]=0;
				}
			}
			else
			{
				if (max_r[3] || max_angle[3])
				{
					r_queue[0][3]=r_queue[1][3];
					r_queue[1][3]=max_r[3];
				}
			}
		}
	}
	else if ((hough_record[3][2]>2) || (hough_record[3][3]>2))  //耞琌硈尿岿眎OR硈尿眎тぃ
	{
		if (r_queue_count_ro<2)
		{
			if (max_r[3] || max_angle[3]) r_queue[r_queue_count_ro++][3]=max_r[3];
			max_r[3]=hough_record[3][0];
			max_angle[3]=hough_record[3][1];
		}
		else if (r_queue_count_ro==2)
		{	
			if ( (abs(max_r[3]-r_queue[0][3])<=10) && (abs(max_r[3]-r_queue[1][3])<=10) && (abs(r_queue[0][3]-r_queue[1][3])<=10) )
			{
				if ((lane_inside_position[3]-lane_inside_position[5]>30) && (lane_inside_position[3]-lane_inside_position[5]<70) && (lane_inside_position[5]!=999) && (lane_inside_position[3]!=999))
				{
					hough_record[3][0]=max_r[3];
					hough_record[3][1]=max_angle[3];
					hough_record[3][2]=0;
					hough_record[3][3]=0;
					r_queue[0][3]=0;
					r_queue[1][3]=0;
					r_queue[2][3]=0;
					r_queue_count_ro=0;
				}
				else
				{
					max_r[3]=hough_record[3][0];
					max_angle[3]=hough_record[3][1];
				}
			}
			else
			{
				if (max_r[3] || max_angle[3])
				{
					r_queue[0][3]=r_queue[1][3];
					r_queue[1][3]=max_r[3];
				}
				max_r[3]=hough_record[3][0];
				max_angle[3]=hough_record[3][1];
			}
		}
	}
	else
	{
		if ((max_r[3]) && (max_angle[3]))
		{
			if ( (abs(hough_record[3][0]-max_r[3])>10) || (abs(hough_record[3][1]-max_angle[3])>8) )
			{
				hough_record[3][2]+=1;
				max_r[3]=hough_record[3][0];
				max_angle[3]=hough_record[3][1];
			}
			else //临⊿ó笵糴ぃ
			{
				hough_record[3][0]=max_r[3];
				hough_record[3][1]=max_angle[3];
				hough_record[3][2]=0;
				hough_record[3][3]=0;
			}
		}
		else
		{
			hough_record[3][3]+=1;
			max_r[3]=hough_record[3][0];
			max_angle[3]=hough_record[3][1];
		}
	}
	//-----------------------------------outside right lane------------------------------------------------
	//---------------------------------------干------------------------------------------------------

	/*max_r[0]=297;
	max_angle[0]=56;
	max_r[1]=614;
	max_angle[1]=123;

	hough_record[0][0]=max_r[0];
	hough_record[0][1]=max_angle[0];
	hough_record[1][0]=max_r[1];
	hough_record[1][1]=max_angle[1];*/



	for (j=video_v_higher;j<video_v_lower;j++)
	{	
		short r1,r2,r3,r4,tmp[4]={999,999,999,999},lock2[2]={0};
		for (i=video_h_left_limit;i<video_h_right_limit;i++)
		{		
			if ( (hough_record[0][0] || hough_record[0][1]) && (hough_record[1][0] || hough_record[1][1]) && (max_angle[0] || max_r[0]) && (max_angle[1] || max_r[1]) )
			{
				r1=cos_matrix[max_angle[0]*cos_matrix_width+i]+cos_matrix[(90-max_angle[0])*cos_matrix_width+j];
				r3=cos_matrix[max_angle[1]*cos_matrix_width+i]+cos_matrix[(max_angle[1]-90)*cos_matrix_width+j]+width;
			}

			if ((hough_record[2][0] || hough_record[2][1]) && (max_angle[2] || max_r[2])) r2=cos_matrix[max_angle[2]*cos_matrix_width+i]+cos_matrix[(90-max_angle[2])*cos_matrix_width+j];
			
			if ((hough_record[3][0] || hough_record[3][1]) && (max_angle[3] || max_r[3])) r4=cos_matrix[max_angle[3]*cos_matrix_width+i]+cos_matrix[(max_angle[3]-90)*cos_matrix_width+j]+width;	

			if ((r1==max_r[0]))
			{
				tmp[0]=i;
				if (lock[0]) hough_line_record[0][j]=i;
			}
			if ((r3==max_r[1]))
			{
				tmp[1]=i;
				if ((lock[0])&&(!lock2[0])) 
				{
					lock2[0]=1;
					hough_line_record[1][j]=i;
				}
			}
			if ((r2==max_r[2]))
			{
				tmp[2]=i;
				if (lock[2]) hough_line_record[2][j]=i;
			}
			if ((r4==max_r[3]))
			{
				tmp[3]=i;
				if ((lock[3])&&(!lock2[1])) 
				{
					lock2[1]=1;
					hough_line_record[3][j]=i;
				}
			}

			if ((abs(tmp[1]-tmp[0])<=5) && (!(lock[0]))  && (tmp[0]!=999)  && (tmp[1]!=999))
			{
				lock[0]=1;
				hough_record[0][4]=j;
				hough_record[0][6]=i;
				memset(hough_line_record[0],0,1000);
				memset(hough_line_record[1],0,1000);
				hough_line_record[0][j]=i;
				hough_line_record[1][j]=i;
			}

			if ((abs(tmp[2]-tmp[0])<=5) && (!(lock[2])) && (tmp[0]!=999)  && (tmp[2]!=999))
			{
				lock[2]=1;
				hough_record[2][4]=j;
				memset(hough_line_record[2],0,1000);
				hough_line_record[2][j]=i;
			}

			if ((abs(tmp[3]-tmp[1])<=5) && (!(lock[3])) && (tmp[3]!=999)  && (tmp[1]!=999))
			{
				lock[3]=1;
				hough_record[3][4]=j;
				memset(hough_line_record[3],0,1000);
				hough_line_record[3][j]=i;
			}
			
		}
	}		

}