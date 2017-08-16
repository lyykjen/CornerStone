#include<stdio.h>
#include<dirent.h>

int main(void)
{
        DIR *sdcardRoot=NULL;
		DIR *sdcardDcim=NULL;
        int i=0,j=0;	
        struct dirent *EntryRoot;
		struct dirent *EntryDcim;
        if((sdcardRoot = opendir("./"))==NULL)
        {
 	       printf("opendir failed!");
        	return 1;
        }
        else
        {
			if((sdcardDcim = opendir("./DCIM"))!=NULL)
			{
			   while(EntryDcim=readdir(sdcardDcim))
			   {				   
				   if(strcmp(EntryDcim->d_name,".")==0 || strcmp(EntryDcim->d_name,"..")==0) 
					continue;
					i++;
					printf("filename%d=%s\n",j,EntryDcim->d_name);
					
			   }
			}
			
	        while(EntryRoot=readdir(sdcardRoot))
			{	
				if(strcmp(EntryRoot->d_name,".")==0 || strcmp(EntryRoot->d_name,"..")==0) 
					continue;				
				j++;  	
				printf("filename%d=%s\n",i,EntryRoot->d_name);				    
        	}
			printf("TotalFileNumber = %d\n",i+j);
	        closedir(sdcardRoot);
			closedir(sdcardDcim);
        }
        return 0;
}
