#ifndef __STACK_H__
#define __STACK_H__
//#include <iostream>

const int MaxStackSize = 100;

template <class T>
class TStack
{
  T *pMem;		//стек
  int size=0;	//размер стека
  int top;	//индекс верхнего элемента
public:
  TStack(int _size)	//конструктор
  {
	  size = _size;
	  top = -1;
	  if ((size < 1) || (size > MaxStackSize))
		  throw "Wrong Size";
   
    pMem = new T[size];
  }
  ~TStack()	//деструктор
  {
    delete [] pMem;
  }
  void Push(const T value);		// поместить элемент в стек
  T Pop();	// удалить из стека элемент 
  bool IsEmpty();	// проверка пустоты
  bool IsFull();	//проверка переполнения
  T TopElem();	//	получить верхний элемент
};

template <class T>
void TStack<T>::Push(const T value)
{
	if (IsFull()) throw "Full"; // стек полон

	pMem[++top] = value; // помещаем элемент в стек 
}

template<class T>
inline T TStack<T>::Pop()
{
	if (IsEmpty()) throw "Empty";	// стек пуст

	return pMem[top--];
}


template<class T>
inline bool TStack<T>::IsEmpty()	// проверка на пустоту
{
	return top == -1;
}

template<class T>
inline bool TStack<T>::IsFull()	//проверка на переполнение
{
	return top == size-1;
}

template<class T>
inline T TStack<T>::TopElem()
{
	if (IsEmpty()) throw "Empty";	// стек пуст
	return pMem[top];	//верхний элемент
}

#endif
