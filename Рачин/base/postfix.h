#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"

using namespace std;

class TPostfix
{
  string infix;	// инфиксная
  string postfix;	// постфиксная
public:
  int NArgs,Lett;	//Кол-во переменных
  TPostfix(); // конструктор 
  TPostfix(string c); // конструктор 

  void SetInfix(string c);	//Запись инфиксной формы
  int Priority(char c); // сравнение приоритета элементов
  bool CheckString();	//Проверка инфиксной формы
  string GetInfix() { return infix; }	// получить инфиксную форму
  string GetPostfix() { return postfix; }	//получить постфиксную форму
  bool Operations(char c);  // Проверка - Операция
  bool Arguments(char c);  // Проверка - Символ
  bool Digits(char c);	// Проверка - Цифра
  string ArgsInPost(bool b);	//Количество аргументов
  string ToPostfix();	// преобразование к постфиксной форме
  double Calculate(double* Args); // Ввод переменных, вычисление по постфиксной форме
};

#endif
