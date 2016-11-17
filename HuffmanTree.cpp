#define _CRT_SECURE_NO_WARNINGS
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																					HuffmanTree
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int m, s1, s2; // m是总结点个数，s1,s2用于筛选出最小和第二小的两个数

typedef struct 
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;                				//动态分配数组存储赫夫曼树

typedef char** Huffmancode;							//动态分配数组存储赫夫曼编码表

//选出weight最小的两个结点,S1保存最小的，S2保存第二小的
void selectmin(HuffmanTree HT,int nNode)            //默认parent值为0的结点为根结点
{
	int i,j;           
	for (i=1;i<=nNode;i++)
		if (HT[i].parent==0)
		{
			s1=i;
			break;
		}
	for (j=i+1;j<=nNode;j++)
		if (HT[j].parent==0)
		{
			s2=j;
			break;
		}
	for (i=1;i<=nNode;i++)
		if ((HT[i].weight<HT[s1].weight)&&(HT[i].parent==0)&&(s2!=i))
			s1=i;

	for (j=1;j<=nNode;j++)
		if ((HT[j].weight<HT[s2].weight)&&(HT[j].parent==0)&&(s1!=j))
			s2=j;

	if (HT[s2].weight<HT[s1].weight)
	{
		int temp=s1;
		s1=s2;
		s2=temp;
	}
}

//w[]用于存放n个结点的权值,构造huffman树，并求出其huffman编码
void Huffmancoding(HuffmanTree &HT,Huffmancode &HC,int *w,int nNode)
{
	int i,j;
	int cur, father;
	if (nNode<1)
		return ;
	m=2*nNode-1;
	HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));							//0号单元未用

	//初始化huffman树
	for (i=1;i<=nNode;i++)													//初始化前n个带权结点
	{
		HT[i].weight=w[i-1];
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}

	for (j=nNode+1;j<=m;j++)
	{
		HT[j].weight=0;
		HT[j].parent=0;
		HT[j].lchild=0;
		HT[j].rchild=0;
	}

	/*--------------------------Huffman树的构建--------------------------------*/
	for (i=nNode+1;i<=m;i++)
	{
		selectmin(HT,i-1);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	 /*-------------------------Huffman编码------------------------------------*/
	 HC=(Huffmancode)malloc((nNode)*sizeof(char*));
	 char *cd=(char *)malloc(nNode*sizeof(char));									//临时用于保存编码
	 cd[nNode-1]='\0';

	 for (i=1;i<=nNode;i++)
	 {
	 	int start =nNode-1;
	 	for (cur=i,father=HT[i].parent;father!=0;cur=father,father=HT[father].parent)
	 		if (HT[father].lchild==cur)
	 			cd[--start]='0';
	 		else
	 			cd[--start]='1';
	 	HC[i]=(char *)malloc((nNode-start)*sizeof(char));
	 	strcpy(HC[i],&cd[start]);
	 }
	 free(cd);
}

int main(void)
{
	HuffmanTree HT;
	Huffmancode HC;
	int *w,nNode,i;
	cout<<"Please input the node numbers:";
	cin>>nNode;
	HC=(Huffmancode)malloc((nNode+1)*sizeof(char*));
	w=(int *)malloc(nNode*sizeof(int));
	cout<<"Please input each node's weight:";
	for (i=0;i<nNode;i++)
		cin>>w[i];
	Huffmancoding(HT,HC,w,nNode);
	cout << "Each node's Huffmancode:" << endl;
	
	for (i = 1; i <= nNode; i++)
		printf("%2d(%4d):%s\n", i, w[i-1], HC[i]);			
}
