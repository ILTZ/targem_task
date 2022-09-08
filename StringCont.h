#ifndef STRINGCONT_H
#define STRINGCONT_H

/*1. Ќаписан на C++11 без каких либо сторонних библиотек. Ќе использует в своей основе 
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.

2.  ласс не шаблонный. ѕоддерживает строки произвольного размера, использу€ базовые 
операции работы с динамическим хипом (функции malloc()/free() или операторы new/delete)
дл€ манипул€ции последовательност€ми символов типа char.

3. »меет конструктор копировани€, оператор присваивани€ и поддерживает move-сематнику.
” класса есть "внешний" оператор сложени€ двух строк.*/

#include <iostream>

namespace DynamicString
{
	class StringCont
	{
	private:

	public:
		StringCont()										noexcept;
		StringCont(const wchar_t* _inputString);
		StringCont(const StringCont& _other);
		StringCont(StringCont&& _other)						noexcept;

		~StringCont();

	public:
		StringCont& operator=(const StringCont& _other);
		StringCont& operator=(StringCont&& _other)			noexcept;
		friend StringCont& operator+=(StringCont& _first, const StringCont& _second);

	private:
		const wchar_t& operator[](int _index) const;

	public:
		StringCont& Append(wchar_t _symbol);

		StringCont& ClearString();

		const wchar_t* GetString()		const noexcept;
		size_t GetLength()				const noexcept;

	private:
		wchar_t* mainString;
		size_t size;

		void deleteString();
		wchar_t* expand(const wchar_t* _ptr, size_t _newSize) const;
	};

	std::wostream& operator<<(std::wostream& _os, const StringCont& _s);
	std::wistream& operator>>(std::wistream& _is, StringCont& _s);

	StringCont operator+(const StringCont& _f, const StringCont& _s);
	
	bool operator<(const StringCont& _first, const StringCont& _second);
	bool operator>(const StringCont& _first, const StringCont& _second);
	bool operator==(const StringCont& _first, const StringCont& _second);

}

#endif