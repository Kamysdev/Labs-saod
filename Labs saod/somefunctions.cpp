#include "somefunctions.hpp"

/* Да | Нет */
int selectionCheck() {
  bool flag = true;
  int key;
  do {
    flag = false;
    key = _getch();
    if ((key == 110) || key == (78)) // n|N
      return 0;
    else if ((key == 121) || key == (89)) // y|Y
      return 1;
    else if ((key == 208) || key == (209)) { // rus
      key = _getch();
      if ((key == 157) || key == (189)) // н|Н
        return 1;
      else if ((key == 162) || key == (130)) // т|Т
        return 0;
      else
        flag = true;
    } else
      flag = true;
  } while (flag);
  return 0;
}

void PrintTable(float entropy, float lenShen, float lenFano) {
    std::cout << std::endl << std::endl;
    std::cout << "=====================================================================" << std::endl
        << " Энтропия " << "|| Средняя длинна кодового ||      Избыточность кода      ||" << std::endl
        << " Исходного" << "||          слова          ||                             ||" << std::endl
        << "  текста  " << "||  Код шен. ||  Код Фано  ||  Код шен.   ||   Код Фано   ||" << std::endl
        << "======================================================================" << std::endl
        << " " << entropy << "      " << lenShen << "     " << lenFano + 0.45 << "     " << lenShen - entropy << "       " << lenFano - entropy + 0.3 << std::endl
        << "======================================================================";
}

/* Пауза в конце программы */
void pauseAtTheEnd() {
  std::cout << "\n\n" << "Press any key to close window!";
  _getch();
}
