#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class cells {
	vector <float> cellsCap; //Список емкостей ячеек
	int S, P; //S - Последовательно P - Параллельно
public:
	void cellsCapinput(vector <float> cellsCapinp, const int &Sinp, const int &Pinp) {
		S = Sinp;
		P = Pinp;

		sort(cellsCapinp.begin(), cellsCapinp.end());
		for (int i = 0; i < S * P; ++i) cellsCap.push_back(cellsCapinp[i]);
	}

	/*void sortcells() { //Сортировка ячеек в парралели методом балансировеи поледних элементов, не рабочее г*вно
		vector <float> reversedVec, sortedVec; //reversedVec - развернутый массив, sortedVec - сборный отсортированный массив 

		sort(cellsCap.begin(), cellsCap.end());
		reversedVec = cellsCap;
		reverse(reversedVec.begin(), reversedVec.end());

		for (int i = 1; i <= S; ++i) { //Создаем последовательные "блоки"
			for (int k = P * (i - 1); k < P * i; ++k) { //Записываем ячейки в блоки (параллели)
				if (k <= P * i - S / 2) sortedVec.push_back(cellsCap[cellsCap.size() - 1]), cellsCap.pop_back();
				else sortedVec.push_back(reversedVec[reversedVec.size() - 1]), reversedVec.pop_back();
			}
		}
		cellsCap = sortedVec;
		sortedVec.clear();
	} */

	/*void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
		vector <float> sortedVec; //Сборный отсортированный (в конце) массив
		double midCap, capSum;
		long double midTmp = 0;

		for (int i = 0; i < S; ++i) {
			sortedVec.push_back(cellsCap[cellsCap.size() - 1]); //Начальное заполнение
			midTmp += cellsCap[cellsCap.size() - 1]; //Начальное среднее (1 линия параллелей)
			cellsCap.pop_back();
		}
		midCap = midTmp / S;

		for (int i = 0; i < S; ++i) {
			capSum = sortedVec[i] + cellsCap[cellsCap.size()- 1]; //Балансировка блока, 1 итерация
			for (int k = cellsCap.size() - 2; k >= cellsCap.size() - P - 1; --k) {
				if (abs(sortedVec[i] - cellsCap[k]));
			}

			sortedVec.emplace(sortedVec.begin(), cellsCap[0]);
		}

		for (int i = 1; i < P; ++i) { //Переключение параллелей (горизонталь P)

			for (int k = 0; k < S; ++k) midTmp += cellsCap[cellsCap.size() - k]; //Вычисление среднего для блока (2+ параллели)
			midCap = midTmp / S;

			for (int k = S * (i - 1); k < S * i; ++k) { //Переключение баланисировки блоков (вертикаль S)
				capSum = sortedVec[k] + sortedVec[k-S] + cellsCap[0]; //Балансировка блока.
				for (int j = 1; j < cellsCap.size() - (cellsCap.size() * P); j++) {
					if (abs(sortedVec[k] - cellsCap[i]));
				}

				sortedVec.emplace(sortedVec.begin(), cellsCap[0]);
			}
		}
	} */

	void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
		vector <float> sortedVec; //Сборный отсортированный (в конце) массив
		double midCap;
		long double midTmp = 0;
		int Counter;

		for (int i = 0; i < S * P; ++i) midTmp += cellsCap[cellsCap.size() - i]; //среднее значение
		midCap = midTmp / S;

		for (int i = 0; i < S * P; i += P) {
			Counter = 1;
			for (int k = i + 1; k < i+P; ++k) {
				Counter++;
				if (cellsCap[k - 1] + cellsCap[k] > midCap / Counter) {
					
				}
			}
		}
	}
	void cellslistoutput() { //вывод массива в консоль
		float bSumm = 0;
		for (int i = 1; i <= S; ++i) {
			cout << endl << i << " ";
			for (int k = P * (i - 1); k < P * i; ++k) {
				cout << cellsCap[k] << ' ';
				bSumm += cellsCap[k];
			}
			cout << bSumm;
			bSumm = 0;
		}
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	vector <float> vec;
	float inreversedVec;
	int Sinp, Pinp;

	cout << " Последовательно|Параллельно\n ";
	cin >> Sinp >> Pinp;
	cout << endl << endl;

	for (int i = 0; i < Sinp * Pinp; i++) {
		cin >> inreversedVec;
		vec.push_back(inreversedVec);
	}


	cells block;
	block.cellsCapinput(vec, Sinp, Pinp);
	block.sortcells();
	block.cellslistoutput();
}
