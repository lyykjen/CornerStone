#include <stdio.h>  
#include <malloc.h>  
typedef  struct Tree tree ;  
/* 
定义二叉树的结构体 
*/  
struct Tree{  
	int data;  
	tree *left;  
	tree *right;  
};  
tree *p[100];  
/* 
初始化二叉树 
*/  
tree *initTree(tree* H){  
	H = NULL;  
	int data = 0;  
	printf(" 输入data \n ");  
	scanf("%d",&data);  
	if(data!=0){  
		H = (tree *)malloc(sizeof(tree));  
		H->data = data;  
		printf(" t data is %d \n",H->data);  
		printf(" 请输入左字树data \n");  
		H->left = initTree(H->left);  
		printf(" 请输入右字树data \n");  
		H->right = initTree(H->right);  
	}  
	return H;  
}  
/* 
先序遍历 
*/  
void DLR(tree* H){  
	if(NULL!=H){  
		printf(" data is %5d \n",H->data);  
		DLR(H->left);  
		DLR(H->right);  
	}  
}  
  
/* 
中序遍历 
*/  
void LDR(tree* H){  
	if(NULL!=H){  
		LDR(H->left);  
		printf(" data is %5d \n",H->data);  
		LDR(H->right);  
	}  
}  
  
/* 
后序遍历 
*/  
void LRD(tree* H){  
	if(NULL!=H){  
		LRD(H->left);  
		LRD(H->right);  
		printf(" data is %5d \n",H->data);  
	}  
}  
  
/* 
计算树的深度 
*/  
int deep(tree* H){  
	int d1 = 0;  
	int d2 = 0;  
	if(NULL!=H){  
		d1 = deep(H->left) +1;  
		d2 = deep(H->right) +1;  
	}  
	return d1>=d2? d1:d2;  
}  
//计算总的节点数  
int node(tree* H){  
	int n = 0;  
	if(NULL!=H){  
		n = node(H->left)+node(H->right) +1;  
	}  
	return n;  
}  
//计算叶子节点  
int CountLeaf(tree* H){  
	if(NULL==H) return 0;  
	if((NULL==H->left)&&(NULL==H->right)){  
		return 1;  
	}  
	return CountLeaf(H->left) + CountLeaf(H->right);  
}  
void main(){  
	tree *H = (tree*)malloc(sizeof(tree)) ;  
	 H = initTree(H);  
	 printf("DLR : \n");  
	 DLR(H);  
	 printf("LDR : \n");  
	 LDR(H);  
	 printf("LRD : \n");  
	 LRD(H);  
	 printf("\n deep is %5d \n ",deep(H));  
	 printf(" CountLeaf is %5d \n",CountLeaf(H));  
	 printf(" node number is %5d  \n",node(H));  
}  