#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);
void isOne(int, int, int);

struct isRect{
	int top, bottom, right, left;
}isRect;

int isRealX=0, isRealY=0;

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

	isOne(isRealX, isRealY, 20);

	glFlush(); // ȭ�鿡 ����ϱ�

}


void isOne(int isMX, int isMY, int isSize){
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; ++i){
		int isX = isSize * cos(i*(3.14 / 180)), isY = isSize * sin(i*(3.14 / 180));

		isX += isMX;
		isY += isMY;

		glVertex3f(isX, isY, 0);
		//printf("%d. (%f, %f)\t", i, 100 * cos(i*(3.14 / 180)), 100 * sin(i*(3.14 / 180)));
	}
	glEnd();
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
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
		isRealX = x, isRealY = y;
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
