#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(void) {
	HANDLE hStdOut;
	COORD position;
	DWORD numWritten;
	WORD color;

	system("cls");
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hStdOut , BACKGROUND_GREEN );
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |Åú|Åú|  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |Åú|Åú|  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	printf(" |  |  |  |  |  |  |  |  |\n");
	printf(" -------------------------\n");
	color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | BACKGROUND_GREEN;
	position.X = 11;  position.Y = 7;
	FillConsoleOutputAttribute(hStdOut , color , 2, position , &numWritten );
	position.X = 14;  position.Y = 9;
	FillConsoleOutputAttribute(hStdOut , color , 2, position , &numWritten );

	color = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	SetConsoleTextAttribute(hStdOut , color );

	return  EXIT_SUCCESS;
}