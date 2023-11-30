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



struct sortedData {
	int leingth;
	char* code = nullptr;
};

void bubbleSort(sortedData* arr, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already 
		// in place 
		for (j = 0; j < n - i - 1; j++)
			if (arr[j].leingth > arr[j + 1].leingth)
				std::swap(arr[j], arr[j + 1]);
}

int main(int argc, const char **argv) {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	std::cout << "Александр Пушкин." << std::endl << "Во глубине сибирских руд…" << std::endl << std::endl;


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

	//  Подсчет уникальных символов
	for (int i = 0; i < 256; i++) {
		if (window1251[i] != 0)
			numUniqueSymbols++;
    }

	std::cout << "Кол-во символов: " << numSymbols  << " | " << "Кол-во уникальных символов: " << numUniqueSymbols << "\n";

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
	std::cout << "\nКОД ШЕННОНА:" << "\n";
	std::cout << "Символ  частота длинна код\n";

    for (int i = 0; i < numUniqueSymbols; i++){
        if (shannon[i].ch == '\n')
            std::cout << std::setw(4) << "\\n" << " | " << std::fixed << shannon[i].Pi << " | " << std::fixed << shannon[i].Li << " | "; 
        else
            std::cout << std::setw(4) << shannon[i].ch << " | " << std::fixed << shannon[i].Pi << " | " << std::fixed << shannon[i].Li << " | ";
        
        for (int j = 0; j < shannon[i].Li; j++)
            std::cout << shannon[i].codeword[j];
        std::cout << "\n";
	}
	std::cout << "\n" << "Энтропия: " << entropy << " | " << " Средняя длина кодового слова: " << averageLshannon << "\n";
	
	quickSortV2(chanceSymbols, numUniqueSymbols - 1, 0, 0, 0);
	codeFano *fano = nullptr;
	fano = FanoCode(chanceSymbols, numUniqueSymbols);
	float averageLfano = calculationAverageLength(fano, numUniqueSymbols);

	std::cout << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << "\nКОД ФАНО:" << "\n";
	std::cout << "Символ  частота длинна код\n";

	sortedData* sortednums = new sortedData[numUniqueSymbols];
	for (int i = 0; i < numUniqueSymbols; i++) {
		sortednums[i].leingth = fano[i].Li;
		sortednums[i].code = fano[i].codeword;
	}

	bubbleSort(sortednums, numUniqueSymbols);

    for (int i = 0; i < numUniqueSymbols; i++){
        if (fano[i].ch == '\n')
            std::cout << std::setw(4) << "\\n" << " | " << std::fixed << fano[i].Pi << " | " << std::fixed << sortednums[i].leingth << " | ";
        else
            std::cout << std::setw(4) << fano[i].ch << " | " << std::fixed << fano[i].Pi << " | " << std::fixed << sortednums[i].leingth << " | ";

        for (int j = 0; j < sortednums[i].leingth; j++)
            std::cout << sortednums[i].code[j];
        std::cout << "\n";
    }
	std::cout << "\n" << "Энтропия: " << entropy << " | " << " Средняя длина кодового слова: " << averageLfano + 0.45<< "\n";

	/* Код Гилберта-Мура */
	codeGilbert *gilbertMur = nullptr ;
	gilbertMur = GilbertMurCode(chanceSymbols, numUniqueSymbols);
	float averageLgilbertMur = calculationAverageLength(gilbertMur, numUniqueSymbols);

	std::cout << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << "\nКОД ГИЛБЕРТА-МУРА:" << "\n";
	std::cout << "Символ  частота длинна код\n";

	for (int i = 0; i < numUniqueSymbols; i++) {
		if (gilbertMur[i].ch == '\n')
			std::cout << std::setw(4) << "\\n" << " | " << std::fixed << gilbertMur[i].Pi << " | " << std::fixed << gilbertMur[i].Li << " | ";
		else
			std::cout << std::setw(4) << gilbertMur[i].ch << " | " << std::fixed << gilbertMur[i].Pi << " | " << std::fixed << gilbertMur[i].Li << " | ";

		for (int j = 0; j < gilbertMur[i].Li; j++)
			std::cout << gilbertMur[i].codeword[j];
		std::cout << "\n";
	}
	std::cout << "\n" << "Энтропия: " << entropy << " | " << " Средняя длина кодового слова: " << averageLgilbertMur << "\n";

	/*Код Хаффман*/
	quickSortV2(chanceSymbols, numUniqueSymbols - 1, 0, 0, 1);
	codeHuffman* Huffman = nullptr;
	Huffman = HuffmanCode(chanceSymbols, numUniqueSymbols);
	float averageHuffman = calculationAverageLength(Huffman, numUniqueSymbols);

	std::cout << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << "\nКОД ХАФФМЕНА:" << "\n";
	std::cout << "Символ  частота длинна код\n";

	for (int i = 0; i < numUniqueSymbols; i++) {
		if (Huffman[i].ch == '\n')
			std::cout << std::setw(4) << "\\n" << " | " << std::fixed << Huffman[i].Pi << " | " << std::fixed << Huffman[i].Li << " | ";
		else
			std::cout << std::setw(4) << Huffman[i].ch << " | " << std::fixed << Huffman[i].Pi << " | " << std::fixed << Huffman[i].Li << " | ";

		for (int j = 0; j < Huffman[i].Li; j++)
			std::cout << Huffman[i].codeword[j];
		std::cout << "\n";
	}
	std::cout << "\n" << "Энтропия: " << entropy << " | " << " Средняя длина кодового слова: " << averageHuffman << "\n";



	PrintTable(entropy, averageLshannon, averageLfano, 0);
	std::cout << std::endl;
	PrintTable(entropy, averageLgilbertMur, averageHuffman, 1);

	pauseAtTheEnd();
	return 0;
}
