#include<stdio.h>
#include<dirent.h>

int main(void)
{
        DIR *dirptr=NULL;
		DIR *dirptr1=NULL;
        int i=0;
		int j=0;
        struct dirent *entry;
		struct dirent *entry1;
        if((dirptr = opendir("./"))==NULL)
        {
 	       printf("opendir failed!");
        	return 1;
        }
        else
        {
			if((dirptr1 = opendir("./test"))!=NULL)
			{
			   while(entry1=readdir(dirptr1))
			   {				   
				   if(strcmp(entry1->d_name,".")==0 || strcmp(entry1->d_name,"..")==0) 
					continue;
					j++;
					printf("filename%d=%s\n",j,entry1->d_name);
					
			   }
			}
			
	        while(entry=readdir(dirptr))
			{	
				if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0 || strcmp(entry->d_name,"test")==0) 
					continue;				
				i++;  	
				printf("filename%d=%s\n",i,entry->d_name);				    
        	}
			printf("TotalFileNumber = %d\n",i+j);
	        closedir(dirptr);
			closedir(dirptr1);
        }
        return 0;
}
