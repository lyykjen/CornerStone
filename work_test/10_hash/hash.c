#include<stdio.h>
#include<string.h>
#define HASHSIZE 32    


//待存入表格数据

char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do",
        "double", "else", "enum", "extern", "float", "for", "goto",
        "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static",
        "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
        "while"
};

char keybuf[HASHSIZE][10];
static char val_flag[HASHSIZE];//标致已占用存储单元


void ClearFlag()
{
    int i;
    
    for (i = 0;i < HASHSIZE;i++)
    {
        val_flag[i] = (HASHSIZE+1);//清标致位
    }
}

//哈希函数，从数据中抽出某个成员用于哈希值的计算

unsigned int hash(char *s)
{
    unsigned int hashval;
    int i = 0;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;//使用31的原因可能是为了更好的分配hash地址，避免"冲突"，并且31只占用5bit
    hashval = hashval % HASHSIZE; //计算下标


    while ((val_flag[hashval] != (HASHSIZE+1)) && (i<32))
    {
        i++;
        hashval = (hashval + i)%HASHSIZE;    //冲突处理，存储单元(下标)偏移

    }
    if (i<HASHSIZE)
    {
        printf("\n元素下标(%d): 冲突次数： %d -- ",hashval,i);
        val_flag[hashval] = hashval; //表示该单元被占用

        return hashval;
    }
    return -1;
}

int main(void)
{
  int i, size, pos;

  size = sizeof(keywords) / sizeof(keywords[0]);//计算关键字数量
	//printf("total_size = %d,sizeof(keywords) = %d,sizeof(keywords[0]) = %d \n",size,sizeof(keywords),sizeof(keywords[0]));
	//printf("keywords[0] = %s \n",keywords[0]);
 
  //将数据存入哈希表

  ClearFlag();
  for(i = 0;i < size; i++)
     strcpy(keybuf[hash(keywords[i])],keywords[i]);

  //根据数据结构中某个成员作为索引值，查找对应数据

  ClearFlag();
  for(i = 0; i < size; i++)
  {
    pos = hash(keywords[i]);    
    printf("%-10s: %-3d\n", keybuf[pos], pos);
  }

  return 0;
}
