#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulardoublelinkedlist.h"

extern Node *Head;

Node *CreateNode(int no, char* name, char* phone)             // ��� ����
{
	Node *NewNode;

	NewNode = (Node *)malloc(sizeof(Node));
	NewNode->no = no;
	strncpy(NewNode->name, name, _LENTH_NAME_);
	strncpy(NewNode->phone, phone, _LENTH_PHONE_);
	NewNode->PrevNode = NULL;
	NewNode->NextNode = NULL;

	return NewNode;
}

void DestroyNode(Node *DelNode)                   // ��� �Ҹ�
{
	free(DelNode);
}

void AppendNode(Node **tHead, Node *NewNode)      // ��� �߰�
{
	if (*tHead == NULL)
	{
		*tHead = NewNode;
		NewNode->PrevNode = NewNode;
		NewNode->NextNode = NewNode;
	}
	else
	{
		NewNode->PrevNode = Head->PrevNode;
		NewNode->NextNode = Head;
		Head->PrevNode->NextNode = NewNode;
		Head->PrevNode = NewNode;
	}
}

void InsertAfter(Node *Current, Node *NewNode)   // Ư�� ��� �ڿ� ����
{
	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;
	Current->NextNode->PrevNode = NewNode;
	Current->NextNode = NewNode;
}

void RemoveNode(Node **tHead, Node *Remove)       // ��� ����
{
	if (*tHead == Remove)                         // ��� ��带 ������ ��
	{
		if (Remove->NextNode == Remove)           // ��尡 �ϳ��� ���
		{
			*tHead = NULL;
			Head = NULL;                        // Head ������ NULL�� �ʱ�ȭ

		}
		else
		{
			*tHead = Remove->NextNode;            // ���� ��� ���� ��带 ��� ���� ����
			Head = Remove->NextNode;
		}
	}
	Remove->PrevNode->NextNode = Remove->NextNode;
	Remove->NextNode->PrevNode = Remove->PrevNode;
	Remove->PrevNode = NULL;
	Remove->NextNode = NULL;
	DestroyNode(Remove);
}

void InsertNewHead(Node **tHead, Node *NewNode)   // ��� ��� ����
{
	if (*tHead == NULL)
	{
		NewNode->PrevNode = NewNode;
		NewNode->NextNode = NewNode;
	}
	else
	{
		NewNode->PrevNode = (*tHead)->PrevNode;
		NewNode->NextNode = *tHead;
		(*tHead)->PrevNode->NextNode = NewNode;
		(*tHead)->PrevNode = NewNode;
	}
	*tHead = NewNode;
}

void InsertBefore(Node **tHead, Node *Current, Node *NewNode)   // Ư�� ��� �տ� ����
{
	if (*tHead == Current)                       // ��� ��� �տ� �����ϴ� ��� ��� ������ ����
	{
		*tHead = NewNode;
	}
	NewNode->PrevNode = Current->PrevNode;
	NewNode->NextNode = Current;
	Current->PrevNode->NextNode = NewNode;
	Current->PrevNode = NewNode;
}

Node *GetNodeAt(Node *Head, int Location)          // Ư�� ��ġ�� ��� ã��
{
	Node *Current = Head;

	while ((Current != NULL) && (Location > 1))    // ��尡 �ְ� ���� ���ϴ� ��ġ�� ���� ���� ���
	{
		Current = Current->NextNode;               // ���� ���� �̵�
		if (Current == Head)                       // �� ���� ���Ƽ� ������ �� ���
		{
			Current = NULL;
			break;
		}
		Location--;
	}

	return Current;
}

int GetNodeCount(Node *Head)                       // ��� �� Ȯ��
{
	int cnt = 0;
	Node *Current = Head;

	while (Current != NULL)                        // ��尡 ���� ���
	{
		cnt++;
		Current = Current->NextNode;
		if (Current == Head)                       // ������ ������ �� ���
		{
			break;
		}
	}

	return cnt;
}

Node *FindNode(Node *Head, char* FindData)   // Ư�� ���� ���� ��� ã��
{
	Node *Current = Head;

	while ((Current != NULL) && (strcmp(Current->name, FindData) != 0))
	{
		Current = Current->NextNode;
		if (Current == Head)
		{
			Current = NULL;
			break;
		}
	}

	return Current;
}

int put_listNo(Node* Head)
{
	int i=1;
	Node *Current = Head;

	while ((Current != NULL))
	{
		Current->no = i;
		Current = Current->NextNode;
		if (Current == Head)
		{
			Current = NULL;
			break;
		}
		i++;
	}
	return i;
}

void ascending_sort(Node* Head)
{
	Node* Current = Head;
	Node* tempNode;
	char temp[20] = {0};
	int ntemp;
	int cmp;

	while(Current != NULL)
	{	
		if (Current == Head->PrevNode)
		{
			Current = NULL;
			break;
		}	
		tempNode = Current->NextNode;
		while(Current != NULL)
		{
			if (tempNode == Head)
			{
				tempNode = NULL;	
				break;
			}
			if (cmp = strcmp(Current->name, tempNode->name) > 0)
			{
				strncpy(temp, Current->name,20);
				strncpy(Current->name, tempNode->name,20);
				strncpy(tempNode->name, temp,20);

				strncpy(temp, Current->phone,12);
				strncpy(Current->phone, tempNode->phone,12);
				strncpy(tempNode->phone, temp,12);

				ntemp = Current->no;
				Current->no = tempNode->no;
				tempNode->no = ntemp;

			}
			tempNode = tempNode->NextNode;
		}
		Current = Current->NextNode;	
	}
}

Node *FindNode_index(Node *Head, int FindData)   // index Node ������ ��ȯ
{
	Node *Current = Head;

	while ((Current != NULL) && (Current->no != FindData))
	{
		Current = Current->NextNode;
		if (Current == Head)
		{
			Current = NULL;
			break;
		}
	}
	return Current;
}

void DestroyList(Node **tHead, Node *Head)
{
	while(1)
	{
		if (*tHead == NULL)
		{			
			break;
		}
		RemoveNode(&Head, Head);
	}
}

