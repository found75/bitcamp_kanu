#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "circulardoublelinkedlist.h"
#include "BinaryInOut.h"

/*  TODO 수정 내역 참고 하세요. (2016.11.29)
	history
	2016.11.16
	1. 화면 레이아웃 조정.
	2. 목록 조회 화면에서 순번 [000001] 형식으로 표시 되던 것을 [      1] 형식으로 표시 되게 수정. (신규,수정도 동일 처리.)
	3. 프로그램 시작 종료시 progress 메세지 추가.
	4. Page 작업시 Page에 표시되는 아이템수 변수를 _PAGE_ITEM_COUNT_ 값으로 통일.
	5. LoadData() 파일이 없을때 오류 발생버그 수정.
	6. typedef struct tagNode  char name[_LENTH_NAME_]; char phone[_LENTH_PHONE_];  선언 수정.
	7. maxCnt -> maxPageCnt  메소드 이름 변경.
	8. main.c 에사 사용한 전역 변수 지역화. [static ]
	9. SortItme() 함수 아규먼트 제거
	10. 코드 정리 사용하지 않는 변수 제거.
	11. typedef struct tagNode 구조체 하나로 통합. (BinaryInOut.h , circulardoublelinkedlist.h)
	12. InputChar 메소드. SDIIN 값 입력시 버퍼 크기 초과 하면 사용자 메세지 표시.
	13. [이전],[다음] 페이지 메세지 함수 성공시에만 호출하게 수정.
*/

//#define _ASSERT_
#define _PAGE_ITEM_COUNT_ 10 //1 Page 에 표시할 최대 아이템 겟수.

enum _eMenu
{
	eNone= 0,
	eNew = 1,
	eChg,
	eDel,
	eSearchName, //이름 검색
	eDetail,	 //번호 검색
	eSort,
	ePrePage,	//7번 앞페이지
	eNextPage,  //8번 다음페이지
	eExit		//9번 종료
	
};
typedef enum _eMenu eMenu;

Node* Head = NULL;
static char szMessage[255] = {0}; //최종 메세지를 저정할 변수
static int speed[4] = {150,70,50,30}; //tApplication start message 속도 변수

static int _noSeq = 1; //순번 값을 저장한다. (파일 로드시 제일 큰값으로 업데이트 필요.) - g
static int currentPage = 0;	//현제 페이지

int maxPageCnt(); //최대 페이지 수를 반환 한다.

//화면 상단에 표시할 메세지를 설정 한다.
void SetLastMessage(char* szStr)
{
	memset(szMessage,0x00,sizeof(szMessage));
	strcpy(szMessage,szStr);
}

//STD IN 의 입력을 받는다.
//return -1 이면 입력값 추가.
 int InputChar(char* szBuff,int pCnt)
{
	int nCnt	= 0;
	int ch		= 0;
	while(1)
	{
		ch = getchar();
		if(ch == '\n' || ch == 0x1b) //Enter Or Esc 코드가들어 오면 종료 한다.
		{
			if(ch == 0x1b)
			{
				nCnt = 0;
			}
			break;
		}
		if(nCnt < (pCnt-1))
		{
			szBuff[nCnt++] = (char)ch;
		}
		else
		{
			printf("\t*\t사용자 길이를 초과 하였습니다. (초과한 데이터는 버리고 저장 합니다.)\n");
			break; //버퍼 입력 초과로 종료
		}		
	}
	fflush(stdin);
	szBuff[nCnt] = 0x00;
	return nCnt;
}
//Menu 값을 String 값으로변겅 하낟.
char* menuTStirng(eMenu menu)
{
	switch(menu)
	{
	case eNone:
		return "None";
	case eNew:
		return "신규";
	case eChg:
		return "수정";
	case eDel:
		return "삭제";
	case eSearchName:
		return "검색";
	case eDetail:
		return "상세보기";
	case eSort:
		return "정렬";
	case eExit:
		return "종료";
	}
	return "error";
}
//선택 메뉴 메세지를 화면에 표시 한다.
int displayMenu()
{	
	eMenu selMenu;
	printf("\t**********************************************************************************************\n");
	printf("\t*이전 페이지(7)    신규(1),수정(2),삭제(3),검색(4),상세(5),정렬(6),종료(9)      다음페이지(8)*\n");
	printf("\t**********************************************************************************************\n");
	
	while(1)
	{	
		int nSel = 0;
		char ch[2] ;
		selMenu = eNone;
		nSel = getch();
		ch[0] = (char)nSel;
		ch[1] = 0x00;
		nSel = atoi(ch);
		if(nSel >= eNew && nSel <= eExit)
		{			
			selMenu = (eMenu)nSel;
			break;
		}
	}
	return selMenu;
}
//데이터를 화면에 표시 한다.
int displayData(eMenu menu)
{
	int row, nodecnt;
	int offset;
	int totcnt;
	int i = 0;
	
	Node* pNode = NULL;

	printf("\n\n");
	printf("\t**********************************************************************************************\n");
	printf("\t*\t%-60s                         *\n",szMessage);
	printf("\t**********************************************************************************************\n");
	printf("\t*\t%5s\t\t%20s\t\t%20s                 *\n","순번","이름","전화번호");
	printf("\t**********************************************************************************************\n");
	
	nodecnt = GetNodeCount(Head);        // 노드 수 계산 테스트
	
	//GetNodeCount(Node *Head)
	totcnt = GetNodeCount(Head);
	offset = 1 + (currentPage * _PAGE_ITEM_COUNT_);

	//for(row = 1 ; row <= nodecnt ; row++)
	for(row =  offset; row <= offset+9 ; row++)
	{	
		
		if(totcnt == row-1)
			break;
		pNode = GetNodeAt(Head, row);
		printf("\t*\t%3d\t\t%20s\t\t%20s                 *\n",pNode->no,pNode->name,pNode->phone);
		
		
	}
	printf("\t**********************************************************************************************\n");
	printf("\t*(%3d/%3d)페이지의 (%2d) 개의 데이터가 조회 되었습니다.                                       *\n",currentPage+1,maxPageCnt(),row-1 - _PAGE_ITEM_COUNT_*currentPage);
	printf("\t**********************************************************************************************\n");

	return nodecnt;
}

//파일에서 데이터를 로드한다.
int LoadData()
{	
	int i;
	int max = 0;
	Node* temp = NULL; 	

	printf("\tApplication  Start");
	for(i = 0; i < 40; i++)
	{
		printf(".");
		Sleep(speed[i/10]);
	}
	system("cls");

	while(1)		//데이터 읽어오기 파일에서
	{
		temp = CreateNode(1, "임시", "00000000000");
		i = ReadBinaryFromDat((ppbook)temp);
		AppendNode(&Head, temp);

		if (i == 0)
		{
			RemoveNode(&Head, temp);
			temp = NULL;
			break;
		}
	}
	temp = Head;
	while(1)		// Max No. 찾기
	{		
		if(Head== NULL)	// 파일이 없을때
		{
				break;			
		}
		else
		{
			temp = temp->NextNode;
			if (max < temp->no)
			{
				max = temp->no;				
			}
			if (temp == Head)
			{
				break;
			}
		}
	}
	return (max+1); //다음에 사용할 변수라서 +1 을 한다.
}

//신규 아이템을 선택 한다.
Node* NewItem()
{
	Node* pNew = NULL;
	char name[_LENTH_NAME_]	= {0};
	char phone[_LENTH_PHONE_]	= {0};
	int ch = 0;
	int index = 0;
	int nRet = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*\t순    번: (%3d)                                                                          *\n",_noSeq);
	printf("\t*\t이    름: ");  nRet = InputChar(name,sizeof(name));
	printf("\t*\t전화번호: ");  InputChar(phone,sizeof(phone));
	printf("\t**********************************************************************************************\n");	
	if(strlen(name) == 0  ||  strlen(phone) == 0)
	{
		SetLastMessage("입력 되지 않은 값이 있습니다.");
	}
	else
	{
		pNew = (Node *)malloc(sizeof(Node)); 
		pNew->no = _noSeq;
		strncpy(pNew->name, name, sizeof(name));
		strncpy(pNew->phone, phone,sizeof(phone));
		pNew->PrevNode = NULL;
		pNew->NextNode = NULL;
		_noSeq++;
	}
	return pNew;
}
//수정할 아이템을 선택 한다.
int ChangeItem()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*수정할 데이터를 선택 하시기 바랍니다.*\n");
	printf("\t*번     호: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//삭제할 아이템을 선택 한다.
int DeleteItme()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*삭제할 아이템을 선택 하세요.*\n");
	printf("\t*번     호: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//검색할 이름을 선택 한다.
int SearchName(char* szOutName)
{
	char sztmpName[255]	= {0};
	int selNum  = 0;	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*검색할 이름을 검색 하세요ㅜ ? .*\n");
	printf("\t*이     름: ");  InputChar(sztmpName,sizeof(sztmpName));
	printf("\t**********************************************************************************************\n");
	if(strlen(sztmpName) != 0)
	{
		strcpy(szOutName,sztmpName);
	}
	return strlen(sztmpName);
}
//아이텀의 No 를 반환 한다.
int SearchNo()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*검색할 데이터를 선택 하시기 바랍니다.*\n");
	printf("\t*번     호: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//아이템을 이름순으로 정렬 한다
int SortItme()
{
	ascending_sort(Head);
	SetLastMessage("내림차순(Name) 으로 정렬 되었습니다.");
}

int main(void)
{
	//int maxNo;
	Node* pNode = NULL;
	eMenu selMenu = eNone;
	_noSeq = LoadData(); // 파일리드시 No 최고값 반환
	
	SetLastMessage("전화번호부를 처음 실행 합니다.");
	do
	{
		system("cls");
		displayData(selMenu);
		selMenu = displayMenu();

		switch(selMenu)
		{
		case eNew:	// 입력
			pNode = NewItem();
			if(pNode != NULL)
			{
				char buff[255] = {0};
				AppendNode(&Head, CreateNode(pNode->no,pNode->name, pNode->phone));
				sprintf(buff,"Num:[%d] ,Name: [%s] ,Phone: [%s] 데이터가 추가 되었습니다.",pNode->no,pNode->name,pNode->phone);
				free(pNode); pNode  = NULL;
				SetLastMessage(buff);
			}
			break;
		case eChg:	// 수정
			{
				char name[_LENTH_NAME_]	= {0};
				char phone[_LENTH_PHONE_]	= {0};
				int nNo = 0;
				nNo = ChangeItem();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("선택된 데이터가 없습니다.");
				}
				else
				{

					//pNode
					printf("\t*\t순    번: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t이    름: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t전    번: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");
					printf("\t*\t순    번: [%3d]                                                                         *\n",pNode->no);
					printf("\t*\t이    름: ");  InputChar(name,sizeof(name));
					printf("\t*\t전    번: ");  InputChar(phone,sizeof(phone));
					printf("\t**********************************************************************************************\n");
					name[20-1] = 0x00;  //buffer overflow 를 방지 하지 위하여
					phone[12-1] = 0x00; //buffer overflow 를 방지 하지 위하여
					if(strlen(name) == 0  ||  strlen(phone) == 0)
					{
						SetLastMessage("입력 되지 않은 값이 있습니다.");
					}
					else
					{
						strncpy(pNode->name, name, sizeof(name));
						strncpy(pNode->phone, phone,sizeof(phone));
						SetLastMessage("[수정] 명령이 실행되었습니다.");
					}
				}
			}
			break;
		case eDel:	// 삭제
			{
				char name[_LENTH_NAME_]	= {0};
				char phone[_LENTH_PHONE_]	= {0};
				int nNo = 0;
				nNo = DeleteItme();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("선택된 데이터가 없습니다.");
				}
				else
				{
					char buff[2];
					//pNode
					printf("\t*\t순    번: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t이    름: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t전    번: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");
					printf("\t*\t삭제 하시겠습니가 ? (Y/N) ");  InputChar(buff,sizeof(buff));
					printf("\t**********************************************************************************************\n");
					if(toupper(buff[0]) == (int)'Y' ) //소문자시 대문자로 변환
					{
						RemoveNode(&Head, pNode);
						SetLastMessage("[삭제] 명령이 실행되었습니다.");
#ifdef _ASSERT_
						assert(0);
#endif
						//삭제. 
					}
				}
			}
			break;
		case eSearchName:	// 검색
			{				
				char szName[255];
				Node *searchResult;
				SearchName(szName);
				printf("\t이름으로 검색 -> [%s]",szName);
				
				searchResult = FindNode(Head, szName);

				printf("번호: %d\n", searchResult->no);
				printf("이름: %s\n", searchResult->name);
				printf("전번: %s\n", searchResult->phone);
				getchar();


			}
			break;
		case eDetail:	// 상세
			{
				int nNo = 0;
				nNo = SearchNo();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("선택된 데이터가 없습니다.");
				}
				else
				{
					//pNode
					printf("\t*\t순    번: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t이    름: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t전    번: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");					
					getchar();
				}
				
			}
			break;
		case eSort: //정렬
			SortItme();
			SetLastMessage("[정렬] 명령이 실행되었습니다.");
			break;
		case eExit:
			{
				int i = 0;
				WriteBinaryToDat((ppbook)Head);
#ifdef _ASSERT_
				assert(0);
#endif
				printf("\tApplication  Exit");
				for(i = 0 ; i < 10; i++)
				{
					printf(".");
					Sleep(300);
				}
			}
			break;
		case ePrePage:
			if(currentPage > 0)
			{
				currentPage--;
				SetLastMessage("[이전페이지] 명령이 실행되었습니다.");
			}
			break;
		case eNextPage:
			if(currentPage+1 < maxPageCnt())
			{
				currentPage++;			
				SetLastMessage("[다음페이지] 명령이 실행되었습니다.");
			}
			
			break;
	
		}
	}
	while(selMenu != eExit);
	return 0;
}

int maxPageCnt()
{
	int totcnt;
	int maxPage;
	totcnt = 0;
	maxPage = 0;
	
	totcnt = GetNodeCount(Head);

	maxPage = totcnt/_PAGE_ITEM_COUNT_;
	if((totcnt % _PAGE_ITEM_COUNT_) != 0)
	{
		maxPage++;
	}
	return maxPage ;

}
