/*strtoint*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
 
struct lcm_request_data_s
{ 
	unsigned int  camera_version;	
	char moduleName[8];
	char branch[5];
}lcm_request_data;

int main(void)
{
    unsigned int fw = 0;
	unsigned char model;
	//unsigned int * fw_str;
    char *ver = "E90_0.6.02_A";
	char *str = "0602A";
	
	memcpy(&lcm_request_data.moduleName, &ctrl_cam.cmd_params[0], sizeof(u64));
	memcpy(lcm_request_data.camera_version, &ctrl_cam.cmd_params[8], sizeof(u8)*3);
	memcpy(lcm_request_data.branch, &ctrl_cam.cmd_params[11], sizeof(u8)*3);
	//memcpy(fw_str,"0.6.02_A",sizeof(fw_str));	
	printf("str2 = %d\n",'A');
	//printf("fw_str = %s\n",fw_str);
    return 0;
}