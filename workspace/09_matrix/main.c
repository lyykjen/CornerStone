    #include <stdio.h>  
    #include "matrix.h"  
      
    //打印2维矩阵  
    void printf_matrix(struct _Matrix *A)  
    {  
        int i = 0;  
        int j = 0;  
        int m = 0;  
        int n = 0;  
          
        m = A->m;  
        n = A->n;  
        for (i = 0;i < m;i++)  
        {  
            for (j = 0;j < n;j++)  
            {  
                printf("%f\t",matrix_read(A,i,j));  
            }  
            printf("\n");  
        }  
    }  
      
    int main()  
    {  
        int i = 0;  
        int j = 0;  
        int k = 0;  
        struct _Matrix m1;  
        struct _Matrix m2;  
        struct _Matrix m3;  
          
        //初始化内存  
        matrix_set_m(&m1,3);  
        matrix_set_n(&m1,3);  
        matrix_init(&m1);  
        matrix_set_m(&m2,3);  
        matrix_set_n(&m2,3);  
        matrix_init(&m2);  
        matrix_set_m(&m3,3);  
        matrix_set_n(&m3,3);  
        matrix_init(&m3);  
          
        //初始化数据  
        k = 1;  
        for (i = 0;i < m1.m;i++)  
        {  
            for (j = 0;j < m1.n;j++)  
            {  
                matrix_write(&m1,i,j,k++);  
            }  
        }  
          
        for (i = 0;i < m2.m;i++)  
        {  
            for (j = 0;j < m2.n;j++)  
            {  
                matrix_write(&m2,i,j,k++);  
            }  
        }  
          
        //原数据  
        printf("A:\n");  
        printf_matrix(&m1);  
        printf("B:\n");  
        printf_matrix(&m2);  
          
        printf("A:行列式的值%f\n",matrix_det(&m1));  
          
        //C = A + B  
        if (matrix_add(&m1,&m2,&m3) > 0)  
        {  
            printf("C = A + B:\n");  
            printf_matrix(&m3);  
        }  
          
        //C = A - B  
        if (matrix_subtract(&m1,&m2,&m3) > 0)  
        {  
            printf("C = A - B:\n");  
            printf_matrix(&m3);  
        }  
          
        //C = A * B  
        if (matrix_multiply(&m1,&m2,&m3) > 0)  
        {  
            printf("C = A * B:\n");  
            printf_matrix(&m3);  
        }  
          
        //C = AT  
        if (matrix_transpos(&m1,&m3) > 0)  
        {  
            printf("C = AT:\n");  
            printf_matrix(&m3);  
        }  
          
        if (matrix_inverse(&m1,&m3) > 0)  
        {  
            printf("C = A^(-1):\n");  
            printf_matrix(&m3);  
        }  
          
        getchar();  
        return 0;  
    }  
