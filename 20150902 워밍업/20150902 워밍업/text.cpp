#include<iostream>
#include <cmath>
using namespace std;
#define SIZE 3

void add(int vector1[SIZE], int vector2[SIZE]); //���� ��
int main()
{
	int vector1[SIZE];
	int vector2[SIZE];
	int vectorplus1;
	int vectorplus2;
	int vectorplus3;
	int vectormi1;
	int vectormi2;
	int vectormi3;
	char ch;
	cout << "input vector1�� 1��° �� �Է� "; cin >> vector1[0];
	cout << "input vector1�� 2��° �� �Է� "; cin >> vector1[1];
	cout << "input vector1�� 3��° �� �Է� "; cin >> vector1[2];
	cout << "input vector2�� 1��° �� �Է� "; cin >> vector2[0];
	cout << "input vector2�� 2��° �� �Է� "; cin >> vector2[1];
	cout << "input vector2�� 3��° �� �Է� "; cin >> vector2[2];
	while (1)
	{
		cout << "+: �� ������ ��" << endl << "-: �� ������ ��" << endl
			<< "d: �� ������ ������ �� ������ ���հ�(�ڻ��� ������ ���)" << endl
			<< "c �� ������ ����" << endl << "l: �� ������ ������ ũ��" << endl;



		cout << "vector1 : <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << endl;
		cout << "vector2 : <" << vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">" << endl;
		cout << "���� : "; cin >> ch;
		if (ch == '+')
		{
			vectorplus1 = vector1[0] + vector2[0];
			vectorplus2 = vector1[1] + vector2[1];
			vectorplus3 = vector1[2] + vector2[2];
			cout << "+: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " + " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << vectorplus1 << ", " << vectorplus2 << ", " << vectorplus3 << "> " << endl;
		}
		else if (ch == '-')
		{
			vectormi1 = vector1[0] - vector2[0];
			vectormi2 = vector1[1] - vector2[1];
			vectormi3 = vector1[2] - vector2[2];
			cout << "-: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " - " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << vectormi1 << ", " << vectormi2 << ", " << vectormi3 << "> " << endl;
		}
		else if (ch == 'd')
		{
			int inner = 0;
			double Root1;
			double Root2;
			double a = 0;
			double b = 0;
			double cosain;
			for (int i = 0; i < SIZE; ++i)
			{
				inner = inner + vector1[i] * vector2[i];
			}
			cout << "����: " << inner << ", ";

			for (int i = 0; i < SIZE; ++i)
			{
				a = a + vector1[i];
				b = b + vector2[i];
			}
			Root1 = sqrt(a);
			Root2 = sqrt(b);

			cosain = cos(inner / Root1*Root2);

			cout << "cos =  " << cosain << endl;

		}
		else if (ch == 'c')
		{
			int temp1;
			int temp2;
			int temp3;
			temp1 = vector1[1] * vector2[2] - vector1[2] * vector2[1];
			temp2 = -(vector1[0] * vector2[2] - vector1[2] * vector2[0]);
			temp3 = vector1[0] * vector2[1] - vector1[1] * vector2[0];

			cout << "c: <" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " x " << "<"
				<< vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "<" << temp1 << ", " << temp2 << ", " << temp3 << "> " << endl;

		}
		else if (ch == 'l')
		{
			double root1;
			double root2;

			root1 = sqrt(vector1[0] * vector1[0] + vector1[1] * vector1[1] + vector1[2] * vector1[2]);
			root2 = sqrt(vector2[0] * vector2[0] + vector2[1] * vector2[1] + vector2[2] * vector2[2]);

			cout << "l: root<" << vector1[0] << ", " << vector1[1] << ", " << vector1[2] << ">" << " = " << "root"
				<< "<" << root1 << ">" << "root<" << vector2[0] << ", " << vector2[1] << ", " << vector2[2] << ">"
				<< " = " << "root" << "<" << root2 << "> " << endl;

		}

	}
}

