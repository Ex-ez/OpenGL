#include <GL/glut.h> // includes gl.h glu.h
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define PI 3.141592

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Timerfunction(int value);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void SetupRC();
int draw;

typedef struct _POS{
	float x;
	float y;
	float z;
	float rotate;   //����
	float revolve;   //���� �˵� ����
	int size = 0;
}POS;

POS sun;
POS earth[3];
POS moon[3];
void main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);              // �������� ��ġ����
	glutInitWindowSize(800, 600);                  // �������� ũ�� ����
	glutCreateWindow("Example14");                 // ������ ���� (������ �̸�)
	SetupRC();                              //�ʱ�ȭ
	glutDisplayFunc(drawScene);                    // ��� �Լ��� ����
	glutReshapeFunc(Reshape);                      // �ٽ� �׸��� �Լ��� ����
	//glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, Timerfunction, 1);           //Ÿ�̸� �Լ� ����
	glutMainLoop();

}

void SetupRC()
{
	sun.x = 0.0f;
	sun.y = 0.0f;
	sun.z = 0.0f;
	earth[0].x = 300.0f;
	earth[0].y = 0.0f;
	earth[0].z = 0.0f;
	earth[1].x = 300 / sqrt(2.0);
	earth[1].y = 300 / sqrt(2.0);
	earth[1].z = 0.0f;
	earth[2].x = 300 / sqrt(2.0);
	earth[2].y = -300 / sqrt(2.0);
	earth[2].z = 0.0f;
}


GLvoid drawScene(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ� + ���� ���� Ŭ����

	glLoadIdentity();

	//glPushMatrix();
	glLineWidth(4.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(300, 0, 0);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 300, 0);
	glEnd();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 300);
	glEnd();

	glBegin(GL_POINTS);


	glPushMatrix();


	glRotatef(90, 1.0f, 0.0f, 0.0f);

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	/*for (int i = 0; i <= 360; i++){
	float x = 300*cos(i* PI / 180);
	float z = 300*sin(i* PI / 180);
	glVertex3f(sun.x+x, sun.y, sun.z+z);
	}*/

	glutWireTorus(2.0, 300, 20, 360);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRotatef(60.0f, 1.0f, 1.0f, 0.0f);
	for (int i = 0; i <= 360; i++){
		float x = 300 * cos(i* PI / 180) / sqrt(2.0);
		float y = 300 * cos(i* PI / 180) / sqrt(2.0);
		float z = 300 * sin(i* PI / 180);
		glVertex3f(sun.x + x, sun.y + y, sun.z + z);
	}
	//glRotatef(30.0f, 1.0f, 1.0f, 0.0f);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	for (int i = 0; i <= 360; i++){
		float x = -300 * cos(i* PI / 180) / sqrt(2.0);
		float y = 300 * cos(i* PI / 180) / sqrt(2.0);
		float z = 300 * sin(i* PI / 180);
		glVertex3f(sun.x + x, sun.y + y, sun.z + z);
	}
	glPopMatrix();
	glEnd();

	glPushMatrix();               //�¾�
	glLineWidth(0.5);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0f, 0.0f, 0.0f, 0.0f);
	glutWireSphere(120.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
	glRotatef(earth[0].rotate, 0.0f, 1.0f, 0.0f);
	glTranslatef(earth[0].x, earth[0].y, earth[0].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 0.0f, 1.0f, 1.0f);
	glRotatef(earth[1].rotate, -1.0f, 1.0f, 0.0f);
	glTranslatef(earth[1].x, earth[1].y, earth[1].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(earth[2].rotate, 1.0f, 1.0f, 0.0f);
	glTranslatef(earth[2].x, earth[2].y, earth[2].z);
	glutWireSphere(60.0f, 30, 30);
	glPopMatrix();

	glPopMatrix();
	//glFlush(); // ȭ�鿡 ����ϱ�
	glutSwapBuffers();     //�����
}

void Reshape(int w, int h) {
	GLfloat nRange = 800.0f;

	//--- ����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);

	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//-- ������ ���� ���� �Ǵ� ���� ���� �� �� ���� �����Ѵ�.
	// Ŭ���� ���� ����: ���� ������ ���
	//glOrtho (-400, 400.0, -300.0, 300.0, -100.0, 100.0);

	// Ŭ���� ���� ����: ���� ������ ���
	gluPerspective(60.0f, w / h, 1.0, 2000.0);
	gluLookAt(0.0, 600.0, 600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Timerfunction(int value)
{
	earth[0].rotate += 1.0;
	earth[1].rotate += 2.0;
	earth[2].rotate += 3.0;

	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(50, Timerfunction, 1);                                //Ÿ�̸� �Լ� �缳��
}


void Keyboard(unsigned char key, int x, int y)
{
	//if (key == '1')  //�� 
	//   draw = 1;
	//if (key == '2')  //����ü 
	//   draw = 2;


	glutPostRedisplay();
}
