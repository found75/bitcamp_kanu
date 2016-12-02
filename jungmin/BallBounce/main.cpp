#include <stdio.h>
#include "turboc.h"


void draw_main2();
void main()
{
	draw_main2();
}

#define _ROW_ 30
#define _COL_ 30

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
		printf("бс");
		Sleep(100);

		gotoxy(0,0);
		printf("%03d,%03d",col,row);
	
	}
}