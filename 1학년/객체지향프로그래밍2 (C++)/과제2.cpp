#include <iostream> //12171651 컴퓨터공학과 오윤석
using namespace std;

ostream& bell(ostream& output)
{
	return output << '\a';
}

ostream& carriageReturn(ostream& output)
{
	return output << '\r';
}

ostream& tab(ostream& output)
{
	return output << '\t';
}

ostream& endline(ostream& output)
{
	return output << '\n' << flush;
}

ostream& tab2(ostream& output) //가로 탭 추가
{
	return output << '\v';
}

ostream& backspace(ostream& output) //백스페이스
{
	return output << '\b';
}

int main()
{
	cout << "Testing the tab manipulator: " << endline
		<< 'a' << tab << 'b' << tab << 'c' << endline;
	
	cout << "Testing the carriageReturn and bell manipulators:"
		<< endline << "...........";

	cout << bell;
	cout << carriageReturn << "-----" << endline;
	
	cout << "aaaaaaaa" << tab2 << "bbbbbb"; //가로탭
	
	cout << "ccccccc" << backspace << "dddddd"; //백스페이스
}
