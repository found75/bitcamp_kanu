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

Node *CreateNode(int no, char* name, char* phone);  // ��� ����
void DestroyNode(Node *DelNode);                    // ��� �Ҹ�
void AppendNode(Node **tHead, Node *NewNode);       // ��� �߰�
void InsertAfter(Node *Current, Node *NewNode);     // ��� ����
void RemoveNode(Node **tHead, Node *Remove);        // ��� ����

void InsertNewHead(Node **tHead, Node *NewNode);    // ��� ��� ����
void InsertBefore(Node **tHead, Node *Current, Node *NewNode);  // Ư�� ��� �տ� ����

Node *GetNodeAt(Node *Head, int Location);          // Ư�� ��ġ�� ��� ã��
int GetNodeCount(Node *Head);                       // ��� �� Ȯ��
Node *FindNode(Node *Head, char* FindData);			// Ư�� ���� ��(�̸�)�� ��� ã��
int put_listNo(Node* Head);							// ����Ʈ�� �Ϸù�ȣ �ֱ�
void ascending_sort(Node* Head);					//�̸� ��������(��������) ���� 
Node *FindNode_index(Node *Head, int FindData);		//Ư�� ��(int no)�� ã�� ��� ã�� 
void DestroyList(Node **tHead, Node *Head);			//����� List ����



#endif  // _CIRCULAR_LINKED_LIST_