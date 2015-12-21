#include <GL/glut.h> // includes gl.h glu.h
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h> // ��� ���� ����
#include <Windows.h> // ��Ʈ�� ���� ���� �ڷ� ����

GLubyte *pBytes; // �����͸� ����ų ������
BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
GLuint texture_object[12];
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);

typedef struct POS{
	int x;
	int y;
	int z;
	float theta1;
	float theta2;
	int rcolor;
	int gcolor;
	int bcolor;
}POS;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void vLightCircle();
void vGround();
void vQURaus();

float fCircleX = 0.0;
float fCircleY = 0.0;
float fCircleZ = 100.0;

void Mouse(int button, int state, int x, int y);
void Timerfunction(int value);
void particleTimer(int value);
void SpecialKeyboard(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void vinit();
float zview, yupdown, yupdownmove;
bool light1, crush, spotlight, particle;
void vLine();
void crushcheck(int ballx, int ballz, int bdleftx, int bdleftz, int bdrightx, int bdrightz);
POS ball, smallball[50];
int lastmove, lightcount, minus, radius;

float AmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
float AmbientLight3[] = { 0.5f, 0.5f, 0.5f, 1.0f };
float DiffuseLight[] = { 1.0, 1.0, 1.0, 1.0f };
float SpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
float lightPos1[] = { 80.0f, 0.0f, 80.0f, 1.0f };
float lightPos2[] = { -80.0f, 0.0f, -80.0f, 1.0f };
float lightPos3[] = { 0.0f, -150.0f, 180.0f, 1.0f };
float Spot_direction[] = { 0.0, -1.0, 0.0 };
float Spot_cutoff[] = { 30.0f };
#define PI 3.141592

void main(int argc, char *argv[]){
	srand((unsigned)time(NULL));
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);// ���÷��� ��� ����
	glutInitWindowPosition(100, 100);              // �������� ��ġ����
	glutInitWindowSize(800, 600);                  // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004");                 // ������ ���� (������ �̸�)
	vinit();                                                                                                                                               //�ʱ�ȭ
	glutDisplayFunc(drawScene);                    // ��� �Լ��� ����
	glutReshapeFunc(Reshape);                      // �ٽ� �׸��� �Լ��� ����
	glutMouseFunc(Mouse);                          //���콺 �Է� �Լ�
	glutMotionFunc(Motion);                        //���콺 ����ä �����϶�
	glutSpecialFunc(SpecialKeyboard);                                                  // Ű���� �Է�
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(500, Timerfunction, 1);           //Ÿ�̸� �Լ� ����
	glutTimerFunc(50, particleTimer, 2);           //Ÿ�̸� �Լ� ����
	glutMainLoop();

}
// ������ ��� �Լ�

void vinit(){
	fCircleX = 0.0;
	fCircleY = 0.0;
	zview = 600.0;

	ball.x = 0.0;
	ball.y = -200;
	ball.z = 180;
	lightPos3[0] = ball.x;
	lightPos3[2] = ball.z;

	light1 = true;
	crush = false;
	spotlight = false;
	particle = false;
	for (int i = 0; i < 50; i++){
		smallball[i].rcolor = rand() % 256;
		smallball[i].gcolor = rand() % 256;
		smallball[i].bcolor = rand() % 256;
		smallball[i].theta1 = rand() % 360;
		smallball[i].theta2 = rand() % 360;
	}
	glGenTextures(11, texture_object);

	// �ٴ�
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	pBytes = LoadDIBitmap("image/Ground.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1023, 669, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �簢��
	// 1
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	pBytes = LoadDIBitmap("image/1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 2
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	pBytes = LoadDIBitmap("image/2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 3
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	pBytes = LoadDIBitmap("image/3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 65, 63, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 4
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	pBytes = LoadDIBitmap("image/4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 64, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 5
	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	pBytes = LoadDIBitmap("image/5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 64, 65, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ��
	glBindTexture(GL_TEXTURE_2D, texture_object[6]);
	pBytes = LoadDIBitmap("image/moon.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 227, 227, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);



	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[7]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[8]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[9]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// ����
	glBindTexture(GL_TEXTURE_2D, texture_object[10]);
	pBytes = LoadDIBitmap("image/B01.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 192, 480, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// �ؽ�ó ��� ����
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	// �ؽ�ó ���� Ȱ��ȭ


	lastmove = 0;
	lightcount = 0;
	minus = 1;
	radius = 0;
	yupdown = 5.0;
	yupdownmove = false;
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT2);

	glEnable(GL_DEPTH_TEST);                                             // ���� ����
	glFrontFace(GL_CCW);                                                                    // �ո� ���� 
	glEnable(GL_CULL_FACE);                                              // ���δ� �߶󳽴� 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // ���� ����
}

GLvoid drawScene(GLvoid){
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // ������ ������ ��ü�� ĥ�ϱ� + ���� ���� Ŭ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glEnable(GL_LIGHTING);                    //���� ����ϰڴ�.
	gluLookAt(0.0, 0.0, zview, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glRotatef(fCircleY, 0.0, 1.0, 0.0);
	glTranslatef(0.0, -100.0, 0.0);
	glRotatef(fCircleX, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 100.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	//----------------------------------------------------------------------------------

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);

	glLightfv(GL_LIGHT2, GL_AMBIENT, AmbientLight3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos3);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Spot_direction);
	glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, Spot_cutoff);
	glShadeModel(GL_SMOOTH);




	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-25.0, -100.0, 25.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(25.0, -100.0, 25.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(25.0, -100.0, -25.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-25.0, -100.0, -25.0);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(25.0, -200.0, 25.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(25.0, -200.0, -25.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(25.0, -100.0, -25.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(25.0, -100.0, 25.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-25.0, -200.0, 25.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(25.0, -200.0, 25.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(25.0, -100.0, 25.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-25.0, -100.0, 25.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(25.0, -200.0, -25.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-25.0, -200.0, -25.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-25.0, -100.0, -25.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(25.0, -100.0, -25.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[5]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-25.0, -200.0, -25.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-25.0, -200.0, 25.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-25.0, -100.0, 25.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-25.0, -100.0, -25.0);
	glEnd();

	//----------------------------------------------����--------------------------------------
	vQURaus();

	glPushMatrix();			//�ٴ�
	vGround();
	glPopMatrix();


	//---------------------------------------------------------�ǹ���--------------------------------

	/*glPushMatrix();
	glTranslatef(-150.0, -170.0, 150.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glScalef(5.0, 3.0, 3.0);
	glutSolidCube(20.0);
	glPopMatrix();*/

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-200, -140, 180);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(-100, -140, 180);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(-100, -140, 120);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-200, -140, 120);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[2]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-200, -200, 180);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(-100, -200, 180);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(-100, -140, 180);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-200, -140, 180);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-100, -200, 180);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(-100, -200, 120);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(-100, -140, 120);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-100, -140, 180);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[4]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-100, -200, 120);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(-200, -200, 120);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(-200, -140, 120);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-100, -140, 120);
	glEnd();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[1]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-200, -200, 120);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(-200, -200, 180);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(-200, -140, 180);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-200, -140, 120);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-150.0, -130.0, 0.0);
	glColor3f(0.3f, 0.5f, 0.7f);
	glScalef(2.0, 7.0, 3.0);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-150.0, -150.0, -150.0);
	glColor3f(0.5f, 0.3f, 1.0f);
	glScalef(2.0, 5.0, 2.0);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150.0, -150.0, -150.0);
	glColor3f(0.8f, 0.1f, 0.1f);
	glScalef(4.0, 5.0, 3.0);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150.0, -130.0, 100.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glScalef(2.0, 7.0, 1.0);
	glutSolidCube(20.0);
	glTranslatef(0.0, 0.0, -100.0);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(150.0, -70.0, 50.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glScalef(2.0, 1.0, 5.0);
	glutSolidCube(20.0);
	glPopMatrix();

	//---------------------------------------------------------�ǹ���--------------------------------

	glPushMatrix();				//��
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(ball.x, ball.y + 10.0, ball.z);
	if (!particle)
		glutSolidSphere(10.0, 20, 20);
	else{
		for (int i = 0; i < 50; i++){
			glPushMatrix();
			glColor3b(smallball[i].rcolor, smallball[i].gcolor, smallball[i].bcolor);
			glTranslatef(smallball[i].x, smallball[i].y, smallball[i].z);
			glutSolidSphere(2.0, 20, 20);
			glPopMatrix();
		}
	}
	glPopMatrix();


	glPushMatrix();			//���� 1
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
	vLightCircle();
	glPopMatrix();

	glPushMatrix();			//���� 2
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
	vLightCircle();
	glPopMatrix();

	glPopMatrix();

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
	// glOrtho (-400, 400.0, -300.0, 300.0, -100.0, 100.0);
	// Ŭ���� ���� ����: ���� ������ ���
	gluPerspective(60.0f, w / h, 1.0, 2000.0);

	//  gluLookAt(0.0, 600.0, 600.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Mouse(int button, int state, int x, int y){
	glutPostRedisplay();
}

void Motion(int x, int y){

}
void particleTimer(int value){
	if (particle){
		for (int i = 0; i < 50; i++){
			smallball[i].x = radius*sin(smallball[i].theta1*PI / 180)*cos(smallball[i].theta2*PI / 180);
			smallball[i].y = radius*sin(smallball[i].theta1*PI / 180)*sin(smallball[i].theta2*PI / 180);
			smallball[i].z = radius*cos(smallball[i].theta1*PI / 180);
		}
		radius += 2;
	}
	if (radius == 40){
		radius = 0;
		particle = false;
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(50, particleTimer, 2);                                //Ÿ�̸� �Լ� �缳��
}

void Timerfunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(50, Timerfunction, 1);                                //Ÿ�̸� �Լ� �缳��
}


void SpecialKeyboard(int key, int x, int y){
	if (key == GLUT_KEY_UP){
		if (ball.z > -190)
			ball.z -= 3;
		lastmove = 1;
	}
	if (key == GLUT_KEY_DOWN){
		if (ball.z < 190)
			ball.z += 3;
		lastmove = 2;
	}
	if (key == GLUT_KEY_LEFT){
		if (ball.x > -190)
			ball.x -= 3;
		lastmove = 3;
	}
	if (key == GLUT_KEY_RIGHT){
		if (ball.x < 190)
			ball.x += 3;
		lastmove = 4;
	}
	if (ball.x == 150 && 10 <= ball.z && ball.z <= 90){
		lightcount++;
		minus = -1;
	}

	crushcheck(ball.x, ball.z, -200, 120, -100, 180);
	crushcheck(ball.x, ball.z, -170, -30, -130, 30);
	crushcheck(ball.x, ball.z, -170, -170, -130, -130);
	crushcheck(ball.x, ball.z, -25, -25, 25, 25);
	crushcheck(ball.x, ball.z, 110, -180, 190, -120);
	crushcheck(ball.x, ball.z, 130, -10, 170, 10);
	crushcheck(ball.x, ball.z, 130, 90, 170, 110);
	if (crush){
		if (lastmove == 1)
			ball.z += 3;
		if (lastmove == 2)
			ball.z -= 3;
		if (lastmove == 3)
			ball.x += 3;
		if (lastmove == 4)
			ball.x -= 3;
		crush = false;
	}
	lightPos3[0] = ball.x;
	lightPos3[1] = -150.0;
	lightPos3[2] = ball.z;


	if (lightcount % 4 == 0){
		AmbientLight[0] = 0.3f;
		AmbientLight[1] = 0.3f;
		AmbientLight[2] = 0.3f;
	}
	else if (lightcount % 4 == 1){
		AmbientLight[0] = 0.5f;
		AmbientLight[1] = 0.0f;
		AmbientLight[2] = 0.0f;
	}
	else if (lightcount % 4 == 2){
		AmbientLight[0] = 0.0f;
		AmbientLight[1] = 0.5f;
		AmbientLight[2] = 0.0f;
	}
	else if (lightcount % 4 == 3){
		AmbientLight[0] = 0.0f;
		AmbientLight[1] = 0.0f;
		AmbientLight[2] = 0.5f;
	}


	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y){
	
	if (key == 'r'){
		fCircleY += 3.0;
	}

	if (key == 'z')
		fCircleZ+= 10.0;
	if (key == 'Z')
		fCircleZ-= 10.0;

	if (key == 'w')
		fCircleX+= 2.0;
	if (key == 's')
		fCircleX-= 2.0;



	if (key == '1'){
		light1 = !light1;
		if (light1){
			glEnable(GL_LIGHT0);
			glEnable(GL_LIGHT1);
		}
		else{
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
		}
	}
	if (key == '3'){
		spotlight = !spotlight;
		if (spotlight)
			glEnable(GL_LIGHT2);
		else
			glDisable(GL_LIGHT2);
	}
	if (key == '4'){
		particle = true;
		radius = 0;
		for (int i = 0; i < 50; i++){
			smallball[i].rcolor = rand() % 256;
			smallball[i].gcolor = rand() % 256;
			smallball[i].bcolor = rand() % 256;
			smallball[i].theta1 = rand() % 360;
			smallball[i].theta2 = rand() % 360;
			smallball[i].x = 0;
			smallball[i].y = 0;
			smallball[i].z = 0;
		}
	}

	if (key == 27)
		exit(0);
	glutPostRedisplay();
}
void vLine(){

	glLineWidth(4.0);
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(100, 0, 0);
	glEnd();

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 100, 0);
	glEnd();

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 100);
	glEnd();

	glLineWidth(0.5);
}

void crushcheck(int ballx, int ballz, int bdleftx, int bdleftz, int bdrightx, int bdrightz){
	if (bdleftx - 10 <= ballx && ballx <= bdrightx + 10 && bdleftz <= ballz && ballz <= bdrightz)
		crush = true;
	if (bdleftx <= ballx && ballx <= bdrightx && bdleftz - 10 <= ballz && ballz <= bdrightz + 10)
		crush = true;
}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// ���̳ʸ� �б� ���� ������ ����
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// ������ BMP �������� Ȯ������.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER ��ġ�� �A��.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// ��Ʈ�� �̹��� �����͸� ���� �޸� ������ ����.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// ��Ʈ�� ���� ����� �д´�.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ���� ũ�� ����
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� ��������.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� ��������.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}


void vLightCircle(){
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(5, 20, 10);
}

void vGround(){
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_object[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3i(-200, -200, 200);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3i(200, -200, 200);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3i(200, -200, -200);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3i(-200, -200, -200);
	glEnd();
}


void vQURaus(){
	glBindTexture(GL_TEXTURE_2D, texture_object[7]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-300.0, -200.0, 300.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-300.0, 200.0, -300.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-300.0, 200.0, 300.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[8]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(-300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(300.0, 200.0, -300.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(-300.0, 200.0, -300.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[9]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(300.0, -200.0, -300.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(300.0, -200.0, 300.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(300.0, 200.0, 300.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(300.0, 200.0, -300.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture_object[10]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f);
	glVertex3f(300.0, -200.0, 300.0);
	glTexCoord2d(1.0f, 0.0f);
	glVertex3f(-300.0, -200.0, 300.0);
	glTexCoord2d(1.0f, 1.0f);
	glVertex3f(-300.0, 200.0, 300.0);
	glTexCoord2d(0.0f, 1.0f);
	glVertex3f(300.0, 200.0, 300.0);
	glEnd();
}