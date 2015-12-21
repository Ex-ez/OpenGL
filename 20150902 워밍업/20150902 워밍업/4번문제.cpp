#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>

int isVectorA[3];
int isVectorB[3];
int isVectorR[3];

void isAutoRnad();
void isPutMake();
void isPluse();
void isMinuse();
void isVector4();
void isVector5();
void isVector6();
void isShow(int);

int main(){
	int isNum;
	isAutoRnad();
	while (1){
		printf("0. �ڵ� ���� ����\n");
		printf("1. ���� ���� ����\n");
		printf("2. �� ������ ��(+)\n");
		printf("3. �� ������ ��(-)\n");
		printf("4. �� ������ ������ �ι����� ���հ�\n");
		printf("5. �� ������ ����\n");
		printf("6. �� ������ ������ ũ��\n");
		printf("7. �Էµ� ���� Ȯ���ϱ�\n");
		printf("Input Num : ");

		scanf_s("%d", &isNum);
		if (isNum == 0){
			isAutoRnad();
		}
		else if (isNum == 1){
			isPutMake();
		}
		else if (isNum == 2){
			isPluse();
		}
		else if (isNum == 3){
			isMinuse();
		}
		else if (isNum == 4){
			isVector4();
		}
		else if (isNum == 5){
			isVector5();
		}
		else if (isNum == 6){
			isVector6();
		}
		else 	if (isNum == 7){
			system("cls");
			isShow(1);
			isShow(2);
			isShow(3);
		}


	}
}

void isVector5(){
	system("cls");
	printf("5. �� ������ ����\n");

	printf("(%d, %d, %d) x (%d, %d, %d) = ", isVectorA[0], isVectorA[1], isVectorA[2], isVectorB[0], isVectorB[1], isVectorB[2]);
	int isA, isB, isC;
	isA = (isVectorA[1] * isVectorB[2]) - (isVectorA[2] * isVectorB[1]);
	isB = (isVectorA[2] * isVectorB[0]) - (isVectorA[0] * isVectorB[2]);
	isC = (isVectorA[0] * isVectorB[1]) - (isVectorA[1] * isVectorB[0]);

	printf("(%d, %d, %d)\n\n", isA, -isB, isC);

}

void isVector6(){
	system("cls");
	printf("6. �� ������ ������ ũ��\n");
	isShow(1);
	int isSumroot = 0;
	double isSumrootA = 0;

	for (int i = 0; i < 3; ++i){
		isSumroot = isSumroot + isVectorA[i];
	}
	isSumrootA = isSumroot;
	printf("root(%d, %d, %d) = root(%d) = %f\n", isVectorA[0], isVectorA[1], isVectorA[2], isSumroot, sqrt(isSumrootA));

	isSumroot = 0;
	isSumrootA = 0;
	printf("\n");
	isShow(2);
	for (int i = 0; i < 3; ++i){
		isSumroot = isSumroot + isVectorB[i];
	}
	isSumrootA = isSumroot;
	printf("root(%d, %d, %d) = root(%d) = %f\n", isVectorB[0], isVectorB[1], isVectorB[2], isSumroot, sqrt(isSumrootA));

	printf("\n");
}

void isVector4(){
	system("cls");
	printf("4. �� ������ ������ �ι����� ���հ�\n");

	int isOne = 0;
	double isAPlus = 0;
	double isBPlus = 0;
	double isRootA;
	double isRootB;
	double isResult;

	for (int i = 0; i < 3; ++i){
		isOne = isOne + isVectorA[i] * isVectorB[i];
	}

	printf("���� : %d\n", isOne);

	for (int i = 0; i < 3; ++i){
		isAPlus = isAPlus + isVectorA[i];
		isBPlus = isBPlus + isVectorB[i];
	}

	isRootA = sqrt(isAPlus);
	isRootB = sqrt(isBPlus);

	isResult = cos(isOne / isRootA*isRootB);

	printf("���հ� : %f\n", isResult);

	printf("\n");
}

void isPluse(){
	system("cls");
	printf("2. �� ������ ��(+)\n");
	for (int i = 0; i < 3; ++i){
		isVectorR[i] = isVectorA[i] + isVectorB[i];
	}
	isShow(3);
}

void isMinuse(){
	system("cls");
	printf("3. �� ������ ��(-)\n");
	for (int i = 0; i < 3; ++i){
		isVectorR[i] = isVectorA[i] - isVectorB[i];
	}
	isShow(3);
}

void isAutoRnad(){
	system("cls");
	printf("Auto init..!\n\n");
	for (int i = 0; i < 3; ++i){
		srand((unsigned int)time(NULL) + i);
		isVectorA[i] = rand() % 2 + 1;
		if (isVectorA[i] == 2)
			isVectorA[i] = 0;
	}

	for (int i = 0; i < 3; ++i){
		srand((unsigned int)time(NULL) + time(NULL) + i);
		isVectorB[i] = rand() % 2 + 1;
		if (isVectorB[i] == 2)
			isVectorB[i] = 0;
	}
}

void isPutMake(){
	system("cls");
	int isNum;

	for (int i = 0; i < 3; ++i){
		printf("���� A�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isVectorA[i] = isNum;
	}

	for (int i = 0; i < 3; ++i){
		printf("���� B�� %d��° �� �Է����ּ���..!\n", i);
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		isVectorB[i] = isNum;
	}

	printf("�Է� �Ϸ�..!\n\n");

}

void isShow(int isNum){
	if (isNum == 1){
		printf("A ���� : \n");
		printf("(%d, %d, %d)\n", isVectorA[0], isVectorA[1], isVectorA[2]);
	}
	else if (isNum == 2){
		printf("B ���� : \n");
		printf("(%d, %d, %d)\n", isVectorB[0], isVectorB[1], isVectorB[2]);
	}
	else if (isNum == 3){
		printf("R ���� : \n");
		printf("(%d, %d, %d)\n", isVectorR[0], isVectorR[1], isVectorR[2]);
	}
	printf("\n\n");
}