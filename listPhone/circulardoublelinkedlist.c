#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulardoublelinkedlist.h"

extern Node *Head;

Node *CreateNode(int no, char* name, char* phone)             // 노드 생성
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

void DestroyNode(Node *DelNode)                   // 노드 소멸
{
	free(DelNode);
}

void AppendNode(Node **tHead, Node *NewNode)      // 노드 추가
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

void InsertAfter(Node *Current, Node *NewNode)   // 특정 노드 뒤에 삽입
{
	NewNode->NextNode = Current->NextNode;
	NewNode->PrevNode = Current;
	Current->NextNode->PrevNode = NewNode;
	Current->NextNode = NewNode;
}

void RemoveNode(Node **tHead, Node *Remove)       // 노드 제거
{
	if (*tHead == Remove)                         // 헤드 노드를 제거할 때
	{
		if (Remove->NextNode == Remove)           // 노드가 하나인 경우
		{
			*tHead = NULL;
			Head = NULL;                        // Head 포인터 NULL로 초기화

		}
		else
		{
			*tHead = Remove->NextNode;            // 제거 노드 다음 노드를 헤드 노드로 설정
			Head = Remove->NextNode;
		}
	}
	Remove->PrevNode->NextNode = Remove->NextNode;
	Remove->NextNode->PrevNode = Remove->PrevNode;
	Remove->PrevNode = NULL;
	Remove->NextNode = NULL;
	DestroyNode(Remove);
}

void InsertNewHead(Node **tHead, Node *NewNode)   // 헤드 노드 삽입
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

void InsertBefore(Node **tHead, Node *Current, Node *NewNode)   // 특정 노드 앞에 삽입
{
	if (*tHead == Current)                       // 헤드 노드 앞에 삽입하는 경우 헤드 포인터 변경
	{
		*tHead = NewNode;
	}
	NewNode->PrevNode = Current->PrevNode;
	NewNode->NextNode = Current;
	Current->PrevNode->NextNode = NewNode;
	Current->PrevNode = NewNode;
}

Node *GetNodeAt(Node *Head, int Location)          // 특정 위치의 노드 찾기
{
	Node *Current = Head;

	while ((Current != NULL) && (Location > 1))    // 노드가 있고 아직 원하는 위치에 오지 않은 경우
	{
		Current = Current->NextNode;               // 다음 노드로 이동
		if (Current == Head)                       // 한 바퀴 돌아서 앞으로 온 경우
		{
			Current = NULL;
			break;
		}
		Location--;
	}

	return Current;
}

int GetNodeCount(Node *Head)                       // 노드 수 확인
{
	int cnt = 0;
	Node *Current = Head;

	while (Current != NULL)                        // 노드가 없는 경우
	{
		cnt++;
		Current = Current->NextNode;
		if (Current == Head)                       // 마지막 노드까지 센 경우
		{
			break;
		}
	}

	return cnt;
}

Node *FindNode(Node *Head, char* FindData)   // 특정 값을 갖는 노드 찾기
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

Node *FindNode_index(Node *Head, int FindData)   // index Node 포인터 반환
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

