#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void init(void);
void Mouse(int button, int state, int x, int y);
void TimerFunction(int value);

static int mx, my, px[10], py[10];
static float g_fAngle = 0;
static bool leftCheck = false;
int pts[10][100][2]; // pts[]��ü�� []�Ѿ��Ѱ� []x ,y��
int num_pts = 40; //�Ѿ˼�
int clickCount = 0; //Ŭ��ī����
float fullladian[10]; //�����°�

void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ��� 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ���� 
	glutCreateWindow("Example4"); // ������ ���� (������ �̸�)
	init();

	glutTimerFunc(100, TimerFunction, 1);
	//glutSpecialFunc(SKeyboard);
	glutMouseFunc(Mouse); //���콺
	glutDisplayFunc(drawScene); // ��� �Լ��� ����

	glutReshapeFunc(Reshape); glutMainLoop();
}
// ������ ��� �Լ�
GLvoid drawScene(GLvoid)
{
	float radius = 2.0f;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // �������� 'blue' �� ���� 
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� 

	//  clear all pixels
	for (int z = 0; z < 10; z++)
	{
		if (leftCheck)
			for (int i = 0; i < num_pts; i++)
			{
				pts[z][i][0] = px[z] + cos((i + 1)*(360 / 40.f)) * fullladian[z];
				pts[z][i][1] = py[z] + sin((i + 1)*(360 / 40.f)) * fullladian[z];
			}

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < num_pts; i++)
		{
			glPushMatrix();//���
			glTranslatef(pts[z][i][0], pts[z][i][1], 0.0f); //�̵�
			glBegin(GL_POLYGON);  //�ٰ���(��)
			for (float fAngle = 0.f; fAngle < 360.f; fAngle += 1.0f)
			{
				glVertex2f(cos(fAngle) * radius, sin(fAngle) * radius);
			}
			glEnd();
			glPopMatrix();
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, 800.0f, 600.0f, 0, -1.0, 1.0);
}


void init(void)
{
	for (int i = 0; i < 10; i++)
	{
		px[i] = -300;
		py[i] = -300;
	}
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		leftCheck = true;

		clickCount++;
		if (clickCount >= 10)
			clickCount = 0;

		px[clickCount] = x;
		py[clickCount] = y;
		fullladian[clickCount] = 10;
	}
}


void TimerFunction(int value)
{
	for (int i = 0; i < 10; i++)
		fullladian[i] += 5;
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}