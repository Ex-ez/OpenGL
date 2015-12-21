#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int is3x3[3][3];
int is3x3Two[3][3];
int is3x3Result[3][3];
int is4x4[4][4];

int determinantResult = 0;

void input3x3();
void inputRand3x3();
void show3x3(int);
void pluse3x3();
void minus3x3();
void multiplication3x3();
void determinant3x3();
void is3x3To4x4();

int main(){
	int isNum;
	inputRand3x3();
	while (1){
		printf("0. �ڵ� ��� ����\n");
		printf("1. 3x3 ��� �Է��ϱ�\n");
		printf("2. ����� ����\n");
		printf("3. ����� ����\n");
		printf("4, ����� ����\n");
		printf("5. ��Ľ��� ��\n");
		printf("6. 3x3 ����� 4x4 ��ķ� ��ȯ\n");
		printf("7. 3x3 ��� Ȯ���ϱ�\n");
		printf("Input Num : ");
		scanf_s("%d", &isNum);
		if (isNum == 0){
			inputRand3x3();
		}
		else 	if (isNum == 1){
			input3x3();
		}
		else 	if (isNum == 2){
			multiplication3x3();
			show3x3(3);
		}
		else 	if (isNum == 3){
			pluse3x3();
			show3x3(3);
		}
		else 	if (isNum == 4){
			minus3x3();
			show3x3(3);
		}
		else 	if (isNum == 5){
			determinant3x3();
		}
		else 	if (isNum == 6){
			is3x3To4x4();
		}
		else if (isNum == 7){
			system("cls");
			show3x3(1);
			show3x3(2);
			show3x3(3);
			show3x3(4);
		}
		else{
			system("cls");
			printf("���� : �Է°� ����..!\n\n");
		}
	}
}



void is3x3To4x4(){
	system("cls");
	int isNum;

	printf("1. A ��Ľ� ��ȯ�ϱ�.\n");
	printf("2. B ��Ľ� ��ȯ�ϱ�.\n");
	printf("3. R ��Ľ� ��ȯ�ϱ�.\n");
	printf("Input Num : ");
	scanf_s("%d", &isNum);
	printf("\n");


	if (isNum == 1){
		printf("A�� 3x3 ���� 4x4�� ��ȯ : \n");
		show3x3(1);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}
	else if (isNum == 2){
		printf("B�� 3x3 ���� 4x4�� ��ȯ : \n");
		show3x3(2);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3Two[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}
	else if (isNum == 3){
		printf("R�� 3x3 ���� 4x4�� ��ȯ : \n");
		show3x3(3);
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				is4x4[i][j] = is3x3Result[i][j];
			}
		}
		is4x4[3][3] = 1;
		show3x3(4);
	}

}

void determinant3x3(){
	system("cls");
	int isNum;

	printf("1. A ��Ľ� ���ϱ�.\n");
	printf("2. B ��Ľ� ���ϱ�.\n");
	printf("3. R ��Ľ� ���ϱ�.\n");
	printf("Input Num : ");
	scanf_s("%d", &isNum);
	printf("\n");

	if (isNum == 1){
		printf("A��Ľ� : \n");
		show3x3(1);
		determinantResult = is3x3[0][0] * is3x3[1][1] * is3x3[2][2]
			+ is3x3[0][1] * is3x3[1][2] * is3x3[2][0]
			+ is3x3[0][2] * is3x3[1][0] * is3x3[2][1]
			- is3x3[0][0] * is3x3[1][2] * is3x3[2][1]
			- is3x3[0][1] * is3x3[1][0] * is3x3[2][2]
			- is3x3[0][2] * is3x3[1][1] * is3x3[2][0];
		printf("A��Ľ� : %d\n\n\n", determinantResult);
	}
	else if (isNum == 2){
		printf("B��Ľ� : \n");
		show3x3(2);
		determinantResult = is3x3Two[0][0] * is3x3Two[1][1] * is3x3Two[2][2]
			+ is3x3Two[0][1] * is3x3Two[1][2] * is3x3Two[2][0]
			+ is3x3Two[0][2] * is3x3Two[1][0] * is3x3Two[2][1]
			- is3x3Two[0][0] * is3x3Two[1][2] * is3x3Two[2][1]
			- is3x3Two[0][1] * is3x3Two[1][0] * is3x3Two[2][2]
			- is3x3Two[0][2] * is3x3Two[1][1] * is3x3Two[2][0];
		printf("A��Ľ� : %d\n\n\n", determinantResult);
	}
	else if (isNum == 3){
		printf("R��Ľ� : \n");
		show3x3(2);
		determinantResult = is3x3Result[0][0] * is3x3Result[1][1] * is3x3Result[2][2]
			+ is3x3Result[0][1] * is3x3Result[1][2] * is3x3Result[2][0]
			+ is3x3Result[0][2] * is3x3Result[1][0] * is3x3Result[2][1]
			- is3x3Result[0][0] * is3x3Result[1][2] * is3x3Result[2][1]
			- is3x3Result[0][1] * is3x3Result[1][0] * is3x3Result[2][2]
			- is3x3Result[0][2] * is3x3Result[1][1] * is3x3Result[2][0];
		printf("A��Ľ� : %d\n\n\n", determinantResult);
	}

	
}

void pluse3x3(){
	system("cls");
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Result[i][j] = is3x3[i][j] + is3x3Two[i][j];
			printf("%d + %d = %d\n", is3x3[i][j], is3x3Two[i][j], is3x3Result[i][j]);
		}
	}
}

void minus3x3(){
	system("cls");
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Result[i][j] = is3x3[i][j] - is3x3Two[i][j];
			printf("%d - %d = %d\n", is3x3[i][j], is3x3Two[i][j], is3x3Result[i][j]);
		}
	}
}

void multiplication3x3(){
	system("cls");

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			for (int h = 0; h < 3; h++){
				is3x3Result[i][j] += is3x3[i][h] * is3x3Two[h][j];
			}
		}
	}
}

void input3x3(){
	system("cls");
	printf("1. 3x3 ��� A �Է��ϱ�\n");
	printf("1��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[0][%d] �� : ", i);
		scanf_s("%d", &is3x3[0][i]);
	}
	printf("2��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[1][%d] �� : ", i);
		scanf_s("%d", &is3x3[1][i]);
	}

	printf("3��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[2][%d] �� : ", i);
		scanf_s("%d", &is3x3[2][i]);
	}

	printf("1. 3x3 ��� B �Է��ϱ�\n");
	printf("1��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[0][%d] �� : ", i);
		scanf_s("%d", &is3x3Two[0][i]);
	}
	printf("2��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[1][%d] �� : ", i);
		scanf_s("%d", &is3x3Two[1][i]);
	}

	printf("3��° �� �ڷḦ �Է����ּ��� : \n");
	for (int i = 0; i < 3; ++i){
		printf("[2][%d] �� : ", i);
		scanf_s("%d", &is3x3Two[2][i]);
	}

	printf("\n\n");
}

void inputRand3x3(){
	system("cls");
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3[i][j] = rand() % 9 + 1;
		}
	}

	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j){
			is3x3Two[i][j] = rand() % 9 + 1;
		}
	}
	printf("Auto init..!\n\n");
}

void show3x3(int isNum){
	if (isNum == 1){
		printf("3x3 ��� A Ȯ���ϱ�\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 2){
		printf("\n3x3 ��� B Ȯ���ϱ�\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3Two[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 3){
		printf("\n3x3 ��� R Ȯ���ϱ�\n\n");
		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				printf("%d ", is3x3Result[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
	else if (isNum == 4){
		printf("\n4x4 ��� Ȯ���ϱ�\n\n");
		for (int i = 0; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				printf("%d ", is4x4[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}