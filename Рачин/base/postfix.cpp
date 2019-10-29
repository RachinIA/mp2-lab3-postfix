#include "postfix.h"
#include "stack.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
TPostfix::TPostfix()
{
	infix = "a+b";
}

TPostfix::TPostfix(string c)
{
	infix = c;
}

void TPostfix::SetInfix(string c)
{
	infix = c;
	postfix = "";
}

int TPostfix::Priority(char c)
{
	if(c=='(')return 0;
	if(c==')')return 1;
	if(c=='+')return 2;
	if(c=='-')return 2;
	if(c=='*')return 3;
	if(c=='/')return 3;
	return -1;
}

bool TPostfix::CheckString()
{
	if (infix.length() == 0) return false;
	string c="";
	int Size = infix.length();
	for (int i = 0; i < Size; i++)
		if(infix[i] !=' ')c += infix[i];
	infix = c;
	int LB = 0, RB = 0, OpByOp=0;
	for (int i = 0; i < Size; i++)
	{
		if (infix[i] == '(') {
			LB++; continue;
		}
		if (infix[i] == ')') {
			RB++; continue;
		}
		if (Operations(infix[i]))
		{
			OpByOp++; if (OpByOp > 2)return false;
		}
		else OpByOp = 0;
	}
	if (RB != LB)return false;
	if ( infix[0] == '*' || infix[0] == '/') return false;
	if (infix[infix.length()-1] == '+' || infix[infix.length()-1] == '-' || infix[infix.length()-1] == '*' || infix[infix.length()-1] == '/') return false;
	return true;
}

bool TPostfix::Operations(char c)
{
	const string Operations = "+-*/()";
	if (Operations.find(c) == string::npos)
		return false;
	else return true;
}

bool TPostfix::Arguments(char c)
{
	if (c <= 'z' && c >= 'a') return true;
	return false;
}

bool TPostfix::Digits(char c)
{
	const string Digits = "0123456789";
	if (Digits.find(c) == string::npos)
		return false;
	else return true;
}

string TPostfix::ArgsInPost(bool b)
{
	string tmp="";
	int Size = postfix.length();
	for (int i = 0; i < Size; i++)
		if (Arguments(postfix[i])) tmp += postfix[i];
	Lett = tmp.length();
	int a = Lett;
	string temp = tmp;
	for (int i = 0; i <Lett; i++)
	{
		for (int j = i + 1; j < Lett; j++)
		{
			if ((temp[i] == temp[j]) && (temp[i] != '0'))
			{
				a--;
				temp[j] = '0';
			}
		}
	}
	NArgs = a;
	if (b)
		return tmp;
	else {
		tmp = "";
		for (int i = 0; i < Lett; i++)
			if (temp[i] != '0')tmp += temp[i];
		return tmp;
	}
	}



string TPostfix::ToPostfix()
{
	if (!CheckString()) throw "Incorrect ex";
	int Size = infix.length();
	TStack<char> Stack(Size);
	postfix = "";
	for (int i = 0; i < Size; i++)
	{
		if (Arguments(infix[i])) postfix += infix[i];
		else if (Operations(infix[i])) {
			if (Stack.IsEmpty())
				Stack.Push(infix[i]);
			else if (Stack.TopElem() == '(')
				Stack.Push(infix[i]);
			else if (infix[i] == '(')
				Stack.Push(infix[i]);
			else if (infix[i] == ')')
			{
				while (Stack.TopElem() != '(')
				{
					postfix += Stack.Pop();
				}
				Stack.Pop();
			}
			else if (Priority(infix[i]) > Priority(Stack.TopElem()))
				Stack.Push(infix[i]);
			else
			{
				while ((Stack.TopElem() != '('))
				{
					if (Priority(infix[i]) > Priority(Stack.TopElem()))
						break;
					postfix += Stack.Pop();
					if (Stack.IsEmpty())
						break;
				}
				Stack.Push(infix[i]);
			}
		}
	}
	while (!Stack.IsEmpty())
	{
		postfix += Stack.Pop();
	}
	return postfix;
}

double TPostfix::Calculate(double* _A)
{
	int Size = postfix.length();
	TStack<double> Stack(Size);
	double val1, val2;
	int j = 0;
	double* A = new double[NArgs]();
	if (NArgs == Lett) 
	{
		for (int i = 0; i < NArgs; i++)
		{
			A[i] = _A[i];
		}
	}
	else
	{
		string tmp = ArgsInPost(!(NArgs == Lett));
		int k = 0;
		for (int i = 0; i < Lett; i++)
		{
			if (Arguments(tmp[i]))
			{
				A[i] = _A[k++];
			}
			for (int j = i + 1; j < Lett; j++)
			{
				if (Arguments(tmp[j]))
				{
					if ((tmp[i] == tmp[j]) && (tmp[i] != ' '))
					{
						A[j] = A[i];
						tmp[j] = ' ';
					}
				}
			}
		}

	}
	j = 0;
	for (int i = 0; i < Size; i++)
	{
		if (Arguments(postfix[i]))
		{
			Stack.Push(A[j++]);
		}
		else
		{
			val1 = Stack.Pop();
			val2 = Stack.Pop();

			switch (postfix[i])
			{
			case '+':
				Stack.Push(val1 + val2);
				break;
			case '-':
				Stack.Push(val2 - val1);
				break;
			case '/':
				Stack.Push(val2 / val1);
				break;
			case '*':
				Stack.Push(val1 * val2);
				break;
			}
		}
	}
	return Stack.TopElem();
}
