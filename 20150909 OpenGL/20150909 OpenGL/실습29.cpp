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

struct isRect{
	int top, bottom, right, left;
}isRect;

GLfloat ctrlpoints[20][3] = {
	{ -40.0, -40.0, 0.0 }, { -20.0, 40.0, 0.0 }, { 20.0, 20.0, 0.0 }, { 40.0, 0.0, 0.0 } };

int index = 0;

typedef struct sMouse{
	int x;
	int y;
}sMouse;

sMouse sMous[20];


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

	for (int i = 0; i < 100; ++i){
		if (ctrlpoints[i * 3][0] != 0){
			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[i * 3][0]);

			glEnable(GL_MAP1_VERTEX_3);

			glPointSize(5.0);
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_POINTS);
			for (int j = 0; j < 100; j++)
				glVertex3fv(&ctrlpoints[j][0]);
			glEnd();

			glMapGrid1f(100.0, 0, 1.0);	       // �Ű����� 0~1 ���̸� 100���� ����
			glEvalMesh1(GL_LINE, 0, 100);   // �������� ���� �κ� 0~100���� ������ �׸�
		}
	}


	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	glutTimerFunc(5, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	printf("%f, %f, %f", ctrlpoints[0][0], ctrlpoints[0][1], ctrlpoints[0][2]);
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
		printf("Left = (%d, %d)\n", x, y);

		ctrlpoints[index][0] = x;
		ctrlpoints[index][1] = y;
		sMous[index].x = x;
		sMous[index].y = y;
		index++;
		//index
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
