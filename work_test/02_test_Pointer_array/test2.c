#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
int main()
{
	int argc = 6;
	int i = 0;
	int latitude = 108031.5,longitude = 246852.6;
	//int latitude = 108.5*pow(10,7),longitude = 24.6*pow(10,7);
	char gps[6][10]={ "lgdst",
                 "0",
                 "rx",
                 "loc-gps",
                 "00",
                 "00"
	};
	
	printf("latitude = %.2f,longitude = %.2f\n",(float)latitude,(float)longitude);
	char *pgps[6];
	sprintf(gps[4], "%f",(float)(latitude/pow(10,7)));
	sprintf(gps[5], "%f",(float)(longitude/pow(10,7)));
	//sprintf(gps[4], "%d", latitude);
	//sprintf(gps[5], "%d" ,longitude );
	//memcpy(gps[5], longitude, sizeof(gps_data->longitude));
	
	for(i=0;i<6;i++)
		pgps[i] = gps[i];
	for(i=0;i<6;i++)
		printf("pgps[%d] = %s\n",i,pgps[i]);
	//lgdst_access_rx_ctl(argc,pgps,NULL);
}