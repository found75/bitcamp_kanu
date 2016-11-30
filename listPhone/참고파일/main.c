#include <stdio.h>
#include <stdlib.h>
#include "circulardoublelinkedlist.h"

void print_list(Node *list);

Node* Head = NULL;

int main(void)
{
	Node *temp;
	
	AppendNode(&Head, CreateNode("ȫ�浿", "41034440442"));
	AppendNode(&Head, CreateNode("��ȫ��", "12345612342"));
	AppendNode(&Head, CreateNode("�����", "01067235468"));
	AppendNode(&Head, CreateNode("���¿�", "01034440442"));
	print_list(Head);
	
	ascending_sort(Head);
	print_list(Head);
	
	temp = FindNode(Head, "�����");	//�˻� - �̸��� ���� Node�� ������ ��ȯ
	printf("%2d\n", temp->no);
	temp = FindNode_index(Head, 3);	//�˻� - �̸��� ���� Node�� ������ ��ȯ
	printf("%s\n", temp->name);
	

	return 0;
}

void print_list(Node *list)
{
	int i, cnt;

	cnt = GetNodeCount(list);        // ��� �� ��� �׽�Ʈ
	for (i = 1; i < cnt+1; i++)
	{
		printf("No.%2d\n", GetNodeAt(list, i)->no);
		printf("Name :%s\n", GetNodeAt(list, i)->name);
		printf("phone : %s\n\n", GetNodeAt(list, i)->phone);
	}
	printf("\n");
}


/*// ��� ������ �߰� �׽�Ʈ
	AppendNode(&Head, CreateNode(1));
	AppendNode(&Head, CreateNode(2));
	AppendNode(&Head, CreateNode(3));
	print_list(Head);

	// ��� ���� �׽�Ʈ
	InsertAfter(GetNodeAt(Head, 0), CreateNode(10));  // ù ��� ������ ����
	print_list(Head);

	InsertAfter(GetNodeAt(Head, 3), CreateNode(30));  // ������ ��� ������ ����
	print_list(Head);

	InsertAfter(GetNodeAt(Head, 2), CreateNode(20));  // �߰� ��� ������ ����
	print_list(Head);

	// ��� ���� �׽�Ʈ
	RemoveNode(&Head, GetNodeAt(Head, 0));  // ù ��° ��� ����
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 4));  // ������ ��� ����
	print_list(Head);

	RemoveNode(&Head, GetNodeAt(Head, 2));  // �߰� ��� ����
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 2));  // ������ ��� ����
	print_list(Head);

	RemoveNode(&Head, GetNodeAt(Head, 1));  // ������ ��� ����
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 0));  // �ϳ� ���� ������ ��� ����
	print_list(Head); 
	
	// ��� ���� �׽�Ʈ
	InsertNewHead(&Head, CreateNode(3));    // 3�� ó�� ���� ����
	print_list(Head);

	InsertNewHead(&Head, CreateNode(2));    // 3 �տ� 2 ����
	print_list(Head);

	InsertNewHead(&Head, CreateNode(1));    // 2 �տ� 1 ����
	print_list(Head);

	// Ư�� ��� �տ� �߰� �׽�Ʈ
	InsertBefore(&Head, GetNodeAt(Head, 0), CreateNode(10));   // ù ��° ��� �տ� 10 ����
	print_list(Head);

	InsertBefore(&Head, GetNodeAt(Head, 2), CreateNode(20));   // �� ��° ��� �տ� 20 ����
	print_list(Head);

	InsertBefore(&Head, GetNodeAt(Head, 4), CreateNode(30));   // �ټ� ��° ��� �տ� 30 ����
	print_list(Head);

	// ��� ã�� �׽�Ʈ
	Node *temp = FindNode(Head, 1);  // 1���� ���� ��� ã��
	RemoveNode(&Head, temp);         // ����Ʈ���� �ش� ��� ����
	DestroyNode(temp);               // ����Ʈ���� ���ŵ� ��� �޸� ����
	print_list(Head);*/