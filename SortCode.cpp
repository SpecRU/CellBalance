#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class cells {
	vector <float> cellsCap; //Список емкостей ячеек
	int S, P; //S - Последовательно P - Параллельно
public:
	void cellsCapinput(vector <float> cellsCapinp, const int& Sinp, const int& Pinp) {
		S = Sinp;
		P = Pinp;

		sort(cellsCapinp.rbegin(), cellsCapinp.rend());
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

	/*void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
		vector <float> sortedVec; //Сборный отсортированный (в конце) массив
		double midCap;
		long double midTmp = 0;

		for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
		midCap = midTmp / S;
		cout << endl << midCap << endl;

		float tmp;
		for (int i = 0; i < S * P; i += P) { //Перебор блоков, ход по P
			tmp = 0;
			sortedVec.push_back(cellsCap[cellsCap.size() - 1]); //Вставка 
			tmp += cellsCap[cellsCap.size() - 1];
			cellsCap.pop_back(); //удаление его из cellsCap
			for (int k = P - 1; k > 0; --k) { //Перебор элементов в блоке
				for (int j = 1; j <= cellsCap.size(); ++j) { //j - перебор элементов для cellsCap
					if (j == cellsCap.size()) {
						sortedVec.push_back(cellsCap[cellsCap.size() - 1]);
						tmp += cellsCap[cellsCap.size() - 1];
						cellsCap.erase(cellsCap.begin() + cellsCap.size() - 1);
						break;
					}
					if (tmp + cellsCap[j] >= midCap / k) { //Посмотреть midcap
						sortedVec.push_back(cellsCap[j - 1]);
						tmp += cellsCap[j - 1];
						cellsCap.erase(cellsCap.begin() + j - 1);
						break;
					} 
				}
			}
		}
		cellsCap = sortedVec;
	} */

	/*void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости //выставить rbegin rend во вводе
		double midCap;
		long double midTmp = 0;

		for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
		midCap = midTmp / S;
		cout << endl << midCap << endl;
	
		int count = 0;
		float parCap = 0, tmpCap;
		int localP = P;
		for (int i = 0; i < S * P; ++i) { //Перебор массива ячеек
			if (count == P) count = 0, parCap = 0;
			++count;

			sort(cellsCap.rbegin(), cellsCap.rend() - i);

			if (count == 1) {
				parCap += cellsCap[i];
			}
			else {
				tmpCap = cellsCap[i];
				auto expl = [midCap, parCap, count, localP](float i) {return i + parCap <= midCap / (localP + 1 - count); };
				auto out = find_if(cellsCap.begin() + i, cellsCap.end(), expl);

				(out != cellsCap.end())
					? cellsCap[i] = *out, cellsCap[distance(cellsCap.begin(), out)] = tmpCap, parCap += cellsCap[i]
					: cellsCap[i] = cellsCap[cellsCap.size() - 1], cellsCap[cellsCap.size() - 1] = tmpCap, parCap += cellsCap[i];
			}
		}
	} */
	
	void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости //выставить rbegin rend во вводе
		double midCap;
		long double midTmp = 0;

		for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
		midCap = midTmp / S;
		cout << endl << midCap << endl;

		int count = 0;
		float parCap = 0, tmpCap;
		int localP = P;
		for (int i = 0; i < S * P; ++i) { //Перебор массива ячеек
			if (count == P) count = 0, parCap = 0;
			++count;

			sort(cellsCap.rbegin(), cellsCap.rend() - i);

			if (count == 1) {
				parCap += cellsCap[i];;
			}
			else {
				tmpCap = cellsCap[i];
				auto expl = [midCap, parCap, count, localP](float i) {return i + parCap <= midCap / (localP + 1 - count); };
				auto out = find_if(cellsCap.begin() + i, cellsCap.end(), expl);

				(out != cellsCap.end())
					? cellsCap[i] = *out, cellsCap[distance(cellsCap.begin(), out)] = tmpCap, parCap += cellsCap[i]
					: cellsCap[i] = cellsCap[cellsCap.size() - 1], cellsCap[cellsCap.size() - 1] = tmpCap, parCap += cellsCap[i];
			}
		}
	} 

	void cellslistoutput() { //вывод массива в консоль
		float bSumm = 0;
		for (int i = 1; i <= S; ++i) {
			cout << endl << "Блок№" << i << " |";
			for (int k = P * (i - 1); k < P * i; ++k) {
				cout << cellsCap[k] << ' ';
				bSumm += cellsCap[k];
			}
			cout << "|total=" << bSumm;
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