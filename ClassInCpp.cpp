#include "pch.h"
#include <iostream>
#include <conio.h>
#include "consoleroutine.h"
#include "consts.h"
#include "tgeom.h"
#include "tpoint.h"
#include "trect.h"
#include "tcircle.h"
#include "list2link.h"

void printState(list2 *points) {
	consoleSetColors(clBlack, clLightGreen);
	consoleGotoXY(0, 0);
	printf("count = %d         ", list2_count(points) );
}

void clearBoomPoints(list2 *points, list2 *boom) {
	list2 *p = NULL;
	list2 *b = list2_gotofirst(boom);
	while (NULL != b) {
		TCircle *c = (TCircle*)b->geom;
		p = list2_gotofirst(points);
		while (NULL != p) {
			TPoint *t = (TPoint *)p->geom;
			if (0 != c->Contains(t->x, t->y)) {
				list2 *nxt = p->next;
				list2_del(p);
				p = nxt;
			}else{
				p = p->next;
			}
		}
		b = b->next;
	}
}

int main(int argc, char*argv[]) {
/*
    srand(100000);
	list2 *list = NULL;
	for (int i = 0; i < 1000; i++) {
		list = list2_ins(list);
		switch (rand() % 3 ) {
		  case 0: list->geom = new TPoint ; break;
		  case 1: list->geom = new TRect  ; break;
		  case 2: list->geom = new TCircle; break;
		}
		list->geom->id = i;
		list->geom->InitTest();
	}
	list2_print(list);
	list2_savetofile(list, "d:\\test_lis2link_classes.txt");
	list2_clear(list);
*/
	list2 *list = list2_loadfromfile(NULL, "d:\\test_lis2link_classes.txt");
	list2_print(list);
	
	int key = _getch();

/*
	list2 *points = NULL;
	for (int i = 0; i < 300; i++) {
		points = list2_ins(points);
		points->geom = new TPoint;
	}
	list2 *boom = NULL;
	list2 *rect = NULL;

	list2_print(points);

	int key  = 0; // нажатая пользователем клавиша
	int flag = 0;
	do {
		list2_print(boom);
		list2_print(rect);
		printState(points);
		consoleGotoXY(0, 0);
		key = _getch();
		consoleSetColors(clWhite, clBlack);
		switch (key) {
		    case KEY_ESCAPE:
				flag = 1;
				break;
			case KEY_F1:
				if (NULL == boom) {
					for (int i = 0; i < 10; i++) {
						boom = list2_ins(boom);
						boom->geom = new TCircle;
					}
				}else {
					clearBoomPoints(points, boom);
					list2_clear(boom);
					boom = NULL;
				}
				break;
			case KEY_F2:
				if (NULL == rect) {
					for (int i = 0; i < 10; i++) {
						rect = list2_ins(rect);
						rect->geom = new TRect;
					}
				} else {
					list2_clear(rect);
					rect = NULL;
				}
				break;
		}
	} while (0 == flag);

	list2_clear(boom);
	list2_clear(rect);
	list2_clear(points);
*/
	consoleSetColors(clWhite, clBlack);
	return (0);
}
