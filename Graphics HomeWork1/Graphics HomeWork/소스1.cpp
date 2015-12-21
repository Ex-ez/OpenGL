#include <GL/glut.h> // includes gl.h glu.h
#include <iostream>
#include<time.h>
#include<stdlib.h>
GLvoid drawScene(GLvoid);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Reshape(int w, int h);
GLvoid Time(int value);

struct setting
{
	float w; //�ʺ�
	float h; //����
	float dir = 1; //����
	float trance; //�̵�

};
setting Box, basket, water, move;

struct position
{
	int x = 0; // x��ǥ
	int y = 0; // y��ǥ
};
position mouse, top_mouse, bottom_mouse;

void init();

int count = 0;

void main(int argc, char *argv[])
{
	//�ʱ�ȭ �Լ��� glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA ); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Slice and Take it!"); // ������ ���� (������ �̸�) 
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutTimerFunc(100, Time, 1);
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ������ Black 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 
	glPushMatrix();


	glPushMatrix();
	glTranslatef(Box.trance, 0, 0); // x������ �̵�
	glBegin(GL_QUADS);
	init(); // Box.w, Box.h �� �ʱⰪ -80 , 70
	glColor3f(1, 1, 0);
	glVertex2f(Box.w, Box.h);            // ���� �ڽ� ����
	glVertex2f(Box.w, Box.h - 20);
	glVertex2f(Box.w + 30, Box.h - 20);
	glVertex2f(Box.w + 30, Box.h);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(basket.trance, 0, 0); // x������ �̵�

	glBegin(GL_LINE_STRIP);
	init(); // basket.w , basket.h �� �ʱⰪ -80, -50;
	glColor3f(1, 1, 1);
	glVertex2f(basket.w, basket.h);
	glVertex2f(basket.w, basket.h - 30);                  // �ٱ���
	glVertex2f(basket.w + 40.0, basket.h - 30);
	glVertex2f(basket.w + 40.0, basket.h);
	glEnd();
	glBegin(GL_QUADS);
	init(); // water.w, water.h �� �ʱⰪ -80 , -65
	glColor3f(0, 0, 1);
	glVertex2f(water.w, water.h);            // ��
	glVertex2f(water.w, water.h - 15);
	glVertex2f(water.w + 39.5, water.h - 15);
	glVertex2f(water.w + 39.5, water.h);
	glEnd();

	glPopMatrix();


	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glEnd();

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 1, 1);
	glVertex2i(top_mouse.x, top_mouse.y);
	glVertex2i(bottom_mouse.x, bottom_mouse.y);
	glEnd();
	glPopMatrix();

	glPopMatrix();


	glFlush(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	glutPostRedisplay(); // ȭ�� �� ���
}

GLvoid Mouse(int button, int state, int x, int y)
{
	//---------------------------------------------------------------------
	// y���� ���� ������� ���Ͽ� ��ü������ y�� ����
	y = 600 - y;
	// Ȥ�ö� ���̳ʽ� ���� ������ ������ �ش� ���̳ʽ� �κ��� �ٽ� �÷����� ����.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d, %d\n", x, y);
		top_mouse.x = x;
		top_mouse.y = y;
	}




	count++;




	glutPostRedisplay(); // ȭ�� �� ���

}
GLvoid Motion(int x, int y)
{
	//---------------------------------------------------------------------
	// y���� ���� ������� ���Ͽ� ��ü������ y�� ����
	y = 600 - y;
	// Ȥ�ö� ���̳ʽ� ���� ������ ������ �ش� ���̳ʽ� �κ��� �ٽ� �÷����� ����.
	if (y >= 0){
		-y;
	}
	//---------------------------------------------------------------------
	printf("%d, %d\n", x, y);
	bottom_mouse.x = x;
	bottom_mouse.y = y;


	glutPostRedisplay();
}

GLvoid Time(int sec)
{
	Box.trance += Box.dir * 1;
	if (Box.trance > 150){
		Box.dir = -1;
	}
	if (Box.trance < -20){
		Box.dir = 1;
	}

	basket.trance += basket.dir * 1;
	if (basket.trance > 140){
		basket.dir = -1;
	}
	if (basket.trance < -20){
		basket.dir = 1;
	}





	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(30, Time, 3);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{


	}
}


void init()
{
	Box.w = -80;
	Box.h = 70;

	basket.w = -80;
	basket.h = -50;

	water.w = -80;
	water.h = -65;

}