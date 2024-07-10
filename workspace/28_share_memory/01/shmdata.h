#ifndef _SHMDATA_H_HEADER  
#define _SHMDATA_H_HEADER  
  
#define TEXT_SZ 2048  
  
struct shared_use_st  
{  
	bool written;//作为一个标志，true：表示可写，false表示可读 
	char text[TEXT_SZ];//记录写入和读取的文本  
};  
  
#endif  