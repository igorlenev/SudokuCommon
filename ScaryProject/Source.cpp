#include <iostream>
#include <string>
#include "Printer.h"
#include "Generator.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string input = "%start";
	print(input);
	while (true) {
		if (input == "%stop") { break; }
		cout << "¬ведите следующую команду: ";
		cin >> input;
		print(input);
	}
	endlF();
	cout << "»гра окончена. ";
	system("pause");
	exit(1);
	return 0;
}