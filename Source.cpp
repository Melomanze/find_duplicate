#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "ConsoleColor.h"

using namespace std;

struct track
{
	string artist;
	string name;
	string full = "";
	string duration;
	bool dub = false;
	track* next = NULL;
	track* prev = NULL;
};
track* First = NULL;
track* Last = NULL;

void ParsingSongFromFile() {
	string s1, s2, s, m, d;
	ifstream f("C:\\Users\\root\\Desktop\\2.txt");

	track* p;
	if (!f.eof()) {
		getline(f, s1);
		getline(f, s2);
		getline(f, d);
		getline(f, s);
		//s = s1 + " -" + s2;
		First = new track;
		p = First;
		p->artist = s1;
		p->name = s2;
		p->full;
		p->duration = d;
		p->prev = NULL;
		while (!f.eof()) {
			getline(f, s1);
			getline(f, s2);
			getline(f, d);
			getline(f, s);
			s = s1 + " - " + s2;
			p->next = new track;
			p->next->prev = p;
			p = p->next;
			p->artist = s1;
			p->name = s2;
			p->duration = d;
		}
		Last = p;
		//p->next = NULL;
	}
	f.close();
}

bool trigger(bool p) {
	return p ? false : true;
}

void CompareSong(bool a, bool n, bool d) {
	SetConsoleOutputCP(CP_UTF8);
	ParsingSongFromFile();
	track* p;
	track* c;
	track* t;
	int k = NULL;

	p = First;
	while (p != NULL) {
		if (a) p->full += p->artist;
		if (a && n) p->full += " -";
		if (n) p->full += p->name;
		if (d) p->full += " " + p->duration;
		p = p->next;
	}
	p = First;
	while (p != NULL) {
		c = p->next;
		while (c != NULL) {
			if ((p->full == c->full) && (p->dub == false)) {
				p->dub = true;
				t = c->prev;
				if (c->next != NULL) {
					c->next->prev = c->prev;
					c->prev->next = c->next;
				}
				else {
					c->prev->next = NULL;
				}
				free(c);
				c = t;
			}
			//if (p->full == c->full) cout << p->full << " | " << c->full << endl;
			//add commit t
			c = c->next;
		}
		if (p->dub == true) cout << p->full << endl;
		p = p->next;
	}
	SetConsoleOutputCP(1251);
	cout << "Нажмите любую кнопку чтобы продолжить...";
	k = _getch();
	if (k != NULL) system("cls");
}

void ClearFlagDub() {
	track* p;
	p = First;
	while (p != NULL) {
		p->dub = false;
		p = p->next;
	}
}

int main() {
	//SetConsoleOutputCP(CP_UTF8); //при работе с файлами
	SetConsoleOutputCP(1251); //при работе с "cout"
	bool a = 0;
	bool n = 0;
	bool d = 0;
	bool err = 0;
	int key = NULL;
	while (key != 27) {
		//ClearFlagDub();
		cout << white << "------------------------\n";
		if (err == true) cout << "| Статус: " << red << "Ошибка" << white << "       |\n";
		else cout << white << "| Статус:              |\n";
		cout << "| Провести поиск по:   | \n";
		if (a == true) cout << white << "|" << green << " [1] Артисту" << white << "          |\n";
		else cout << white << "|" << red << " [1] Артисту" << white << "          |\n";
		if (n == true) cout << white << "|" << green << " [2] Названию" << white << "         |\n";
		else cout << white << "|" << red << " [2] Названию" << white << "         |\n";
		if (d == true) cout << white << "|" << green << " [3] Длительности" << white << "     |\n";
		else cout << white << "|" << red << " [3] Длительности" << white << "     |\n";
		cout << white << "------------------------\n|" << green << " [Enter] Начать поиск" << white << " |\n|" << red << " [Esc] Выход" << white << "          |\n------------------------\n";
		key = _getch(); //получение кода нажатой кнопки
		system("cls");
		err = false;
		if (key == '1') a = trigger(a); //триггер переменной true/false
		if (key == '2') n = trigger(n);
		if (key == '3') d = trigger(d);
		if (key == 13 && (a == true || n == true || d == true)) CompareSong(a, n, d);
		if (key == 13 && a == false && n == false && d == false) err = true;
	}
}