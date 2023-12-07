#include <iostream>
#include <Windows.h>
#include <iomanip>
#include "procedures.hpp"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::cout << "" << std::setw(15) << "";
	std::cout << "                                                                                    Кодовое слово                                                 " << "\n";

	std::cout << "" << std::setw(15) << "     Число     ";
	//std::cout << "        Бинарный код          " << "\n";

	//std::cout << "" << std::setw(15) << "";
	std::cout << "            Fixed + Variable                        гамма-код Элиаса                          омега-код Элиаса            " << "\n";

	uint8_t	number = 1; // 0 - 255	
	do
	{
		std::cout << "|";
		std::cout << std::left << std::setw(15) << (int)number - 1;
		//std::cout << "|";
		//std::cout << std::left << std::setw(30) << binary(number);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << fixedVariable(number - 1);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << gammaCodeElias(number);
		std::cout << "|";
		std::cout << std::left << std::setw(38) << omegaCodeElias(number);
		std::cout << "|";
		std::cout << "\n";

		number++;
	} while (number != 0);

	return 0;

}