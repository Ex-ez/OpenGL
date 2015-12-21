#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isDrawline();
void isDrawSinCos(int);
void isDrawSpring();
void isDrawRect();
void isDrawMove(int);
void isRectRotation();
void isRestart();
void isExpand(int);
void isCosinToLine();
void isCosinToLineTwo();
void print();

#define isTotalData 1000

struct isRect{
	int top, bottom, right, left;
}isRect;


float isStartX = -10.0, isStartY = 0.0, isSizeData = 2.0;
int isSelectRect = 0, isCosinToLineData = 0;

typedef struct isDrawDesign{
	float isDataX, isDataY;
}isDrawDesign;

isDrawDesign isRealData[isTotalData];


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
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'Black' �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	isDrawline();	// ����� x,y�� �׷��ֱ�
	print();

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	if (isCosinToLineData == 1){
		isCosinToLine();
	}
	else if (isCosinToLineData == 2){
		isCosinToLineTwo();
	}
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	if (key == 's' || key == 'S'){
		isSelectRect = 0;
		isDrawSinCos(isSelectRect);
	}
	else if (key == 'c' || key == 'C'){
		isSelectRect = 1;
		isDrawSinCos(isSelectRect);
	}
	else if (key == 'p' || key == 'P'){
		isSelectRect = 2;
		isDrawSpring();
	}
	else if (key == 'q' || key == 'Q'){
		isSelectRect = 3;
		isDrawRect();
	}
	else if (key == 'x'){
		isDrawMove(0);
	}
	else if (key == 'X'){
		isDrawMove(1);
	}
	else if (key == 'y'){
		isDrawMove(2);
	}
	else if (key == 'Y'){
		isDrawMove(3);
	}
	else if (key == 'r' || key == 'R'){
		isRectRotation();
	}
	else if (key == 'i' || key == 'I'){
		isRestart();
	}
	else if (key == 'z'){
		isExpand(0);
	}
	else if (key == 'Z'){
		isExpand(1);
	}
	else if (key == '.'){
		exit(1);
	}
	else if (key == 'b' || key == 'B'){
		isCosinToLineData = 1;
	}
	else if (key == 'e' || key == 'E'){
		exit(1);
	}

}

void Mouse(int button, int state, int x, int y){
	//---------------------------------------------------------------------
	// y���� ���� ������� ���Ͽ� ��ü������ y�� ����
	y = isRect.right - y;
	// Ȥ�ö� ���̳ʽ� ���� ������ ������ �ش� ���̳ʽ� �κ��� �ٽ� �÷����� ����.
	if (y >= 0){
		-(y);
	}
	//---------------------------------------------------------------------
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(-10, 10, -10, 10, -1.0, 1.0);
	isRect.bottom = -10, isRect.top = 10, isRect.left = -10, isRect.right = 10;
}

void isRestart(){
	if (isSelectRect == 0){
		isDrawSinCos(isSelectRect);
	}
	else if (isSelectRect == 1){
		isDrawSinCos(isSelectRect);
	}
	else if (isSelectRect == 2){
		isDrawSpring();
	}
	else if (isSelectRect == 3){
		isDrawRect();
	}
}

void isDrawMove(int isPM){

	for (int i = 0; i < isTotalData; ++i){
		if (isPM == 0){
			isRealData[i].isDataX -= 0.05;
		}
		else if (isPM == 1){
			isRealData[i].isDataX += 0.05;
		}
		else if (isPM == 2){
			isRealData[i].isDataY -= 0.05;
		}
		else if (isPM == 3){
			isRealData[i].isDataY += 0.05;
		}
	}

}

void isRectRotation(){
	for (int i = 0; i < isTotalData; ++i){
		isRealData[i].isDataX = isRealData[i].isDataX * cos(3.141592 / 180) - isRealData[i].isDataY * sin(3.141592 / 180);
		isRealData[i].isDataY = isRealData[i].isDataX * sin(3.141592 / 180) + isRealData[i].isDataY * cos(3.141592 / 180);
	}
}

void isDrawline(){
	//Y ��
	glBegin(GL_LINE_STRIP); // ��
	glPointSize(1.0f);//���� ũ��
	glColor3f(1.0f, 1.0f, 0.0f); // �׸��� ���� 'Yellow' ���� ����
	glVertex3f(0.0f, -10, 1.0f);//���� ��ǥ
	glVertex3f(0.0f, 10, 1.0f);//���� ��ǥ
	glEnd();

	//X ��
	glBegin(GL_LINE_STRIP); // ��
	glPointSize(1.0f);//���� ũ��
	glColor3f(1.0f, 1.0f, 0.0f); // �׸��� ���� 'Yellow' ���� ����
	glVertex3f(-10.0f, 0.0f, 1.0f);//���� ��ǥ
	glVertex3f(10.0f, 0.0f, 1.0f);//���� ��ǥ
	glEnd();
}

void isDrawSinCos(int isData){
	// 0 sin 1 cos
	isStartX = -10.0;
	for (int i = 0; i < isTotalData; ++i){
		isStartX += 0.1;
		if (isData == 0){
			isStartY = isSizeData*sin(isStartX);
		}
		else{
			isStartY = isSizeData*cos(isStartX);
		}
		isRealData[i].isDataX = isStartX;
		isRealData[i].isDataY = isStartY;
		//printf("%d. (%f, %f)\n", i, isStartX, isStartY);
	}
}

void isDrawSpring(){
	int isSize = 3;
	float isSpringNum = 0;
	float isStartX = 5.0;	// X���� ��ġ
	float isStartY = 0.0;	// Y���� ��ġ
	for (int i = 0; i < isTotalData; ++i){
		isRealData[i].isDataX = (cos(i * (3.141592 / 180)) * isSize) + isStartX + isSpringNum;
		isRealData[i].isDataY = (sin(i * (3.141592 / 180)) * isSize) + isStartY;
		isSpringNum -= 0.01;
	}
}

void isDrawRect(){
	float isDX = -5.0, isDY = 5.0;

	for (int i = 0; i < 250; ++i){
		isRealData[i].isDataX = isDX;
		isRealData[i].isDataY = isDY;
		if (isDY >= -5.0){
			isDY -= 0.05;
		}
	}

	for (int i = 250; i < 500; ++i){
		isRealData[i].isDataX = isDX;
		isRealData[i].isDataY = isDY;
		if (isDX <= 5.0){
			isDX += 0.05;
		}
	}

	for (int i = 500; i < 750; ++i){
		isRealData[i].isDataX = isDX;
		isRealData[i].isDataY = isDY;
		if (isDY <= 5.0){
			isDY += 0.05;
		}
	}

	for (int i = 750; i < isTotalData; ++i){
		isRealData[i].isDataX = isDX;
		isRealData[i].isDataY = isDY;
		if (isDX >= -5.0){
			isDX -= 0.05;
		}
	}
}

void isExpand(int isZO){
	for (int i = 0; i < isTotalData; ++i){
		if (isZO == 0){
			isRealData[i].isDataX *= 1.1;
			isRealData[i].isDataY *= 1.1;
		}
		else{
			isRealData[i].isDataX /= 1.1;
			isRealData[i].isDataY /= 1.1;
		}
	}
}

void isCosinToLine(){
	isSizeData -= 0.1;

	isDrawSinCos(isSelectRect);

	if (isSizeData <= 0.0){
		isCosinToLineData = 2;
		if (isSelectRect == 0){
			isSelectRect = 1;
		}
		else{
			isSelectRect = 0;
		}
		isCosinToLineTwo();
	}
}

void isCosinToLineTwo(){
	isSizeData += 0.1;
	isDrawSinCos(isSelectRect);

	if (isSizeData >= 2.0){
		isCosinToLineData = 0;
	}
}

void print(){
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);//����
	glPointSize(1.0f);//���� ũ��
	glBegin(GL_LINE_STRIP);

	for (int i = 0; i < isTotalData; ++i){
		glVertex3f(isRealData[i].isDataX, isRealData[i].isDataY, 1.0f);//���� ��ǥ
	}

	glEnd();
}