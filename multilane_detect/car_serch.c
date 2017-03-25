#include "MultiLane.h"
#include <math.h>

//shadow_position[0]=j;
//shadow_position[1]=hough_line_record[1][j] - hough_line_record[0][j];
//shadow_position[2]=shadow_start;
//shadow_position[3]=shadow_end;

void car_serch(short hough_record[][30],short hough_line_record[][1000],short curve_record[][480],unsigned char * sobel, unsigned char * input_y, unsigned char * input_u, unsigned char * input_v,short *shadow_position,int width,int height)
{
	short i,j,k;
	//---------Host lane------------------
	short draw_en=0,track_start,track_end,serch_i_start,serch_i_end;
	short threshold_dif=0,mistake_count=0;
	static short error_count=0,not_found_count=0;	
	//---------Host lane------------------

	if (shadow_position[0])
	{
		track_start=shadow_position[0]+20;
		track_end=shadow_position[0]-20;
	}
	else
	{
		track_start=video_v_lower;
		track_end=hough_record[0][4]+10;
	}
	
	for (j=track_start;j > track_end;j--)
	{		
		short shadow_count=0,shadow_start=999,shadow_end=999,lock=0;
		short light_dif=0,shadow_error=0,mistake=0,offset_light=0;
		if ((j>=hough_record[0][4]+150) || (hough_record[0][7]))
		{
			serch_i_start=hough_line_record[0][j];
			if (hough_line_record[1][j]) serch_i_end=hough_line_record[1][j];
			else serch_i_end=630;
		}
		else
		{
			if ( ((curve_record[1][j]-curve_record[0][j]) < 10) && ((hough_line_record[1][j]-hough_line_record[0][j]) >= 10) )
			{
				serch_i_start=hough_line_record[0][j];
				serch_i_end=hough_line_record[1][j];
				
			}
			else
			{
				serch_i_start=curve_record[0][j];
				serch_i_end=curve_record[1][j];
			}
		}

		if (j>200) //较近的距离
		{			
			if (j>220) //分段阈值，较近的地方阴影比较暗
			{
				for (i=serch_i_start;i < serch_i_end;i++)
				{
					if ((input_y[(j+1)*width+(i)]<=((shadow_th>>1)+10)) && (input_y[(j)*width+(i)]<=((shadow_th>>1)+10)) && (input_y[(j-1)*width+(i)]<=((shadow_th>>1)+10-threshold_dif)) )
					{
						if (!lock) 
						{
							shadow_start=i;
							lock=1;
						}
						shadow_end=i;
						shadow_count++;
					}
				}
			}
			else //较远的地方阴影比较亮
			{
				for (i=serch_i_start;i < serch_i_end;i++)
				{
					if ((input_y[(j+1)*width+(i)]<=(shadow_th)) && (input_y[(j)*width+(i)]<=(shadow_th)) && (input_y[(j-1)*width+(i)]<=(shadow_th)) )
					{
						if ((!lock) || (shadow_error>=5))
						{
							shadow_start=i;
							lock=1;
							shadow_error=0;
						}
						shadow_end=i;
						shadow_count++;
					}
					else
					{
						shadow_error++;
					}
				}
			}

			if ((shadow_count > ((serch_i_end - serch_i_start)>>2) ) && (shadow_count) && ((shadow_end-shadow_start)>=8) ) //阴影长度大于车道宽四分之一
			{				
				shadow_error=0;
				for (i=shadow_start;i < shadow_end;i++)
				{
					if ( ((!serch_i_start) || (serch_i_end==630)) && (shadow_count>((shadow_end-shadow_start)>>1)) ) offset_light=20;
					else offset_light=0;
					if ( ((input_y[(j+15+offset_light)*width+(i)]-input_y[(j)*width+(i)])>25) ) 
					{
						light_dif++;						
					}
					else shadow_error++;
				}
				if ( ( (light_dif > ((serch_i_end - serch_i_start)>>2))&&((light_dif>=shadow_error+5)||(((shadow_end-shadow_start)*5)>=((serch_i_end - serch_i_start)<<2))) ) || (((light_dif > ((serch_i_end - serch_i_start)/6)) || (shadow_count > ((serch_i_end - serch_i_start)/3))) && ((serch_i_end - serch_i_start)>250) && (light_dif)) )
				{	
					if ( (((abs(j-shadow_position[0])<15) || (!shadow_position[0])) && ((abs(shadow_start-shadow_position[2])<10) ||(!shadow_position[2]))) || (light_dif > ((serch_i_end - serch_i_start)>>1)) || (shadow_count > ((serch_i_end - serch_i_start)/3)) )
					{
						if (((shadow_count > ((serch_i_end - serch_i_start)/3))) && ((serch_i_end - serch_i_start)>250))
						{
							int shadow_count_2=0;
							for (k=(j-1);k>(j-((serch_i_end - serch_i_start)>>2));k--)
							{
								for (i=serch_i_start;i<serch_i_end;i++)
								{
									if (input_y[(k)*width+(i)]<=((shadow_th>>1)+10-threshold_dif)) shadow_count_2++;
								}
							}							
							if (shadow_count_2 > ((((serch_i_end - serch_i_start)>>2)*(serch_i_end - serch_i_start))>>3)) 
							{
								mistake=1;
								threshold_dif=shadow_th>>2;
								mistake_count++;
							}
						}
						if ((!mistake) || (mistake_count>=2)) //若上面是一大块阴影，代表是杂讯，而也有例外是因为车子太大，真的车底阴影会被误判成杂讯
						{
							shadow_position[0]=j;
							shadow_position[1]=serch_i_end - serch_i_start;
							shadow_position[2]=shadow_start;
							shadow_position[3]=shadow_end;					
							
							j=track_end+1;	
						}						
					}
					else
					{
						error_count++;
						//j=track_end+1;	
					}
					not_found_count=0;
				}
			}
		}
		else //更远的阴影搜寻
		{
			for (i=serch_i_start;i < serch_i_end;i++)
			{
				if (input_y[j*width+i]<=(shadow_th))
				{
					if ((!lock) || (shadow_error>=5))
					{
						shadow_start=i;
						lock=1;
						shadow_error=0;
					}
					shadow_end=i;
					shadow_count++;
				}
				else
				{
					shadow_error++;
				}
			}

			if ( (shadow_count >= ((serch_i_end - serch_i_start)/5)) && (shadow_count) && ((shadow_end-shadow_start)>=8) )
			{
				for (i=shadow_start;i < shadow_end;i++) //比较远的地方可以车子阴影的亮度差
				{
					if (((input_y[(j-1)*width+(i)]-input_y[(j)*width+(i)])>=18) /*|| ((input_y[(j-2)*width+(i)]-input_y[(j)*width+(i)])>=18) */) light_dif++;
				}
				if ( (light_dif >= ((shadow_end-shadow_start)/3)) && (light_dif>=5)) //大于车底阴影三分之一则为车子
				{
					short k,check_2=0;					

					for (k=(j-3);k>=(j-8);k--)
					{
						for (i=(shadow_start+20);i>=(shadow_start-20);i--)
						{
							if ( (abs(input_y[(k)*width+(i)]-input_y[(k)*width+(i-2)])>=30) && (i<(shadow_end-((shadow_end-shadow_start)>>1))) )
							{
								check_2++;
								i=shadow_start-21;
							}
						}
						for (i=(shadow_end-20);i<=(shadow_end+20);i++)
						{
							if ( (abs(input_y[(k)*width+(i)]-input_y[(k)*width+(i+2)])>=30) && (i>(shadow_start+((shadow_end-shadow_start)>>1))) )
							{
								check_2++;
								i=shadow_end+21;
							}
						}
					}
						
					if (check_2>=7)
					{
						if ( ((abs(j-shadow_position[0])<15) || (!shadow_position[0])) && ((abs(shadow_start-shadow_position[2])<10) ||(!shadow_position[2])) ) 
						{
							shadow_position[0]=j;
							shadow_position[1]=serch_i_end - serch_i_start;
							shadow_position[2]=shadow_start;
							shadow_position[3]=shadow_end;
							j=track_end+1;	
						}
						else
						{
							error_count++;
							//j=track_end+1;	
						}
						not_found_count=0;
					}
					
				}
				else //另一种可能的阴影形态
				{					
					light_dif=0;					
					for (i=shadow_start;i < shadow_end;i++) //搜寻三列阴影数值相近
					{
						if ((input_y[(j+1)*width+(i)]<=(shadow_th)) && (input_y[(j)*width+(i)]<=(shadow_th)) && (input_y[(j-1)*width+(i)]<=(shadow_th)) )
						{
							light_dif++;
						}
					}
					if ( light_dif >= ((shadow_end-shadow_start)/3) )
					{
						short k,check_2=0,car_y_l=0,car_y_r=0;
						
						for (k=(j-3);k>=(j-8) && (k>track_end);k--)
						{
							for (i=(shadow_start+20);i>=(shadow_start-20);i--) //找左右边缘线
							{
								if ( (abs(input_y[(k)*width+(i)]-input_y[(k)*width+(i-2)])>=30) && (abs(input_y[(k)*width+(i)]-input_y[(k)*width+(i-4)])>=30) && (i<(shadow_end-((shadow_end-shadow_start)>>1))) && ((!car_y_l) || (abs(car_y_l-input_y[(k)*width+(i)])<8)) && (input_y[(k)*width+(i-2)]<150) )
								{
									check_2++;
									car_y_l=input_y[(k)*width+(i)];
									i=shadow_start-21;
								}
							}
							for (i=(shadow_end-20);i<=(shadow_end+20);i++)
							{
								if ( (abs(input_y[(k)*width+(i-2)]-input_y[(k)*width+(i)])>=30) && (abs(input_y[(k)*width+(i-4)]-input_y[(k)*width+(i)])>=30) && (i>(shadow_start+((shadow_end-shadow_start)>>1))) && ((!car_y_r) || (abs(car_y_r-input_y[(k)*width+(i-2)])<8))  && (input_y[(k)*width+(i)]<150) )
								{
									check_2++;
									car_y_r=input_y[(k)*width+(i-2)];
									i=shadow_end+21;
								}
							}
						}
						if (check_2>=7) //搜寻点共十点，符合七成则为车
						{													
							if ( ((abs(j-shadow_position[0])<15) || (!shadow_position[0])) && ((abs(shadow_start-shadow_position[2])<10) ||(!shadow_position[2])) )
							{
								shadow_position[0]=j;
								shadow_position[1]=serch_i_end - serch_i_start;
								shadow_position[2]=shadow_start;
								shadow_position[3]=shadow_end;
								j=track_end+1;	
							}
							else
							{
								error_count++;
								//j=track_end+1;	
							}
							not_found_count=0;
						}	
					}
				}
			}		
		}
	}
	
	if (j==(track_end))
	{
		not_found_count++;
		if (not_found_count>=3)
		{
			memset(shadow_position,0,sizeof(int)*4);
			not_found_count=0;
		}
		error_count=0;

	}
	/*else if (error_count>=3) //礚
	{
		memset(shadow_position,0,sizeof(int)*4);
		error_count=0;
	}*/

}