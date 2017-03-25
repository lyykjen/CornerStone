#include "MultiLane.h"
#include <math.h>

int line_filter(unsigned char *input_y,unsigned char *input_u,unsigned char *input_v,unsigned char * sobel,unsigned char *sobel_origin,int width,int height)
{
	short i,j,k,h;
	short serch_en=0,serch_start_i=0;
	short serch_en_curve=0,serch_start_i_curve=0;
	
	for (j=video_v_higher;j < video_v_lower;j++)
	{		
		for (i=video_h_left_limit;i < video_h_right_limit;i++)
		{			
			if ( ((input_y[j*width+i+2]-input_y[j*width+i-2])>line_filter_light_out_diff) && (!serch_en) )
			{
				serch_start_i=i;
				serch_en=1;
			}
			else if ( ((input_y[j*width+i+2]-input_y[j*width+i-2])<(-line_filter_light_out_diff)) && (serch_en) )
			{
				serch_en=0;
				if ( ((i-serch_start_i)<=lane_width) &&  ((i-serch_start_i)>=8) && (j>(240)) )
				{	
					for (k=serch_start_i;k<i;k++) sobel_origin[j*width+k]=255;
					sobel[j*width+serch_start_i+((i-serch_start_i)>>1)]=255;
					i+=30;
				}
				else if ( ((i-serch_start_i)<=10) &&  ((i-serch_start_i)>=5) && (j>(200)) )
				{
					for (k=serch_start_i;k<i;k++) sobel_origin[j*width+k]=255;
					sobel[j*width+serch_start_i+((i-serch_start_i)>>1)]=255;
					i+=30;
				}
				else if ( ((i-serch_start_i)<=5) && (j>(video_v_higher)))
				{
					for (k=serch_start_i;k<i;k++) sobel_origin[j*width+k]=255;
					sobel[j*width+serch_start_i+((i-serch_start_i)>>1)]=255;
					i+=30;
				}
				serch_start_i=0;
			}			
			else if ((i-serch_start_i)>lane_width)
			{
				serch_en=0;
				serch_start_i=0;				
			}
		}
	}

	for (j=(video_v_higher+50);j < (video_v_lower-80);j++)
	{		
		for (i=video_h_left_limit>>1;i < video_h_right_limit;i++)
		{			
			if ( ((input_y[j*width+i+4]-input_y[j*width+i-4])>=10) && (!serch_en) )
			{
				serch_start_i=i;
				serch_en=1;
			}
			else if ( ((input_y[j*width+i+4]-input_y[j*width+i-4])<=(-10)) && (serch_en) )
			{
				serch_en=0;
				if ( ((i-serch_start_i)>0) && ((i-serch_start_i)<=lane_width) )
				{		
					for (k=serch_start_i-10;( (!sobel[j*width+k])&&(k < (i+10)) );k++);

					if (k==i+10) sobel[j*width+serch_start_i+((i-serch_start_i)>>1)]=255;
					i+=30;
				}				
				serch_start_i=0;
			}
			else if ((i-serch_start_i)>lane_width)
			{
				serch_en=0;
				serch_start_i=0;
			}
		}
	}

	
} 