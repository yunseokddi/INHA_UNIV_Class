#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

int physical_address[256] = { 0 };
int physical_num = 0;
int frame_number_1 = 0;
int TLB_hit = 0;
int TLB_A_hit = 0;

void create_reference_string(string filename, int arr[1000][2]);
void tlb(int page_number, int tlb_table[32][3], int offset, int frame_table[256][4]);
void frame_table_allocation(int page_number, int frame_table[256][4], int offset);
void allocation_physical(int frame_number, int offset);
int invertTwotoTen(string data);
void allocation_TLB_LRU(int TLB[32][3]);
void allocation_frame(int frame[256][4]);
void frame_table_A_allocation(int page_number, int frame_table[256][4], int offset);
void tlb_app(int page_number, int tlb_table[32][3], int offset, int frame_table[256][4], unsigned int tlb_A_table[32]);

void create_reference_string(string filename, int arr[1000][2]) //address.txt ���Ͽ� �ִ� logical address�� �迭�� �ű��.
{
	string filepath = filename;

	ifstream openFile(filepath, ios::in);

	string s_logical_address;
	string str;
	string page;
	string offset;
	int i_page;
	int i_offset;

	if (openFile.is_open())
	{
		int i = 0;

		while (getline(openFile, s_logical_address))
		{
			int i_logical = atoi(s_logical_address.c_str());
			bitset<16> s_logical_address (i_logical);
			str = s_logical_address.template to_string<char,char_traits<char>, allocator<char> >();
			page = str.substr(0, 8);
			offset = str.substr(8, 16);

			i_page = invertTwotoTen(page);
			i_offset = invertTwotoTen(offset);

			arr[i][0] = i_page;
			arr[i][1] = i_offset;

			i++;


		}


		openFile.close();
	}
}

void tlb(int page_number, int tlb_table[32][3], int offset, int frame_table[256][4])
{


	int tlb_check = 0; //tlb check���ִ� ����. tlb�� �����ϸ� 1, �ƴϸ� 0
	int tlb_frame = 0;
	int tlb_idx = 0;
	int tlb_full = 0; //tlb�� �� ���� ������ 1 �ƴϸ� 0
	int tlb_not_full_idx = 0;

	for (int i = 0; i < 32; i++) //tlb check
	{
		
		if (tlb_table[i][0] == -1) //tlb�� full���� Ȯ��
		{
			tlb_full = 1; //�� ���� ������ 1
			tlb_not_full_idx = i;
		}

		if (page_number == tlb_table[i][0])
		{
			tlb_check = 1;
			tlb_frame = tlb_table[i][1];
			tlb_idx = i;
			break;

		}
	}


	if (tlb_check == 1) //���� tlb�� page_number�� �����Ѵٸ�
	{
		


		allocation_physical(tlb_frame, offset); //physical.txt �� ����

		for (int counter = 0; counter < 32; counter++) //tlb�� �Ⱦ��� �ֵ� count ����
		{
			if (counter == tlb_idx || tlb_table[counter][1] == -1)
			{
				tlb_table[counter][2] = 0;
				continue;
			}

			tlb_table[counter][2]++;
		}
		TLB_hit++;

	}

	else //tlb�� page_number�� �������� �ʴٸ�
	{


		int max = -2;
		int max_idx = 0;

		frame_table_allocation(page_number, frame_table, offset);


		if (tlb_full != 1) //tlb�� �� �� ������ 
		{

			for (int counter = 0; counter < 32; counter++) //tlb replacement
			{
				if (tlb_table[counter][2] > max)
				{

					max = tlb_table[counter][2];
					max_idx = counter;
				}

			}

			tlb_table[max_idx][0] = page_number;
			tlb_table[max_idx][1] = frame_number_1;
			tlb_table[max_idx][2] = 0;

			for (int i = 0; i < 32; i++)
			{
				if (i == max_idx)
				{
					continue;
				}

				else
				{
					tlb_table[i][2]++;
				}
			}
		}

		else //tlb�� �� ���� �ʾ����� 
		{
			tlb_table[tlb_not_full_idx][0] = page_number;
			tlb_table[tlb_not_full_idx][1] = frame_number_1;
			tlb_table[tlb_not_full_idx][2] = 0;

			for (int i = 0; i < 32; i++)
			{
				if (i == tlb_not_full_idx || tlb_table[i][0] == -1)
				{
					continue;
				}

				else
				{
					if (tlb_table[i][0] == -1)
					{
						continue;
					}

					else
					{
						tlb_table[i][2]++;
					}
				}
			}
		}

	}


}


void frame_table_allocation(int page_number, int frame_table[256][4], int offset)
{
	int frame_check = 0; //frame table�� page number�� �ִ��� Ȯ���ϴ� ����. ������ 0, ������ 1
	int frame_idx = 0;

	for (int i = 0; i < 256; i++)
	{
		if (frame_table[i][2] == page_number)
		{
			frame_check = 1;
			frame_idx = i;

		}
	}

	if (frame_check == 1) //frame table�� �����Ѵٸ�
	{
		allocation_physical(frame_idx, offset);

		for (int i = 0; i < 256; i++) //count ����
		{

			if (i == frame_idx)
			{
				frame_table[i][3] = 0;
			}

			else if (frame_table[i][1] == 1)
			{
				frame_table[i][3]++;
			}
		}
		frame_number_1 = frame_idx;

	}



	else //frame table�� �������� �ʴ´ٸ�
	{
		int check_full_frame = 0; //frame�� �ڸ��� ������ 0, ������ 1

		for (int counter = 0; counter < 256; counter++) //frame�� ����������
		{
			if (frame_table[counter][2] == -1)
			{
				check_full_frame = 0;
				break;
			}
			else
			{
				check_full_frame = 1;
			}
		}


		if (check_full_frame == 0)
		{


			for (int count = 0; count < 256; count++)
			{
				if (frame_table[count][2] == -1)
				{

					frame_table[count][1] = 1;
					frame_table[count][2] = page_number;


					for (int i = 0; i < 256; i++) //count ����
					{
						if (frame_table[i][1] == 1)
						{
							frame_table[i][3]++;
						}
					}
					frame_table[count][3] = 0;
					frame_idx = frame_table[count][0];
					allocation_physical(frame_idx, offset);
					frame_number_1 = frame_idx;
					break;
				}
			}

		}

		else
		{
			int max_idx = 0;
			int max = -2;

			for (int idx = 0; idx < 256; idx++)
			{
				if (frame_table[idx][3] > max)
				{
					max = frame_table[idx][3];
					max_idx = idx;
				}
			}

			frame_table[max_idx][1] = 1;
			frame_table[max_idx][2] = page_number;

			for (int i = 0; i < 256; i++) //count ����
			{
				if (frame_table[i][1] == 1)
				{
					frame_table[i][3]++;
				}
			}
			frame_table[max_idx][3] = 0;
			frame_idx = frame_table[max_idx][0];
			allocation_physical(frame_idx, offset);
			frame_number_1 = frame_idx;

		}

	}

}




void allocation_physical(int frame_number, int offset) //frame number�� offet�� ������ �ּ� ��ȯ�� physical.txt�� ����
{
		string physical_txt = "physical.txt";

		ofstream output(physical_txt, ios::app);
		output << frame_number*256+offset << endl;

}


int invertTwotoTen(string data)
{

	int arr[8] = { 0 };
	int sum = 0;
	for (int count = 0; count < 8; count++)
	{

		if (data.at(count) - 48 < 0)
		{
			arr[count] = 0;
		}

		else
		{
			arr[count] = data.at(count) - 48;
		}


	}


	for (int counter = 0; counter < 8; counter++)
	{
		sum = sum + arr[counter] * pow(2, 7 - counter);

	}

	return sum;

}


void allocation_TLB_LRU(int TLB[32][3]) // TLB_LRU ����
{
	string physical_txt = "TLB_LRU.txt";

	ofstream output(physical_txt, ios::app);

	output << "page#" << " " << "frame#" << endl;

	for (int counter = 0; counter < 32; counter++)
	{
		output << TLB[counter][0] << " " << TLB[counter][1] << endl;
	}

}

void allocation_TLB_A_LRU(int TLB[32][3]) // TLB_LRU ����
{
	string physical_txt = "TLB_LRUA.txt";

	ofstream output(physical_txt, ios::app);

	output << "page#" << " " << "frame#" << endl;

	for (int counter = 0; counter < 32; counter++)
	{
		output << TLB[counter][0] << " " << TLB[counter][1] << endl;
	}

}

void allocation_TLB_LRU_A(int TLB[32][3]) // TLB_LRU ����
{
	string physical_txt = "TLB_LRUA.txt";

	ofstream output(physical_txt, ios::app);

	output << "page#" << " " << "frame#" << endl;

	for (int counter = 0; counter < 32; counter++)
	{
		output << TLB[counter][0] << " " << TLB[counter][1] << endl;
	}

}

int frame_all = 0;

void allocation_frame(int frame[256][4]) // frame_table ����
{
	string physical_txt = "frame_table.txt";

	if (frame_all == 1)
	{
		physical_txt = "frame_table_2.txt";
	}

	ofstream output(physical_txt, ios::app);

	output << "frame#" << " " << "flag"<<" " <<"page#" << endl;

	for (int counter = 0; counter < 256; counter++)
	{
		output << frame[counter][0] << " " << frame[counter][1] <<" " <<frame[counter][2]<< endl;
	}

}

void tlb_app(int page_number, int tlb_table[32][3], int offset, int frame_table[256][4], unsigned int tlb_A_table[32]) //tlb approximate
{


	int tlb_check = 0; //tlb check���ִ� ����. tlb�� �����ϸ� 1, �ƴϸ� 0
	int tlb_frame = 0;
	int tlb_idx = 0;
	int tlb_full = 0; //tlb�� �� ���� ������ 1 �ƴϸ� 0
	int tlb_not_full_idx = 0;

	for (int i = 0; i < 32; i++) //tlb check
	{
		if (tlb_table[i][0] == -1) //tlb�� full���� Ȯ��
		{
			tlb_full = 1; //�� ���� ������ 1
			tlb_not_full_idx = i;
		}

		if (page_number == tlb_table[i][0])
		{

			tlb_check = 1;
			tlb_frame = tlb_table[i][1];
			tlb_idx = i; //tlb hit�� �Ͼ tlb table idx
			break;

		}
	}


	if (tlb_check == 1) //���� tlb�� page_number�� �����Ѵٸ�
	{

		for (int counter = 0; counter < 32; counter++) //tlb�� �Ⱦ��� �ֵ� count ����
		{
			if (counter == tlb_idx) //tlb table�� hit�� �Ͼ ��� ���������� sift�� �� ���ʿ� 1 �߰�
			{
				tlb_A_table[counter] = tlb_A_table[counter] / 2 + 2147483648;
				continue;
			}

			else if (tlb_table[counter][1] == -1) //tlb table�� �Ҵ��� �ȵǾ��ִ� �ֵ��� �׳� �Ѿ
			{
				continue;
			}


			tlb_A_table[counter] = (tlb_A_table[counter] / 2); //������ �Ҵ� �Ǿ� �ִ� �ֵ��� ���������� sift
		}
		TLB_A_hit++;

	}

	else //tlb�� page_number�� �������� �ʴٸ�
	{
		unsigned int min = 4294967295;
		int min_idx = 0;

		frame_table_A_allocation(page_number, frame_table, offset);


		if (tlb_full != 1) //tlb�� �� �������� 
		{
			for (int counter = 0; counter < 32; counter++) //victim ����
			{
				if (tlb_A_table[counter] < min)
				{
					min = tlb_A_table[counter];
					min_idx = counter;
				}
			}

			tlb_table[min_idx][0] = page_number;
			tlb_table[min_idx][1] = frame_number_1;

			for (int i = 0; i < 32; i++)
			{
				if (i == min_idx)
				{
					tlb_A_table[i] = 2147483648;
				}

				else
				{
					tlb_A_table[i] = (tlb_A_table[i] / 2);
				}
			}

		}

		else //tlb�� �ڸ��� �ִٸ�
		{
			tlb_table[tlb_not_full_idx][0] = page_number;
			tlb_table[tlb_not_full_idx][1] = frame_number_1;

			for (int i = 0; i < 32; i++)
			{
				if (i == tlb_not_full_idx)
				{
					tlb_A_table[i] = 2147483648;
				}

				else
				{

					if (tlb_table[i][0] == -1) //���� ����� �׳� �ѱ�
					{
						continue;
					}

					else //�̹� �Ҵ� �� �ֵ��� ���������� 1ĭ�� shift
					{
						tlb_A_table[i] = (tlb_A_table[i] / 2);
					}
				}
			}

		}
	
		


		


	}


}

void frame_table_A_allocation(int page_number, int frame_table[256][4], int offset)
{
	int frame_check = 0; //frame table�� page number�� �ִ��� Ȯ���ϴ� ����. ������ 0, ������ 1
	int frame_idx = 0;

	for (int i = 0; i < 256; i++)
	{
		if (frame_table[i][2] == page_number)
		{
			frame_check = 1;
			frame_idx = i; //frame table�� hit�� �� idx

		}
	}

	if (frame_check == 1) //frame table�� �����Ѵٸ�
	{

		frame_number_1 = frame_idx;

	}



	else //frame table�� �������� �ʴ´ٸ�
	{
		int check_full_frame = 0; //frame�� �ڸ��� ������ 0, ������ 1

		for (int counter = 0; counter < 256; counter++) //frame�� ����������
		{
			if (frame_table[counter][2] == -1)
			{
				check_full_frame = 0;
				break;
			}
			else
			{
				check_full_frame = 1;
			}
		}


		if (check_full_frame == 0)
		{


			for (int count = 0; count < 256; count++)
			{
				if (frame_table[count][2] == -1)
				{

					frame_table[count][1] = 1;
					frame_table[count][2] = page_number;


					for (int i = 0; i < 256; i++) //count ����
					{
						if (frame_table[i][1] == 1)
						{
							frame_table[i][3]++;
						}
					}
					frame_table[count][3] = 0;
					frame_idx = frame_table[count][0];
					frame_number_1 = frame_idx;
					break;
				}
			}

		}

		else
		{
			int max_idx = 0;
			int max = -2;

			for (int idx = 0; idx < 256; idx++)
			{
				if (frame_table[idx][3] > max)
				{
					max = frame_table[idx][3];
					max_idx = idx;
				}
			}

			frame_table[max_idx][1] = 1;
			frame_table[max_idx][2] = page_number;

			for (int i = 0; i < 256; i++) //count ����
			{
				if (frame_table[i][1] == 1)
				{
					frame_table[i][3]++;
				}
			}
			frame_table[max_idx][3] = 0;
			frame_idx = frame_table[max_idx][0];
			frame_number_1 = frame_idx;

		}

	}

}

int main()
{
	string filepath = "C:/Users/oys53/Desktop/INHA/�б�/3�г�/1�б�/���۷����� �ý���/����2/address.txt"; //file path�� logical address�� �������ش�.
	int logical_arr[1000][2] = { -1 }; //address.txt�� �ִ� logical address�� page_number, offset���� ������. logical_arr[i][0]: page number, logical_arr[i][1]: offset
	int tlb_table[32][3] = { -1 }; // page#, frame#, lru counter# �� �����ϴ� 32 ũ���� tlb table
	int frame_table[256][4] = { -1 };
	unsigned int tlb_A_table[32] = { 0 };

	for (int i = 0; i < 256; i++) //frame table�� �̸� frame_number �Ҵ�, flag 0 �ʱ�ȭ, count 0 �ʱ�ȭ (#frame, #flag, #page, #counter)
	{
		frame_table[i][0] = i;
		frame_table[i][1] = 0;
		frame_table[i][2] = -1;
		frame_table[i][3] = 0;
	}

	create_reference_string(filepath, logical_arr); //address.txt�� �����ϴ� logical address�� arr�� �Ҵ�



	for (int i = 0; i < 1000; i++)
	{
		tlb(logical_arr[i][0], tlb_table, logical_arr[i][1], frame_table);




	}


	allocation_TLB_LRU(tlb_table);
	allocation_frame(frame_table);
	cout << "LRU TLB hit is: " <<TLB_hit << endl;

	//LRUA ����
	for (int i = 0; i < 256; i++) //frame table�� �̸� frame_number �Ҵ�, flag 0 �ʱ�ȭ, count 0 �ʱ�ȭ (#frame, #flag, #page, #counter)
	{
		frame_table[i][0] = i;
		frame_table[i][1] = 0;
		frame_table[i][2] = -1;
		frame_table[i][3] = 0;
	}

	


	tlb_table[32][3] = { -1 }; //TLB table �ʱ�ȭ

	for (int i = 0; i < 1000; i++)
	{
		tlb_app(logical_arr[i][0], tlb_table, logical_arr[i][1], frame_table, tlb_A_table);
	}

	frame_all++;

	allocation_TLB_A_LRU(tlb_table);
	allocation_frame(frame_table);

	cout << "LRUA TLB hit is: " << TLB_A_hit << endl;

	return 0;
}