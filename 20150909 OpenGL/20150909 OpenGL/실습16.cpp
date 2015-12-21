#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void special(int key, int x, int y);
void TimerFunction(int);

float fXNum = 0.0;
float fYNum = 0.0;
float fZNum = 0.0;

float fCXNum = 0.0;
float fCYNum = 0.0;
float fCZNum = 0.0;

void vLine();
void vGround();
void vCircle();

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
	glutSpecialFunc(special);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	//-------------------------------------------------------------
	
	/*glRotatef(fXNum, 1.0, 0.0, 0.0);
	glRotatef(fYNum, 0.0, 1.0, 0.0);
	glRotatef(fZNum, 0.0, 0.0, 1.0);*/

	

	
	glPushMatrix(); //Save
	glRotatef(30, 1.0, 0, 0.0);

	glPushMatrix(); //Save
	vLine();
	glPopMatrix();


	glPushMatrix(); //Save
	vGround();
	glPopMatrix();


	glTranslatef(0, -200, 0);

	glPushMatrix(); //Save

	glTranslatef(fXNum, 0, 0);
	glRotated(fCXNum, 0, 0, 1.0);

	glTranslatef(0, 0, fZNum);
	glRotated(fCZNum, 1.0, 0, 0);

	vCircle();
	glPopMatrix();

	glPopMatrix();

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	//glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'x'){
		fXNum += 5.0;
	}
	if (key == 'X'){
		fXNum -= 5.0;
	}

	if (key == 'y'){
		fYNum += 5.0;
	}
	if (key == 'Y'){
		fYNum -= 5.0;
	}

	if (key == 'z')
		fZNum += 5.0;
	if (key == 'Z')
		fZNum -= 5.0;

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT){
		fCXNum -= 5.0;
		if (fXNum >= -265.0){
			fXNum -= 5.0;
		}
		fCZNum = 0.0;
	}
	if (key == GLUT_KEY_RIGHT){
		fCXNum += 5.0;
		if (fXNum <= 265.0){
			fXNum += 5.0;
		}
		fCZNum = 0.0;
	}
	if (key == GLUT_KEY_DOWN){
		fCZNum += 5.0;
		if (fZNum <= 135.0){
			fZNum += 5.0;
		}
		fCXNum = 0.0;
	}
	if (key == GLUT_KEY_UP){
		fCZNum -= 5.0;
		if (fZNum >= -70.0){
			fZNum -= 5.0;
		}
		fCXNum = 0.0;
	}

	//printf("fXNum = %f, fZNum = %f\nfCXNum = %f, fCZNum = %f\n\n", fXNum, fZNum, fCXNum, fCZNum);

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){
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

void vLine(){
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();
}

void vGround(){
	glTranslatef(0, -170, 80);
	glScaled(5.0, 0.1, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
}

void vCircle(){
	glColor3f(1.0, 0.0, 1.0);
	glutWireSphere(30, 20, 10);
}