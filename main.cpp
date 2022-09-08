/*����������� ����� ������������ �����, �������:

1. ������� �� C++11 ��� ����� ���� ��������� ���������. �� ���������� � ����� ������ 
�����-���� ������ ���������� ������������ �����, ����������� ��� ����� ���������� STL.

2. ����� �� ���������. ������������ ������ ������������� �������, ��������� ������� 
�������� ������ � ������������ ����� (������� malloc()/free() ��� ��������� new/delete)
��� ����������� �������������������� �������� ���� char.

3. ����� ����������� �����������, �������� ������������ � ������������ move-���������.
� ������ ���� "�������" �������� �������� ���� �����.

��� ������������� ������������ �����-�� ���������� ������ ����������� (���� COW � 
������������� ���������).

�������� ������ � �������������� ����� ������ ����� � ������-���� ���������� STL. 
��������� ������ ��������� ������ �����, ����� �������� ��� � �������, ��������
������������������� ��� ����� ��������.

���������-������ �������� �� ��������� ������.*/

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