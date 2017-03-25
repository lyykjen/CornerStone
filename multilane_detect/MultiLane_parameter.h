//Source video存放?存
static unsigned char *input_y_R,*input_y_L;
static unsigned char *input_u_R,*input_v_R,*input_u_L,*input_v_L;
//===============Source video存放?存=================
//===============Sobel?果存放?存====================
static unsigned char *sobel;
static unsigned char *lane_outside;
static unsigned char *lane_inside;
//===============Sobel?果存放?存====================
//===============影片分辨率=============================
int width=640,height=480;
//===============影片分辨率=============================
//===============霍夫相?存放===========================
short hough_record[4][30]={{0}};	//[][0]=>Left_inside,[][1]=>Left_outside,[][2]=>Right_inside,[][3]=>Right_outside
unsigned char hough_angle[8]={35,65,70,80,120,145,95,125}; //Left_inside[min][max],Left_outside[min][max],Right_inside[min][max],[Right_outside[min][max]
//unsigned char hough_angle[8]={1,90,1,90,91,180,91,180}; //Left_inside[min][max],Left_outside[min][max],Right_inside[min][max],[Right_outside[min][max]
short hough_r[8]={250,330,190,250,490,650,690,750};			//Left_inside[min][max],Left_outside[min][max],Right_inside[min][max],[Right_outside[min][max]
//short hough_r[8]={1,1199,1,1199,1,1199,1,1199};			//Left_inside[min][max],Left_outside[min][max],Right_inside[min][max],[Right_outside[min][max]
static short hough_line_record[4][1000]={{0}};	//??hough?位置
//===============霍夫相?存放===========================
short shadow_position[12]={0};
unsigned char inside_lane_is_yellow=0;
short back_light[30]={0};
short curve_record[2][video_height]={{0}};

//??宣告
FILE *fp_input_L,*fp_input_R;
FILE *fp_sobel_inside,*fp_sobel_outside;
FILE *fp_multilane,*fp_sobel;
FILE *fp_tmp,*fp_class_coordinate;
FILE *fp_y_excel,*fp_uv_excel;
FILE *fp_0_hough,*fp_1_hough,*fp_2_hough,*fp_3_hough;
