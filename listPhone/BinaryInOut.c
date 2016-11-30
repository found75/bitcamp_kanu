#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BinaryInOut.h"
#include "circulardoublelinkedlist.h"
//Node* 
extern Node* Head;	//Node pointer

/*
void WriteBinaryToDat(ppbook ppb)
{
	FILE *out = 0;
	out=fopen("phonebook.dat","wb");
	ppb = (ppbook)Head;

	if(out == NULL)
	{
		puts("데이터 저장 실패.");
	} 
	else
	{		 
		while(1)	

		{
			fwrite(ppb, sizeof(pbook), 1 , out);
			if (ppb->next_index == (ppbook)Head)
				break;
			ppb = ppb->next_index;
		}
		fclose(out);	
	}
}
int ReadBinaryFromDat(ppbook ppb)
{
	FILE *in = 0;
	static int cnt = 0;
	int rtn = 1;
	in=fopen("phonebook.dat","rb");
	
	if(in == NULL)
	{
//		printf("파일 phonebook.dat를 열수 없어서 생성합니다.\n");
//      in = fopen("phonebook.dat", "w+b");//파일이 없을 경우 생성합니다.
		rtn = 0;
	}
	else
	{
		fseek(in, sizeof(pbook)*cnt, 0);
		rtn = fread(ppb,sizeof(pbook),1, in);
		cnt++;
		fclose(in);
	}



	return rtn;
}
*/




void WriteBinaryToDat(Node* ppb)
{
	FILE *out = 0;
	out=fopen("phonebook.dat","wb");
	ppb = (ppbook)Head;

	if(out == NULL)
	{
		puts("데이터 저장 실패.");
	} 
	else
	{		 
		while(1)	

		{
			fwrite(ppb, sizeof(pbook), 1 , out);
			if (ppb->NextNode == (ppbook)Head)
				break;
			ppb = ppb->NextNode;
		}
		fclose(out);	
	}
}
int ReadBinaryFromDat(Node* ppb)
{
	FILE *in = 0;
	static int cnt = 0;
	int rtn = 1;
	in=fopen("phonebook.dat","rb");
	
	if(in == NULL)
	{
//		printf("파일 phonebook.dat를 열수 없어서 생성합니다.\n");
//      in = fopen("phonebook.dat", "w+b");//파일이 없을 경우 생성합니다.
		rtn = 0;
	}
	else
	{
		fseek(in, sizeof(pbook)*cnt, 0);
		rtn = fread(ppb,sizeof(pbook),1, in);
		cnt++;
		fclose(in);
	}
	return rtn;
}

