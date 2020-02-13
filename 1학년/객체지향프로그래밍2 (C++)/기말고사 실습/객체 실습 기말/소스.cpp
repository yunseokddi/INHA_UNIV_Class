#include <fstream>
#include <iostream>
#include <string> // char*

using namespace std;

template <typename T>
class Student
{
private:
	string s_name;
	T subject[3]; //과목별 점수

public:
	Student()
	{
		subject[0] = NULL;
		subject[1] = NULL;
		subject[2] = NULL;
	}
	~Student()
	{

	}

	void setstudent(string a, T b, T c, T d)
	{
		s_name = a;
		subject[0] = b;
		subject[1] = c;
		subject[2] = d;
	}

	string getstudentName()
	{
		return this->s_name;

	}
	T *getSubjectScore()
	{
		return this->subject;
	}
};

template <typename T>
class List
{
private:
	int count;
	string filename;
	Student <T> student[52];
	ofstream outFile;
	ifstream inFile;
public:
	List(string p_filename)
	{
		this->filename = p_filename;
		this->count = 0;
		inFile = ifstream(this->filename);
		while (!inFile.eof())
		{
			T score0, score1, score2;
			string name;
			inFile >> name >> score0 >> score1 >> score2;
			student[count].setstudent(name, score0, score1, score2);
			count++;
		}
		count--;
		inFile.close();
	}
	~List()
	{
		inFile.close();
		outFile.close();
	}

	void printList()
	{
		this->outFile = ofstream(filename);

		for (int i = 0; i < count; i++)
		{
			outFile << student[i].getstudentName() << " " << student[i].getSubjectScore()[0]
				<<" " << student[i].getSubjectScore()[1] << " "<<  student[i].getSubjectScore()[2] << endl;

		}
	}

	void showList()
	{
		for (int i = 0; i < count; i++)
		{
			cout << student[i].getstudentName() << " " << student[i].getSubjectScore()[0]
				<< " " << student[i].getSubjectScore()[1] << " " << student[i].getSubjectScore()[2] << endl;

		}
	}

	void addStudent(string a, T b, T c, T d)
	{
		if (count < 52)
			this->student[count].setstudent(a, b, c, d);
		count++;
	}

	void removeStudent(int n)
	{
		if (n < count)
		{
			for (int i = n; i < count; i++)
			{
				this->student[i] = this->student[i + 1];
			}
			
			count--;
		}
	}

	//중간 점수로 추가됨.
	void sortHigh()
	{
		//해당 번호의 과목으로 오름차순으로 배열 정렬
	}

	void sortLow()
	{
		// '' 내림차순으로 배열 정렬
	}
};

void main()
{
	List<char> test0("print.txt");
	test0.showList();

	test0.addStudent("NOPE",'A', 'B', 'C');
	test0.showList();
	test0.printList();
	cout << endl;
	test0.removeStudent(4);
	test0.showList();
	test0.printList();

	system("PAUSE");
}