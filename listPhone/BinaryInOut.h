#ifndef _BINARY_IN_OUT_
#define _BINARY_IN_OUT_
#include "circulardoublelinkedlist.h";
typedef struct _phonebook pbook, *ppbook;

struct _phonebook{
	int idex_num;
	char name[20];
	char phone[12];
	ppbook pre_index;
	ppbook next_index;
};

//void WriteBinaryToDat(ppbook ppb);		//data -> file write
//int ReadBinaryFromDat(ppbook ppb);		//file -> read data
void WriteBinaryToDat(Node* ppb);		//data -> file write
int ReadBinaryFromDat(Node* ppb);		//file -> read data


#endif