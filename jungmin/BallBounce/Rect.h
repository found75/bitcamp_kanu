#ifndef _RECT_H_
#define _RECT_H_
struct _pos
{
	int row;
	int col;
};

enum _eMove
{
	UpRight = 0,
	DownRight,
	DownLeft,
	UpLeft
};

enum _eDege
{
	Up = 0,
	Right,
	Left,
	Down
};

typedef enum _eDege  eEge;
typedef enum _eMove eMove;
typedef struct _pos Pos;

#define _ROW_ 30
#define _COL_ 40

//������ ��ġ�� �����̸� �׸���.
void Draw(Pos pos);
void Remove(Pos pos);

//���� ��ġ�� ��ȯ �Ѵ�.
Pos StartPos();
Pos NextPos(Pos pos);
int IseEge(eEge type,Pos pos,eMove dirct);
eMove NextDirect(); //���� ���� ������ ��ȯ �Ѵ�.
void draw_main();
void draw_main2();
//extern eMove mvDirect[4] ={DownRight, UpRight,UpLeft,DownLeft};
//extern int _nDirect = 0; //���� ���� �ε����� ���� �Ѵ�.
////���� ���� ���� ��ġ�� �����Ѵ�.
//extern eMove _curDire = DownRight;
//extern Pos _curPos;

extern eMove mvDirect[4];
extern int _nDirect; //���� ���� �ε����� ���� �Ѵ�.
//���� ���� ���� ��ġ�� �����Ѵ�.
extern eMove _curDire;
extern Pos _curPos;

#endif