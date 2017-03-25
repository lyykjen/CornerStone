#include "MultiLane.h"
#include <math.h>

void detect_curve(unsigned char * input_y, unsigned char * input_u, unsigned char * input_v,unsigned char * sobel,short curve_record[][video_height],short hough_record[][30],short hough_line_record[][1000],int width,int height)
{
	int i,j,k=0,ul,ur,angle;
	float br,bl;
	int max_curve[25][41][2]={0};
	int max_l_k=0,max_r_k=0,temp_l=30,temp_r=30;
	int h=0,vp=0,offset=0,max_r_offset=0,max_l_offset=0;
		
	/*hough_record[1][1]=133;
	hough_record[0][1]=66;
	hough_record[0][4]=162;
	hough_record[0][6]=356;*/

	br=-tan(3.1415926*hough_record[1][1]/180);
	bl=-tan(3.1415926*hough_record[0][1]/180);
		
	h=hough_record[0][4];
	vp=hough_record[0][6];
		
	
	for (j=hough_record[0][4]+30;j<hough_record[0][4]+150;j++)
	{	
		for (k=-5000;k<=5000;k+=1000)
		{
			for(offset=-20;offset<=20;offset++)
			{
				ul=((k/(j-h))+(bl*(j-h)))+vp+offset;
				if ((sobel[j*width+ul]))
				{
					max_curve[k/1000+12][offset+20][0]+=1;
				}
			}
		}		
	}	
	
	for (j=hough_record[0][4]+30;j<hough_record[0][4]+150;j++)
	{	
		for (k=-5000;k<=5000;k+=1000)
		{
			for(offset=-20;offset<=20;offset++)
			{
				ur=((k/(j-h))+(br*(j-h)))+vp+offset;
				if ((sobel[j*width+ur]))
				{
					max_curve[k/1000+12][offset+20][1]+=1;
				}
			}
		}		
	}
	
		
	for(offset=0;offset<41;offset++)
	{
		for (k=0;k<25;k++)
		{
			if ( (temp_l <= max_curve[k][offset][0]) )
			{
				max_l_k = (k-12)*1000;
				temp_l=max_curve[k][offset][0];		
				max_l_offset=offset-20;
			}		
			if ( (temp_r <= max_curve[k][offset][1]) )
			{
				max_r_k = (k-12)*1000;
				temp_r=max_curve[k][offset][1];	
				max_r_offset=offset-20;
			}
		}
	}
	if ( ((max_l_k>0) && (max_r_k<0)) || ((max_l_k<0) && (max_r_k>0)) )
	{		
		max_l_k=0;
		max_r_k=0;
	}	
	/*hough_record[0][10]=max_l_k;
	hough_record[0][11]=temp_l;
	hough_record[0][12]=max_r_k;
	hough_record[0][13]=temp_r;*/
	if ((!max_l_k) || (!max_r_k)) hough_record[0][7]=1;
	else hough_record[0][7]=0;
	//max_r_k=2000;
	//max_l_k=1000;

	memset(curve_record,0,video_height*2*sizeof(short));
	for (j=hough_record[0][4]+1;j<hough_record[0][4]+150;j++)
	{					
		ul=((max_l_k/(j-h))+(bl*(j-h)))+vp-5;
		ur=((max_r_k/(j-h))+(br*(j-h)))+vp+max_r_offset;
		if ((ul>=0) && (ul<=640)) curve_record[0][j]=ul;
		if ((ur>=0) && (ur<=640)) curve_record[1][j]=ur;			
	}
	
}