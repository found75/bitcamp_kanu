#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <assert.h>

#include "circulardoublelinkedlist.h"
#include "BinaryInOut.h"

/*  TODO ���� ���� ���� �ϼ���. (2016.11.29)
	history
	2016.11.16
	1. ȭ�� ���̾ƿ� ����.
	2. ��� ��ȸ ȭ�鿡�� ���� [000001] �������� ǥ�� �Ǵ� ���� [      1] �������� ǥ�� �ǰ� ����. (�ű�,������ ���� ó��.)
	3. ���α׷� ���� ����� progress �޼��� �߰�.
	4. Page �۾��� Page�� ǥ�õǴ� �����ۼ� ������ _PAGE_ITEM_COUNT_ ������ ����.
	5. LoadData() ������ ������ ���� �߻����� ����.
	6. typedef struct tagNode  char name[_LENTH_NAME_]; char phone[_LENTH_PHONE_];  ���� ����.
	7. maxCnt -> maxPageCnt  �޼ҵ� �̸� ����.
	8. main.c ���� ����� ���� ���� ����ȭ. [static ]
	9. SortItme() �Լ� �ƱԸ�Ʈ ����
	10. �ڵ� ���� ������� �ʴ� ���� ����.
	11. typedef struct tagNode ����ü �ϳ��� ����. (BinaryInOut.h , circulardoublelinkedlist.h)
	12. InputChar �޼ҵ�. SDIIN �� �Է½� ���� ũ�� �ʰ� �ϸ� ����� �޼��� ǥ��.
	13. [����],[����] ������ �޼��� �Լ� �����ÿ��� ȣ���ϰ� ����.
*/

//#define _ASSERT_
#define _PAGE_ITEM_COUNT_ 10 //1 Page �� ǥ���� �ִ� ������ �ټ�.

enum _eMenu
{
	eNone= 0,
	eNew = 1,
	eChg,
	eDel,
	eSearchName, //�̸� �˻�
	eDetail,	 //��ȣ �˻�
	eSort,
	ePrePage,	//7�� ��������
	eNextPage,  //8�� ����������
	eExit		//9�� ����
	
};
typedef enum _eMenu eMenu;

Node* Head = NULL;
static char szMessage[255] = {0}; //���� �޼����� ������ ����
static int speed[4] = {150,70,50,30}; //tApplication start message �ӵ� ����

static int _noSeq = 1; //���� ���� �����Ѵ�. (���� �ε�� ���� ū������ ������Ʈ �ʿ�.) - g
static int currentPage = 0;	//���� ������

int maxPageCnt(); //�ִ� ������ ���� ��ȯ �Ѵ�.

//ȭ�� ��ܿ� ǥ���� �޼����� ���� �Ѵ�.
void SetLastMessage(char* szStr)
{
	memset(szMessage,0x00,sizeof(szMessage));
	strcpy(szMessage,szStr);
}

//STD IN �� �Է��� �޴´�.
//return -1 �̸� �Է°� �߰�.
 int InputChar(char* szBuff,int pCnt)
{
	int nCnt	= 0;
	int ch		= 0;
	while(1)
	{
		ch = getchar();
		if(ch == '\n' || ch == 0x1b) //Enter Or Esc �ڵ尡��� ���� ���� �Ѵ�.
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
			printf("\t*\t����� ���̸� �ʰ� �Ͽ����ϴ�. (�ʰ��� �����ʹ� ������ ���� �մϴ�.)\n");
			break; //���� �Է� �ʰ��� ����
		}		
	}
	fflush(stdin);
	szBuff[nCnt] = 0x00;
	return nCnt;
}
//Menu ���� String �����κ��� �ϳ�.
char* menuTStirng(eMenu menu)
{
	switch(menu)
	{
	case eNone:
		return "None";
	case eNew:
		return "�ű�";
	case eChg:
		return "����";
	case eDel:
		return "����";
	case eSearchName:
		return "�˻�";
	case eDetail:
		return "�󼼺���";
	case eSort:
		return "����";
	case eExit:
		return "����";
	}
	return "error";
}
//���� �޴� �޼����� ȭ�鿡 ǥ�� �Ѵ�.
int displayMenu()
{	
	eMenu selMenu;
	printf("\t**********************************************************************************************\n");
	printf("\t*���� ������(7)    �ű�(1),����(2),����(3),�˻�(4),��(5),����(6),����(9)      ����������(8)*\n");
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
//�����͸� ȭ�鿡 ǥ�� �Ѵ�.
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
	printf("\t*\t%5s\t\t%20s\t\t%20s                 *\n","����","�̸�","��ȭ��ȣ");
	printf("\t**********************************************************************************************\n");
	
	nodecnt = GetNodeCount(Head);        // ��� �� ��� �׽�Ʈ
	
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
	printf("\t*(%3d/%3d)�������� (%2d) ���� �����Ͱ� ��ȸ �Ǿ����ϴ�.                                       *\n",currentPage+1,maxPageCnt(),row-1 - _PAGE_ITEM_COUNT_*currentPage);
	printf("\t**********************************************************************************************\n");

	return nodecnt;
}

//���Ͽ��� �����͸� �ε��Ѵ�.
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

	while(1)		//������ �о���� ���Ͽ���
	{
		temp = CreateNode(1, "�ӽ�", "00000000000");
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
	while(1)		// Max No. ã��
	{		
		if(Head== NULL)	// ������ ������
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
	return (max+1); //������ ����� ������ +1 �� �Ѵ�.
}

//�ű� �������� ���� �Ѵ�.
Node* NewItem()
{
	Node* pNew = NULL;
	char name[_LENTH_NAME_]	= {0};
	char phone[_LENTH_PHONE_]	= {0};
	int ch = 0;
	int index = 0;
	int nRet = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*\t��    ��: (%3d)                                                                          *\n",_noSeq);
	printf("\t*\t��    ��: ");  nRet = InputChar(name,sizeof(name));
	printf("\t*\t��ȭ��ȣ: ");  InputChar(phone,sizeof(phone));
	printf("\t**********************************************************************************************\n");	
	if(strlen(name) == 0  ||  strlen(phone) == 0)
	{
		SetLastMessage("�Է� ���� ���� ���� �ֽ��ϴ�.");
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
//������ �������� ���� �Ѵ�.
int ChangeItem()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*������ �����͸� ���� �Ͻñ� �ٶ��ϴ�.*\n");
	printf("\t*��     ȣ: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//������ �������� ���� �Ѵ�.
int DeleteItme()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*������ �������� ���� �ϼ���.*\n");
	printf("\t*��     ȣ: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//�˻��� �̸��� ���� �Ѵ�.
int SearchName(char* szOutName)
{
	char sztmpName[255]	= {0};
	int selNum  = 0;	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*�˻��� �̸��� �˻� �ϼ���� ? .*\n");
	printf("\t*��     ��: ");  InputChar(sztmpName,sizeof(sztmpName));
	printf("\t**********************************************************************************************\n");
	if(strlen(sztmpName) != 0)
	{
		strcpy(szOutName,sztmpName);
	}
	return strlen(sztmpName);
}
//�������� No �� ��ȯ �Ѵ�.
int SearchNo()
{
	char szNo[255]	= {0};
	int selNum  = 0;
	
	int ch = 0;
	int index = 0;
	printf("\t**********************************************************************************************\n");
	printf("\t*�˻��� �����͸� ���� �Ͻñ� �ٶ��ϴ�.*\n");
	printf("\t*��     ȣ: ");  InputChar(szNo,sizeof(szNo));
	selNum = atoi(szNo);
	printf("\t**********************************************************************************************\n");
	return selNum;
}
//�������� �̸������� ���� �Ѵ�
int SortItme()
{
	ascending_sort(Head);
	SetLastMessage("��������(Name) ���� ���� �Ǿ����ϴ�.");
}

int main(void)
{
	//int maxNo;
	Node* pNode = NULL;
	eMenu selMenu = eNone;
	_noSeq = LoadData(); // ���ϸ���� No �ְ� ��ȯ
	
	SetLastMessage("��ȭ��ȣ�θ� ó�� ���� �մϴ�.");
	do
	{
		system("cls");
		displayData(selMenu);
		selMenu = displayMenu();

		switch(selMenu)
		{
		case eNew:	// �Է�
			pNode = NewItem();
			if(pNode != NULL)
			{
				char buff[255] = {0};
				AppendNode(&Head, CreateNode(pNode->no,pNode->name, pNode->phone));
				sprintf(buff,"Num:[%d] ,Name: [%s] ,Phone: [%s] �����Ͱ� �߰� �Ǿ����ϴ�.",pNode->no,pNode->name,pNode->phone);
				free(pNode); pNode  = NULL;
				SetLastMessage(buff);
			}
			break;
		case eChg:	// ����
			{
				char name[_LENTH_NAME_]	= {0};
				char phone[_LENTH_PHONE_]	= {0};
				int nNo = 0;
				nNo = ChangeItem();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("���õ� �����Ͱ� �����ϴ�.");
				}
				else
				{

					//pNode
					printf("\t*\t��    ��: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");
					printf("\t*\t��    ��: [%3d]                                                                         *\n",pNode->no);
					printf("\t*\t��    ��: ");  InputChar(name,sizeof(name));
					printf("\t*\t��    ��: ");  InputChar(phone,sizeof(phone));
					printf("\t**********************************************************************************************\n");
					name[20-1] = 0x00;  //buffer overflow �� ���� ���� ���Ͽ�
					phone[12-1] = 0x00; //buffer overflow �� ���� ���� ���Ͽ�
					if(strlen(name) == 0  ||  strlen(phone) == 0)
					{
						SetLastMessage("�Է� ���� ���� ���� �ֽ��ϴ�.");
					}
					else
					{
						strncpy(pNode->name, name, sizeof(name));
						strncpy(pNode->phone, phone,sizeof(phone));
						SetLastMessage("[����] ����� ����Ǿ����ϴ�.");
					}
				}
			}
			break;
		case eDel:	// ����
			{
				char name[_LENTH_NAME_]	= {0};
				char phone[_LENTH_PHONE_]	= {0};
				int nNo = 0;
				nNo = DeleteItme();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("���õ� �����Ͱ� �����ϴ�.");
				}
				else
				{
					char buff[2];
					//pNode
					printf("\t*\t��    ��: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");
					printf("\t*\t���� �Ͻðڽ��ϰ� ? (Y/N) ");  InputChar(buff,sizeof(buff));
					printf("\t**********************************************************************************************\n");
					if(toupper(buff[0]) == (int)'Y' ) //�ҹ��ڽ� �빮�ڷ� ��ȯ
					{
						RemoveNode(&Head, pNode);
						SetLastMessage("[����] ����� ����Ǿ����ϴ�.");
#ifdef _ASSERT_
						assert(0);
#endif
						//����. 
					}
				}
			}
			break;
		case eSearchName:	// �˻�
			{				
				char szName[255];
				Node *searchResult;
				SearchName(szName);
				printf("\t�̸����� �˻� -> [%s]",szName);
				
				searchResult = FindNode(Head, szName);

				printf("��ȣ: %d\n", searchResult->no);
				printf("�̸�: %s\n", searchResult->name);
				printf("����: %s\n", searchResult->phone);
				getchar();


			}
			break;
		case eDetail:	// ��
			{
				int nNo = 0;
				nNo = SearchNo();
				pNode = FindNode_index(Head,nNo);
				if(pNode == NULL)
				{
					SetLastMessage("���õ� �����Ͱ� �����ϴ�.");
				}
				else
				{
					//pNode
					printf("\t*\t��    ��: [%3d]                                                                       *\n",pNode->no);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->name);
					printf("\t*\t��    ��: [%20s]                                                                       *\n",pNode->phone);
					printf("\t**********************************************************************************************\n");					
					getchar();
				}
				
			}
			break;
		case eSort: //����
			SortItme();
			SetLastMessage("[����] ����� ����Ǿ����ϴ�.");
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
				SetLastMessage("[����������] ����� ����Ǿ����ϴ�.");
			}
			break;
		case eNextPage:
			if(currentPage+1 < maxPageCnt())
			{
				currentPage++;			
				SetLastMessage("[����������] ����� ����Ǿ����ϴ�.");
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
