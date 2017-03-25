#include <stdio.h>
#include <memory.h>
#include "MultiLane.h"
#include "MultiLane_video.h"
#include "MultiLane_function.h"
#include "MultiLane_parameter.h"
#include <time.h>
#include <math.h>
//#pragma comment(lib,"ws2_32.lib")
//extern void car_back_light(unsigned char *input_y, unsigned char *input_u, unsigned char *input_v, unsigned char *temp, short hough_line_record[][1000], short *back_light_record, short *shadow_position, int width, int height);
int main(void)
{
	int i,j,frame_num=1;//,tmp=0,video_count=0
	int avg_u,avg_v,avg_y;
	short run_count=2,weather[2]={0};	//[0]=day,[1]=night
	double total_time;

	total_time=clock();
	file_open();		//秨郎捌祘Α
	memory_inital();	//疠拘砰﹍て


//while (((fp_input_L = fopen(video_source_list[video_count],"rb")) !=0) && ((fp_input_R = fopen(video_source_list_R[video_count],"rb")) !=0))
//{
	//printf("%s\n",video_source_list_R[0]);
	//video_count++;
	while (fread(input_y_L,1,y_size,fp_input_L)  && fread(input_y_R,1,y_size,fp_input_R) )
	{
		printf("frame=%d\n",frame_num++);
//﹍て--------------------------------------------------
	memset(sobel,0,sizeof(unsigned char) * y_size);
	memset(lane_inside,0,sizeof(unsigned char) * y_size);
	memset(lane_outside,0,sizeof(unsigned char) * y_size);
//﹍て--------------------------------------------------
		if(!fread(input_u_L,1,uv_size,fp_input_L))
		{
			printf("Error:Can't read fp_input_L\n");
			return -1;
		}
		if(!fread(input_v_L,1,uv_size,fp_input_L))
		{
			printf("Error:Can't read fp_input_L\n");
			return -1;
		}
		if(!fread(input_u_R,1,uv_size,fp_input_R))
		{
			printf("Error:Can't read fp_input_L\n");
			return -1;
		}
		if(!fread(input_v_R,1,uv_size,fp_input_R))
		{
			printf("Error:Can't read fp_input_L\n");
			return -1;
		}
			

		if (frame_num==2)
		{
			for (j=0;j<height;j++)
			{
				for (i=0;i<width;i++)
				{
					fprintf(fp_y_excel,"%d\t",input_y_L[j*width+i]);										
				}
				fprintf(fp_y_excel,"\n");
			}
			for (j=0;j<(height>>1);j++)
			{
				for (i=0;i<(width>>1);i++)
				{					
					fprintf(fp_uv_excel,"%d\t",input_u_L[j*(width>>1)+i]);
				}
				fprintf(fp_uv_excel,"\n");
			}
			fprintf(fp_uv_excel,"\n");
			for (j=0;j<(height>>1);j++)
			{
				for (i=0;i<(width>>1);i++)
				{					
					fprintf(fp_uv_excel,"%d\t",input_v_L[j*(width>>1)+i]);						
				}
				fprintf(fp_uv_excel,"\n");
			}
		}	
		if (frame_num==611)
		{
			frame_num=frame_num;
		}
		else if (frame_num==4124)
		{
			frame_num=frame_num;
		}
		
		if (run_count==2)
		{			
			run_count=0;

			avg_u=0;
			avg_v=0;
			avg_y=0;

			for (i=200;i<456;i++) 
			{
				avg_u+=input_u_L[76160+i];
				avg_v+=input_v_L[76160+i];
				avg_y+=(input_y_L[305920+i]+input_y_L[1280+i]);
			}
			avg_u>>=8;
			avg_v>>=8;
			avg_y>>=9;
			if (((abs(avg_v-avg_u) <= 10)&&(avg_y>50))||(avg_y>110)) 
			{
				if (((!weather[0])&&(!weather[1])) || (weather[1]<5))
				{
					hough_record[0][9]=0;
					weather[1]=0;
				}
				else if ((weather[0]>=5)&&(weather[1]>=5)) memset(weather,0,sizeof(short));
				if (weather[0]<5) weather[0]+=1;
			}
			else if ((abs(avg_v-avg_u) >10)||(avg_y<=90)) 
			{
				if (((!weather[0])&&(!weather[1])) || (weather[0]<5))
				{
					hough_record[0][9]=1;
					weather[0]=0;
				}
				else if ((weather[0]>=5)&&(weather[1]>=5)) memset(weather,0,sizeof(short));
				if (weather[1]<5) weather[1]+=1;
			}
			//hough_record[0][9]=1;

			line_filter(input_y_L,input_u_L,input_v_L,sobel,lane_outside,width,height);			

			hough_combine(sobel,hough_record,hough_line_record,hough_r,hough_angle,width,height);

			if (hough_record[0][4]) detect_curve(input_y_L,input_u_L,input_v_L,lane_outside,curve_record,hough_record,hough_line_record,width,height);

			if (hough_record[0][4]) LDWS(hough_record,hough_line_record,width,height);

			/*if ( (hough_record[0][4]) && ((hough_record[0][9])||(back_light[0]))) 
			car_back_light(input_y_L,input_u_L,input_v_L,lane_inside,hough_line_record,back_light,shadow_position,width,height);*/

			//if ((hough_record[0][4]) && ((!hough_record[0][9])||(shadow_position[0]))) car_serch(hough_record,hough_line_record,curve_record,sobel,input_y_L,input_u_L,input_v_L,shadow_position,width,height);
			
			if (!shadow_position[0]) hough_record[0][8]=0; //没有阴影资讯，清除前一张距离资讯，若加入判断是否有搜寻到车尾灯，则会出错

			if (!back_light[9]) hough_record[0][10]=0;

			if ((shadow_position[0] >= parallax_serch_en) || (back_light[9] >= parallax_serch_en)) parallax(input_y_L,input_y_R,hough_record,hough_line_record,shadow_position,back_light,width,height); //视察搜寻

			//if ((shadow_position[0])||(back_light[0])) Lane_width_transfer_distance(shadow_position,back_light,input_y_L,input_u_L,input_v_L,hough_line_record,hough_record,width,height);	//想办法解决浮点	

			if (back_light[0]) draw_car_back_light();
			draw_line();
			if (hough_record[0][4]) draw_LDWS();
			if ((shadow_position[0])&&(!back_light[0])) draw_car_shadow();
			
		}
		else
		{
			draw_line();
			if (back_light[0]) draw_car_back_light();
			if (hough_record[0][4]) draw_LDWS();
			if ((shadow_position[0])&&(!back_light[0])) draw_car_shadow();
			//if ((shadow_position[0])||(back_light[0])) Lane_width_transfer_distance(shadow_position,back_light,input_y_L,input_u_L,input_v_L,hough_line_record,hough_record,width,height);	//想办法解决浮点	
			run_count++;
		}
		
		fprintf(fp_0_hough,"%d\t",hough_record[0][0]);
		fprintf(fp_0_hough,"%d\t",hough_record[0][1]);
		fprintf(fp_0_hough,"%d\t",hough_record[1][0]);
		fprintf(fp_0_hough,"%d\t",hough_record[1][1]);
		fprintf(fp_0_hough,"%d\t",hough_record[2][0]);
		fprintf(fp_0_hough,"%d\t",hough_record[2][1]);
		fprintf(fp_0_hough,"%d\t",hough_record[3][0]);
		fprintf(fp_0_hough,"%d\n",hough_record[3][1]);

		fprintf(fp_1_hough,"%d\t",hough_record[0][20]);
		fprintf(fp_1_hough,"%d\t",hough_record[0][21]);
		fprintf(fp_1_hough,"%d\t",hough_record[0][22]);
		fprintf(fp_1_hough,"%d\t",hough_record[0][23]);
		fprintf(fp_1_hough,"%d\t",hough_record[1][21]);
		fprintf(fp_1_hough,"%d\n",hough_record[1][22]);

		fprintf(fp_2_hough,"%d\t",back_light[7]+((back_light[8]-back_light[7])>>1));
		fprintf(fp_2_hough,"%d\t",hough_line_record[0][back_light[6]]);
		fprintf(fp_2_hough,"%d\t",hough_line_record[1][back_light[6]]);
		fprintf(fp_2_hough,"%d\t\t",(hough_line_record[0][back_light[6]]<(back_light[7]+((back_light[8]-back_light[7])>>1))) && (hough_line_record[1][back_light[6]]>(back_light[7]+((back_light[8]-back_light[7])>>1))) );
		fprintf(fp_2_hough,"%d\t",hough_record[0][9]);
		fprintf(fp_2_hough,"%d\t",avg_y);
		fprintf(fp_2_hough,"%d\t",avg_u);
		fprintf(fp_2_hough,"%d\n",avg_v);

		fprintf(fp_3_hough,"%d\t",back_light[0]);
		fprintf(fp_3_hough,"%d\t",back_light[1]);
		fprintf(fp_3_hough,"%d\t",back_light[2]);
		fprintf(fp_3_hough,"%d\t",back_light[3]);
		fprintf(fp_3_hough,"%d\t",back_light[4]);
		fprintf(fp_3_hough,"%d\t",back_light[5]);
		fprintf(fp_3_hough,"%d\t",back_light[6]);
		fprintf(fp_3_hough,"%d\t",back_light[7]);
		fprintf(fp_3_hough,"%d\t",back_light[8]);
		fprintf(fp_3_hough,"%d\n",back_light[9]);

		fwrite(input_y_L,1,y_size,fp_multilane);
		fwrite(input_u_L,1,uv_size,fp_multilane);
		fwrite(input_v_L,1,uv_size,fp_multilane);		
	
		memset(input_u_L,127,uv_size);
		memset(input_v_L,127,uv_size);
			
		fwrite(sobel,1,y_size,fp_sobel);
		fwrite(input_u_L,1,uv_size,fp_sobel);
		fwrite(input_v_L,1,uv_size,fp_sobel);	

		fwrite(lane_inside,1,y_size,fp_sobel_inside);
		fwrite(input_u_L,1,uv_size,fp_sobel_inside);
		fwrite(input_v_L,1,uv_size,fp_sobel_inside);

		fwrite(lane_outside,1,y_size,fp_sobel_outside);
		fwrite(input_u_L,1,uv_size,fp_sobel_outside);
		fwrite(input_v_L,1,uv_size,fp_sobel_outside);

	}
//}
	fclose(fp_sobel_inside);
	fclose(fp_sobel_outside);
	fclose(fp_multilane);
	fclose(fp_sobel);

	total_time = ((double)clock()-total_time) / CLOCKS_PER_SEC;
	printf("fps=%lf\n",(double)(frame_num-1)/total_time);
	return 0;
}

int file_open()
{
	if ((fp_input_L = fopen(source_L,"rb"))==0)
	{
		printf("Error:Can't open Source_L file\n");
		return 0;
	}
	if ((fp_input_R = fopen(source_R,"rb"))==0)
	{
		printf("Error:Can't open Source_R file\n");
		return 0;
	}
	if ((fp_sobel_inside = fopen(video_inside_lane,"wb"))==0)
	{
		printf("Error:Can't open inside_lane file\n");
		return 0;
	}
	if ((fp_sobel_outside = fopen(video_outside_lane,"wb"))==0)
	{
		printf("Error:Can't open outside_lane file\n");
		return 0;
	}
	
	if ((fp_0_hough = fopen(hough_0_out,"wb"))==0)
	{
		printf("Error:Can't open coordinate_out file\n");
		return 0;
	}	

	if ((fp_1_hough = fopen(hough_1_out,"wb"))==0)
	{
		printf("Error:Can't open coordinate_out file\n");
		return 0;
	}	

	if ((fp_2_hough = fopen(hough_2_out,"wb"))==0)
	{
		printf("Error:Can't open coordinate_out file\n");
		return 0;
	}	

	if ((fp_3_hough = fopen(hough_3_out,"wb"))==0)
	{
		printf("Error:Can't open coordinate_out file\n");
		return 0;
	}	

	if ((fp_multilane = fopen(E_maltilane,"wb"))==0)
	{
		printf("Error:Can't open multilane file\n");
		return 0;
	}

	if ((fp_sobel = fopen(sobel_out,"wb"))==0)
	{
		printf("Error:Can't open sobel file\n");
		return 0;
	}	

	if ((fp_y_excel = fopen(excel_y,"wb"))==0)
	{
		printf("Error:Can't open fp_y_excel file\n");
		return 0;
	}
	if ((fp_uv_excel = fopen(excel_uv,"wb"))==0)
	{
		printf("Error:Can't open fp_y_excel file\n");
		return 0;
	}

	return 0;
}

void memory_inital()
{
	input_y_R = (unsigned char *)malloc(sizeof(unsigned char) * y_size);
	input_u_R = (unsigned char *)malloc(sizeof(unsigned char) * uv_size);
	input_v_R = (unsigned char *)malloc(sizeof(unsigned char) * uv_size);
	input_y_L = (unsigned char *)malloc(sizeof(unsigned char) * y_size);
	input_u_L = (unsigned char *)malloc(sizeof(unsigned char) * uv_size);
	input_v_L = (unsigned char *)malloc(sizeof(unsigned char) * uv_size);	
	sobel = (unsigned char *)malloc(sizeof(unsigned char) * y_size);	
	lane_inside = (unsigned char *)malloc(sizeof(unsigned char) * y_size);
	lane_outside = (unsigned char *)malloc(sizeof(unsigned char) * y_size);
}

void draw_line()
{
	short i,j;
	for (j=hough_record[0][4]+30;j<video_v_lower;j++)
	{
		if ((hough_line_record[0][j]) && (j>=hough_record[0][4]+150))
		{
			i=hough_line_record[0][j];
			if (!hough_record[0][5])
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
			}
			else
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=100;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=200;
			}
		}
		else if ((curve_record[0][j]) && (j<hough_record[0][4]+150))
		{
			i=curve_record[0][j];
			if (!hough_record[0][5])
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
			}
			else
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=100;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=200;
			}
		}
		if ((hough_line_record[1][j]) && (j>=hough_record[0][4]+150))
		{
			i=hough_line_record[1][j];
			if (!hough_record[1][5])
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
			}
			else
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=100;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=200;
			}
		}
		else if ((curve_record[1][j]) && (j<hough_record[0][4]+150))
		{
			i=curve_record[1][j];
			if (!hough_record[1][5])
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
			}
			else
			{
				input_y_L[j*width+i]=200;
				input_u_L[(i>>1)+(j>>1)*(width>>1)]=100;
				input_v_L[(i>>1)+(j>>1)*(width>>1)]=200;
			}
		}
	}
	for (j=hough_record[2][4];j<video_v_lower;j++)
	{
		if (hough_line_record[2][j])
		{
			i=hough_line_record[2][j];
			input_y_L[j*width+i]=200;
			input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
			input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
		}
	}
	for (j=hough_record[3][4];j<video_v_lower;j++)
	{
		if (hough_line_record[3][j])
		{
			i=hough_line_record[3][j];
			input_y_L[j*width+i]=200;
			input_u_L[(i>>1)+(j>>1)*(width>>1)]=0;
			input_v_L[(i>>1)+(j>>1)*(width>>1)]=0;
		}
	}
}

void draw_LDWS()
{
	short i,j,k;

	for (j=460;j<480;j++)
	{
		for (i=LDWS_car_middle;i<(LDWS_car_middle+5);i++)
		{
			input_y_L[j*width+i]=200;
			input_u_L[(i>>1)+(j>>1)*(width>>1)]=255;
			input_v_L[(i>>1)+(j>>1)*(width>>1)]=60;
		}

		k=(hough_line_record[1][sampling_v_inside_position]-hough_line_record[0][sampling_v_inside_position])>>1;
			
		for (i=(hough_line_record[0][sampling_v_inside_position]+k);i<(hough_line_record[0][sampling_v_inside_position]+k+5);i++)
		{
			input_y_L[j*width+i]=200;
			input_u_L[(i>>1)+(j>>1)*(width>>1)]=60;
			input_v_L[(i>>1)+(j>>1)*(width>>1)]=255;
		}
	}
}

void draw_car_shadow()
{
	short i,j;
	j=shadow_position[0];
	for (i=shadow_position[2];i<(shadow_position[3]);i++)
	{
		input_y_L[j*width+i]=200;
		input_u_L[(i>>1)+(j>>1)*(width>>1)]=255;
		input_v_L[(i>>1)+(j>>1)*(width>>1)]=60;
	}
}
void draw_car_back_light()
{
	short k,mid;
	mid=back_light[0];
	for (k=back_light[1];k<back_light[2];k++)
	{
		input_y_L[k*width+mid]=255;
		input_u_L[(mid>>1)+(k>>1)*(width>>1)]=175;
		input_v_L[(mid>>1)+(k>>1)*(width>>1)]=50;
	}
	mid=back_light[3];
	for (k=back_light[4];k<back_light[5];k++)
	{
		input_y_L[k*width+mid]=255;
		input_u_L[(mid>>1)+(k>>1)*(width>>1)]=175;
		input_v_L[(mid>>1)+(k>>1)*(width>>1)]=50;
	}
	mid=back_light[6];
	for (k=back_light[7];k<back_light[8];k++)
	{
		input_y_L[mid*width+k]=255;
		input_u_L[(k>>1)+(mid>>1)*(width>>1)]=175;
		input_v_L[(k>>1)+(mid>>1)*(width>>1)]=50;
	}
	mid=back_light[9];
	for (k=back_light[7];k<back_light[8];k++)
	{
		input_y_L[mid*width+k]=255;
		input_u_L[(k>>1)+(mid>>1)*(width>>1)]=255;
		input_v_L[(k>>1)+(mid>>1)*(width>>1)]=255;
	}
}
