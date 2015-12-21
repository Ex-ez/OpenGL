#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isUDLR();
void isDrawRect(int, int, int, int);
void isDrawCircle(int, int, int);

#define isRealRect 3

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct  isClick{
	int isX, isY;
	bool isReady = false;
}isClick;

typedef struct isReDot{
	bool  isStart = false;
	int isX = 0, isY = 0;
	int isPlusSize = 0;
	int isUDLR = 0; // 4���� üũ
}isReDot;

isClick isClickRect;
isReDot isRectData[isRealRect];

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
	srand((unsigned)time(NULL) + GetTickCount());
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (int i = 0; i < isRealRect; ++i){
		if (isRectData[i].isStart == false){
			int isX = rand() % 700, isY = rand() % 500;
			isRectData[i].isPlusSize = rand() % 100 + 10;
			isRectData[i].isX = isX, isRectData[i].isY = isY;
			isRectData[i].isStart = true;
		}
		isDrawRect(isRectData[i].isX, isRectData[i].isY, isRectData[i].isX + isRectData[i].isPlusSize, isRectData[i].isY + isRectData[i].isPlusSize);
	}
	/*
	���� �̿��Ͽ� ��Ƽ�ٸ���� �Ͽ� ���׶��� �����
	*/
	glPointSize(20.0);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);
	glColor3f(255, 0, 0); // �׸��� ���� 'Red' ���� ����
	glVertex2i(isClickRect.isX, isClickRect.isY);
	glEnd();
	
	//isDrawCircle(isClickRect.isX, isClickRect.isY, 10);


	glFlush(); // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	if (isClickRect.isX != 0 && isClickRect.isY != 0){
		isUDLR();
	}

	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
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
		isClickRect.isReady = true;
		isClickRect.isX = x, isClickRect.isY = y;
		printf("Left = (%d, %d)\n", x, y);
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		isClickRect.isReady = false;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		for (int i = 0; i < isRealRect; ++i){
			int isX = rand() % 700, isY = rand() % 500;
			isRectData[i].isPlusSize = rand() % 100 + 10;
			isRectData[i].isX = isX, isRectData[i].isY = isY;
			isRectData[i].isStart = true;
		}
		printf("Right = (%d, %d)\n", x, y);
	}
}

void isUDLR(){
	for (int i = 0; i < isRealRect; ++i){
		if (isRectData[i].isX > isClickRect.isX){
			isRectData[i].isX -= 1;
			printf("%d. (%d, %d) : X-=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isY > isClickRect.isY){
			isRectData[i].isY -= 1;
			printf("%d. (%d, %d) : Y-=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isX < isClickRect.isX){
			isRectData[i].isX += 1;
			printf("%d. (%d, %d) : X+=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
		if (isRectData[i].isY < isClickRect.isY){
			isRectData[i].isY += 1;
			printf("%d. (%d, %d) : Y+=1\n", i, isRectData[i].isX, isRectData[i].isY);
		}
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(1.0f, 1.0f, 1.0f); // �׸��� ���� 'White' ���� ����
	glRecti(isX, isY, isX2, isY2); // �簢�� �׸��� (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	for (int i = 0; i < 360; ++i){
		int isX = isSize * cos(i*(3.14 / 180)), isY = isSize * sin(i*(3.14 / 180));
		isX += isMX;
		isY += isMY;
		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

