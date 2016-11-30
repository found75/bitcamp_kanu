#include <stdio.h>
#include <stdlib.h>
#include "circulardoublelinkedlist.h"

void print_list(Node *list);

Node* Head = NULL;

int main(void)
{
	Node *temp;
	
	AppendNode(&Head, CreateNode("홍길동", "41034440442"));
	AppendNode(&Head, CreateNode("엄홍길", "12345612342"));
	AppendNode(&Head, CreateNode("이재명", "01067235468"));
	AppendNode(&Head, CreateNode("이태웅", "01034440442"));
	print_list(Head);
	
	ascending_sort(Head);
	print_list(Head);
	
	temp = FindNode(Head, "이재명");	//검색 - 이름이 같은 Node의 포인터 반환
	printf("%2d\n", temp->no);
	temp = FindNode_index(Head, 3);	//검색 - 이름이 같은 Node의 포인터 반환
	printf("%s\n", temp->name);
	

	return 0;
}

void print_list(Node *list)
{
	int i, cnt;

	cnt = GetNodeCount(list);        // 노드 수 계산 테스트
	for (i = 1; i < cnt+1; i++)
	{
		printf("No.%2d\n", GetNodeAt(list, i)->no);
		printf("Name :%s\n", GetNodeAt(list, i)->name);
		printf("phone : %s\n\n", GetNodeAt(list, i)->phone);
	}
	printf("\n");
}


/*// 노드 생성과 추가 테스트
	AppendNode(&Head, CreateNode(1));
	AppendNode(&Head, CreateNode(2));
	AppendNode(&Head, CreateNode(3));
	print_list(Head);

	// 노드 삽입 테스트
	InsertAfter(GetNodeAt(Head, 0), CreateNode(10));  // 첫 노드 다음에 삽입
	print_list(Head);

	InsertAfter(GetNodeAt(Head, 3), CreateNode(30));  // 마지막 노드 다음에 삽입
	print_list(Head);

	InsertAfter(GetNodeAt(Head, 2), CreateNode(20));  // 중간 노드 다음에 삽입
	print_list(Head);

	// 노드 제거 테스트
	RemoveNode(&Head, GetNodeAt(Head, 0));  // 첫 번째 노드 제거
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 4));  // 마지막 노드 제거
	print_list(Head);

	RemoveNode(&Head, GetNodeAt(Head, 2));  // 중간 노드 제거
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 2));  // 마지막 노드 제거
	print_list(Head);

	RemoveNode(&Head, GetNodeAt(Head, 1));  // 마지막 노드 제거
	print_list(Head);
	
	RemoveNode(&Head, GetNodeAt(Head, 0));  // 하나 남은 마지막 노드 제거
	print_list(Head); 
	
	// 헤드 삽입 테스트
	InsertNewHead(&Head, CreateNode(3));    // 3을 처음 노드로 삽입
	print_list(Head);

	InsertNewHead(&Head, CreateNode(2));    // 3 앞에 2 삽입
	print_list(Head);

	InsertNewHead(&Head, CreateNode(1));    // 2 앞에 1 삽입
	print_list(Head);

	// 특정 노드 앞에 추가 테스트
	InsertBefore(&Head, GetNodeAt(Head, 0), CreateNode(10));   // 첫 번째 노드 앞에 10 삽입
	print_list(Head);

	InsertBefore(&Head, GetNodeAt(Head, 2), CreateNode(20));   // 세 번째 노드 앞에 20 삽입
	print_list(Head);

	InsertBefore(&Head, GetNodeAt(Head, 4), CreateNode(30));   // 다섯 번째 노드 앞에 30 삽입
	print_list(Head);

	// 노드 찾기 테스트
	Node *temp = FindNode(Head, 1);  // 1값을 갖는 노드 찾기
	RemoveNode(&Head, temp);         // 리스트에서 해당 노드 제거
	DestroyNode(temp);               // 리스트에서 제거된 노드 메모리 해제
	print_list(Head);*/