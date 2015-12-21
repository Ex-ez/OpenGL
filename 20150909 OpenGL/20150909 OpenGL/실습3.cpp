#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

struct isRect{
	int top, bottom, right, left;
}isRect;

void isDataRand();
void isDrawTriangles(int, int, int, int);
void isDrawRect(int, int, int, int);
void isDrawPolygon(int, int, int, int);
void isDrawLines(int, int, int, int);

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	/*
	//---------------------------------------------------------------------
	isDrawTriangles(400, 200, 600, 400);
	isDrawTriangles(0, 0, 200, 200);
	//---------------------------------------------------------------------
	isDrawRect(200, 200, 400, 400);
	isDrawRect(0, 400, 200, 600);
	//---------------------------------------------------------------------
	isDrawPolygon(200, 400, 400, 600);
	isDrawPolygon(400, 0, 600, 200);
	//---------------------------------------------------------------------
	isDrawLines(200, 0, 400, 200);
	isDrawLines(400, 400, 600, 600);
	isDrawLines(0, 200, 200, 400);
	//---------------------------------------------------------------------
	*/
	isDataRand();
	glFlush(); // ȭ�鿡 ����ϱ�
	
}

void isDrawLines(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // ��
	glColor3f(1.0f, 1.0f, 0.0f); // �׸��� ���� 'Yellow' ���� ����
	glVertex2i(isX + 50, isY + 50);
	glVertex2i(isX2 - 50, isY2 - 50);
	glEnd();
	//---------------------------------------------------------------------
}

void isDrawPolygon(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_POLYGON); // ������
	glColor3f(0.0f, 100, 100); // �׸��� ���� 'Blue' ���� ����
	glVertex2i(isX + 20, (isY + isY2) / 2 + 15);
	glColor3f(0.0f, 100, 150); // �׸��� ���� 'Blue' ���� ����
	glVertex2i(isX + 60, isY + 50);
	glColor3f(0.0f, 0, 200); // �׸��� ���� 'Blue' ���� ����
	glVertex2i(isX2 - 50, isY + 50);
	glColor3f(0.0f, 0, 250); // �׸��� ���� 'Blue' ���� ����
	glVertex2i(isX2 - 50, isY2 - 20);
	glColor3f(0.0f, 0.0f, 255); // �׸��� ���� 'Blue' ���� ����
	glVertex2i(isX + 60, isY2 - 20);
	glEnd();
	//---------------------------------------------------------------------
}

void isDrawTriangles(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //�ﰢ��
	glColor3f(100, 100, 0.0f); // Red
	glVertex2i(isX + 50, isY + 50); //�ﰢ���� ù��° �������� ��ǥ�� �����Ѵ�.
	glColor3f(200, 0.0f, 0.0f); // Red
	glVertex2i((isX + isX2) / 2, isY2 - 20); //�ﰢ���� �ι�° �������� ��ǥ�� �����Ѵ�.
	glColor3f(255, 0.0f, 0.0f); // Red
	glVertex2i(isX2 - 50, isY + 50); //�ﰢ���� ����° �������� ��ǥ�� �����Ѵ�.
	glEnd(); //�׸��⸦ �����Ѵ�.
	//---------------------------------------------------------------------
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(0, 255, 0.0f); // �׸��� ���� 'green' ���� ����
	glRecti(isX + 50, isY + 50, isX2 - 50, isY2 - 20); // �簢�� �׸��� (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isDataRand(){
	int isX = 0, isY = 0;
	int isX2 = 200, isY2 = 200;

	for (int j = 0; j < 3; ++j){
		for (int i = 0; i < 3; ++i){
			srand((unsigned)time(NULL)+isY2*isY+isX2*isX);
			int isRandDraw = rand() % 4;

			if (isRandDraw == 0){
				isDrawTriangles(isX, isY, isX2, isY2);
			}
			else if (isRandDraw == 1){
				isDrawLines(isX, isY, isX2, isY2);
			}
			else  if (isRandDraw == 2){
				isDrawPolygon(isX, isY, isX2, isY2);
			}
			else  if (isRandDraw == 3){
				isDrawRect(isX, isY, isX2, isY2);
			}
			isY2 += 200, isY += 200;
		}
		isX += 200, isX2 += 200, isY2 = 200, isY= 0;
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0, 600.0, 0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 600, isRect.left = 0, isRect.right = 600;
}