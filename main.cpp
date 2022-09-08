/*Реализовать класс динамических строк, который:

1. Написан на C++11 без каких либо сторонних библиотек. Не использует в своей основе 
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.

2. Класс не шаблонный. Поддерживает строки произвольного размера, используя базовые 
операции работы с динамическим хипом (функции malloc()/free() или операторы new/delete)
для манипуляции последовательностями символов типа char.

3. Имеет конструктор копирования, оператор присваивания и поддерживает move-сематнику.
У класса есть "внешний" оператор сложения двух строк.

Нет необходимости использовать какие-то изощренные методы оптимизации (типа COW и 
многопоточной поддержки).

Написать пример с использованием этого класса строк и какого-либо контейнера STL. 
Программа должна принимать список строк, затем выдавать его в порядке, обратном
лексикографическому без учета регистра.

Программа-пример работает из командной строки.*/

#include "TestProg.h"

#include <io.h>
#include <fcntl.h>

struct CMDCode
{
	int out = _O_U16TEXT;
	int in = _O_U16TEXT;
	int err = _O_U16TEXT;
};

// To read from cmd most type of characters (including russian)
void swapCondoleCode(CMDCode& _struct)
{
	_struct.out = _setmode(_fileno(stdout), _struct.out);
	_struct.in = _setmode(_fileno(stdin), _struct.in);
	_struct.err = _setmode(_fileno(stderr), _struct.err);
}


int wmain(int argc, wchar_t* argv[])
{
	try
	{	
		CMDCode cmd;
		swapCondoleCode(cmd);

		App::TestProg t;
		t.DoProgramm(argc, argv);
	}
	catch (std::exception& _ex)
	{
		std::cout << _ex.what() << std::endl;
	}


	system("pause");
	return 0;

}