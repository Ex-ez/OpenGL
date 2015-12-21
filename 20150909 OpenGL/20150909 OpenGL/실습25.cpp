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
void vLightCircle();

float fMapZ = 0.0;
float vMapY = 0.0;
float vMapX = 0.0;
float fView = 0.0;

float fRect = 0.0;


float fAmbient = 0.05;
float fDiffuse = 0.1;
float fSpecular = 0.1;
bool bLight1 = false;

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(10, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);      // ���� Ȱ��ȭ
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	if (bLight1 == true){
		glEnable(GL_LIGHT0);
	}
	else{
		glDisable(GL_LIGHT0);
	}

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	glRotated(vMapY, 0, 1.0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	glTranslatef(400, 200, -500);
	vLightCircle();
	glPopMatrix();

	glPushMatrix(); //Save
	//-----------------------------------
	glTranslatef(-100, 0, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -50, 0);
	glVertex3f(0, 50, 0);
	glEnd();
	//-----------------------------------
	glPushMatrix(); //Save
	glRotated(fRect, 0, 1.0, 0);
	glTranslatef(-40, 0, 0);
	glutSolidCube(40);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Save
	//-----------------------------------
	glTranslatef(100, 0, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(50, 0, 0);
	glVertex3f(-50, 0, 0);
	glEnd();
	//-----------------------------------
	glPushMatrix(); //Save
	glRotated(fRect, 1.0, 0, 0);
	glTranslatef(0, -40, 0);
	glutSolidSphere(20, 15, 20);
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Save
	//-----------------------------------
	glTranslatef(0, -150, 0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, -50, 0);
	glVertex3f(0, 50, 0);
	glEnd();
	//-----------------------------------
	glPushMatrix(); //Save
	glRotated(fRect, 0, 1.0, 0);
	glTranslatef(100, 0, 0);
	glPushMatrix(); //Save
	glRotated(90, 1.0, 0.0, 0);
	glutSolidTorus(2, 50, 10, 50);
	glutSolidSphere(20, 15, 20);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix(); //Save
	vGround();
	glPopMatrix();
	glPopMatrix();

	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	fRect += 5.0;

	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}
	if (key == 'r'){
		vMapY += 3.0;
	}

	if (key == '1'){
		if (bLight1 == true){
			bLight1 = false;
		}
		else{
			bLight1 = true;
		}
	}

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		fMapZ -= 3.0;
	}
	if (key == GLUT_KEY_RIGHT){
		fMapZ += 3.0;
	}
	if (key == GLUT_KEY_DOWN){
		vMapX += 3.0;
	}
	if (key == GLUT_KEY_UP){
		vMapX -= 3.0;
	}
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

	gluLookAt(0, 0, 500, 0, 0, -1, 0, 1, 0);

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
	glTranslatef(0, -210, 100);
	glScaled(4.0, 0.1, 2.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
}

void vLight1(){
	GLfloat lightpos[] = { 400, 200, -500, 1 };
	GLfloat ambientLight[] = { fAmbient, fAmbient, fAmbient, 1.0f };       // ��� �ֺ���
	GLfloat DiffuseLight[] = { fDiffuse, fDiffuse, fDiffuse, 1.0f };
	GLfloat SpecularLight[] = { fSpecular, fSpecular, fSpecular, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}

void vLightCircle(){
	glColor3f(1.0, 1.0, 1.0);
	glutSolidSphere(5, 20, 10);
}