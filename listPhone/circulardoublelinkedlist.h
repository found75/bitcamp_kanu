#ifndef _CIRCULAR_LINKED_LIST_ //p
#define _CIRCULAR_LINKED_LIST_

typedef int ElementType;

#define _LENTH_NAME_ 20
#define _LENTH_PHONE_ 12


typedef struct tagNode
{
	int no;
	char name[_LENTH_NAME_];
	char phone[_LENTH_PHONE_];
	struct tagNode *PrevNode;
	struct tagNode *NextNode;
} Node;

extern Node* Head;

Node *CreateNode(int no, char* name, char* phone);  // 노드 생성
void DestroyNode(Node *DelNode);                    // 노드 소멸
void AppendNode(Node **tHead, Node *NewNode);       // 노드 추가
void InsertAfter(Node *Current, Node *NewNode);     // 노드 삽입
void RemoveNode(Node **tHead, Node *Remove);        // 노드 제거

void InsertNewHead(Node **tHead, Node *NewNode);    // 헤드 노드 삽입
void InsertBefore(Node **tHead, Node *Current, Node *NewNode);  // 특정 노드 앞에 삽입

Node *GetNodeAt(Node *Head, int Location);          // 특정 위치의 노드 찾기
int GetNodeCount(Node *Head);                       // 노드 수 확인
Node *FindNode(Node *Head, char* FindData);			// 특정 값을 갖(이름)는 노드 찾기
int put_listNo(Node* Head);							// 리스트의 일련번호 주기
void ascending_sort(Node* Head);					//이름 오름차순(ㄱㄴㄷ순) 정렬 
Node *FindNode_index(Node *Head, int FindData);		//특정 값(int no)을 찾는 노드 찾기 
void DestroyList(Node **tHead, Node *Head);			//종료시 List 해제



#endif  // _CIRCULAR_LINKED_LIST_