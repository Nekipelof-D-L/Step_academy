#include "pch.h"
#include <iostream>
#include <conio.h>
#include "../ClassInCpp/consts.h"
#include "../ClassInCpp/strutils.h"
#include "../ClassInCpp/consoleroutine.h"
#include "../ClassInCpp/tgeom.h"
#include "../ClassInCpp/tpoint.h"
#include "../ClassInCpp/trect.h"
#include "../ClassInCpp/list2link.h"

void printStatus1(short x, short y, short Left, short Top) {
	char *s = (char *)malloc(255 * sizeof(char));
	nullStr(s, 255);
	strcpy_s(s, 255, "F2=Save DEL=Delete F3=TPoint(Bank) F4=TPoint(House) F5=TPoint(Cafe) F6=TPoint(Shop) ");
	consoleSetColors(clBlack, clLightRed);
	consoleGotoXY(Left, Top);
	printf("x:3%d y:%3d      %s", x, y, s);
	free(s);
}

list2 *map_add_TPoint(list2 *map, short x, short y, TPointType t, 
	ConsoleColors color, ConsoleColors bgcolor) {
	TPoint *p = new TPoint();
	p->x = x;
	p->y = y;
	p->typ = t;
	p->color = color;
	p->bgcolor = bgcolor;
	list2 *result = list2_ins(map);
	result->geom = p;
	return result;
}
int map_contains(list2 *map, short x, short y) {
	list2 *item = list2_gotofirst(map);
	while (NULL != item) {
		if (1 == item->geom->Contains(x,y)) {
			return 1;
		}
		item = item->next;
	}
	return 0;
}

int main() {
	TRect *console = new TRect();
	console->x = 1;
	console->y = 1;
	console->width  = consoleSizeX() - 1;
	console->height = consoleSizeY() - 1;
	
	TPoint *tank = new TPoint();
	tank->x = console->x + console->width  / 2;
	tank->y = console->y + console->height / 2;
	tank->typ     = ptPen;
	tank->bgcolor = clLightGreen;
	tank->color   = clLightGreen;

	list2 *map = NULL;

	int flagExit = 0;
	int keyPressed = 0;
	do {
		printStatus1(tank->x, tank->y, 0, 0);
		list2_print(map);
		tank->Print();
		consoleGotoXY(tank->x, tank->y);
		keyPressed = _getch();
		tank->Erase();
		switch (keyPressed) {
		    case KEY_ESCAPE: {
				flagExit = 1;
				break;
		    }
			case KEY_DELETE: {
				if (NULL != map) {
					list2 *p = list2_gotofirst(map);
					while (NULL != p) {
						if (1 == p->geom->Contains(tank->x, tank->y)) {
							list2 *ptemp = p->next;
							if (p == list2_gotofirst(map)) {
								map = list2_gotolast(map);
							}
							if (p == list2_gotolast(map)) {
								map = list2_gotofirst(map);
							}
							if (1 == list2_count(map)) {
								map = NULL;
							}
							list2_del(p);
							p = ptemp;
						} else {
							p = p->next;
						}
					}
				}
				break;
			}
			case KEY_LEFT: {
				if (tank->x > console->x) {
					tank->x--;
				}
				break;
			}
			case KEY_RIGHT: {
				if (tank->x < console->width) {
					tank->x++;
				}
				break;
			}
			case KEY_UP: {
				if (tank->y > console->y) {
					tank->y--;
				}
				break;
			}
			case KEY_DOWN: {
				if (tank->y < console->height) {
					tank->y++;
				}
				break;
			}
			case KEY_F2: {
				if (NULL != map) {
					list2_savetofile(map, "d:\\map.txt");
				}
			}
			case KEY_F3: {
				if (0 == map_contains(map, tank->x, tank->y)) {
					map = map_add_TPoint(map, tank->x, tank->y, ptBank, clBlack, clLightGreen);
				}
				break;
			}
			case KEY_F4: {
				if (0 == map_contains(map, tank->x, tank->y)) {
					map = map_add_TPoint(map, tank->x, tank->y, ptHouse, clWhite, clBrown);
				}
				break;
			}
			case KEY_F5: {
				if (0 == map_contains(map, tank->x, tank->y)) {
					map = map_add_TPoint(map, tank->x, tank->y, ptCafe, clWhite, clLightRed);
				}
				break;
			}
			case KEY_F6: {
				if (0 == map_contains(map, tank->x, tank->y)) {
					map = map_add_TPoint(map, tank->x, tank->y, ptShop, clBlack, clLightCyan);
				}
				break;
			}
		}
	} while (0 == flagExit);

	delete tank;
	//delete console;
	
	consoleSetColors(clWhite, clBlack);
	return 0;
}