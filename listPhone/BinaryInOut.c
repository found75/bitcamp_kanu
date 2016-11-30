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
		puts("������ ���� ����.");
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
//		printf("���� phonebook.dat�� ���� ��� �����մϴ�.\n");
//      in = fopen("phonebook.dat", "w+b");//������ ���� ��� �����մϴ�.
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
		puts("������ ���� ����.");
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
//		printf("���� phonebook.dat�� ���� ��� �����մϴ�.\n");
//      in = fopen("phonebook.dat", "w+b");//������ ���� ��� �����մϴ�.
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

