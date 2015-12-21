#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void TimerFunction(int value);
void isDrawRect(int, int, int, int);
void isChangeRect();
void isChangeRGB();

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct isReDot{
	bool  isStart = false;
	int isX[2], isY[2];
}isReDot;

int isRealNum = 0;
isReDot isData[10];
int isRGB[3] = { 255, 255, 255 };


void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(100, TimerFunction, 1);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (int i = 0; i < 10; ++i){
		if (isData[i].isStart == true){
			isDrawRect(isData[i].isX[0], isData[i].isY[0], isData[i].isX[1], isData[i].isY[1]);
		}
	}

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	isChangeRGB();
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//---------------------------------------------------------------------
		// y���� ���� ������� ���Ͽ� ��ü������ y�� ����
		y = isRect.right - y;
		// Ȥ�ö� ���̳ʽ� ���� ������ ������ �ش� ���̳ʽ� �κ��� �ٽ� �÷����� ����.
		if (y >= 0){
			-(y);
		}
		//---------------------------------------------------------------------
		if (isRealNum >= 10){
			isRealNum = 0;
		}
		isData[isRealNum].isX[0] = x, isData[isRealNum].isY[0] = y;
		isData[isRealNum].isX[1] = x + 40, isData[isRealNum].isY[1] = y + 20;
		isData[isRealNum].isStart = true;
		isRealNum += 1;
		printf("Left Click = %d. (%d, %d)\n", isRealNum, x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		isChangeRect();
		printf("Right = (%d, %d)\n", x, y);
	}
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(isRGB[0], isRGB[1], isRGB[2]); // �׸��� ���� 'green' ���� ����
	glRecti(isX, isY, isX2, isY2); // �簢�� �׸��� (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isChangeRect(){
	int isTemp[2];
	for (int i = 0; i < 10; ++i){
		if (isData[i].isStart == true){

			isTemp[0] = isData[i].isX[0];
			isTemp[1] = isData[i].isY[0];

			isData[i].isX[0] = isData[i].isY[1];
			isData[i].isY[0] = isData[i].isX[1];

			isData[i].isY[1] = isTemp[0];
			isData[i].isX[1] = isTemp[1];
		}
	}
	printf("isChangeRect()\n");
}

void isChangeRGB(){
	srand((unsigned)time(NULL) + GetTickCount());
	//---------------------------------------------------------------------
	// RGB ������ Ŭ���Ҷ����� �������� ����.
	if (rand() % 3 == 0){
		isRGB[0] = 255, isRGB[1] = 0, isRGB[2] = 0;
	}
	else if (rand() % 3 == 1){
		isRGB[0] = 0, isRGB[1] = 255, isRGB[2] = 0;
	}
	else if (rand() % 3 == 2){
		isRGB[0] = 0, isRGB[1] = 0, isRGB[2] = 255;
	}
	//---------------------------------------------------------------------
}


GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}