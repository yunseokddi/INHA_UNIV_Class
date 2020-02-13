#include <iostream>
#include <fstream>
#include <string>

//Mix column 과정 연산자
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x4d))
#define Multiply(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * xtime(x)) ^                       \
      ((y>>2 & 1) * xtime(xtime(x))) ^                \
      ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
      ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

using namespace std;

//---------------------------------------------------------------global variable------------------------------------------------------------------------

int AES_round = 0; //round count (각 라운드 관리 counter)
int round_key[11][4][4] = { -1 }; //해당 round에 매핑되는 key

//S-Box 선언후 시작
int s_box[16][16] = { {21,10,59,33,2,199,15,188,63,114,221,138,24,153,193,91},
						 {161,47,166,79,208,1,218,80,50,38,83,9,127,96,147,58},
						 {238,206,169,187,204,194,56,248,247,205,190,251,242,32,22,34},
						 {134,145,45,3,151,35,186,117,129,23,175,68,86,4,130,25},
						 {232,17,89,5,234,214,227,229,88,196,254,213,131,27,66,159},
						 {100,136,216,105,192,217,195,253,71,53,143,252,148,155,142,7},
						 {125,84,87,163,168,78,191,113,245,177,14,210,99,55,132,167},
						 {95,198,20,202,72,16,189,6,180,231,157,162,222,176,178,172},
						 {74,67,182,215,146,244,29,118,75,49,85,133,207,135,109,237},
						 {18,112,92,154,224,158,212,120,94,37,179,122,31,51,241,233},
						 {12,137,219,42,243,70,43,62,255,8,115,110,126,220,97,226},
						 {60,123,164,200,249,141,225,11,116,13,82,183,121,150,28,57},
						 {128,104,181,40,52,36,239,44,106,69,184,139,64,223,39,171},
						 {101,173,230,235,152,30,246,209,46,98,165,90,124,170,76,61},
						 {48,228,93,119,149,211,250,144,26,236,54,203,65,140,156,73},
						 {197,185,108,160,240,0,111,107,81,77,102,19,103,41,201,174} };

//Inverse Mix column을 위한 변환 arr
string dec2hex[16] = { "0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F" };

//rc 선언
int rc[4][10] = { {1,2,4,8,16,32,64,128,77,154},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0},
					  {0,0,0,0,0,0,0,0,0,0}
				};


//--------------------------------------------------------------------------function---------------------------------------------------

string convert2hex(int num)
{
	for (int i = 0; i < 16; i++)
	{
		if (i == num)
		{

			return dec2hex[i];
		}
	}
}



void MC(int* plain)
{
	int plain_column[4][4] = { -1 };
	int num1 = 0;
	int num2 = 0;
	uint8_t i;
	uint8_t Tmp, Tm, t;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			plain_column[i][j] = plain[num1];
			num1++;
		}
	}


	for (i = 0; i < 4; ++i)
	{
		t = plain_column[i][0];
		Tmp = plain_column[i][0] ^ plain_column[i][1] ^ plain_column[i][2] ^ plain_column[i][3];
		Tm = plain_column[i][0] ^ plain_column[i][1]; Tm = xtime(Tm);  plain_column[i][0] ^= Tm ^ Tmp;
		Tm = plain_column[i][1] ^ plain_column[i][2]; Tm = xtime(Tm); plain_column[i][1] ^= Tm ^ Tmp;
		Tm = plain_column[i][2] ^ plain_column[i][3]; Tm = xtime(Tm); plain_column[i][2] ^= Tm ^ Tmp;
		Tm = plain_column[i][3] ^ t;   Tm = xtime(Tm); plain_column[i][3] ^= Tm ^ Tmp;
	}


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				plain[num2] = plain_column[i][j];
				num2++;
			}
		}

		cout << "MC: ";
		
		for (int i = 0; i < 16; i++)
		{
			cout << plain[i] << " ";
		}

		cout << endl;

}

void inverse_MC(int* plain)
{
	int plain_column[4][4] = { -1 };
	int num1 = 0;
	int num2 = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			plain_column[i][j] = plain[num1];
			num1++;
		}
	}

	int i;
	uint8_t a, b, c, d;
	for (i = 0; i < 4; ++i)
	{
		a = plain_column[i][0];
		b = plain_column[i][1];
		c = plain_column[i][2];
		d = plain_column[i][3];

		plain_column[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);

		plain_column[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);

		plain_column[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
	
		plain_column[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	
	}
	
	


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			plain[num2] = plain_column[i][j]%256;
			num2++;
		}
	}


	cout << "MC: ";

	for (int i = 0; i < 16; i++)
	{
		cout << plain[i] << " ";
	}

	cout << endl;

}

void AR(int* plain, int* key)
{
	for (int i = 0; i < 16; i++)
	{
		plain[i] = plain[i] ^ key[i];
	}

	cout << "AR: ";

	for (int j = 0; j < 16; j++)
	{
		cout << plain[j] << " ";
	}
	cout << endl;
}


void SB(int* plain) //key값을 s_box에 치환
{

	int key_column; //열, 가로
	int key_row; //행, 세로


	cout << "SB: ";

	for (int i = 0; i < 16; i++)
	{

		key_column = plain[i] / 16;
		key_row = plain[i] % 16;

		plain[i] = s_box[key_column][key_row];

		cout << plain[i] << " ";

	}
	cout << endl;


}



void Inverse_SB(int* plain)
{

	int key_column = 0; //열, 가로
	int key_row = 0; //행, 세로
	string str_column;
	string str_row;
	string original;
	const char* ch_original;
	int sb_val = 0;


	cout << "SB: ";

	int count = 0;
	int count1 = 0;

	for (int i = 0; i < 16; i++)
	{
		count1++;
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				if (plain[i] == s_box[j][k])
				{
					str_column = convert2hex(j);
					str_row = convert2hex(k);
					
					original = str_column + str_row;

					ch_original = original.c_str();

					plain[i] = (int)strtol(ch_original, NULL, 16);

					cout << plain[i] << " ";
					
					
						goto here;
				}
			}

			

		}

	here:
		;

	}
	
	cout << endl;


}

void SR(int* plain)
{
	int row1[4] = { -1 };
	int row2[4] = { -1 };
	int row3[4] = { -1 };
	int row4[4] = { -1 };

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	for (int i = 0; i < 16; i++) //연산 편의를 위해 각 row로 나누기
	{
		if (i % 4 == 0)
		{
			row1[a] = plain[i];
			a++;
		}

		else if (i % 4 == 1)
		{
			row2[b] = plain[i];
			b++;
		}
		else if (i % 4 == 2)
		{
			row3[c] = plain[i];
			c++;

		}

		else if (i % 4 == 3)
		{
			row4[d] = plain[i];
			d++;
		}
	}



	int dmp = row2[0];

	for (int i = 0; i < 3; i++) //row2 1번 left shift
	{
		row2[i] = row2[i + 1];
	}
	row2[3] = dmp;


	for (int i = 0; i < 2; i++) //row3 2번 left shift
	{
		dmp = row3[0];

		for (int j = 0; j < 3; j++)
		{
			row3[j] = row3[j + 1];
		}

		row3[3] = dmp;
	}

	for (int i = 0; i < 3; i++) //row4 3번 left shift
	{
		dmp = row4[0];

		for (int j = 0; j < 3; j++)
		{
			row4[j] = row4[j + 1];
		}

		row4[3] = dmp;
	}
	
	for (int i = 0; i < 4; i++)
	{
		plain[i * 4] = row1[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4)+1] = row2[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4) + 2] = row3[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4) + 3]= row4[i];
	}

	cout << "SR: ";

	for (int i = 0; i < 16; i++)
	{
		cout << plain[i] << " ";
	}
	cout << endl;


}

void reverse(int arr[], int start, int end) {
	int temp;
	end = end - 1;
	while (start < end) {
		temp = arr[start];
		arr[start] = arr[end];
		arr[end] = temp;
		start++;
		end--;
	}
}

void shiftRight(int arr[], int d, int n) {
	reverse(arr, 0, n - d);
	reverse(arr, n - d, n);
	reverse(arr, 0, n);
}

void Inverse_SR(int* plain)
{
	int row1[4] = { -1 };
	int row2[4] = { -1 };
	int row3[4] = { -1 };
	int row4[4] = { -1 };

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;

	for (int i = 0; i < 16; i++) //연산 편의를 위해 각 row로 나누기
	{
		if (i % 4 == 0)
		{
			row1[a] = plain[i];
			a++;
		}

		else if (i % 4 == 1)
		{
			row2[b] = plain[i];
			b++;
		}
		else if (i % 4 == 2)
		{
			row3[c] = plain[i];
			c++;

		}

		else if (i % 4 == 3)
		{
			row4[d] = plain[i];
			d++;
		}
	}

	shiftRight(row2, 1, 4);
	shiftRight(row3, 2, 4);
	shiftRight(row4, 3, 4);

	


	for (int i = 0; i < 4; i++)
	{
		plain[i * 4] = row1[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4) + 1] = row2[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4) + 2] = row3[i];
	}

	for (int i = 0; i < 4; i++)
	{
		plain[(i * 4) + 3] = row4[i];
	}

	cout << "SR: ";

	for (int i = 0; i < 16; i++)
	{
		cout << plain[i] << " ";
	}
	cout << endl;


}




void key_substitue(int* key_arr) //key값을 s_box에 치환
{

	int dmp0 = key_arr[0];
	int dmp1 = key_arr[1];
	int dmp2 = key_arr[2];
	int dmp3 = key_arr[3];

	key_arr[0] = dmp1; //1행->0행
	
	key_arr[1] = dmp2; //2행->1행

	key_arr[2] = dmp3; //3행->2행

	key_arr[3] = dmp0; //0행->3행

	int key_column; //열, 가로
	int key_row; //행, 세로



	for (int i = 0; i < 4; i++)
	{

		key_column = key_arr[i] / 16;
		key_row = key_arr[i] % 16;

		key_arr[i] = s_box[key_column][key_row];

	}


}


void key_expansion(int key[][4]) //key expansion
{


	int key_column0[4] = { -1 };
	int key_column1[4] = { -1 };
	int key_column2[4] = { -1 };
	int key_column3[4] = { -1 };

	int past_column0[4] = { -1 };
	int past_column1[4] = { -1 };
	int past_column2[4] = { -1 };
	int past_column3[4] = { -1 };
	int past_past_column3[4] = { -1 };
	
	for (int i = 0; i < 4; i++)
	{
		key_column0[i] = key[0][i];
	
	}

	for (int i = 0; i < 4; i++)
	{
		key_column1[i] = key[1][i]; 

	}

	for (int i = 0; i < 4; i++)
	{
		key_column2[i] = key[2][i];

	}

	for (int i = 0; i < 4; i++)
	{
		key_column3[i] = key[3][i];
		past_past_column3[i] = key[3][i];
	}


	key_substitue(key_column3);	//s_box 치환 완료

	key_column3[0] = key_column3[0] ^  rc[0][AES_round]; //RC, 2행 XOR 연산


	AES_round++;




	for (int i = 0; i < 4; i++)
	{
		past_column0[i] = key_column0[i];
	
	}

	for (int i = 0; i < 4; i++)
	{
		past_column1[i] = key_column1[i];
	
	}

	for (int i = 0; i < 4; i++)
	{
		past_column2[i] = key_column2[i];
	
	}

	for (int i = 0; i < 4; i++)
	{
		past_column3[i] = key_column3[i];

	}
		
	//xor 연산 시작


	for (int i = 0; i < 4; i++)
	{
		key_column0[i] = past_column0[i] ^ key_column3[i];
	
	}

	for (int i = 0; i < 4; i++)
	{
		key_column1[i] = key_column0[i]^past_column1[i] ;
	
	}

	for (int i = 0; i < 4; i++)
	{
		key_column2[i] = key_column1[i]^ past_column2[i];
	
	}


	for (int i = 0; i < 4; i++)
	{
		key_column3[i] = key_column2[i]^ past_past_column3[i];
	
	}


	//다음 round key 할당
	for (int i = 0; i < 4; i++)
	{
		key[0][i] = key_column0[i];

	}

	for (int i = 0; i < 4; i++)
	{
	key[1][i]= key_column1[i];

	}

	for (int i = 0; i < 4; i++)
	{
		 key[2][i]= key_column2[i];

	}

	for (int i = 0; i < 4; i++)
	{
		key[3][i] = key_column3[i];
	}

	
	
}

//--------------------------------------------------------------------------------------main-------------------------------------------------------------------------
int main()
{
	int plain_text[16] = { -1 }; //binary 파일에 저장된 plain_text를 저장하는 arr
	int key[16] = { -1 };
	int plain_text_dec_arr[4][4] = { -1 }; //
	int key_dec_arr[4][4] = { -1 };
	int count = 0;
	int real_round_key[11][16] = { -1 }; //실제 key


	string plain_file = "C:/Users/YunSeok/Desktop/INHA/학교/3학년/2학기/컴퓨터보안/과제2/homework2/homework2/plain.bin"; //실행 할때 경로 바꿔주세요

	ifstream plain_input(plain_file, ios::in | ios::binary);

	plain_input.read((char*)plain_text, sizeof(plain_text)); //binary 파일 불러오기


	plain_input.close();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) //plain text를 plain_text_dec_arr에 저장
		{
			plain_text_dec_arr[i][j] = plain_text[count];
			count++;
		}
	}

	count = 0;


	//save key into array
	string key_file = "C:/Users/YunSeok/Desktop/INHA/학교/3학년/2학기/컴퓨터보안/과제2/homework2/homework2/key.bin";  //실행 할때 경로 바꿔주세요


	ifstream key_input(key_file, ios::in | ios::binary);

	key_input.read((char*)key, sizeof(key));


	key_input.close();

	cout << hex;

	cout << "RC: "; //cout RC	

	for (int i = 0; i < 10; i++)
	{
		cout << rc[0][i] << " ";
	}

	cout << endl;


	cout << "PLAIN: "; //cout PLAIN

	for (int i = 0; i < 16; i++)
	{
		cout << plain_text[i] << " ";
	}
	cout << endl;


	cout << "KEY: "; //cout key

	for (int i = 0; i < 16; i++)
	{
		cout << key[i] << " ";
	}

	cout << endl;
	



	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			key_dec_arr[i][j] = key[count];
			
			count++;
		}
	}
	

	//Key expansion start

	cout << endl;
	cout << "<-----ENCRYPTION----->" << endl;
	cout << endl;
	cout << "KEY EXPANSION" << endl;

	for (int i = 0; i < 11; i++)
	{
		cout << dec;
		cout << "Round " << AES_round << " : ";
		cout << hex;
		for (int j = 0; j < 4; j++) //round key 할당
		{
			for (int k = 0; k < 4; k++)
			{
				round_key[i][j][k] = key_dec_arr[j][k]; //round key arr에서 i는 round
				cout << round_key[i][j][k] << " ";
			}
		}
		cout << endl;
		key_expansion(key_dec_arr);

	}

	


	int num = 0;

	for (int i = 0; i < 11; i++)		//key를 2차원 배열로 변환
	{
		for (int j = 0; j < 4; j++)
		{
			if (num == 16)
			{
				num = 0;
			}

			for (int k = 0; k < 4; k++)
			{
				real_round_key[i][num] = round_key[i][j][k];
				num++;
			}
			
		}
	}

	cout << endl;

	//Key expansion finish

	//ENCRYPTION start!
	for (int i = 0; i < 11; i++)
	{
		cout << dec;
		cout << "ROUND " << i << endl;
		cout << hex;
		if (i == 0)
		{
			
				AR(plain_text, real_round_key[i]);
			


		}

		else if (i == 10)
		{
			SB(plain_text);
			SR(plain_text);
			AR(plain_text, real_round_key[i]);
		}

		else
		{
			SB(plain_text);
			SR(plain_text);
			MC(plain_text);
			AR(plain_text, real_round_key[i]);

			
		}

		cout << endl;
	}

	cout << endl;

	cout << "CIPHER: ";

	for (int i = 0; i < 16; i++)
	{
		cout << plain_text[i] << " ";
	}
	cout << endl;

	ofstream output("cipher.bin", ios::out | ios::binary);

	output.write((char*)plain_text, sizeof(plain_text) - 1);
	
	output.close();



	//ENCRYPTION finish!
	//DECRYPTION start

	cout << endl;
	cout << "<----- DECRYPTION ----->" << endl << endl;
	int round = 0;
	for (int i = 10; i > -1; i--)
	{
		

		cout << dec;
		cout << "ROUND " << round << endl;
		cout << hex;
		if (i == 10)
		{
			AR(plain_text, real_round_key[i]);
			round++;
		}

		else if (i == 0)
		{
			Inverse_SR(plain_text);
			Inverse_SB(plain_text);
			AR(plain_text, real_round_key[i]);
			round++;

			cout << endl;
			cout << "DECRYPTED: ";

			for (int j = 0; j < 16; j++)
			{
				cout << plain_text[j] << " ";
			}
			cout << endl;

		}

		else
		{
			Inverse_SR(plain_text);
			Inverse_SB(plain_text);
			AR(plain_text, real_round_key[i]);
			inverse_MC(plain_text);
			round++;
		}

		cout << endl;
	}

	ofstream output2("decrypt.bin", ios::out | ios::binary);

	output2.write((char*)plain_text, sizeof(plain_text) - 1);

	output2.close();



	return 0;

}

