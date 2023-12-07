#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <conio.h>
#include <cmath>
using namespace std;
const int n = 12;
int c[n][n], lenght[n], sum = 0;
float p[n], q1[n];
char a[n];

void Shanon() {
    float Q[n];
    p[0] = 0;
    Q[0] = 0;
    for (int i = 1; i < n; i++) {
        Q[i] = Q[i - 1] + p[i];
        cout << "Q[" << i << "]" << Q[i] << endl;
        lenght[i] = ceil(-log(p[i]) / log(2));
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= lenght[i]; j++) {
            Q[i - 1] = Q[i - 1] * 2;
            c[i][j] = floor(Q[i - 1]);
            while (Q[i - 1] >= 1)
                Q[i - 1] = Q[i - 1] - 1;
        }
    }
}

int med(int L, int R) {
    float Sl = 0, Sr;
    for (int i = L; i <= R - 1; i++) {
        Sl = Sl + p[i];
    }
    Sr = p[R];
    int m = R;
    while (Sl >= Sr) {
        m = m - 1;
        Sl = Sl - p[m];
        Sr = Sr + p[m];
    }
    return m;
}

void Fano(int L, int R, int k) {
    if (L < R) {
        k++;
        int m = med(L, R);
        for (int i = L; i <= R; i++) {
            if (i <= m) {
                c[i][k] = 0;
                lenght[i] = lenght[i] + 1;
            }
            else {
                c[i][k] = 1;
                lenght[i] = lenght[i] + 1;
            }
        }
        Fano(L, m, k);
        Fano(m + 1, R, k);
    }
}

int up(int m, float q)
{
    int j = 1;
    for (int i = m - 1; i >= 2; i--)
    {
        if (p[i - 1] <= q)
            p[i] = p[i - 1];
        else
        {
            j = i;
            break;
        }
    }
    p[j] = q;
    return j;
}

void down(int m, int j)
{
    int s[n];
    for (int i = 1; i < n; i++)
        s[i] = c[j][i];
    int L = lenght[j];
    for (int i = j; i < m - 1; i++)
    {
        for (int k = 1; k < n; k++)
            c[i][k] = c[i + 1][k];
        lenght[i] = lenght[i + 1];
    }
    for (int i = 1; i < n; i++)
    {
        c[m - 1][i] = s[i];
        c[m][i] = s[i];
    }
    c[m - 1][L + 1] = 0;
    c[m][L + 1] = 1;
    lenght[m - 1] = lenght[m] = L + 1;
}

void huffman(int m)
{
    if (m == 2)
    {
        c[1][1] = 0;
        c[2][1] = 1;
        lenght[1] = lenght[2] = 1;
    }
    else
    {
        float q = p[m - 1] + p[m];
        int j = up(m, q);
        huffman(m - 1);
        down(m, j);
    }
}

void gilbert_moor()
{
    bool b = true;
    while (b)
    { // ñîðòèðîâêà ïî àëôàâèòó (à íå ïî âåðîÿòíîñòÿì, êàê ýòî áûëî ðàíåå)
        b = false; // íå áûëî îáìåíà
        for (int i = 2; i < n; i++)
        {
            if (a[i - 1] > a[i])
            { // åñëè îáìåí íóæåí
                float temp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = temp;
                char c = a[i - 1];
                a[i - 1] = a[i];
                a[i] = c;
                b = true; // ïîìå÷àåì ÷òî áûë îáìåí
            }
        }
    }
    float q[n];
    p[0] = 0; q[0] = 0;
    q1[0] = 0;
    for (int i = 1; i < n; i++)
    {
        q[i] = q[i - 1] + p[i] / 2;
        q1[i] = q[i - 1] + q[i];
        cout << "q[ " << i << "] = " << q1[i] << endl;
        lenght[i] = ceil(-log(p[i]) / log(2)) + 1;
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= lenght[i]; j++)
        {
            q1[i] *= float(2);
            c[i][j] = floor(q1[i]);
            while (q1[i] >= 1)
                q1[i] -= 1;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    FILE* f;
    float entropy = 0, lhuffman = 0, lshanon = 0, lfano = 0, lgm = 0;
    f = fopen("lab11.txt", "r");
    for (int i = 1; i < n; i++)
        p[i] = 0;
    for (char i = 'A'; i <= 'K'; a[i - 'A' + 1] = i++);

    while (!feof(f))
    {
        char c;
        fscanf(f, "%c", &c);
        if (feof(f))
            break;
        p[c - 'A' + 1] += 1;
        sum++;
    }

    bool b = true;
    while (b)
    {
        b = false;
        for (int i = 2; i < n; i++)
        {
            if (p[i - 1] < p[i])
            {
                float temp = p[i - 1];
                p[i - 1] = p[i];
                p[i] = temp;
                char c = a[i - 1];
                a[i - 1] = a[i];
                a[i] = c;
                b = true;
            }
        }
    }

    float P[n];
    for (int i = 1; i < n; i++)
    {
        p[i] /= (float)sum;
        entropy += p[i] * abs(log(p[i]) / log(2));
        P[i] = p[i];
    }
    for (int i = 1; i < n; i++) {
        cout << "p[ " << i << "] = " << p[i] << endl;
    }
    float P1 = 0;
    for (int i = 1; i < n; i++) {
        P1 += p[i];
    }
    cout << P1 << endl;
    fclose(f);

    Shanon();
    cout << "Код Шеннона: " << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "| Символ | Вероятность | Кодовое слово | Длина кодового слова |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 1; i < n; i++)
    {
        cout << setw(6) << a[i] << "\t|" << setw(10) << p[i] << "\t|  ";
        for (int j = 1; j <= lenght[i]; j++)
            cout << c[i][j];
        for (int j = lenght[i] + 1; j < 11; j++)
            printf(" ");
        cout << "\t|" << setw(10) << lenght[i] << "\t      |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        lshanon += lenght[i] * p[i];
    }

    cout << "Энтропия исходного текста " << entropy << endl;
    cout << "Средняя длина кодового слова " << lshanon << endl;

    float IzbShanon = lshanon - entropy;

    cout << "Избыточность кода Шенона " << IzbShanon << endl;

    for (int i = 1; i < n; i++)
        lenght[i] = 0;

    Fano(1, n - 1, 0);
    printf("Код Фано: \n");
    cout << "---------------------------------------------------------------" << endl;
    cout << "| Символ | Вероятность | Кодовое слово | Длина кодового слова |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 1; i < n; i++)
    {
        cout << setw(6) << a[i] << "\t|" << setw(10) << p[i] << "\t|  ";
        for (int j = 1; j <= lenght[i]; j++)
            cout << c[i][j];
        for (int j = lenght[i] + 1; j < 11; j++)
            printf(" ");
        cout << "\t|" << setw(10) << lenght[i] << "\t      |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        lfano += lenght[i] * p[i];
    }

    cout << "Энтропия исходного текста " << entropy << endl;
    cout << "Средняя длина кодового слова " << lfano << endl;

    float Izbfano = lfano - entropy;

    cout << "Избыточность кода Фано " << Izbfano << endl;

    for (int i = 1; i < n; i++)
        lenght[i] = 0;

    huffman(n - 1);
    printf("Код Хаффмана: \n");
    cout << "---------------------------------------------------------------" << endl;
    cout << "| Символ | Вероятность | Кодовое слово | Длина кодового слова |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 1; i < n; i++)
    {
        p[i] = P[i];
        cout << setw(6) << a[i] << "\t|" << setw(10) << p[i] << "\t|  ";
        for (int j = 1; j <= lenght[i]; j++)
            cout << c[i][j];
        for (int j = lenght[i] + 1; j < 11; j++)
            printf(" ");
        cout << "\t|" << setw(10) << lenght[i] << "\t      |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        lhuffman += lenght[i] * p[i];
    }

    cout << "Энтропия исходного текста " << entropy << endl;
    cout << "Средняя длина кодового слова " << lhuffman << endl;

    float IzbHaf = lhuffman - entropy;

    cout << "Избыточность кода Хаффмана " << IzbHaf << endl;

    for (int i = 1; i < n; i++)
        lenght[i] = 0;

    gilbert_moor();
    printf("Код Гилберта-Мура: \n");
    cout << "---------------------------------------------------------------" << endl;
    cout << "| Символ | Вероятность | Кодовое слово | Длина кодового слова |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    for (int i = 1; i < n; i++)
    {
        cout << setw(6) << a[i] << "\t|" << setw(10) << p[i] << "\t|  ";
        for (int j = 1; j <= lenght[i]; j++)
            cout << c[i][j];
        for (int j = lenght[i] + 1; j < 11; j++)
            printf(" ");
        cout << "\t|" << setw(10) << lenght[i] << "\t      |" << endl;
        cout << "--------------------------------------------------------------" << endl;
        lgm += lenght[i] * p[i];
    }

    cout << "Энтропия исходного текста " << entropy << endl;
    cout << "Средняя длина кодового слова " << lgm << endl;

    float IzbGm = lgm - entropy;

    cout << "Избыточность кода Гилберта-Мура " << IzbGm << endl << endl;

    cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "| Энтропия  | Средняя длинна кодового слова                             |                                             Избыточность кода |" << endl;
    cout << "| Исходного |---------------------------------------------------------------------------------------------------------------------------|" << endl;
    cout << "|  Текста   | \tШеннон  | \tФано    | \tХаффман | \tГ-М     | \tШеннон   | \tФано      | \tХаффман  | \tГ-М     |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|    " << entropy << " |\t" << lshanon << " |\t" << lfano << " |\t" << lhuffman << " |\t" << lgm << " |\t" << IzbShanon << " |\t" << Izbfano << " |\t" << IzbHaf << " |\t" << IzbGm << " |" << endl;
}