#include <iostream>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

#include "somefunctions.hpp"
#include "functions.hpp"
#include "codings.hpp"
#include "struct.hpp"

int main(int argc, const char **argv) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "��������� ������." << std::endl << "�� ������� ��������� ���" << std::endl << std::endl;


	std::string	filename = "./lab10.txt";
	unsigned int numSymbols = 0;
	unsigned int numUniqueSymbols = 0;

	unsigned short int window1251[256] = {0};

	std::ifstream file; 
	unsigned char ch;
	file.open (filename);
	if (!file){
		throw std::runtime_error("Error of opening");
	}
	
	while ((ch = file.get()) && !file.eof()){
		numSymbols++;
		window1251[(int)ch]++;
	}

	//  ������� ���������� ��������
	for (int i = 0; i < 256; i++) {
		if (window1251[i] != 0)
			numUniqueSymbols++;
    }

	std::cout << "���-�� ��������: " << numSymbols  << " | " << "���-�� ���������� ��������: " << numUniqueSymbols << "\n";

	file.close();

	chanceSymbol *chanceSymbols = new chanceSymbol[numUniqueSymbols];

	unsigned short int temp = 0;
	for (int i = 0; i < 256; i++){
		if (window1251[i] != 0){
			chanceSymbols[temp].ch = (char)i;
			chanceSymbols[temp].chance = (float)window1251[i] / numSymbols;
			temp++;
		}
	}
	printChanceSymbols(chanceSymbols, numUniqueSymbols, window1251);

	float entropy = calculationEntropy(chanceSymbols, numUniqueSymbols);

	codeShannon *shannon = nullptr ;
	shannon = ShannonCode(chanceSymbols, numUniqueSymbols);
	float averageLshannon = calculationAverageLength(shannon, numUniqueSymbols);

	std::cout << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << "\n��� �������:" << "\n";
	std::cout << "������  ������� ������ ���\n";
    for (int i = 0; i < numUniqueSymbols; i++){
        if (shannon[i].ch == '\n')
            std::cout << std::setw(4) << "\\n" << " | " << std::fixed << shannon[i].Pi << " | " << std::fixed << shannon[i].Li << " | "; 
        else
            std::cout << std::setw(4) << shannon[i].ch << " | " << std::fixed << shannon[i].Pi << " | " << std::fixed << shannon[i].Li << " | ";
        
        for (int j = 0; j < shannon[i].Li; j++)
            std::cout << shannon[i].codeword[j];
        std::cout << "\n";
	}
	std::cout << "\n" << "��������: " << entropy << " | " << " ������� ����� �������� �����: " << averageLshannon << "\n";
	
	quickSortV2(chanceSymbols, numUniqueSymbols - 1, 0, 0, 0);
	codeFano *fano = nullptr;
	fano = FanoCode(chanceSymbols, numUniqueSymbols);
	float averageLfano = calculationAverageLength(fano, numUniqueSymbols);

	std::cout << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << "\n��� ����:" << "\n";
	std::cout << "������  ������� ������ ���\n";
    for (int i = 0; i < numUniqueSymbols; i++){
        if (fano[i].ch == '\n')
            std::cout << std::setw(4) << "\\n" << " | " << std::fixed << fano[i].Pi << " | " << std::fixed << fano[i].Li << " | "; 
        else
            std::cout << std::setw(4) << fano[i].ch << " | " << std::fixed << fano[i].Pi << " | " << std::fixed << fano[i].Li << " | ";
        
        for (int j = 0; j < fano[i].Li; j++)
            std::cout << fano[i].codeword[j];
        std::cout << "\n";
    }
	std::cout << "\n" << "��������: " << entropy << " | " << " ������� ����� �������� �����: " << averageLfano << "\n";

	/* ��� ��������-���� */
	codeGilbert *gilbertMur = nullptr ;
	gilbertMur = GilbertMurCode(chanceSymbols, numUniqueSymbols);
	float averageLgilbertMur = calculationAverageLength(gilbertMur, numUniqueSymbols);

	PrintTable(entropy, averageLshannon, averageLfano);



	pauseAtTheEnd();
	return 0;
}