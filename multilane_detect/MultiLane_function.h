//---------------------------函數宣告---------------------------------------
extern int  file_open(void);
extern void memory_inital(void);
extern void draw_line(void);
extern void draw_LDWS(void);
extern void draw_car_shadow(void);
extern void draw_car_back_light(void);
extern int line_filter(unsigned char *input_y,unsigned char *input_u,unsigned char *input_v,unsigned char * sobel,unsigned char *sobel_origin,int width,int height);
extern int check_lane_type(short inside_hough_record[][4],short hough_record[][4], unsigned char * input_u, unsigned char * input_v,int width,int height);
extern void LDWS(short hough_record[][30],short hough_line_record[][1000],int width,int height);
extern void car_serch(short hough_record[][30],short hough_line_record[][1000],short curve_record[][480],unsigned char * sobel, unsigned char * input_y, unsigned char * input_u, unsigned char * input_v,short *shadow_position,int width,int height);
extern short hough_combine(unsigned char * lane,short hough_record[][30],short hough_line_record[][1000],short *hough_r,unsigned char *hough_angle,int width,int height);
extern void parallax(unsigned char *input_y_L,unsigned char *input_y_R,short hough_record[][30],short hough_line_record[][1000],short *shadow_position,short *back_light,int width,int height);
extern void Lane_width_transfer_distance(short *shadow_position,short *back_light,unsigned char *number_y,signed char *number_u,signed char *number_v,short hough_line_record[][1000],short hough_record[][30],int width,int height);
extern void detect_curve(unsigned char * input_y, unsigned char * input_u, unsigned char * input_v,unsigned char * sobel,short curve_record[][video_height],short hough_record[][30],short hough_line_record[][1000],int width,int height);
extern void car_back_light(unsigned char *input_y,unsigned char *input_u,unsigned char *input_v,unsigned char *temp,short hough_line_record[][1000],short *back_light_record,short *shadow_position,int width,int height);
//---------------------------函數宣告---------------------------------------