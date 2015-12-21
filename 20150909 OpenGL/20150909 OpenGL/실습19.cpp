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
void vMenuFunc(int value);


float fBingle = 0.0;
float fBingle2 = 0.0;
int iMmenu, imode;

int  iDepth, iCulling, iShading, iTop, iBottom;

bool bTop = true;
bool bBottom = true;
bool bDepth = false;
bool bCulling = false;
bool bShading = false;

void vLine();

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutMouseFunc(Mouse);

	iDepth = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	iCulling = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 3);
	glutAddMenuEntry("Off", 4);
	iShading = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 5);
	glutAddMenuEntry("Off", 6);
	iTop = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 7);
	glutAddMenuEntry("Off", 8);
	iBottom = glutCreateMenu(vMenuFunc);
	glutAddMenuEntry("On", 9);
	glutAddMenuEntry("Off", 10);

	iMmenu = glutCreateMenu(vMenuFunc);
	glutAddSubMenu("��������", iDepth);
	glutAddSubMenu("�ø�", iCulling);
	glutAddSubMenu("���̵�", iShading);
	glutAddSubMenu("����", iTop);
	glutAddSubMenu("����", iBottom);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc(50, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKey);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�

	//-------------------------------------------------------------
	glPushMatrix(); //Save
	glRotatef(30, 1.0, 0.0, 0.0);
	glRotatef(45, 0.0, 1.0, 0.0);


	glPushMatrix(); //Save
	vLine();
	glPopMatrix();

	glPushMatrix(); //Save
	glRotated(fBingle, 0, 1.0, 0);
	glRotated(fBingle2, 1.0, 0, 0);



	if (bDepth == false){
		glEnable(GL_DEPTH_TEST);

	}
	else{
		glDisable(GL_DEPTH_TEST);

	}

	if (bCulling == true){
		glEnable(GL_CULL_FACE);

	}
	else{
		glDisable(GL_CULL_FACE);

	}


	if (bShading == true){
		glShadeModel(GL_SMOOTH); // �Ǵ� glShadeModel (GL_FLAT)
	}

	if (bBottom == true){
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-100.0, 100.0, 100.0);   //1
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(-100.0, -100.0, 100.0);   //2
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(100.0, -100.0, 100.0);   //3
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(100.0, 100.0, 100.0);   //4
		glEnd();
	}

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(100.0, 100.0, 100.0);   //4
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(100.0, -100.0, 100.0);   //3   
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(100.0, 100.0, -100.0);   //6
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0, 100.0, -100.0);   //5
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(100.0, 100.0, -100.0);   //6
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-100.0, 100.0, 100.0);   //1
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0, 100.0, -100.0);   //5
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8   
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-100.0, -100.0, 100.0);   //2
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(-100.0, -100.0, 100.0);   //2
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-100.0, -100.0, -100.0);   //8
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(100.0, -100.0, -100.0);   //7
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(100.0, -100.0, 100.0);   //3
	glEnd();

	if (bTop == true){
		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-100.0, 100.0, 100.0);  //1
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(100.0, 100.0, 100.0);   //4
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(100.0, 100.0, -100.0);   //6
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-100.0, 100.0, -100.0);   //5
		glEnd();
	}

	glPopMatrix();

	glPopMatrix();
	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();	// ȭ�鿡 ����ϱ�
}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	fBingle -= 1.0;

	glutTimerFunc(50, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'c'){
		fBingle += 1.0;
	}
	if (key == 'v'){
		fBingle -= 1.0;
	}

	if (key == 'd'){
		fBingle2 += 1.0;
	}
	if (key == 'f'){
		fBingle2 -= 1.0;
	}

	glutPostRedisplay();
}

void SpecialKey(int key, int x, int y){
	if (key == GLUT_KEY_LEFT){

	}
	if (key == GLUT_KEY_RIGHT){

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

void vMenuFunc(int iBt){
	switch (iBt){
	default:
	case 1:
		bDepth = true;
		break;
	case 2:
		bDepth = false;
		break;

	case 3:
		bCulling = true;
		break;
	case 4:
		bCulling = false;
		break;

	case 5:
		bShading = true;
		break;
	case 6:
		bShading = false;
		break;

	case 7:
		bTop = true;
		break;
	case 8:
		bTop = false;
		break;
	case 9:
		bBottom = true;
		break;
	case 10:
		bBottom = false;
		break;




	}
	glutPostRedisplay();
}