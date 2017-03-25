//---------------------------影片宣告---------------------------------------
//#define source_L "H:\\temp\\day_2_R2806.yuv"
//#define source_R "H:\\temp\\day_2_L2806.yuv"
//#define source_L "H:\\temp\\day_1_R.yuv"
//#define source_R "H:\\temp\\day_1_L.yuv"
//#define source_L "H:\\temp\\night_2_R.yuv"
//#define source_R "H:\\temp\\night_2_L.yuv"
///home/lvyayun/test/multilane_detect/lane_video/
#define VPath "/home/lvyayun/test/multilane_detect/lane_video"
#define source_L VPath"/day_2_R.yuv"
#define source_R VPath"/night_2_R.yuv"
//#define source_L VPath"/front1_l_600(VGA).yuv"
//#define source_R VPath"/front1_r_600(VGA).yuv"
#define video_outside_lane VPath"/sobel_outside_lane.yuv"
#define video_inside_lane VPath"/sobel_inside_lane.yuv"
#define video_multilane VPath"/multilane1.yuv"
#define excel_out VPath"/sobel_lane.xls"
#define coordinate_out VPath"/coordinate.xls"
#define sobel_out VPath"/sobel.yuv"
#define excel_y	VPath"/y_value.xls"
#define excel_uv VPath"/uv_value.xls"
#define hough_0_out VPath"/hough_0_out.xls"
#define hough_1_out VPath"/hough_1_out.xls"
#define hough_2_out VPath"/hough_2_out.xls"
#define hough_3_out VPath"/hough_3_out.xls"
#define hough_out VPath"/hough.xls"
#define shadow_video VPath"/shadow.yuv"
#define E_maltilane VPath"/multilane2.yuv"

//---------------------------影片宣告---------------------------------------
/*char video_source_list[100][100]=
{
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front1_l_600(VGA).yuv"},
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front2_l_600(VGA).yuv"},
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front3_l_600(VGA).yuv"},
	{NULL},
	{"F:\\video_reserch\\20131126\\?前9.yuv"},
	{"F:\\video_reserch\\20131126\\?前10.yuv"},
	{"F:\\video_reserch\\20131126\\?前11.yuv"},
	{"F:\\video_reserch\\20131126\\?前12.yuv"},
	{"F:\\video_reserch\\20131126\\?前13.yuv"},
	{"F:\\video_reserch\\20131126\\?前14.yuv"},
	{"F:\\video_reserch\\20131126\\?前15.yuv"},
	{"F:\\video_reserch\\20131126\\?前16.yuv"},	
	
	{"F:\\video_reserch\\20131127\\?前5.yuv"},
	{"F:\\video_reserch\\20131127\\?前6.yuv"},
	{"F:\\video_reserch\\20131127\\?前7.yuv"}
};
char video_source_list_R[100][100]=
{
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front1_r_600(VGA).yuv"},
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front2_r_600(VGA).yuv"},
	{"C:\\Users\\Joseph\\Documents\\code\\video_source\\front3_r_600(VGA).yuv"},
	{NULL},
	{"F:\\video_reserch\\20131126\\?前9.yuv"},
	{"F:\\video_reserch\\20131126\\?前10.yuv"},
	{"F:\\video_reserch\\20131126\\?前11.yuv"},
	{"F:\\video_reserch\\20131126\\?前12.yuv"},
	{"F:\\video_reserch\\20131126\\?前13.yuv"},
	{"F:\\video_reserch\\20131126\\?前14.yuv"},
	{"F:\\video_reserch\\20131126\\?前15.yuv"},
	{"F:\\video_reserch\\20131126\\?前16.yuv"},	
	
	{"F:\\video_reserch\\20131127\\?前5.yuv"},
	{"F:\\video_reserch\\20131127\\?前6.yuv"},
	{"F:\\video_reserch\\20131127\\?前7.yuv"}
};*/
