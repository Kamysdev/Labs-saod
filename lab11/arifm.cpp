//#include <iostream>
//#include <cmath>
//#include <locale>
//#include <bitset>
//#include <vector>
//#include <fstream>
//#include <set>
//#include <sstream>
//#include <Windows.h>
//
//struct CharArray {
//    CharArray(char i, long double d)
//    {
//        ch = i;
//        p = d;
//    }
//    char ch;
//    long double p;
//};
//
//std::vector<CharArray> init(std::string& full)
//{
//    std::ifstream fin;
//    fin.open("test.txt");
//    if (fin.is_open()) {
//        std::vector<float> P;
//        std::string alphabet;
//        float count = 0;
//        std::stringstream buffer;
//        buffer << fin.rdbuf();
//        full.append(buffer.str());
//        alphabet.append(full);
//        std::set<char> chars;
//        alphabet.erase(std::remove_if(alphabet.begin(), alphabet.end(),
//                           [&chars](char i) {
//                               if (chars.count(i)) {
//                                   return true;
//                               }
//                               chars.insert(i);
//                               return false;
//                           }),
//            alphabet.end());
//        for (char i : alphabet) {
//            for (char j : full) {
//                if (i == j)
//                    count++;
//            }
//            long double result = (long double)std::round(count / (long double)full.size() * 10000000000) / 10000000000;
//            P.emplace_back(result);
//            count = 0;
//        }
//        long double res = 0;
//        for (auto i : P)
//            res += i;
//        std::cout << "Вероятность: " << res << "\n";
//        fin.close();
//        std::vector<CharArray> vec;
//        vec.reserve(alphabet.length());
//        for (int i = 0; i < alphabet.length(); ++i)
//            vec.emplace_back(alphabet[i], P[i]);
//        return vec;
//    } else {
//        std::cout << "Couldn't open file\n";
//        std::vector<CharArray> vec;
//        return vec;
//    }
//}
//
//std::vector<long double> init_Q(std::vector<CharArray>& arr)
//{
//    int index = 0;
//    std::vector<long double> Q;
//    Q.emplace_back(0);
//    long double sum = 0;
//    for (int i = 0; i < arr.size(); ++i) {
//        while (index <= i) {
//            sum += arr.at(index).p;
//            index++;
//        }
//        Q.emplace_back(sum);
//        index = 0;
//        sum = 0;
//    }
//    return Q;
//}
//
//long double encoding(std::vector<CharArray>& arr, std::vector<long double>& Q, std::string& file) {
//    long double* l = new long double[file.size() + 1];
//    long double* h = new long double[file.size() + 1];
//    long double* r = new long double[file.size() + 1];
//
//    l[0] = 0, h[0] = 1, r[0] = 1;
//    int m;
//
//    for (long i = 1; i <= file.size(); ++i) {
//        char c = file.at(i - 1);
//
//        for (int j = 1; j <= arr.size(); ++j) {
//            if (c == arr.at(j - 1).ch) {
//                m = j;
//                break;
//            }
//        }
//
//        l[i] = l[i - 1] + r[i - 1] * Q.at(m - 1);
//        h[i] = l[i - 1] + r[i - 1] * Q.at(m);
//        r[i] = h[i] - l[i];
//
//        // Вывод информации для всех символов, кроме последнего
//        if (i < file.size()) {
//            std::cout << "Блок: " << file.at(i - 1) << ", левая граница: " << l[i] << ", правая граница: " << r[i] << ", h: " << h[i] << "    " << 1 / h[i] << "\n";
//        }
//    }
//
//    std::cout << "\n";
//    return l[file.size()];
//}
//
//
//void decoded(std::vector<CharArray>& arr, std::vector<long double>& Q, long double value, std::string& token) {
//    std::ofstream fout;
//    fout.open("decoded.txt", std::fstream::app | std::fstream::binary);  // Открываем файл в бинарном режиме
//    if (fout.is_open()) {
//        long double* l = new long double[token.size() + 1];
//        long double* h = new long double[token.size() + 1];
//        long double* r = new long double[token.size() + 1];
//
//        l[0] = 0, h[0] = 1, r[0] = 1;
//        for (int i = 1; i <= token.size(); ++i) {
//            for (int j = 1; j < Q.size(); ++j) {
//                l[i] = l[i - 1] + r[i - 1] * Q.at(j - 1);
//                h[i] = l[i - 1] + r[i - 1] * Q.at(j);
//                r[i] = h[i] - l[i];
//                if (l[i] <= value and value <= h[i])
//                    break;
//            }
//            
//            // Записываем декодированный символ в двоичном виде
//            char decodedChar = token.at(i - 1);
//            std::bitset<8> binaryChar(decodedChar);
//            fout.write(reinterpret_cast<const char*>(&binaryChar), sizeof(binaryChar));
//        }
//    }
//    fout.close();
//}
//
//std::vector<std::string> split(std::string const& s, size_t count)
//{
//    size_t minsize = s.size() / count;
//    int extra = (int)(s.size() - minsize * count);
//    std::vector<std::string> tokens;
//    for (size_t i = 0, offset = 0; i < count; ++i, --extra) {
//        size_t size = minsize + (extra > 0 ? 1 : 0);
//        if ((offset + size) < s.size())
//            tokens.push_back(s.substr(offset, size));
//        else
//            tokens.push_back(s.substr(offset, s.size() - offset));
//        offset += size;
//    }
//    return tokens;
//}
//
//int main()
//{   
//    //SetConsoleCP(1251);
//    //SetConsoleOutputCP(1251);
//    setlocale(LC_ALL, "Russian");
//
//    std::string full;
//    std::vector<CharArray> arr = init(full);
//    std::vector<long double> Q = init_Q(arr);
//    for (auto& i : Q)
//        std::cout << i << "\n";
//    for (auto& i : arr) {
//        std::cout << "Символ: " << i.ch << ", вероятность: " << i.p << std::endl;
//    }
//    std::vector<std::string> tokens = split(full, 7);
//    for (auto& i : tokens)
//        std::cout << "Размер блока: " << i.size() << "\n";
//    for (auto& token : tokens)
//        std::cout << "[" << token << "] ";
//    std::cout << std::endl;
//    std::vector<long double> values;
//    for (auto& token : tokens) {
//        long double code = encoding(arr, Q, token);
//        values.emplace_back(code);
//    }
//
//    std::ofstream decodedFile("decoded.txt", std::ios::binary);
//    if (decodedFile.is_open()) {
//        for (auto& token : tokens) {
//            long double code = encoding(arr, Q, token);
//            decoded(arr, Q, code, token);
//        }
//        decodedFile.close();
//        std::cout << "Файл decoded.txt успешно создан и заполнен." << std::endl;
//    } else {
//        std::cerr << "Ошибка открытия файла decoded.txt" << std::endl;
//        return 1;
//    }
//
//    // Вывод decoded.txt в двоичной системе
//    std::ifstream decodedFileBinary("decoded.txt", std::ios::binary);
//    if (decodedFileBinary.is_open()) {
//        char c;
//        while (decodedFileBinary.get(c)) {
//            std::bitset<8> binaryChar(c);
//            std::cout << binaryChar << " ";
//        }
//        decodedFileBinary.close();
//        std::cout << "\nФайл decoded.txt в двоичной системе успешно выведен." << std::endl;
//    } else {
//        std::cerr << "Ошибка открытия файла decoded.txt" << std::endl;
//        return 1;
//    }
//
//    return 0;
//}