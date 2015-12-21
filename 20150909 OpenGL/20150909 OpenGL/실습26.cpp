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
void vLightCircle();
void vLight1();

float fMapZ = 0.0;
float vMapX = 0.0;
float fView = 0.0;

int iUpDown = 0;
bool bWhatUpDown = true;

float fAmbient = 0.1;
float fAmbient2 = 0.1;
float fAmbient3 = 0.1;
float fDiffuse = 0.1;
float fSpecular = 0.1;
bool bLight1 = false;


int iCarDown = -190;
int iMoveX = 0;
int iTotalMove = 0;
int iWhatPM = 1;
bool bTurnOn = false;
bool bCente = false;

GLfloat lightpos[] = { -iMoveX, 0, iUpDown, 1 };
GLfloat AmbientLight[] = { fAmbient, fAmbient2, fAmbient3, 1.0f };
GLfloat DiffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);
	glutTimerFunc(50, TimerFunction, 1);
	glutTimerFunc(1, TimerFunction, 2);
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
	glEnable(GL_LIGHT0);
	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotated(fMapZ, 0, 0, 1.0);
	glRotated(vMapX, 1.0, 0, 0);
	gluLookAt(0, 0, fView, 0, 0, -1, 0, 1, 0);

	glPushMatrix(); //Save
	//vLine();
	glPopMatrix();
	//---------------------------------------------
	//����
	glPushMatrix(); //Save
	glTranslatef(-150, -210, -120);
	glScaled(1.0, 0.1, 5.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(0, -210, -120);
	glScaled(1.0, 0.1, 5.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
	glPopMatrix();

	glPushMatrix(); //Save
	glTranslatef(150, -210, -120);
	glScaled(1.0, 0.1, 5.0);
	glColor3f(1.0, 1.0, 1.0);
	glutSolidCube(100);
	glPopMatrix();
	//---------------------------------------------
	
	//---------------------------------------------
	//����
	glPushMatrix(); //Save
	lightpos[0] = iMoveX;
	lightpos[1] = 0;
	lightpos[2] = iUpDown;
	glTranslatef(iMoveX, 0, iUpDown);
	vLightCircle();
	vLight1();
	glPopMatrix();
	//---------------------------------------------

	//---------------------------------------------
	//�ڵ���
	glPushMatrix(); //Save
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(iMoveX, iCarDown, iUpDown);
	if (bTurnOn == false){
		glRotated(0, 0.0, 0.0, 1.0);
	}
	else{
		glRotated(-iMoveX, 0.0, 0.0, 1.0);
	}
	glutSolidCube(50);
	//---------------------------------------------

	glPopMatrix();
	glutSwapBuffers();     // ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���

	switch (value){
	case 1:
		if (bWhatUpDown == true){
			iUpDown += 10;
			if (iUpDown >= 100){
				bWhatUpDown = false;
			}
		}
		else{
			iUpDown -= 10;
			if (iUpDown <= -330){
				bWhatUpDown = true;
			}
		}
		glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
		break;

	case 2:
		
		if (bTurnOn == true){
			iMoveX += iWhatPM;
			iCarDown = -150;

			if (iMoveX >= 150){
				bTurnOn = false;
				iCarDown = -190;
			}

			if (bCente == true){
				if (iMoveX == 0){
					bTurnOn = false;
					iCarDown = -190;
				}
			}

			if (iMoveX <= -150){
				bTurnOn = false;
				iCarDown = -190;
			}

		}
		glutTimerFunc(100, TimerFunction, 2); // Ÿ�̸��Լ� �� ����
		break;

	}


}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == '+'){
		fView += 3.0;
	}
	else if (key == '-'){
		fView -= 3.0;
	}

	if (key == 'w'){
		vMapX -= 3.0;
	}
	else if (key == 's'){
		vMapX += 3.0;
	}
	else if (key == 'a'){
		fMapZ -= 3.0;
	}
	else if (key == 'd'){
		fMapZ += 3.0;
	}

	if (key == 'u'){
		fAmbient = 0.1;
		fAmbient2 = 0.0;
		fAmbient3 = 0.0;
		AmbientLight[0] = fAmbient;
		AmbientLight[1] = fAmbient2;
		AmbientLight[2] = fAmbient3;
	}
	else if (key == 'i'){
		fAmbient = 0.1;
		fAmbient2 = 0.1;
		fAmbient3 = 0.1;
		AmbientLight[0] = fAmbient;
		AmbientLight[1] = fAmbient2;
		AmbientLight[2] = fAmbient3;
	}
	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){
		iWhatPM = -10;
		bTurnOn = true;
		if (iMoveX == 150 || iMoveX == -150){
			bCente = true;
		}
		else{
			bCente = false;
		}
	}
	if (key == GLUT_KEY_RIGHT){
		iWhatPM = 10;
		bTurnOn = true;
		if (iMoveX == 150 || iMoveX == -150){
			bCente = true;
		}
		else{
			bCente = false;
		}
	}
	if (key == GLUT_KEY_DOWN){
		
	}
	if (key == GLUT_KEY_UP){
		
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

void vLight1(){
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
}

void vLightCircle(){
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5, 20, 10);
}