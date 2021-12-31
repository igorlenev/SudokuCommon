#include <Windows.h>
#include <iostream> // Для удобства тестирования
#include <string>
#include "Generator.h"
using namespace std;

int ezField[4][4], midField[9][9]; // Игровые поля с правильным решением
int ezFieldG[4][4], midFieldG[9][9]; // Поля игрока
bool ezFieldStatic[4][4], midFieldStatic[9][9]; // Запоминание статических полей
int buff; // Буфер для промежуточных вычислений
int visInts; // Число 
int gamemodeGen;
bool sqCheck[10];

// Обнуление полей
void initial() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ezField[i][j] = 0;
			ezFieldG[i][j] = 0;
			ezFieldStatic[i][j] = false;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			midField[i][j] = 0;
			midFieldG[i][j] = 0;
			midFieldStatic[i][j] = false;
		}
	}
}

// Первая генерация поля (Лёгкий)
void generateEz() {
	initial();
	int startPoint; // Начальная позиция для генератора
	int step; // Шаг для генератора
	startPoint = rand() % 4;
	step = rand() % 2;
	buff = startPoint;

	// Преобразование шага для работоспособности генератора
	if (step == 0) step = 3;
	else step = 1;

	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) buff = startPoint + i / 2;
		buff += 2;
		if (buff > 3) buff -= 4;
		for (int j = 0; j < 4; j++) {
			ezField[i][buff] = j + 1;
			buff += step;
			if (buff > 3) buff -= 4;
		}
	}
}

// Первая генерация поля (Средний)
void generateMid() {
	initial();
	int startPoint; // Начальная позиция для генератора
	int step; // Шаг для генератора
	startPoint = rand() % 3;
	step = rand() % 3 + 1;
	buff = startPoint;

	// Преобразования для работоспособности генератора
	if (step == 2) step = 4;
	if (step == 3) step = 8;
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) buff = startPoint + i / 3;
		buff += 3;
		if (buff > 8) buff -= 9;
		for (int j = 0; j < 9; j++) {
			midField[i][buff] = j + 1;
			buff += step;
			if (buff > 8) buff -= 9;
		}
	}
}

// Генерация ячейки видимого элементов (Лёгкий)
int genVisEzCell() {
	return rand() % 4;
}

// Генерация ячейки видимого элементов (Средний)
int genVisMidCell() {
	return rand() % 9;
}

// Генерация выборки видимых элементов (Лёгкий)
void genVisEzArr() {
	visInts = 3;
	int more = rand() % 4;
	int addVisInts = 1 + rand() % 2;

	for (int i = 0; i < 4; i++) {
		if (i != more) {
			buff = genVisEzCell();
			ezFieldG[i][buff] = ezField[i][buff];
			ezFieldStatic[i][buff] = true;
		}
		else {
			while (addVisInts > 0) {
				buff = genVisEzCell();
				if (!ezFieldStatic[i][buff]) {
					ezFieldG[i][buff] = ezField[i][buff];
					ezFieldStatic[i][buff] = true;
					addVisInts--;
				}
			}
		}
	}
}

// Генерация выборки видимых элементов (Средний)
void genVisMidArr() {
	visInts = 29;
	int more = rand() % 9;
	int addVisInts = 3 + rand() % 3;
	int currVis;

	for (int i = 0; i < 9; i++) {
		if (i != more) {
			currVis = 3;
			while (currVis > 0) {
				buff = genVisMidCell();
				if (!midFieldStatic[i][buff]) {
					buff = genVisMidCell();
					midFieldG[i][buff] = midField[i][buff];
					midFieldStatic[i][buff] = true;
					currVis--;
				}
			}
		}
		else {
			while (addVisInts > 0) {
				buff = genVisMidCell();
				if (!midFieldStatic[i][buff]) {
					midFieldG[i][buff] = midField[i][buff];
					midFieldStatic[i][buff] = true;
					addVisInts--;
				}
			}
		}
	}
}

void sqCheckNull() {
	for (int i = 0; i < 10; i++) {
		sqCheck[i] = false;
	}
}

bool ezSolveCheck() {
	// Проверка по горизонтали и вертикали
	for (int a = 0; a < 4; a++) {
		for (int i = 0; i < 4; i++) {
			if (i < 3) {
				for (int j = i + 1; j < 4; j++) {
					if (ezFieldG[a][i] == ezFieldG[a][j]) return false;
					if (ezFieldG[i][a] == ezFieldG[j][a]) return false;
				}
			}
			if (ezFieldG[a][i] == 0) return false;
		}
	}

	// Проверка по квадратам
	for (int a = 0; a < 2; a++) {
		for (int b = 0; b < 2; b++) {
			sqCheckNull();
			for (int i = a * 2; i <= (a * 2) + 1; i++) {
				for (int j = b * 2; j <= (b * 2) + 1; j++) {
					if (!sqCheck[ezFieldG[i][j]]) { sqCheck[ezFieldG[i][j]] = true; }
					else return false;
				}
			}
		}
	}

	return true;
}

bool midSolveCheck() {
	// Проверка по горизонтали и вертикали
	for (int a = 0; a < 9; a++) {
		for (int i = 0; i < 9; i++) {
			if (i < 8) {
				for (int j = i + 1; j < 9; j++) {
					if (ezFieldG[a][i] == ezFieldG[a][j]) return false;
					if (ezFieldG[i][a] == ezFieldG[j][a]) return false;
				}
			}
			if (ezFieldG[a][i] == 0) return false;
		}
	}

	// Проверка по квадратам
	for (int a = 0; a < 3; a++) {
		for (int b = 0; b < 3; b++) {
			sqCheckNull();
			for (int i = a * 3; i <= (a * 3) + 2; i++) {
				for (int j = b * 3; j <= (b * 3) + 2; j++) {
					if (!sqCheck[ezFieldG[i][j]]) { sqCheck[ezFieldG[i][j]] = true; }
					else return false;
				}
			}
		}
	}

	return true;
}

bool genSolveCheck() {
	if (gamemodeGen == 1 || gamemodeGen == 3) return ezSolveCheck();
	else return midSolveCheck();
}

// Проверка на возможность изменения
bool changeCheck(int i, int j, int a) {
	bool isNotErr = false;
	if ((gamemodeGen == 1 || gamemodeGen == 3) && (ezFieldStatic[i][j] == false) && (a < 5 && a >= 0)) isNotErr = true;
	if ((gamemodeGen == 2 || gamemodeGen == 4) && (midFieldStatic[i][j] == false) && (a < 10 && a >= 0)) isNotErr = true;
	return isNotErr;
}

// Изменение ячейки
void changeCell(int i, int j, int a) {
	if (gamemodeGen == 1 || gamemodeGen == 3) { ezFieldG[i][j] = a; return; }
	else { midFieldG[i][j] = a; return; }
}

// Выбор первой генерации
void generateCheck(int gamemode) {
	initial();
	gamemodeGen = gamemode;
	if (gamemode == 1 || gamemode == 3) { generateEz(); genVisEzArr(); }
	else { generateMid(); genVisMidArr(); }
}