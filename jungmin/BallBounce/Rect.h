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

//지정된 위치에 돌덩이를 그린다.
void Draw(Pos pos);
void Remove(Pos pos);

//시작 위치를 반환 한다.
Pos StartPos();
Pos NextPos(Pos pos);
int IseEge(eEge type,Pos pos,eMove dirct);
eMove NextDirect(); //다음 진행 방향을 반환 한다.
void draw_main();
void draw_main2();
//extern eMove mvDirect[4] ={DownRight, UpRight,UpLeft,DownLeft};
//extern int _nDirect = 0; //진행 방향 인덱스르 저장 한다.
////현재 진행 방향 위치를 저장한다.
//extern eMove _curDire = DownRight;
//extern Pos _curPos;

extern eMove mvDirect[4];
extern int _nDirect; //진행 방향 인덱스르 저장 한다.
//현재 진행 방향 위치를 저장한다.
extern eMove _curDire;
extern Pos _curPos;

#endif