#ifndef STRINGCONT_H
#define STRINGCONT_H

/*1. ������� �� C++11 ��� ����� ���� ��������� ���������. �� ���������� � ����� ������ 
�����-���� ������ ���������� ������������ �����, ����������� ��� ����� ���������� STL.

2. ����� �� ���������. ������������ ������ ������������� �������, ��������� ������� 
�������� ������ � ������������ ����� (������� malloc()/free() ��� ��������� new/delete)
��� ����������� �������������������� �������� ���� char.

3. ����� ����������� �����������, �������� ������������ � ������������ move-���������.
� ������ ���� "�������" �������� �������� ���� �����.*/

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