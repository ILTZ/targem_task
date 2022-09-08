#ifndef TESTPROG_H
#define TESTPROG_H

#include "StringCont.h"
#include <vector>

/*Ќаписать пример с использованием этого класса строк и какого-либо контейнера STL. 
ѕрограмма должна принимать список строк, затем выдавать его в пор€дке, обратном
лексикографическому без учета регистра.*/

using namespace DynamicString;

namespace App
{
	class TestProg
	{
	private:
		const wchar_t separator = L'-';

	private:
		int getUserInteger(const wchar_t* _message, int _topEx, int _botEx) const;
		StringCont getUserString(const wchar_t* _message = nullptr)			const;

	public:
		TestProg() = default;
		TestProg(const TestProg&)				= delete;
		TestProg(TestProg&&)					= delete;
		TestProg& operator=(const TestProg&)	= delete;
		TestProg& operator=(TestProg&&)			= delete;

	public:
		void DoProgramm(int _argc = 0, wchar_t** _argv = nullptr) const;

	private:
		bool prepVector(std::vector<StringCont>& _vec, int _argc = 0, wchar_t** _argv = nullptr)	const;
		void fillVectorFromCmd(int _stringNumbers, std::vector<StringCont>& _vec)					const;
		bool fillVectorFromArgv(std::vector<StringCont>& _vec, wchar_t** _argv, int _argc)			const;

		void doSort(std::vector<StringCont>& _vec) const;

	private:
		void printVector(std::vector<StringCont>& _vec, const wchar_t* _message = nullptr)	const noexcept;
		void printCMDLine(const wchar_t* _message, bool _separate = false)					const noexcept;
		void printSectionSeparator(wchar_t _symbol, size_t _repeatCount)					const noexcept;

	private:
		void bubbleSort(std::vector<StringCont>& _vec, bool(*_comp)(const StringCont&, const StringCont&) = nullptr) const;

	};


}

#endif // !TESTPROG_H

