#include "TestProg.h"

using namespace App;


int TestProg::getUserInteger(const wchar_t* _message, int _topEx, int _botEx) const
{
	if (_message)
		std::wcout << _message << std::endl;

	bool good = false;

	int x;
	while (true)
	{
		if ((std::wcin >> x).good() && x <= _topEx && x >= _botEx)
		{
			std::wcin.clear();
			std::wcin.ignore(100, '\n');
			return x;
		}
		if (std::wcin.fail() || x > _topEx)
		{
			std::wcin.clear();
			std::wcout << L"Uncorrect input!" << std::endl;
		}
		std::wcin.ignore(100, '\n');
	}

	return x;
}

StringCont TestProg::getUserString(const wchar_t* _message) const
{
	if (_message)
		std::wcout << _message << std::endl;

	StringCont temp;
	std::wcin >> temp;

	return temp;
}


void TestProg::DoProgramm(int _argc, wchar_t** _argv) const
{	
	std::vector<StringCont> sVector;
		
	if (_argc > 1)
	{
		if (!prepVector(sVector, _argc, _argv))
			return;
	}
	else
	{
		if (!prepVector(sVector))
			return;
	}

	printVector(sVector, L"Vector before reverse lexicographic permutation effect:");

	doSort(sVector);

	printVector(sVector, L"Vector after reverse lexicographic permutation effect:");

	printCMDLine(L"Program completed.", true);
}



bool App::TestProg::prepVector(std::vector<StringCont>& _vec, int _argc, wchar_t** _argv) const
{
	if (_argv)
	{
		printCMDLine(L"Cmd arguments was found.", true);
		fillVectorFromArgv(_vec, _argv, _argc);
	}
	else
	{
		printCMDLine(L"No cmd arguments found.", true);
		printCMDLine(L"Lines will be entered manually.");
		fillVectorFromCmd(getUserInteger(L"How many lines do you want to enter? ", INT_MAX, 0), _vec);
	}

	if (_vec.size() < 1)
	{
		printCMDLine(L"No lines were found :(\nProgram is terminating...");
		return false;
	}

	return true;
}

void TestProg::fillVectorFromCmd(int _stringNumbers, std::vector<StringCont>& _vec) const 
{
	printCMDLine(L"Type 'end' to stop the process.");
	printCMDLine(L"(Spaces between words in a line are taken into account).");

	for (int i = 0; i < _stringNumbers; ++i)
	{
		std::wcout << L"Line #" << i + 1 << L" : ";

		StringCont temp;
		std::wcin >> temp;

		if (temp == L"end")
		{
			break;
		}

		_vec.push_back(temp);
	}
}

bool App::TestProg::fillVectorFromArgv(std::vector<StringCont>& _vec, wchar_t** _argv, int _argc) const
{
	for (int i = 1; i < _argc; ++i)
	{
		_vec.emplace_back(_argv[i]);
	}

	if (_vec.size() < 1)
	{
		printCMDLine(L"No lines were found :(\nProgram is terminating...");
		return false;
	}

	return true;
}


void TestProg::doSort(std::vector<StringCont>& _vec) const
{
	bubbleSort(_vec, [](const StringCont& _first, const StringCont& _second) -> bool
		{
			return (_first < _second ? true : false);
		});
}

void TestProg::printVector(std::vector<StringCont>& _vec, const wchar_t* _message) const noexcept
{
	if (_message)
		printCMDLine(_message, true);
	
	for (auto& ex : _vec)
	{
		std::wcout << ex.GetString() << std::endl;
	}
}

void App::TestProg::printCMDLine(const wchar_t* _message, bool _separate) const noexcept
{
	if (_message)
	{
		if (_separate)
			printSectionSeparator(separator, wcslen(_message));

		std::wcout << _message << std::endl;
	}
}

void App::TestProg::printSectionSeparator(wchar_t _symbol, size_t _repeatCount) const noexcept
{
	for (size_t i = 0; i < _repeatCount; ++i)
	{
		std::wcout << _symbol;
	}
	std::wcout << std::endl;
}

void App::TestProg::bubbleSort(std::vector<StringCont>& _vec, bool(*_comp)(const StringCont&, const StringCont&)) const 
{
	for (unsigned int i = 0; i < _vec.size(); ++i)
	{
		for (unsigned int j = 0; j < _vec.size() - 1; ++j)
		{
			if (_comp && _comp(_vec[j], _vec[j + 1]))
			{
				std::swap(_vec[j], _vec[j + 1]);
			}
		}
	}
}




