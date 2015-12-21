#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

double isA[3];
double isB[3];
double isC[3];
double isD[3];

void isAutoRnad();
void isPutMake();
void isShow();

void isVector3();
void isVector4();

int main(){
	int isNum;
	isAutoRnad();
	while (1){
		printf("0. �ڵ� ������ ����\n");
		printf("1. ���� ������ ����\n");
		printf("2. �Էµ� �� Ȯ���ϱ�.\n");
		printf("3. 4���� ���������� �����Ǵ� 1���� ���� ������.\n");
		printf("4. 4���� ���������� �����Ǵ� 4���� ���� ��ǥ�� ����.\n");
		printf("5. 4���� �������� ��ǥ��.\n");
		printf("Input Num : ");

		scanf_s("%d", &isNum);

		if (isNum == 0){
			isAutoRnad();
		}
		else if (isNum == 1){
			isPutMake();
		}
		else if (isNum == 2){
			system("cls");
			isShow();
		}
		else if (isNum == 3){

		}
		else if (isNum == 4){
			 isVector4();
		}
		else if (isNum == 5){
			system("cls");
			isShow();
		}


	}

}


void isVector3(){
	// sqrt(((x2 - x1)*(x2 - x1) + (y2-y1)*(y2-y1) +  (z2-z1)*(z2-z1)));

}

void isVector4(){
	system("cls");
	double isResult = 0;
	printf("4. 4���� ���������� �����Ǵ� 4���� ���� ��ǥ�� ����.\n");
	printf("(");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isA[i]);
	}
	printf(") - (");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isB[i]);
	}
	isResult = sqrt(((isB[1] - isA[1])*(isB[1] - isA[1]) + (isB[2] - isA[2])*(isB[2] - isA[2]) + (isB[3] - isA[3])*(isB[3] - isA[3])));
	printf(") = %f\n\n", isResult);

	

}

void isShow(){
	printf("2. �Էµ� �� Ȯ���ϱ�.\n\n");
	printf("A ������ : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isA[i]);
	}
	printf("\n\nB ������ : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isB[i]);
	}

	printf("\n\nC ������ : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isC[i]);
	}

	printf("\n\nD ������ : \n");
	for (int i = 0; i < 3; ++i){
		printf("%f ", isD[i]);
	}
	printf("\n\n");
}

void isAutoRnad(){
	system("cls");
	printf("Auto init..!\n\n");
	for (int i = 0; i < 3; ++i){
		srand((unsigned int)time(NULL) + i);
		isA[i] = rand() % 2 + 1;
		isB[i] = rand() % 3 + 1;
		isC[i] = rand() % 4 + 1;
		isD[i] = rand() % 5 + 1;
	}

}

void isPutMake(){
	system("cls");
	int isNum;

	for (int i = 0; i < 3; ++i){
		printf("������ A�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isA[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("������ B�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isB[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("������ C�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isC[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("������ D�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isD[i] = isNum;
	}

}