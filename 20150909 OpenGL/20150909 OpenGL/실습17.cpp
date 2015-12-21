#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void SpecialKey(int key, int x, int y);
void TimerFunction(int);

void vLine();
void vGround();
void vBox();
void vBox2();
void vBox3();


float fXNum = 0.0;
float fMinPlu = 2.0;
float fZNum = 0.0;


float fMidTurn = 0.0;
float fMidWow = 0.0;

float fHighTurn = 0.0;
float fHighWow = 0.0;

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
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	//-------------------------------------------------------------

	glPushMatrix(); //Save
	glRotatef(30, 1.0, 0, 0.0);
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	vGround();
	glPopMatrix();
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	//vLine();
	glPopMatrix();
	//-------------------------------------------------------------
	glRotated(fZNum, 0, 1.0, 0);
	glTranslatef(fXNum, 0, 0);
	glTranslatef(0, -200, 0);
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	vBox();						// ����

	glPopMatrix();
	//-------------------------------------------------------------
	glTranslatef(0, 70, 0);
	glRotated(fMidTurn, 0, 1.0, 0);
	glRotated(fMidWow, 1.0, 0.0, 0);
	glTranslatef(0, 50, 0);
	glPushMatrix(); //Save
	vBox2();					// �ι�° ����
	glPopMatrix();
	//-------------------------------------------------------------
	glTranslatef(0, 50, 0);
	glRotated(fHighTurn, 0, 1.0, 0);
	glRotated(fHighWow, 1.0, 0.0, 0);
	glTranslatef(0, 50, 0);
	glPushMatrix(); //Save
	vBox3();
	glPopMatrix();
	//-------------------------------------------------------------


	glPopMatrix();

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	fXNum += fMinPlu;

	if (fXNum == 210.0){
		fMinPlu = -2.0;
	}
	else if (fXNum == -210.0){
		fMinPlu = 2.0;
	}

	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'y'){
		// ������ �����δ�.
		fZNum += 1.0;
	}
	else if (key == 'Y'){
		fZNum -= 1.0;
	}

	if (key == 'z'){
		// �߰� ������ ����.
		fMidTurn += 2.0;
	}
	else if (key == 'Z'){
		fMidTurn -= 2.0;
	}

	if (key == 'x'){
		fMidWow += 2.0;
	}
	else if (key == 'X'){
		fMidWow -= 2.0;
	}

	if (key == 'c'){
		fHighTurn += 2.0;
	}
	else if(key == 'C'){
		fHighTurn -= 2.0;
	}

	if (key == 'v'){
		fHighWow += 2.0;
	}
	else if (key == 'V'){
		fHighWow -= 2.0;
	}
	
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		if (fXNum >= -210.0){
			fXNum -= 2.0;
		}
	}
	if (key == GLUT_KEY_RIGHT){
		if (fXNum <= 210.0){
			fXNum += 2.0;
		}
	}
	if (key == GLUT_KEY_DOWN){

	}
	if (key == GLUT_KEY_UP){

	}

	printf("fXNum = %f\n", fXNum);
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

	glTranslatef(0, -120, 100);
	glScaled(4.4, 0.0, 3.8);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
}

void vBox(){
	glColor3f(1.0, 0.0, 0.0);
	glScaled(2.0, 1.5, 1.0);
	//glutSolidCube(100);
	glutWireCube(100);
}

void vBox2(){
	glScaled(1.0, 2.0, 1.0);
	glColor3f(0.0, 0.0, 1.0);
	//glutSolidCube(50);
	glutWireCube(50);
}

void vBox3(){
	glScaled(1.0, 4.0, 1.0);
	glColor3f(0.0, 1.0, 1.0);
	//glutSolidCube(50);
	glutWireCube(25);
}