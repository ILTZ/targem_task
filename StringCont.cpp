#include "StringCont.h"

using namespace DynamicString;

StringCont::StringCont() noexcept :
	mainString{ nullptr }, size{0}
{
}

StringCont::StringCont(const wchar_t* _inputString) :
	mainString{ nullptr }, size{ wcslen(_inputString) }
{
	mainString = expand(_inputString, size);
}

StringCont::StringCont(const StringCont& _other) :
	mainString{nullptr}, size{0}
{	
	if (_other.mainString)
	{
		size = _other.GetLength();

		mainString = expand(_other.mainString, size);
	}
}

StringCont::StringCont(StringCont&& _other) noexcept :
	mainString{ nullptr }, size{0}
{
	if (this != &_other)
	{	
		size = _other.GetLength();

		mainString = std::move(_other.mainString);
		_other.mainString = nullptr;
	}
}

StringCont::~StringCont()
{
	if (mainString)
	{
		delete[] mainString;
		mainString = nullptr;
	}
}

StringCont& StringCont::operator=(const StringCont& _other)
{
	if (_other.mainString)
	{
		size = _other.GetLength();
		deleteString();

		mainString = expand(_other.mainString, size);
	}

	return *this;
}

StringCont& StringCont::operator=(StringCont&& _other) noexcept
{
	if (this != &_other)
	{
		deleteString();
		size = _other.GetLength();

		mainString = std::move(_other.mainString);
		_other.mainString = nullptr;
	}

	return *this;
}

const wchar_t& StringCont::operator[](int _index) const
{
	return mainString[_index];
}

void StringCont::deleteString()
{
	if (mainString)
	{
		delete[] mainString;
		mainString = nullptr;
	}
}

const wchar_t* StringCont::GetString() const noexcept
{
	return mainString;
}

size_t StringCont::GetLength() const noexcept
{
	return size;
}

StringCont& StringCont::Append(wchar_t _symbol)
{
	if (mainString == nullptr)
	{
		mainString = expand(nullptr, 1);
		mainString[0] = _symbol;
		mainString[1] = '\0';
		++size;

		return *this;
	}

	wchar_t* temp = expand(mainString, size + 1);
	temp[size] = _symbol;
	temp[++size] = '\0';

	deleteString();

	mainString = std::move(temp);
	temp = nullptr;


	return *this;
}

StringCont& StringCont::ClearString()
{
	deleteString();
	size = 0;

	return *this;
}

// Use <nullptr> as the first parameter if you want to create a new empty string.
// Use a valid *ptr as the first parameter to copy its value to a new string.
wchar_t* StringCont::expand(const wchar_t* _ptr, size_t _newSize) const
{
	// +1 for '\0'
	wchar_t* temp = new wchar_t[_newSize + 1];

	if (_ptr)
		wcscpy_s(temp, _newSize + 1, _ptr);
	
	return temp;
}


std::wostream& DynamicString::operator<<(std::wostream& _os, const StringCont& _s)
{
	return (_os << _s.GetString());
}
std::wistream& DynamicString::operator>>(std::wistream& _is, StringCont& _s)
{
	_s.ClearString();
	_is >> std::ws;

	wchar_t ch;
	while (_is.get(ch))
	{
		// The space character can also be part of a string
		if (iswspace(ch) && (ch == ' '))
		{
			_s.Append(ch);
			continue;
		}

		if (iswspace(ch))
			break;

		_s.Append(ch);
	}

	return _is;
}

StringCont DynamicString::operator+(const StringCont& _f, const StringCont& _s)
{
	StringCont temp = _f;
	temp += _s;

	return temp;
}
StringCont& DynamicString::operator+=(StringCont& _first, const StringCont& _second)
{
	for (unsigned int i = 0; i < _second.GetLength(); ++i)
	{
		_first.Append(_second[i]);
	}

	return _first;
}

bool DynamicString::operator<(const StringCont& _first, const StringCont& _second)
{
	return (_wcsicmp(_first.GetString(), _second.GetString()) < 0 ? true : false);
}
bool DynamicString::operator>(const StringCont& _first, const StringCont& _second)
{
	return (_wcsicmp(_first.GetString(), _second.GetString()) > 0 ? true : false);
}
bool DynamicString::operator==(const StringCont& _first, const StringCont& _second)
{
	return (_wcsicmp(_first.GetString(), _second.GetString()) == 0 ? true : false);
}

