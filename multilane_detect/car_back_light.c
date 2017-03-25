#include "MultiLane.h"

void car_back_light(unsigned char *input_y,unsigned char *input_u,unsigned char *input_v,unsigned char *temp,short hough_line_record[][1000],short *back_light_record,short *shadow_position,int width,int height)
{
	int i;
	short j,k,h;	
	short serch_start=479,catch_en=0,too_near[4]={0},row_count=0,row=0;	
	static short error_count=0,not_found=0;
	
		
	for (i=0;i<51200;i++)	//479~400
	{
		if (input_y[serch_start*width-i]>240)
		{
			too_near[row]+=1;		
		}	
		
		if ((++row_count)==640)
		{
			row_count=0;
			if (row < 3) row++;
			if (row==3)
			{
				//printf("too_near=%d\n",(too_near[0]+too_near[1]+too_near[2]+too_near[3]));
				if ((too_near[0]+too_near[1]+too_near[2]+too_near[3]) > 1200) 
				{
					catch_en=1;
					break;
				}
				else
				{
					too_near[0]=too_near[1];
					too_near[1]=too_near[2];
					too_near[2]=too_near[3];
					too_near[3]=0;
				}
			}
		}
		
	}
	//system("pause");
		

	if (catch_en)
	{
		back_light_record[0]=150;
		back_light_record[1]=435;
		back_light_record[2]=450;

		back_light_record[3]=540;
		back_light_record[4]=435;
		back_light_record[5]=450;
		
		back_light_record[6]=442;
		back_light_record[7]=150;
		back_light_record[8]=540;

		back_light_record[9]=479;
	}
	else
	{
		for (j=(video_v_lower>>1);j>(video_v_higher>>1);j--)
		{			
			short back_light_list[8]={0},sw=0,back_dif_th=0,v_sum=0,light_limit=0;
			//j=83;

			for (i=(hough_line_record[0][j<<1]>>1)-10;i<(hough_line_record[1][j<<1]>>1)+20;i++)
			{			
				if ( (input_v[j*(width>>1)+i]>=160) && (input_v[j*(width>>1)+i+1]<160) )
				{
					v_sum=((input_v[j*(width>>1)+i-1]+input_v[j*(width>>1)+i-2]+input_v[j*(width>>1)+i-3]+input_v[j*(width>>1)+i-4])>>2);
					if (v_sum>=180) light_limit=20;
					else light_limit=0;
					for (k=2;( (input_y[(j<<1)*width+(i<<1)+k]>=220) || (input_y[((j<<1)-1)*width+(i<<1)+k]>=220) || ((input_y[((j<<1)-1)*width+(i<<1)+k+1]>=220) && (input_y[((j<<1)-1)*width+(i<<1)+k]<220)) || ((input_y[((j<<1))*width+(i<<1)+k+1]>=220) && (input_y[((j<<1))*width+(i<<1)+k]<220))) && (k<(25+light_limit));k++);
					if (k>=6)
					{
						short mid,v_limit,h_limit;					
						back_light_list[sw]=(i<<1);
						back_light_list[sw+1]=(i<<1)+k;
						mid=back_light_list[sw]+((back_light_list[sw+1]-back_light_list[sw])>>1);
						for (k=1;(input_y[((j<<1)-k)*width+mid]>=220);k++);
						back_light_list[sw+2]=(j<<1)-k;
						for (k=1;(input_y[((j<<1)+k)*width+mid]>=220) && ((abs(input_y[((j<<1)+k)*width+mid]-input_y[((j<<1)+k+1)*width+mid])<6) || (input_y[((j<<1)+k+1)*width+mid]>=250) || (input_y[((j<<1)+k)*width+mid]>=250));k++);
						back_light_list[sw+3]=(j<<1)+k;					
						if (((back_light_list[sw+3]-back_light_list[sw+2]<2) || (back_light_list[sw+3]-back_light_list[sw+2]>(25))) || (((back_light_list[sw+1]-back_light_list[sw])<10) && (light_limit)) || (((j<<1)>220) && ((back_light_list[sw+1]-back_light_list[sw-3])<50) && (sw)) )
						{
							if (abs((back_light_list[1]-back_light_list[0])-(back_light_list[5]-back_light_list[4]))<=3) 
							{
								back_light_list[sw+3]=back_light_list[sw+2]+20;
								sw+=4;
							}
							else if (back_light_list[sw+3]-back_light_list[sw+2]<(25+light_limit))
							{
								sw+=4;
							}
							else
							{
								memset(back_light_list+sw,0,sizeof(short)*4);
							}
						}
						else if ((back_light_list[sw+3]-back_light_list[sw+2]>=2) && (back_light_list[sw+3]-back_light_list[sw+2]<=(25+light_limit)))
						{
							sw+=4;					
							if ((back_light_list[1]-back_light_list[0])<15) i+=(6);								
							else i+=(6+light_limit);
							if ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>200) back_dif_th=30;  
							else back_dif_th=0; 
						}
						if (!light_limit)
						{
							v_limit=3;
							h_limit=3;
						}
						else
						{
							v_limit=7;
							h_limit=7;
						}
						if ((sw>=8) && (abs((back_light_list[3]-back_light_list[2])-(back_light_list[7]-back_light_list[6]))<=v_limit) && (abs((back_light_list[1]-back_light_list[0])-(back_light_list[5]-back_light_list[4]))<=h_limit) && ((back_light_list[4]-back_light_list[1])>=(8+back_dif_th)) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<175) && ((back_light_list[4]-back_light_list[1])<=45)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=175) ) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<165) && ((back_light_list[3]-back_light_list[2])<=10)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=165) ) && ( ((hough_line_record[0][j<<1] < (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<=165)) && ((hough_line_record[1][j<<1] > (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<=165)) ) )
						{
							if ((!back_light_record[0]) || ( (abs(back_light_record[6]-(back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1)))<(10+(not_found*3))) && ( abs((back_light_record[7]+((back_light_record[8]-back_light_record[7])>>1))-(back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) < 20)) ) //
							{
								back_light_record[0]=back_light_list[0]+((back_light_list[1]-back_light_list[0])>>1);
								back_light_record[1]=back_light_list[2];
								back_light_record[2]=back_light_list[3];

								back_light_record[3]=back_light_list[4]+((back_light_list[5]-back_light_list[4])>>1);
								back_light_record[4]=back_light_list[6];
								back_light_record[5]=back_light_list[7];
								
								back_light_record[6]=back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1);
								back_light_record[7]=back_light_list[0];
								back_light_record[8]=back_light_list[5];

								if ((back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1))>=(back_light_list[3]+41)) k=back_light_list[3]+10;
								else k=(back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1));

								for (;k<(back_light_list[3]+41);k++)
								{
									short light=0;
									for (h=hough_line_record[0][k];h < hough_line_record[1][k];h++)
									{									
										if ( (h < back_light_list[0]) || (h > back_light_list[5]) )
										{
											if ((input_y[(k-2)*width+h]-input_y[(k+1)*width+h])>(40))
											{
												light++;
											}
										}
									}
									if (light >= ((hough_line_record[1][k]-hough_line_record[0][k])>>2) )
									{
										back_light_record[9]=k;
										k=(back_light_list[3]+41);
									}
								}

								if ((back_light_record[6]+((back_light_list[5]-back_light_list[0])/3) < video_v_lower) && (k==(back_light_list[3]+41))) back_light_record[9]=back_light_record[6]+((back_light_list[5]-back_light_list[0])/3);
								else if (k==(back_light_list[3]+41)) back_light_record[9]=479;
								i=(hough_line_record[1][j<<1]>>1)+20;
								j=(video_v_higher>>1);
								not_found=0;			
							}
							sw-=4;
						}
						else if (sw>=8)
						{
							sw-=4;
							back_light_list[0]=back_light_list[4];
							back_light_list[1]=back_light_list[5];
							back_light_list[2]=back_light_list[6];
							back_light_list[3]=back_light_list[7];
						}
					}
				}
				else if ( (input_v[j*(width>>1)+i]>=160) && (input_v[j*(width>>1)+i-1]<160) )
				{
					for (k=2;((input_y[(j<<1)*width+(i<<1)-k]>=220) || (input_y[((j<<1)-1)*width+(i<<1)-k]>=220) || ((input_y[((j<<1))*width+(i<<1)-k]<220) && (input_y[((j<<1))*width+(i<<1)-k-1]>=220)) ) && ((abs(input_y[((j<<1))*width+(i<<1)-k]-input_y[((j<<1))*width+(i<<1)-k-1])<3) || (k<3) || (input_y[((j<<1))*width+(i<<1)-k]>=250) || (input_y[((j<<1))*width+(i<<1)-k-1]>=250)) && (k<25);k++);
					if (k>=6)
					{
						short mid;					
						back_light_list[sw]=(i<<1)-k;
						back_light_list[sw+1]=(i<<1);
						mid=back_light_list[sw]+((back_light_list[sw+1]-back_light_list[sw])>>1);
						for (k=1;(input_y[((j<<1)-k)*width+mid]>=220);k++);
						back_light_list[sw+2]=(j<<1)-k;
						for (k=1;(input_y[((j<<1)+k)*width+mid]>=220) && (abs(input_y[((j<<1)+k)*width+mid]-input_y[((j<<1)+k+1)*width+mid])<6);k++);
						back_light_list[sw+3]=(j<<1)+k;
						if ((back_light_list[sw+3]-back_light_list[sw+2]<2) || (back_light_list[sw+3]-back_light_list[sw+2]>25))
						{
							memset(back_light_list+sw,0,sizeof(short)*4);						
						}
						else if ((back_light_list[sw+3]-back_light_list[sw+2]>=2) && (back_light_list[sw+3]-back_light_list[sw+2]<=25))
						{
							sw+=4;
							i+=4;
							if ((back_light_list[sw+2]+((back_light_list[sw+3]-back_light_list[sw+2])>>1))>200) back_dif_th=30;
							else back_dif_th=0;
						}
						if ((sw>=8) && (abs((back_light_list[3]-back_light_list[2])-(back_light_list[7]-back_light_list[6]))<=3) && (abs((back_light_list[1]-back_light_list[0])-(back_light_list[5]-back_light_list[4]))<=3) && ((back_light_list[4]-back_light_list[1])>=(10+back_dif_th)) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<175) && ((back_light_list[4]-back_light_list[1])<=45)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=175) ) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<165) && ((back_light_list[3]-back_light_list[2])<=10)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=165) ) && ( (hough_line_record[0][j<<1] < (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) && (hough_line_record[1][j<<1] > (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) ) )
						{
							if ((!back_light_record[0]) || ( (abs(back_light_record[6]-(back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1)))<(10+(not_found*3))) && (abs((back_light_record[7]+((back_light_record[8]-back_light_record[7])>>1))-(back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) < 20) ) )
							{						
								back_light_record[0]=back_light_list[0]+((back_light_list[1]-back_light_list[0])>>1);
								back_light_record[1]=back_light_list[2];
								back_light_record[2]=back_light_list[3];

								back_light_record[3]=back_light_list[4]+((back_light_list[5]-back_light_list[4])>>1);
								back_light_record[4]=back_light_list[6];
								back_light_record[5]=back_light_list[7];

								back_light_record[6]=back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1);
								back_light_record[7]=back_light_list[0];
								back_light_record[8]=back_light_list[5];
								
								if ((back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1))>=(back_light_list[3]+41)) k=back_light_list[3]+10;
								else k=(back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1));

								for (;k<(back_light_list[3]+41);k++)
								{
									short light=0;
									for (h=hough_line_record[0][k];h < hough_line_record[1][k];h++)
									{									
										if ( (h < back_light_list[0]) || (h > back_light_list[5]) )
										{
											if ((input_y[(k-1)*width+h]-input_y[(k+1)*width+h])>(shadow_th>>1))
											{
												light++;
											}
										}
									}
									if (light >= ((hough_line_record[1][k]-hough_line_record[0][k])>>2) )
									{
										back_light_record[9]=k;
										k=(back_light_list[3]+41);
									}
								}

								if ((back_light_record[6]+((back_light_list[5]-back_light_list[0])/3) < video_v_lower) && (k==(back_light_list[3]+41))) back_light_record[9]=back_light_record[6]+((back_light_list[5]-back_light_list[0])/3);
								else if (k==(back_light_list[3]+41)) back_light_record[9]=479;
								i=(hough_line_record[1][j<<1]>>1)+20;
								j=(video_v_higher>>1);
								not_found=0;			
							}
							sw-=4;
						}
						else if (sw>=8)
						{
							sw-=4;
							back_light_list[0]=back_light_list[4];
							back_light_list[1]=back_light_list[5];
							back_light_list[2]=back_light_list[6];
							back_light_list[3]=back_light_list[7];
						}
					}

				}
				if ( (input_v[j*(width>>1)+i]>=160) && (input_v[(j+1)*(width>>1)+i]<160) && (j!=(video_v_higher>>1)) )
				{
					for (k=2;( (input_y[((j<<1)+k)*width+(i<<1)]>=220) || ((input_y[((j<<1)+k+1)*width+(i<<1)]>=220) && (input_y[((j<<1)+k)*width+(i<<1)]<220)) )&& (k<15);k++);
					if (k>=6)
					{
						short mid;					
						back_light_list[sw+2]=(j<<1);
						back_light_list[sw+3]=(j<<1)+k;
						mid=back_light_list[sw+2]+((back_light_list[sw+3]-back_light_list[sw+2])>>1);
						for (k=1;(input_y[mid*width+(i<<1)+k]>=220) && (abs(input_y[mid*width+(i<<1)+k]-input_y[mid*width+(i<<1)+k+1])<6);k++);
						back_light_list[sw+1]=(i<<1)+k;
						for (k=1;(input_y[mid*width+(i<<1)-k]>=220) && (abs(input_y[mid*width+(i<<1)-k]-input_y[mid*width+(i<<1)-k-1])<6);k++);
						back_light_list[sw]=(i<<1)-k;
						if ((back_light_list[sw+3]-back_light_list[sw+2]<2) || (back_light_list[sw+3]-back_light_list[sw+2]>25))
						{
							memset(back_light_list+sw,0,sizeof(short)*4);						
						}
						else if ((back_light_list[sw+3]-back_light_list[sw+2]>=2) && (back_light_list[sw+3]-back_light_list[sw+2]<=25))
						{
							sw+=4;
							//i+=2;
							if ((back_light_list[sw+2]+((back_light_list[sw+3]-back_light_list[sw+2])>>1))>200) back_dif_th=30;
							else back_dif_th=0;
						}
						if ((sw>=8) && (abs((back_light_list[3]-back_light_list[2])-(back_light_list[7]-back_light_list[6]))<=3) && (abs((back_light_list[1]-back_light_list[0])-(back_light_list[5]-back_light_list[4]))<=3) && ((back_light_list[4]-back_light_list[1])>=(10+back_dif_th)) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<175) && ((back_light_list[4]-back_light_list[1])<=45)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=175) ) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<165) && ((back_light_list[3]-back_light_list[2])<=10)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=165) ) && ( (hough_line_record[0][j<<1] < (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) && (hough_line_record[1][j<<1] > (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) ) && (abs((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1)) - (back_light_list[6]+((back_light_list[7]-back_light_list[6])>>1)))<4) )
						{
							if ((!back_light_record[0]) || ( (abs(back_light_record[6]-(back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1)))<(10+(not_found*3))) && (abs((back_light_record[7]+((back_light_record[8]-back_light_record[7])>>1))-(back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) < 20) ) )
							{						
								back_light_record[0]=back_light_list[0]+((back_light_list[1]-back_light_list[0])>>1);
								back_light_record[1]=back_light_list[2];
								back_light_record[2]=back_light_list[3];

								back_light_record[3]=back_light_list[4]+((back_light_list[5]-back_light_list[4])>>1);
								back_light_record[4]=back_light_list[6];
								back_light_record[5]=back_light_list[7];

								back_light_record[6]=back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1);
								back_light_record[7]=back_light_list[0];
								back_light_record[8]=back_light_list[5];

								if ((back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1))>=(back_light_list[3]+41)) k=back_light_list[3]+10;
								else k=(back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1));

								for (;k<(back_light_list[3]+41);k++)
								{
									short light=0;
									for (h=hough_line_record[0][k];h < hough_line_record[1][k];h++)
									{									
										if ( (h < back_light_list[0]) || (h > back_light_list[5]) )
										{
											if ((input_y[(k-2)*width+h]-input_y[(k+1)*width+h])>(40))
											{
												light++;
											}
										}
									}
									if (light >= ((hough_line_record[1][k]-hough_line_record[0][k])>>2) )
									{
										back_light_record[9]=k;
										k=(back_light_list[3]+41);
									}
								}

								if ((back_light_record[6]+((back_light_list[5]-back_light_list[0])/3) < video_v_lower) && (k==(back_light_list[3]+41))) back_light_record[9]=back_light_record[6]+((back_light_list[5]-back_light_list[0])/3);
								else if (k==(back_light_list[3]+41)) back_light_record[9]=479;
								i=(hough_line_record[1][j<<1]>>1)+20;
								j=(video_v_higher>>1);
								not_found=0;			
							}
							sw-=4;
						}
						else if (sw>=8)
						{
							sw-=4;
							back_light_list[0]=back_light_list[4];
							back_light_list[1]=back_light_list[5];
							back_light_list[2]=back_light_list[6];
							back_light_list[3]=back_light_list[7];
						}
					}
				}
				else if ( (input_v[j*(width>>1)+i]>=160) && (input_v[(j-1)*(width>>1)+i]<160) && (j!=(video_v_higher>>1)) )
				{
					for (k=2;( (input_y[((j<<1)-k)*width+(i<<1)]>=220) || ((input_y[((j<<1)-k-1)*width+(i<<1)]>=220) && (input_y[((j<<1)-k)*width+(i<<1)]<220)) ) && ((abs(input_y[((j<<1)-k)*width+(i<<1)]-input_y[((j<<1)-k-1)*width+(i<<1)])<6) || (input_y[((j<<1)-k)*width+(i<<1)]>=250) || (input_y[((j<<1)-k-1)*width+(i<<1)]>=250)) && (k<15);k++);
					if (k>=6)
					{
						short mid;
						back_light_list[sw+3]=(j<<1);
						back_light_list[sw+2]=(j<<1)-k;
						mid=back_light_list[sw+2]+((back_light_list[sw+3]-back_light_list[sw+2])>>1);
						for (k=1;(input_y[mid*width+(i<<1)+k]>=220) && (abs(input_y[mid*width+(i<<1)+k]-input_y[mid*width+(i<<1)+k+1])<6);k++);
						back_light_list[sw+1]=(i<<1)+k;
						for (k=1;(input_y[mid*width+(i<<1)-k]>=220) && (abs(input_y[mid*width+(i<<1)-k]-input_y[mid*width+(i<<1)-k-1])<6);k++);
						back_light_list[sw]=(i<<1)-k;
						if ((back_light_list[sw+3]-back_light_list[sw+2]<2) || (back_light_list[sw+3]-back_light_list[sw+2]>25))
						{
							memset(back_light_list+sw,0,sizeof(short)*4);						
						}
						else if ((back_light_list[sw+3]-back_light_list[sw+2]>=2) && (back_light_list[sw+3]-back_light_list[sw+2]<=25))
						{
							sw+=4;
							//i+=2;
							if ((back_light_list[sw+2]+((back_light_list[sw+3]-back_light_list[sw+2])>>1))>200) back_dif_th=30;
							else back_dif_th=0;
						}
						if ((sw>=8) && (abs((back_light_list[3]-back_light_list[2])-(back_light_list[7]-back_light_list[6]))<=3) && (abs((back_light_list[1]-back_light_list[0])-(back_light_list[5]-back_light_list[4]))<=3) && ((back_light_list[4]-back_light_list[1])>=(10+back_dif_th)) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<175) && ((back_light_list[4]-back_light_list[1])<=45)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=175) ) && ( (((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))<165) && ((back_light_list[3]-back_light_list[2])<=10)) || ((back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1))>=165) ) && ( (hough_line_record[0][j<<1] < (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) && (hough_line_record[1][j<<1] > (back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) ) )
						{
							if ((!back_light_record[0]) || ( (abs(back_light_record[6]-(back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1)))<(10+(not_found*3))) && (abs((back_light_record[7]+((back_light_record[8]-back_light_record[7])>>1))-(back_light_list[0]+((back_light_list[5]-back_light_list[0])>>1))) < 20) ) )
							{						
								back_light_record[0]=back_light_list[0]+((back_light_list[1]-back_light_list[0])>>1);
								back_light_record[1]=back_light_list[2];
								back_light_record[2]=back_light_list[3];

								back_light_record[3]=back_light_list[4]+((back_light_list[5]-back_light_list[4])>>1);
								back_light_record[4]=back_light_list[6];
								back_light_record[5]=back_light_list[7];

								back_light_record[6]=back_light_list[2]+((back_light_list[3]-back_light_list[2])>>1);
								back_light_record[7]=back_light_list[0];
								back_light_record[8]=back_light_list[5];

								if ((back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1))>=(back_light_list[3]+41)) k=back_light_list[3]+10;
								else k=(back_light_list[3]+((back_light_list[4]-back_light_list[1])>>1));

								for (;k<(back_light_list[3]+41);k++)
								{
									short light=0;
									for (h=hough_line_record[0][k];h < hough_line_record[1][k];h++)
									{									
										if ( (h < back_light_list[0]) || (h > back_light_list[5]) )
										{
											if ((input_y[(k-2)*width+h]-input_y[(k+1)*width+h])>(40))
											{
												light++;
											}
										}
									}
									if (light >= ((hough_line_record[1][k]-hough_line_record[0][k])>>2) )
									{
										back_light_record[9]=k;
										k=(back_light_list[3]+41);
									}
								}

								if ((back_light_record[6]+((back_light_list[5]-back_light_list[0])/3) < video_v_lower) && (k==(back_light_list[3]+41))) back_light_record[9]=back_light_record[6]+((back_light_list[5]-back_light_list[0])/3);
								else if (k==(back_light_list[3]+41)) back_light_record[9]=479;
								i=(hough_line_record[1][j<<1]>>1)+20;
								j=(video_v_higher>>1);
								not_found=0;			
							}
							sw-=4;
						}
						else if (sw>=8)
						{
							sw-=4;
							back_light_list[0]=back_light_list[4];
							back_light_list[1]=back_light_list[5];
							back_light_list[2]=back_light_list[6];
							back_light_list[3]=back_light_list[7];
						}
					}
				}
			}
		}
		if (j==(video_v_higher>>1))
		{
			not_found++;
			if (not_found>=3)
			{
				memset(back_light_record,0,sizeof(back_light_record)*9);
				not_found=0;			
			}
		}
	}
	
}