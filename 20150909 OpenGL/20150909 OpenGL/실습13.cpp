#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void vMenuFunc(int value);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

struct isRect{
	int top, bottom, right, left;
}isRect;

float fXNum = 0.0;
float fYNum = 0.0;
float fZNum = 0.0;
float fSNum = 0.0;


float fLeftNum = 0.0;
float fRightNum = 0.0;


int iMmenu, iSmenu, imode;

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	//glutTimerFunc(100, TimerFunction, 1);

	iSmenu = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("��", 1);
	glutAddMenuEntry("����", 2);
	glutAddMenuEntry("������", 3);
	glutAddMenuEntry("������ü", 4);
	iMmenu = glutCreateMenu(vMenuFunc);
	glutAddSubMenu("���", iSmenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutKeyboardFunc(Keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	//glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);
	glTranslated(-150, -100, 0);

	glPushMatrix(); //Save
	glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);
	glTranslated(0, 0, fSNum);

	glRotatef(fLeftNum, 0.0, 1.0, 0.0);

	switch (imode)
	{
	case 1:
		glutWireSphere(80, 50, 50);
		break;
	case 2:
		glRotatef(-90, 1, 0, 0);

		glutWireCone(80, 100, 50, 50);
		break;
	case 3:
		glutWireTeapot(80);
		break;
	case 4:
		glutWireCube(80);
		break;
	}
	glPopMatrix(); //Load

	//-----------------------------------------------------------------------------------------
	glLoadIdentity();		// �迭 ��ġ �ʱ�ȭ
	//-----------------------------------------------------------------------------------------

	glTranslated(150, -100, 0);

	glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);
	glTranslated(0, 0, fSNum);

	glRotatef(fRightNum, 0.0, 1.0, 0.0);

	switch (imode){
	case 1:
		glutSolidSphere(80, 50, 50);
		break;
	case 2:
		glRotatef(-90, 1, 0, 0);

		glutSolidCone(80, 100, 50, 50);
		break;
	case 3:
		glutSolidTeapot(80);
		break;
	case 4:
		glutSolidCube(80);
		break;
	}
	glPopMatrix(); //Load


	//-----------------------------------------------------------------------------------------
	glLoadIdentity();		// �迭 ��ġ �ʱ�ȭ
	//-----------------------------------------------------------------------------------------
	
	glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);
	glTranslated(0, 0, fSNum);
	
	glTranslatef(0, 0, 0);
	// �ش� �κ��� ���Ͽ� �۾��� �Ѵ�.

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3f(-20, -20, -5);
	glVertex3f(80, -20, -5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3f(-20, -20, -5);
	glVertex3f(-20, 80, -5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(10);
	glBegin(GL_LINES);
	glVertex3f(-20, -20, -5);
	glVertex3f(-20, -20, 95);
	glEnd();
	glPopMatrix();

	//-----------------------------------------------------------------------------------------
	glLoadIdentity();		// �迭 ��ġ �ʱ�ȭ
	//-----------------------------------------------------------------------------------------
	glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);
	//glTranslated(0, 0, fSNum);

	glTranslatef(0, -210, 100);
	glScaled(4.0, 0.1, 2.0);
	glColor3f(1.0, 0.0, 1.0);
	glutSolidCube(100);

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	//glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'x')
		fXNum += 5.0;
	if (key == 'X')
		fXNum -= 5.0;

	if (key == 'y')
		fYNum += 5.0;
	if (key == 'Y')
		fYNum -= 5.0;

	if (key == 'z')
		fZNum += 5.0;
	if (key == 'Z')
		fZNum -= 5.0;

	if (key == 'l')
		fLeftNum += 5.0;
	if (key == 'L')
		fLeftNum -= 5.0;

	if (key == 'r')
		fRightNum += 5.0;
	if (key == 'R')
		fRightNum -= 5.0;
	/*
	if (key == 's' )
	fSNum += 1.0;
	if (key == 'S')
	fSNum -= 1.0;
	*/
	glutPostRedisplay();
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0f, w / h, 1.0, 1500.0);

	glTranslatef(0, 0, -500);

	glMatrixMode(GL_MODELVIEW);
}

void vMenuFunc(int iBt){

	switch (iBt){
	default:
		fXNum = 0;
		fYNum = 0;
		fZNum = 0;
		fSNum = 0;
	case 1:
		imode = 1;
		break;
	case 2:
		imode = 2;
		break;
	case 3:
		imode = 3;
		break;
	case 4:
		imode = 4;
		break;

	}
	glutPostRedisplay();
}