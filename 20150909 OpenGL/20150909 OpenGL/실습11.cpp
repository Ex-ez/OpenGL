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

void isDrawline();
void isDrawCircle();
void isDrawTriangles();

float isX = 0.0, isX2 = 0.5, isY = 8.0, isY2=1.0;
float isWhat = 0.0;

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct isCircleData{
	float isDataX, isDataY;
}isCircleData;

isCircleData isDataCircle[360];
isCircleData isDataTriangles[3];


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


	isDrawline();
	isDrawCircle();
	
	glPushMatrix();// ����� �����Ѵ�.
	glRotatef(isWhat, 0.0f, 0.0f, 1.0);
	isDrawTriangles();
	glPopMatrix();// ����� �ҷ��´�.

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	isWhat += 1.5;
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 'u' || key == 'U'){
		isY2 += 0.1;
		isX2 += 0.1;
		isY += 0.1;
	}
	else if (key == 'd' || key == 'D'){
		isY2 -= 0.1;
		isX2 -= 0.1;
		isY -= 0.1;
	}
	else if (key == 'r' || key == 'R'){
		isX = isX * cos(3.141592 / 180) - isY * sin(3.141592 / 180);
		isY = isX * sin(3.141592 / 180) + isY * cos(3.141592 / 180);
	}
	else if (key == 'z' || key == 'Z'){

	}
	printf("(%f, %f) (%f, %f)\n", isX, isY, isX2, isY2);
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
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(-10, 10, -10, 10, -1.0, 1.0);
	isRect.bottom = -10, isRect.top = 10, isRect.left = -10, isRect.right = 10;
}


void isDrawline(){
	//Y ��
	glBegin(GL_LINE_STRIP); // ��
	glPointSize(1.0f);//���� ũ��
	glColor3f(1.0f, 1.0f, 0.0f); // �׸��� ���� 'Yellow' ���� ����
	glVertex3f(0.0f, -10, 1.0f);//���� ��ǥ
	glVertex3f(0.0f, 10, 1.0f);//���� ��ǥ
	glEnd();
	//X ��
	glBegin(GL_LINE_STRIP); // ��
	glPointSize(1.0f);//���� ũ��
	glColor3f(1.0f, 1.0f, 0.0f); // �׸��� ���� 'Yellow' ���� ����
	glVertex3f(-10.0f, 0.0f, 1.0f);//���� ��ǥ
	glVertex3f(10.0f, 0.0f, 1.0f);//���� ��ǥ
	glEnd();
}

void isDrawCircle(){
	float isSize = 7.0;
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	for (int i = 0; i < 360; ++i){
		float isX = isSize * cos(i*(3.141592 / 180)), isY = isSize * sin(i*(3.141592 / 180));

		isX += 0.0;
		isY += 0.0;

		isDataCircle[i].isDataX = isX;
		isDataCircle[i].isDataY = isY;

		glVertex3f(isX, isY, 0);
	}
	glEnd();

}


void isDrawTriangles(){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //�ﰢ��
	glColor3f(1.0f, 1.0f, 1.0f); // �׸��� ���� 'White' ���� ����
	glVertex2f(isX, isY); //�ﰢ���� ù��° �������� ��ǥ�� �����Ѵ�.
	glVertex2f(isX-isX2, isY-isY2); //�ﰢ���� �ι�° �������� ��ǥ�� �����Ѵ�.
	glVertex2f(isX+isX2, isY-isY2); //�ﰢ���� ����° �������� ��ǥ�� �����Ѵ�.
	glEnd(); //�׸��⸦ �����Ѵ�.
	//---------------------------------------------------------------------
}
