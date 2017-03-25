#include "MultiLane.h"
#include <math.h>
//shadow_position[0]=>?影高度
//shadow_position[1]=>?道?
//shadow_position[2]=>?影起?
//shadow_position[3]=>?影??

void parallax(unsigned char *input_y_L,unsigned char *input_y_R,short hough_record[][30],short hough_line_record[][1000],short *shadow_position,short *back_light,int width,int height)
{
	short w,h,i,j;	
	int min_SAD=0xffff,sum_y_L=0,sum_SAD=0;
	short parallax_value=0,test_hight=-1;

	short serch_block_x,serch_block_y; //搜?的block大小
	short parallax_serch_x,parallax_serch_y; //右?面搜??差起?
	short serch_point_x=0,serch_point_y=0; //搜?block起始?

	if (back_light[0])
	{
		serch_point_x=back_light[8];
		serch_point_y=back_light[5];
		serch_block_x=back_light[8]-back_light[7];
		serch_block_y=back_light[5]-back_light[4];
		parallax_serch_x=back_light[8];
		parallax_serch_y=back_light[5];
	}
	else
	{
		parallax_serch_x=shadow_position[3];
		parallax_serch_y=shadow_position[0]-(shadow_position[1]>>4);
		serch_point_x=shadow_position[3];
		serch_point_y=(shadow_position[0]-(shadow_position[1]>>4));
		serch_block_x=(shadow_position[3]-shadow_position[2]);
		serch_block_y=(shadow_position[1]>>4);
	}

	for (h=(parallax_serch_y-20);h<(parallax_serch_y+20);h++) //右?面高度上下各20PIXEL
	{
		for (w=(parallax_serch_x);w>(parallax_serch_x-60);w--) 
		{
			for (j=0;j < serch_block_y;j++)
			{
				for (i=0;i < serch_block_x;i++)
				{
					sum_SAD+=(abs(input_y_L[(serch_point_y+j)*width+(serch_point_x-i)]-input_y_R[(h+j)*width+(w-i)]));
				}
			}
			if (min_SAD > sum_SAD)
			{
				min_SAD=sum_SAD;					
				if (shadow_position[0]) parallax_value=abs(shadow_position[3]-w);
				else if (back_light[0]) parallax_value=abs(back_light[8]-w);
				test_hight=h+j;
				hough_record[1][21]=parallax_value;
			}
			sum_SAD=0;
		}
	}		
}
