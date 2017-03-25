#include "MultiLane.h"
#include <math.h>
//u 114~118
//v 139~142
//

int check_lane_type(short inside_hough_record[][4],short hough_record[][4], unsigned char * input_u, unsigned char * input_v,int width,int height)
{
	short count=0,i;
	short yellow_count=0,total_count=0;
	static unsigned char sequence_frame=0;

	for (i=300;i<video_v_lower;i+=2)
	{
		if (((abs(input_u[(i>>1)*(width>>1)+(inside_hough_record[i][0]>>1)-3]-128)>10) && (abs(input_v[(i>>1)*(width>>1)+(inside_hough_record[i][0]>>1)-3]-128)>10)) ||
			((abs(input_u[(i>>1)*(width>>1)+(inside_hough_record[i][0]>>1)-5]-128)>10) && (abs(input_v[(i>>1)*(width>>1)+(inside_hough_record[i][0]>>1)-5]-128)>10)))	yellow_count++;
			total_count++;		
	}	
	
	if (yellow_count > (total_count>>1)) 
	{
		sequence_frame++;//¤j¤_50%¡A????	
	}
	else sequence_frame=0;

	if (sequence_frame>=3)	hough_record[6][2]=1;
	return sequence_frame;
}