#include "Rect.h"
#include "turboc.h"

eMove mvDirect[4] ={DownRight, UpRight,UpLeft,DownLeft};
int _nDirect = 0; //���� ���� �ε����� ���� �Ѵ�.
//���� ���� ���� ��ġ�� �����Ѵ�.
eMove _curDire = DownRight;
Pos _curPos;

//������ ��ġ�� �����̸� �׸���.
void Draw(Pos pos)
{
	gotoxy(pos.col,pos.row);
	printf("��");

}
void Remove(Pos pos)
{
	gotoxy(pos.col,pos.row);
	printf(" ");
}
//���� ��ġ�� ��ȯ �Ѵ�.
Pos StartPos()
{
	Pos p = {10/2,0};
	return p;
}

Pos NextPos(Pos pos,eMove dirct)
{
	Pos newPos;
	switch(dirct)
	{
	case UpRight:
		newPos.row = pos.row-1;
		newPos.col = pos.col+1;
		break;
	case DownRight:
		newPos.row = pos.row+1;
		newPos.col = pos.col+1;
		break;
	case DownLeft:
		newPos.row = pos.row+1;
		newPos.col = pos.col-1;
		break;
	case UpLeft:
		newPos.row = pos.row-1;
		newPos.col = pos.col-1;
		break;
	}
	return newPos;
}
int IseEge(eEge type,Pos pos,eMove dirct)
{
	switch(type)
	{
	case Up:
		if(pos.row <= 0 && dirct == UpLeft)
			return 1;
		break;
	case Right:
		if(pos.col >= _COL_ && dirct == UpRight)
			return 1;
		break;
	case Left:
		if(pos.col <= 0 && dirct == DownLeft)
			return 1;
		break;
	case Down:
		if(pos.row >= _ROW_ && dirct == DownRight)
			return 1;
		break;
	}
	return 0;
}

void display()
{
//	enum _eMove
//{
//	UpRight = 0,
//	DownRight,
//	DownLeft,
//	UpLeft
//};
//
//enum _eDege
//{
//	Up = 0,
//	Right,
//	Left,
//	Down
//};
}
void draw_main()
{
	clrscr();
	int max = 1000;
	int i = 0;
	while(1)
	{
		if(i == 0)
		{
			_curPos = StartPos();
			_curDire = mvDirect[_nDirect];
			Draw(_curPos);
			i = 1;
		}


		if(IseEge(Up,_curPos,_curDire) == 1)
		{
			_curDire =NextDirect();
		}
		else if(IseEge(Right,_curPos,_curDire) == 1)
		{
			_curDire =NextDirect();
		}
		else if(IseEge(Left,_curPos,_curDire) == 1)
		{
			_curDire =NextDirect();

		}
		else if(IseEge(Down,_curPos,_curDire) == 1)
		{
			_curDire =NextDirect();
		}

		Remove(_curPos);
		_curPos = NextPos(_curPos,_curDire);
		Draw(_curPos);

		Sleep(50);
		//getchar();
	}
}
eMove NextDirect()
{
	_nDirect++;
	return mvDirect[_nDirect%4];
}

void draw_main2()
{
	int row = 10 ,col = 0;
	bool bDirectrow = true;
	bool bDirectcol = false;

	while(1)
	{
		gotoxy(col,row);
		printf(" ");

		if(_COL_ <= col )
			bDirectcol = false;
		else if(col == 0)
			bDirectcol = true;

		if(_ROW_ <= row )
			bDirectrow = false;
		else if(row == 0)
			bDirectrow = true;

		if(bDirectrow )
			row++;
		else
			row--;

		if(bDirectcol )
			col++;
		else
			col--;


		gotoxy(col,row);
		printf("��");
		Sleep(100);

		gotoxy(0,0);
		printf("%03d,%03d",col,row);
	
	}
}




