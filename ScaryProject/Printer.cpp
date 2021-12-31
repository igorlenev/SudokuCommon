#include <iostream>
#include <string>
#include <Windows.h>
#include "Printer.h"
#include "Generator.h"
using namespace std;

string lastInput;
int gamemode;
extern int ezFieldG[4][4], midFieldG[9][9];
extern bool ezFieldStatic[4][4], midFieldStatic[9][9];
extern int ezField[4][4], midField[9][9];

// Перемещение курсора
void onXY(int x, int y) {
	COORD p;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	p.X = x; p.Y = y;
	SetConsoleCursorPosition(handle, p);
}

// Быстрый перенос строки с отступом
void endlF() {
	cout << endl << " ";
}

// Вывод стартового меню
void printHeader() {
	endlF();
	cout << "---------------- Игорь Ленев, ИВБО-03-21, 2021 ----------------------"; endlF();
	cout << "/////////////////////////////////////////////////////////////////////"; endlF();
	cout << "//////      ////  //  ////    //////      ////  ///  ////  //  //////"; endlF();
	cout << "//////   ///////  //  ////  /  /////  //  ////  //  /////  //  //////"; endlF();
	cout << "//////      ////  //  ////  //  ////  //  ////    ///////  //  //////"; endlF();
	cout << "/////////   ////  //  ////  /  /////  //  ////  //  /////  //  //////"; endlF();
	cout << "//////      ////      ////    //////      ////  ///  ////      //////"; endlF();
	cout << "/////////////////////////////////////////////////////////////////////"; endlF();
	endlF(); endlF();
}

void printStart() {
	printHeader();
	cout << "Выберете режим игры:"; endlF();
	cout << "%game1 - 4x4, с помощью"; endlF();
	cout << "%game2 - 9x9, с помощью"; endlF();
	cout << "%game3 - 4x4, без помощи"; endlF();
	cout << "%game4 - 9x9, без помощи"; endlF();
}

// Вывод "помощи"
void help() {
	int x = 37;
	int y = 10;
	onXY(x, y);
	y++;
	cout << "--------- Список команд ---------";
	onXY(x, y);
	y++;
	cout << "%game1 - начать игру на малом по-";
	onXY(x, y);
	y++;
	cout << "  ле с подсказками";
	onXY(x, y);
	y++;
	cout << "%game2 - начать игру на обычном";
	onXY(x, y);
	y++;
	cout << "  поле с подсказками";
	onXY(x, y);
	y++;
	cout << "%game3 - начать игру на малом по-";
	onXY(x, y);
	y++;
	cout << "  ле без подсказок";
	onXY(x, y);
	y++;
	cout << "%game4 - начать игру на обычном";
	onXY(x, y);
	y++;
	cout << "  поле без подсказок";
	onXY(x, y);
	y++;
	cout << "---------------------------------";
	onXY(x, y);
	y++;
	cout << "%stop - выйти из игры";
	onXY(x, y);
	y++;
	cout << "%check - проверка решения";
	onXY(x, y);
	y++;
	cout << "---------------------------------";
	onXY(x, y);
	y++;
	cout << "Заполнение поля судоку реализу-";
	onXY(x, y);
	y++;
	cout << "ется по следующему принципу:";
	onXY(x, y);
	y++;
	cout << "вводится номер (литера) столбца,";
	onXY(x, y);
	y++;
	cout << "номер строки и выбранное значе-";
	onXY(x, y);
	y++;
	cout << "ние. Для обнуления значение \"0\".";
	onXY(x, y);
	y++;
	cout << "Пример: \"b25\", \"c20\"";
	onXY(x, y);
	y++;
	cout << "---------------------------------";

	onXY(1, 31);
}

void printEz() {
	cout << "    a b   c d  "; endlF();
	cout << "  +—————+—————+"; endlF();
	cout << "1 | " << ezFieldG[0][0] << " " << ezFieldG[0][1] << " | " << ezFieldG[0][2] << " " << ezFieldG[0][3] << " |"; endlF();
	cout << "2 | " << ezFieldG[1][0] << " " << ezFieldG[1][1] << " | " << ezFieldG[1][2] << " " << ezFieldG[1][3] << " |"; endlF();
	cout << "  +—————+—————+"; endlF();
	cout << "3 | " << ezFieldG[2][0] << " " << ezFieldG[2][1] << " | " << ezFieldG[2][2] << " " << ezFieldG[2][3] << " |"; endlF();
	cout << "4 | " << ezFieldG[3][0] << " " << ezFieldG[3][1] << " | " << ezFieldG[3][2] << " " << ezFieldG[3][3] << " |"; endlF();
	cout << "  +—————+—————+"; endlF();
}

// Генерация поля лёгкой сложности
void ezPrGen() {
	generateCheck(1);
}

// Вывод поля лёгкой сложности
void ezPr() {
	system("cls");
	printHeader();
	printEz();
	help();
}

// Смотреть на свой страх и риск
void printMid() {
	cout << "    a b c   e f g   h i j"; endlF();
	cout << "  +———————+———————+———————+"; endlF();
	cout << "1 | " << midFieldG[0][0] << " " << midFieldG[0][1] << " " << midFieldG[0][2] << " | " << midFieldG[0][3] << " " << midFieldG[0][4] << " " << midFieldG[0][5] << " | " << midFieldG[0][6] << " " << midFieldG[0][7] << " " << midFieldG[0][8] << " |"; endlF();
	cout << "2 | " << midFieldG[1][0] << " " << midFieldG[1][1] << " " << midFieldG[1][2] << " | " << midFieldG[1][3] << " " << midFieldG[1][4] << " " << midFieldG[1][5] << " | " << midFieldG[1][6] << " " << midFieldG[1][7] << " " << midFieldG[1][8] << " |"; endlF();
	cout << "3 | " << midFieldG[2][0] << " " << midFieldG[2][1] << " " << midFieldG[2][2] << " | " << midFieldG[2][3] << " " << midFieldG[2][4] << " " << midFieldG[2][5] << " | " << midFieldG[2][6] << " " << midFieldG[2][7] << " " << midFieldG[2][8] << " |"; endlF();
	cout << "  +———————+———————+———————+"; endlF();
	cout << "4 | " << midFieldG[3][0] << " " << midFieldG[3][1] << " " << midFieldG[3][2] << " | " << midFieldG[3][3] << " " << midFieldG[3][4] << " " << midFieldG[3][5] << " | " << midFieldG[3][6] << " " << midFieldG[3][7] << " " << midFieldG[3][8] << " |"; endlF();
	cout << "5 | " << midFieldG[4][0] << " " << midFieldG[4][1] << " " << midFieldG[4][2] << " | " << midFieldG[4][3] << " " << midFieldG[4][4] << " " << midFieldG[4][5] << " | " << midFieldG[4][6] << " " << midFieldG[4][7] << " " << midFieldG[4][8] << " |"; endlF();
	cout << "6 | " << midFieldG[5][0] << " " << midFieldG[5][1] << " " << midFieldG[5][2] << " | " << midFieldG[5][3] << " " << midFieldG[5][4] << " " << midFieldG[5][5] << " | " << midFieldG[5][6] << " " << midFieldG[5][7] << " " << midFieldG[5][8] << " |"; endlF();
	cout << "  +———————+———————+———————+"; endlF();
	cout << "7 | " << midFieldG[6][0] << " " << midFieldG[6][1] << " " << midFieldG[6][2] << " | " << midFieldG[6][3] << " " << midFieldG[6][4] << " " << midFieldG[6][5] << " | " << midFieldG[6][6] << " " << midFieldG[6][7] << " " << midFieldG[6][8] << " |"; endlF();
	cout << "8 | " << midFieldG[7][0] << " " << midFieldG[7][1] << " " << midFieldG[7][2] << " | " << midFieldG[7][3] << " " << midFieldG[7][4] << " " << midFieldG[7][5] << " | " << midFieldG[7][6] << " " << midFieldG[7][7] << " " << midFieldG[7][8] << " |"; endlF();
	cout << "9 | " << midFieldG[8][0] << " " << midFieldG[8][1] << " " << midFieldG[8][2] << " | " << midFieldG[8][3] << " " << midFieldG[8][4] << " " << midFieldG[8][5] << " | " << midFieldG[8][6] << " " << midFieldG[8][7] << " " << midFieldG[8][8] << " |"; endlF();
	cout << "  +———————+———————+———————+"; endlF();
}

// Генерация поля обычной сложности
void midPrGen() {
	generateCheck(2);
}

// Вывод поля обычной сложности
void midPr() {
	system("cls");
	printHeader();
	printMid();
	help();
}

// Проверка на возможность изменения и перевод в нужный формат
bool changeCheckPr(string input) {
	int a, i, j;
	if (input[0] < 90) a = int(input[0]) - 65;
	else a = int(input[0]) - 97;
	i = int(input[1]) - 49;
	j = int(input[2]) - 48;
	return changeCheck(i, a, j);
}

// Изменение и перевод в нужный формат
void changeCellPr(string input) {
	int a, i, j;
	if (input[0] < 90) a = int(input[0]) - 65;
	else a = int(input[0]) - 97;
	i = int(input[1]) - 49;
	j = int(input[2]) - 48;
	changeCell(i, a, j);
}

bool solveCheck() {
	bool test = genSolveCheck();
	return genSolveCheck();
}

//
bool helperCheck(string input) {
	int a, i, j;
	if (input[0] < 90) a = int(input[0]) - 65;
	else a = int(input[0]) - 97;
	i = int(input[1]) - 49;
	j = int(input[2]) - 48;
	if (gamemode == 1 && ezField[i][a] != j) { cout << " Вы введи значение, не выбранное генератором судоку. Подумайте ещё. "; return false; }
	if (gamemode == 2 && midField[i][a] != j) { cout << " Вы введи значение, не выбранное генератором судоку. Подумайте ещё. "; return false; }
	return true;
}

// Выбор и вывод соответвствующей графики
void print(string input) {
	if (input == "%start") { lastInput = input; printStart(); return; }
	if (input == "%game1") { lastInput = input; gamemode = 1; ezPrGen(); ezPr(); return; }
	if (input == "%game2") { lastInput = input; gamemode = 2; midPrGen(); midPr(); return; }
	if (input == "%game3") { lastInput = input; gamemode = 3; ezPrGen(); ezPr(); return; }
	if (input == "%game4") { lastInput = input; gamemode = 4; midPrGen(); midPr(); return; }
	if (((input[0] <= 122 && input[0] >= 97) || (input[0] <= 90 && input[0] >= 65)) && (input[1] <= 57 && input[1] >= 48) && (input[2] <= 57 && input[2] >= 48)) {
		if (changeCheckPr(input)) {
			lastInput = input;
			if ((gamemode == 1 || gamemode == 2) && !helperCheck(input)) {
				return;
			}
			changeCellPr(input);
			if (gamemode == 1 || gamemode == 3) { ezPr(); }
			if (gamemode == 2 || gamemode == 4) { midPr(); }
		}
		else cout << " Выбран неверный номер ячейки, или же она является заранее определённой. ";
		return;
	}
	if (input == "%check") {
		lastInput = input;
		if (solveCheck()) {
			cout << " Поздравляю, Вы решили правильно!";
			endlF();
			system("pause");
			system("cls");
			print("%start");
			return;
		}
		else { cout << " Похоже, в Вашем решении что-то не так. Подумайте ещё. "; return; }
	}
	if (input == "") { lastInput = input; }
	if (input == "%stop") { endlF(); lastInput = input; input = "break"; print(input); cout << "Спасибо за игру!"; return; }
	if (input == "break" && lastInput == "%stop") { return; }
	endlF();
	if (input != "%stop" && input != "%check") { cout << "Вы ввели неверную команду. Введите ещё раз. "; endlF(); }
	//cin >> input;
	//print(input);
}