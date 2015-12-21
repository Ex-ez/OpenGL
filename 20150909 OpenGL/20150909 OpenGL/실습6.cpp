#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int, int, int, int);
void Keyboard(unsigned char, int, int);
void TimerFunction(int);

void isDrawRect(int , int , int , int );

void isMoveRect();
void isUDLRChange();

struct isRect{
	int top, bottom, right, left;
}isRect;

typedef struct isReDot{
	bool isViewRect = false;
	bool isStartRect = false;
	int isX[2], isY[2];
	int isRX, isRY;
	int isUDLR = 0; // 4���� üũ
}isReDot;

#define isLimitRect 10
int isDataNum = 0;
isReDot isRectData[isLimitRect];

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

	for (int i = 0; i < isLimitRect; ++i){
		if (isRectData[i].isViewRect == true){
			isDrawRect(isRectData[i].isX[0], isRectData[i].isY[0], isRectData[i].isX[1], isRectData[i].isY[1]);
		}
	}
	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	isMoveRect();
	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);
	isMoveRect();
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

		isRectData[isDataNum].isRX = x, isRectData[isDataNum].isRY = y;
		isRectData[isDataNum].isX[0] = x, isRectData[isDataNum].isY[0] = y;
		isRectData[isDataNum].isX[1] = x+30, isRectData[isDataNum].isY[1] = y+30;
		isRectData[isDataNum].isViewRect = true;
		isRectData[isDataNum].isStartRect = true;
		isRectData[isDataNum].isUDLR = 0;

		isDataNum += 1;

		if (isDataNum >= isLimitRect){
			isDataNum = 0;
		}

		printf("Left = (%d, %d)\n", x, y);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		printf("Right = (%d, %d)\n", x, y);
	}
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	isRect.bottom = 0, isRect.top = 800, isRect.left = 0, isRect.right = 600;
}

void isDrawRect(int isX, int isY, int isX2, int isY2){
	//---------------------------------------------------------------------
	glColor3f(0, 255, 0.0f); // �׸��� ���� 'green' ���� ����
	glRecti(isX , isY , isX2, isY2); // �簢�� �׸��� (x1, y1, x2, y2)
	//---------------------------------------------------------------------
}

void isMoveRect(){
	for (int i = 0; i < isLimitRect; ++i){
		if (isRectData[i].isViewRect == true && isRectData[i].isStartRect == true){
			if (isRectData[i].isUDLR == 0){
				isRectData[i].isX[0] += 2;
				isRectData[i].isX[1] += 2;
			}
			else if (isRectData[i].isUDLR == 1){
				isRectData[i].isY[0] -= 2;
				isRectData[i].isY[1] -= 2;
			}
			else if (isRectData[i].isUDLR == 2){
				isRectData[i].isX[0] -= 2;
				isRectData[i].isX[1] -= 2;
			}
			else if (isRectData[i].isUDLR == 3){
				isRectData[i].isY[0] += 2;
				isRectData[i].isY[1] += 2;
			}

		}
	}
	isUDLRChange();
}

void isUDLRChange(){
	for (int i = 0; i < isLimitRect; ++i){
		if (isRectData[i].isViewRect == true){
			if (isRectData[i].isUDLR == 0 && isRectData[i].isX[1] >= 800){
				isRectData[i].isUDLR = 1;
				//printf("%d", isRectData[i].isX[1]);
			}
			else if (isRectData[i].isUDLR == 1 && isRectData[i].isY[0] <= 0){
				isRectData[i].isUDLR = 2;
				//printf("%d", isRectData[i].isY[0]);
			}
			else if (isRectData[i].isUDLR == 2 && isRectData[i].isX[0] <= 0){
				isRectData[i].isUDLR = 3;
				//printf("%d", isRectData[i].isY[0]);
			}
			else if (isRectData[i].isUDLR == 3 && isRectData[i].isY[0] >= isRectData[i].isRY   ){
				isRectData[i].isUDLR = 0;
				//printf("%d", isRectData[i].isY[0]);
			}

			else if (isRectData[i].isX[0] == isRectData[i].isRX &&  isRectData[i].isY[0] == isRectData[i].isRY){
				isRectData[i].isStartRect = false;
			}

		}
	}
}