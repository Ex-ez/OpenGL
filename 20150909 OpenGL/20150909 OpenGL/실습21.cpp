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

float fMapZ = 0.0;
float vMapX = 0.0;
float fView = 0.0;

bool bDEPTH = true;

#define totalNum 10

typedef struct sTorus{
	bool draw = false;
	bool tr = false;
	float down = 0.0;
	float turn = 0.0;
}sTorus;

sTorus fTorus[totalNum];
int iTorusNum = 0;
int iTotalHeight = 198;

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

	if (bDEPTH == true){
		glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_DEPTH_TEST);
	}

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	//vLine();
	glPopMatrix();

	//--------------------------------------------
	// ��� ��
	glPushMatrix(); //Save
	glTranslatef(0, -210, 100);
	glScaled(4.0, 0.1, 4.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
	glPopMatrix();
	//--------------------------------------------
	glPushMatrix(); //Save
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0, -100, 100);
	glScaled(1, 30, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(0, 0, 100);
	glRotated(90, 1, 0, 0);
	glPushMatrix(); //Save
	glRotated(fTorus[iTorusNum].turn, 0, 0, 1);
	glTranslatef(30, 0, fTorus[iTorusNum].down);
	if (fTorus[iTorusNum].tr == false){
		glColor3f(0.0, 1.0, 1.0);
		glutSolidTorus(10, 50, 10, 10);
	}
	else{
		glColor3f(1.0, 1.0, 0.0);
		glScaled(5.0, 5.0, 1.0);
		glutSolidCube(25);
	}
	glPopMatrix();


	for (int i = 0; i < totalNum; ++i){
		if (fTorus[i].draw == true){
			glPushMatrix(); //Save
			glRotated(fTorus[i].turn, 0, 0, 1);
			glTranslatef(0, 0, fTorus[i].down);
			if (fTorus[i].tr == false){
				glColor3f(0.0, 1.0, 1.0);
				glutSolidTorus(10, 50, 10, 10);
			}
			else{
				glColor3f(1.0, 1.0, 0.0);
				glScaled(5.0, 5.0, 1.0);
				glutSolidCube(25);
			}
			glPopMatrix();
		}
	}



	glPopMatrix();
	glPopMatrix();

	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	if (iTorusNum <= 11){

		if (fTorus[iTorusNum].down <= iTotalHeight){
			fTorus[iTorusNum].down += 1.0;
			fTorus[iTorusNum].turn += 10;
		}
		else{
			iTotalHeight -= 20;
			fTorus[iTorusNum].draw = true;
			iTorusNum += 1;
			if (iTorusNum % 3 == 1){
				fTorus[iTorusNum].tr = true;
			}
			printf("%d", iTorusNum);
		}
	}
	else{
		for (int i = 0; i < totalNum; ++i){
			fTorus[i].draw = false;
			fTorus[i].tr = false;
			fTorus[i].down = 0.0;
			fTorus[i].turn = 0.0;
			iTotalHeight = 198;
			iTorusNum = 0;
		}
	}

	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}

	if (key == 'c'){
		if (bDEPTH == false){
			bDEPTH = true;
		}
		else{
			bDEPTH = false;
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
