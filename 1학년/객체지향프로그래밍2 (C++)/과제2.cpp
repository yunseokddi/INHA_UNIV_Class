#include <iostream> //12171651 ��ǻ�Ͱ��а� ������
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

ostream& tab2(ostream& output) //���� �� �߰�
{
	return output << '\v';
}

ostream& backspace(ostream& output) //�齺���̽�
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
	
	cout << "aaaaaaaa" << tab2 << "bbbbbb"; //������
	
	cout << "ccccccc" << backspace << "dddddd"; //�齺���̽�
}
