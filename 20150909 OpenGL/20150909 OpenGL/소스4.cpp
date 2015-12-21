#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

GLvoid DrawScene(GLvoid);
GLvoid Reshape(int w, int h);

void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void SetupRC();

int Time = 100;

void main()
{
	srand((unsigned)time(NULL));

	//������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //���÷��� ��� ����
	glutInitWindowPosition(500, 0); // ������ ��ġ ����
	glutInitWindowSize(800, 600); //������ ũ�� ����
	glutCreateWindow("CGExample1"); //������ ����(������ �̸�)

	//���� ���� �ʱ�ȭ �Լ�
	SetupRC();

	//�ʿ��� �ݹ� �Լ� ����
	glutDisplayFunc(DrawScene); //��� �Լ��� ����
	//glutTimerFunc(Time, TimerFunction, 1);//Ÿ�̸� �ݹ� �Լ�
	glutMouseFunc(Mouse);//���콺�Է�
	glutKeyboardFunc(Keyboard);//Ű�����Է�
	glutReshapeFunc(Reshape);//�ٽñ׸���

	glutMainLoop();//�̺�Ʈ ���� �����ϱ�
}

//������ ��� �Լ�
GLvoid DrawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��������'black'������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// ������ ������ ��ü�� ĥ�ϱ�

	//�ʿ��� ��ȯ ����
	//   ��ȯ�� �����ϱ� ���ؼ�
	//      glPushMatrix �Լ��� ȣ���Ͽ� ������ ��ǥ �ý����� ����
	//      �ʿ��� ��� ��� �ʱ�ȭ(glLoadIdentity();)
	//      ��ȯ ���� : �̵�, ȸ��, ���� �� �𵨿� ������ ��ȯ �Լ��� ȣ���Ѵ�.
	//      ��ȯ�� ���� �Ŀ��� ������ ��ǥ�ý����� �ٽ� �����ϱ� ���Ͽ� glPopMatrix �Լ� ȣ��



	glPushMatrix();
	glTranslatef(0, 10, 0);
	//glScalef(1.0, 1.0, 1.0);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glutSolidCube(10.0);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 0, 0);
	//glScalef(1.0, 1.0, 1.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCube(10.0);
	glPopMatrix();


	glutSwapBuffers(); //ȭ�鿡 ����ϱ�
}//end of drawScene

GLvoid Reshape(int w, int h)
{
	//����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);

	//���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Ŭ���� ���� ���� : ��������
	gluPerspective(60.0f, w / h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	//�� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);

	//���� ��ȯ : ī�޶��� ��ġ ����
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);

}

void Mouse(int button, int state, int x, int y)
{

}//end of Mouse

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':case '2':case '3':case '4':
		break;
	case 27://ESCŰ�� ����
		exit(0);
		break;
	}
	glutPostRedisplay();
}//end of Keyboard

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(Time, TimerFunction, 1);
}//end of TimerFunction

void SetupRC()//�ɼ����� �������� �Լ�, �ʱ�ȭ�� ������ ������ ���°� ����
{
	//�ʿ��� ������, ��ǥ�� ���� �ʱ�ȭ
	//��� ���� �ʱ�ȭ
}