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
	}

	void Cellsfoutput(const string& fname) {

		ofstream fout;
		fout.open(fname);

		double tmp;

		for (int i = 0; i < S; ++i) {
			fout << "Блок№" << i + 1 << " ";
			tmp = 0;
			for (int k = i; k < cellsCap.size(); k += S) {
				tmp += cellsCap[k];
				fout << cellsCap[k] << ' ';

			}
			fout << "Всего:" << blockSum[i] << "|" << tmp << endl;
		}

		fout.close();
	}

void sortcells() { //Сортировка ячеек в параллели методом подбора ближайшей суммы емкости парралели к средней емкости
	sort(cellsCap.begin(), cellsCap.end());

	vector <double> sortedVec, tmpVec;  //Сборный отсортированный (в конце) массив
	double midCap;
	long double midTmp = 0;

	for (int i = 0; i < S * P; ++i) midTmp += cellsCap[i]; //среднее значение
	midCap = midTmp / S;

	for (int k = 0; k < cellsCap.size(); ++k) {
		tmpVec.push_back(cellsCap[cellsCap.size() - 1]);
		cellsCap.pop_back();
	}

	for (int i = P; i > 0; --i) { //Перебор параллелей, ход по S
		for (int k = 0; k < S; ++k) {
			cellsCap.push_back(tmpVec[0]);
			tmpVec.erase(tmpVec.begin());
		}
		for (int k = 0; k < S; ++k) { //Перебор элементов по вертикали
			/*if (i == P) {
				sortedVec.push_back(cellsCap[0]);
				blockSum[k] += cellsCap[0];
				cellsCap.erase(cellsCap.begin());
				continue;
			}*/
			for (int j = cellsCap.size() - 1; j >= 0; --j) { //Перебор элементов для параллелей
				if (j == 0) {
					sortedVec.push_back(cellsCap[0]);
					blockSum[k] += cellsCap[0];
					cellsCap.erase(cellsCap.begin());
					break;
				}
				if (blockSum[k] + cellsCap[j] >= midCap / i) {
					sortedVec.push_back(cellsCap[j]);
					blockSum[k] += cellsCap[j];
					cellsCap.erase(cellsCap.begin() + j);
					break;
				} 
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
	block.SPinput(14, 6);
	block.sortcells();
	block.Cellsfoutput("1234.txt");
}