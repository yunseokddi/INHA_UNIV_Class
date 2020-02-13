#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <cmath>
#include <bitset>
#include <Windows.h>

using namespace std;

int inverse(int a, int m) // a mod m 역원 구하기
{
	int x = 0;

	for (int i = 1; i < m; i++) {
		if ((a * i) % m == 1) {
			x = i;
		}

		
	}

	return x;
}


int Euclid(int e, int phi) //확장된 유클리드 호제법
{

	int q = 0; //몫 1번째인자와 두번째 인자를 나눈 몫
	int a1 = 1;
	int a2 = 0;
	int a3 = e; //1번째 인자
	int b1 = 0;
	int b2 = 1;
	int b3 = phi; //2번째 인자
	int t1 = 0; //a1 - (q * b1)
	int t2 = 0; //a2 - (q * b2)
	int t3 = 0; //a3 - (q * b3)


	while (b3 > 0 || b3 == 1)
	{
		q = a3 / b3;
		t1 = a1 - (q * b1);
		t2 = a2 - (q * b2);
		t3 = a3 - (q * b3);
		a1 = b1;
		a2 = b2;
		a3 = b3;
		b1 = t1;
		b2 = t2;
		b3 = t3;

		if (b3 == 1)
		{
			return b3;
		}
	}

	return b3;
}

int return_d(int e, int phi) //확장된 유클리드 호제법 (d값 구하기 전용)
{
	srand((unsigned int)time(0));

	int q = 0; //변수의 대한 주석은 위 Euclid함수와 비슷하기 때문에 생략한다.
	int a1 = 1;
	int a2 = 0;
	int a3 = e;
	int output = a3;
	int b1 = 0;
	int b2 = 1;
	int b3 = phi;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;


	while (true)
	{


		while (b3 > 0)
		{
			q = a3 / b3;
			t1 = a1 - (q * b1);
			t2 = a2 - (q * b2);
			t3 = a3 - (q * b3);
			a1 = b1;
			a2 = b2;
			a3 = b3;
			b1 = t1;
			b2 = t2;
			b3 = t3;
			if (b3 < 2)
			{	
		
				if(b1 > 0) //여기서 return 되는 값은 무조건 양수여야 한다.
				{	
					return b1;
				}

				else
				{
					
					return b1+phi;
				}


			}
		}
	}
}


int exp_mod(int a, int n, int z) //a^n mod z 계산
{
	int result = 1;
	long long x = 0;

	x = a % z;

	while (n > 0)
	{
		if ((n % 2) == 1) //해당 비트가 0인지 1인지 검사
		{
		
			result = (result * x) % z;

		}
		x = (x * x) % z;
		n = n / 2;

	}

	return result;
}

int square_multi(int M, int e, int n)
{
	int x = 1;
	int power = M % n;
	std::bitset<32> bs(e);
	int flag = 0;
	int arr[32] = { 0 };
	
	for (int count = 31; count > 0; count--) //1이 시작되는 왼쪽 부분 찾기
	{
		if (bs[count])
		{
			flag = count;
			break;
		}
	}
	
	for (int count = 0; count < flag+1; count++)
	{
		arr[count] = bs[count];
	}
	
	for (int i = 0; i < flag + 1; i++)
	{
		if (arr[i] == 1)
		{
			x = (x * power) % n;
		}
		power = (power * power) % n;
	}

	return x;

}

int miller_rabin(int p)
{
	int s = 0;
	int d = 0;
	int p2 = 0; // p-1 값
	int a[20] = { 0 }; //p보다 작은 임의의 양수
	int flag = 1; //소수인지 아닌지 확인하는 flag 0일때 소수
	int random = 0;


	p2 = p - 1;

	while (true)
	{
		if ((p2 % 2) == 0) //2로 소인수 분해
		{
			s++;
			p2 = p2 / 2;
		}

		else //2로 안나눠지면 그 값이 d가 된다.
		{
			d = p2;
			break;
		}

	}
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 20; i++)
	{
		//Sleep(1000);
		a[i] = 1 + rand() % p - 1; //총 20개의 p보다 작은 난수 생성
	}

	for (int count = 0; count < 20; count++)
	{

		if ((count == 0 && square_multi(a[count], d, p) == p+1) || (count == 0 && square_multi(a[count], d, p) == 1))
		{
			flag = 0;
			break;
		}


		for (int c = 0; c < s - 1; c++)
		{
			if (square_multi(a[count], d * pow(2, c), p) == p - 1 || square_multi(a[count], d * pow(2, c), p) == -1)
			{
		
				flag = 0;
				
				goto here;
			}
		}
	}

	here:

	if (flag == 0)
	{
		return p;
	}

	else
	{
		return 1;
	}



}

int real_china(int c, int d, int p, int q) //중국인의 나머지 정리
{
	int dp = exp_mod(d, 1, p - 1); //d mod p-1
	int dq = exp_mod(d, 1, q- 1); // d mod q-1
	int qinv = inverse(53, 61); // q-1 mod p
	int m1 = exp_mod(c, dp, p); // c^dp mod p
	int m2 = exp_mod(c, dq, q); // c^dq mod q
	int h = ((qinv * (m1 - m2))) % p; // (qinv *(m1 - m2)) mod p
	int m = m2 + (h * q); // m2+ (h*q)

	return m;
	
}

int main() //16384 <= p, q =< 32767
{
	int p = 0;
	int q = 0;
	int n = 0;
	int phi = 0;
	int e = 0;
	int input = 0;
	int d = 0;
	int cipher = 0;
	int decrypt = 0;

	
	while (true) //p가 홀수인지 짝수인지 판별
	{
		Sleep(1000);
		srand((unsigned int)time(NULL));
		
		p = 16384 + rand() % 16383;
		
		if(p%2 == 0)  //짝수일때 다시 random으로 범위안 무작위 수로 세팅
		{
			continue;
		}

		p = miller_rabin(p);

		if (p != 1)
		{
			break;
		}
	}
		
	while (true) //p가 홀수인지 짝수인지 판별
	{
		Sleep(1000);
		srand((unsigned int)time(NULL));

		q = 16384 + rand() % 16383;

		if (q % 2 == 0)  //짝수일때 다시 random으로 범위안 무작위 수로 세팅
		{
			continue;
		}

		q = miller_rabin(q);

		if (q != 1)
		{
			break;
		}
	}
	
	n = p * q; // n값 구하기
	phi = (p - 1) * (q - 1); //phi 구하기


	int tmp = 0;

	while(true)
	{
		srand((unsigned int)time(NULL));

		e = 1 + rand() % phi - 1; //e값 난수 생성

		tmp = Euclid(e, phi); //확장된 유클리드에서 b3값이 1이면 그 수들은 서로소이다.

		if (tmp == 1) //서로수일때 루프탈출, 아니면 다른 e값으로 하기
		{
			break;
		}
	}


	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "N = " << n << endl;
	cout << "phi = " << phi << endl;
	cout << "e = " << e << endl;

	d = return_d(e, phi);
	cout << "d = " << d << endl;
	cout << "Message Input : ";
	cin >> input;
	cout << "Message = " << input << endl;

	
	cout << "**Encryption" << endl;
	cipher = exp_mod(input ,e, n);
	cout << "cipher = " << cipher << endl;

	cout << "**Decryption" << endl;
	decrypt = real_china(cipher, d, p, q);
	cout << "decrypted cipher : " << decrypt << endl;

	
	return 0;
}