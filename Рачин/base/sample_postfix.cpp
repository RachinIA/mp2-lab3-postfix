#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  TPostfix postfix;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  getline (cin,expression);
  cout << expression << endl;
  postfix.SetInfix(expression);
  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  if (postfix.CheckString())
	  cout << "Постфиксная форма: " << postfix.ToPostfix() << endl;
  else cout << "Не верное выражение." << endl;
  cout << "Введите значение для заданного количества переменных: " << postfix.ArgsInPost(postfix.NArgs == postfix.Lett) << endl;
  double* _A = new double[postfix.NArgs];
  for (int i = 0; i < postfix.NArgs; i++)
  {
	  cin >> _A[i];
  }
  res = postfix.Calculate(_A);
  cout<< "Результат:" << res << endl;

  return 0;
}
