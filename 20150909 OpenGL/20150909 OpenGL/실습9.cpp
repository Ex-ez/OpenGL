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
void isC();

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

isClick isClickRect;
isCircle isTC[216];
int isSize = 0;
int isDraw = 0;

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
	for (int i = 0; i < isDraw; ++i){
		isDrawCircle(isTC[i].isSX, isTC[i].isSY, 7);
	}
	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	if (isDraw >= 216){
		//isDraw = 0;
	}
	else{
		isDraw++;
	}
	glutTimerFunc(5, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
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
		isClickRect.isX = x, isClickRect.isY = y;
		isC();
		isDraw = 0;
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

void isDrawCircle(int isMX, int isMY, int isSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	for (int i = 0; i < 360; ++i){
		int isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();
}

void isC(){
	isSize = 0;
	int isRkreh = 0;
	for (int i = 0; i < 108; ++i){

		isTC[i].isSX = isSize * cos(i*(3.141592 / 18));
		isTC[i].isSX += isClickRect.isX;

		isTC[i].isSY = isSize * sin(i*(3.141592 / 18));
		isTC[i].isSY += isClickRect.isY;
		isRkreh += 10;
		isSize++;
		printf("%d, %d = (%d, %d)\n", isRkreh, isSize, isTC[i].isSX, isTC[i].isSY);
	}


	printf("--------------------------\n");

	int temp = (isTC[107].isSX - isTC[0].isSX) * 2;

	isClickRect.isX = isTC[0].isSX + temp;
	isClickRect.isY = isTC[107].isSY;


	for (int i = 108; i < 216; ++i){
		isTC[i].isSX = isSize * sin(i*(3.141592 / 14.3));
		isTC[i].isSX += isClickRect.isX;

		isTC[i].isSY = isSize * cos(i*(3.141592 / 14.3));
		isTC[i].isSY += isClickRect.isY;
		isRkreh -= 10;
		isSize--;
		printf("%d, %d = (%d, %d)\n", isRkreh, isSize, isTC[i].isSX, isTC[i].isSY);

	}
}