#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isDrawCircle(int, int, int);
void isTCircle(int, int, int);


void isInputData(int, int, int);
void isSpreadCircle();

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct  isClick{
	int isX = -300, isY = -300;
	bool isReady = false;
}isClick;

typedef struct  isCircle{
	int isX, isY;
	int isSX, isSY;
	bool isWrite = false;
}isCircle;

#define isLimitClick 10
#define isLimitOne 360

isClick isClickRect[isLimitClick];
int isClickNum = 0;
isCircle isTC[isLimitClick][isLimitOne];

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (int j = 0; j < isLimitClick; ++j){

		if (isClickRect[j].isX >= 0){		// -300 �⺻������ ������  0���� ������ ��������
			isDrawCircle(isClickRect[j].isX, isClickRect[j].isY, 1);
			for (int i = 0; i < isLimitOne; ++i){
				isTCircle(isTC[j][i].isSX, isTC[j][i].isSY, 3);
			}
		}


	}

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	isSpreadCircle();
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'u'){

	}
}

void Mouse(int button, int state, int x, int y){
	//---------------------------------------------------------------------
	// y���� ���� ������� ���Ͽ� ��ü������ y�� ����
	y = isRect.right - y;
	// Ȥ�ö� ���̳ʽ� ���� ������ ������ �ش� ���̳ʽ� �κ��� �ٽ� �÷����� ����.
	if (y >= 0){
		-(y);
	}
	//---------------------------------------------------------------------
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isClickRect[isClickNum].isReady = true;
		isClickRect[isClickNum].isX = x, isClickRect[isClickNum].isY = y;

		printf("%d| %d, %d\n", isClickNum, isClickRect[isClickNum].isX, isClickRect[isClickNum].isY);

		isInputData(x, y, 7);

		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}


void isInputData(int isMx, int isMy, int isSize){

	for (int i = 0; i < isLimitOne; ++i){
		isTC[isClickNum][i].isX = isMx, isTC[isClickNum][i].isY = isMy;
		isTC[isClickNum][i].isWrite = true;

		if (isTC[isClickNum][i].isWrite == true){
			int isX = isSize * cos(i*(3.14159 / 180)), isY = isSize * sin(i*(3.14159 / 180));

			isX += isMx;
			isY += isMy;

			isTC[isClickNum][i].isSX = isX, isTC[isClickNum][i].isSY = isY;
			isTC[isClickNum][i].isWrite = false;
		}
	}
	isClickNum += 1;

	if (isClickNum >= isLimitClick){
		isClickNum = 0;
	}

}

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	for (int i = 0; i < isLimitOne; ++i){
		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

void isTCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'White' ���� ����
	for (int i = 0; i < isLimitOne; ++i){

		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));
		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

int isCCC = 3;
void isSpreadCircle(){

	for (int j = 0; j < isLimitClick; ++j){
		for (int i = 0; i < isLimitOne; ++i){
			int isN = isClickRect[j].isX - isTC[j][i].isSX;
			int isNd = isClickRect[j].isY - isTC[j][i].isSY;

			//printf("%d. (%d, %d) <= (%d, %d) : %d, %d\n", i, isTC[i].isSX, isTC[i].isSY, isClickRect.isX, isClickRect.isY, isN, isNd);
			

			isTC[j][i].isSX += -(isCCC * cos(i*(3.141592 / 180)));
			isTC[j][i].isSY += -(isCCC * sin(i*(3.141592 / 180)));

		}
	}
	++isCCC;
}