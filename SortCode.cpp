#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

class cells {
	vector <double> cellsCap; //Список емкостей ячеек
	vector <double> blockSum; //Емкость блоков
	int S, P; //S - Последовательно P - Параллельно
public:
	void Cellsinput(vector <double> cellsCapinp, const int& Sinp, const int& Pinp) {
		S = Sinp;
		P = Pinp;

		sort(cellsCapinp.begin(), cellsCapinp.end());
		for (int i = 0; i < S * P; ++i) cellsCap.push_back(cellsCapinp[i]);
		for (int i = 0; i < S; ++i) blockSum.push_back(0);
	}

	void SPinput(const int& Sinp, const int& Pinp) { //сюды ввод S - последовательно P - параллельно
		S = Sinp;
		P = Pinp;
		for (int i = 0; i < S; ++i) blockSum.push_back(0);
	}

	void Cellsfinput(const string& fname) {
		ifstream fin;
		fin.open(fname);
		double intmp;

		while (fin >> intmp) {
			cellsCap.push_back(intmp);
		}
		fin.close();

		sort(cellsCap.rbegin(), cellsCap.rend());
	}

	void Cellsfoutput(const string& fname) {

		ofstream fout;
		fout.open(fname);

		for (int i = 0; i < S; ++i) {
			fout << "Блок№" << i + 1 << " ";
			for (int k = i; k < cellsCap.size(); k += S) {
				fout << cellsCap[k] << ' ';

			}
			fout << "Всего:" <<  blockSum[i] << endl;
		}


		fout.close();
	}

void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
	vector <double> sortedVec;  //Сборный отсортированный (в конце) массив
	double midCap;
	long double midTmp = 0;

	for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
	midCap = midTmp / S;

	// cout << endl << midCap << endl; //

	for (int i = P; i > 0; --i) { //Перебор параллелей, ход по S

		for (int k = 0; k < S; ++k) { //Перебор элементов по вертикали
			if (i == P) {
				sortedVec.push_back(cellsCap[0]);
				blockSum[k] += cellsCap[0];
				cellsCap.erase(cellsCap.begin());
				continue;
			}
			for (int j = cellsCap.size() - 2; j >= 0; --j) { //Перебор элементов для параллелей
				if (j == 0) {
					sortedVec.push_back(cellsCap[0]);
					blockSum[k] += cellsCap[0];
					cellsCap.erase(cellsCap.begin());
					break;
				}
				if (blockSum[k] + cellsCap[j] >= midCap / i) {
					sortedVec.push_back(cellsCap[j + 1]);
					blockSum[k] += cellsCap[j + 1];
					cellsCap.erase(cellsCap.begin() + j + 1);
					break;
				} 
			}
		} 
	}
	sortedVec.push_back(cellsCap[0]);
	blockSum[S - 1] += cellsCap[0];
	cellsCap.erase(cellsCap.begin());

	/*double distMin, distMax, tmp, blockDiff;
	for (int i = 0; i < P; ++i) {
		distMin = distance(blockSum.begin(), min_element(blockSum.begin(), blockSum.end())), distMax = distance(blockSum.begin(), max_element(blockSum.begin(), blockSum.end()));
		blockDiff = blockSum[distMax] - blockSum[distMin];

		if ((blockSum[distMax] - blockDiff) - (blockSum[distMin] + blockDiff) < blockDiff) {
			blockSum[distMax] -= blockDiff, blockSum[distMin] += blockDiff;
			tmp = sortedVec[P * distMax + P - 1];
			sortedVec[P * distMax + P - 1] = sortedVec[P * distMin + P - 1];
			sortedVec[P * distMin + P - 1] = tmp;
		}

	} */
	
	for (int i = 0; i < P; ++i) {
		for (int k = 0; k < P; ++k) {
			if (blockSum[i] - blockSum[k]) {

			}
		}
	}

	cellsCap = sortedVec;
} 

void Cellsconsoutput() { //вывод массива в консоль
	/*for (int i = 0; i < S; ++i) {
		cout << endl << "Блок№" << i + 1 << " |";
		for (int k = i; k < cellsCap.size(); k += S) {
			cout << cellsCap[k] << ' ';

		}
		cout << "|total=" << blockSum[i];
	} */
	for (int k = 0; k < cellsCap.size(); k++) {
		cout << cellsCap[k] << ' ';
	}
}
};

int main() {
	setlocale(LC_ALL, "Russian");

	vector <double> vec;
	float inreversedVec;
	int Sinp, Pinp;

	/*cout << " Последовательно|Параллельно\n ";
	cin >> Sinp >> Pinp;
	cout << endl << endl;

	for (int i = 0; i < Sinp * Pinp; i++) {
		cin >> inreversedVec;
		vec.push_back(inreversedVec);
	} */


	cells block;
	block.Cellsfinput("123.txt");
	block.SPinput(6, 3);
	block.sortcells();
	block.Cellsfoutput("1234.txt");
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

/*void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
	vector <double> sortedVec, blockSum;  //Сборный отсортированный (в конце) массив
	double midCap, tmp;
	long double midTmp = 0;
	for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
	midCap = midTmp / S;
	cout << endl << midCap << endl;
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
		blockSum.push_back(tmp);
	}

	vector <double>::iterator iterMin, iterMax;
	double max, min, distMin, distMax;
	tmp = 0;
	for (int i = 0; i < P - 1; ++i) {
		iterMin = min_element(blockSum.begin(), blockSum.end() - i), iterMax = max_element(blockSum.begin(), blockSum.end() - i);
		distMin = distance(blockSum.begin() + i, iterMin), distMax = distance(blockSum.begin() + i, iterMax);


		tmp = sortedVec[P * distMax + P - 1];
		sortedVec[P * distMax + P - 1] = sortedVec[P * distMin + P - 1];
		sortedVec[P * distMin + P - 1] = tmp;


		blockSum.push_back(blockSum[distMax]);
		blockSum.push_back(blockSum[distMin]);
		blockSum.erase(blockSum.begin() + distMax + 1);
		blockSum.erase(blockSum.begin() + distMin + 1);
	}

	cellsCap = sortedVec;
} */