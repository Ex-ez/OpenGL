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

int imX = -300, imY = -300;

void vDrawline(float, float, float, float);
void vDrawTriangles(float, float);

typedef struct sDrawLine{
	int iStartNum = 0;
	float fDataX[2], fDataY[2];
	bool bDraw = false;
}sDrawLine;

sDrawLine  sRealDraw;

//---------------------------------------
void vinit();
float fDataX[2];
float fDataY[2];
//---------------------------------------
// ������ �ﰢ���� �����̱� ���� ���
void vMoveLineT();
bool bDrawReady = false;
float fTDataX[2];
float fTDataY[2];
float fMoveDataY = 0.1;
float fMoveDataX = 0.1;
//---------------------------------------
// ȸ���� �����̱� ���� ���
#define dCircleData 200
void vMoveLineC();
typedef struct  isCircle{
	int icX, icY;
	int icSX, icSY;
}isCircle;
isCircle isTC[dCircleData];
int iSize = 0;
bool bDrawCircleReady = false;
bool bDrawCircleReadyTwo = false;
void vDrawCircle(int, int, int);
void vMakeCircle();
float fCircleSpreadX = 0.1;
float fCircleSpreadY = 0.1;
int iMoveTemp = 199;
//---------------------------------------
#define dZigZagTotal 6
float fZigZagX[dZigZagTotal];
float fZigZagY[dZigZagTotal];
int iZigZagNum = 0;
bool bDrawZigZagReady = false;
bool bDrawZigZagReadyTwo = false;
float fMoveZigZagY = 0.1;
float fMoveZigZagX = 0.1;

float fCopyZigZagX = 0.0;
float fCopyZigZagY = 0.0;

bool bOkayX = false;
bool bOkayY = false;
bool bReverse = false;

int iMoveNum = 0;

void vMovePZigZag();
void vMoveMZigZag();
//---------------------------------------
struct isRect{
	int top, bottom, right, left;
}isRect;

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

	vinit();	// ������ �� �ش� ������ �ٿ��ֱ� ���ؼ� ����
	//---------------------------------------------------------------------
	// ���� �׸���
	if (sRealDraw.bDraw == true){
		vDrawline(sRealDraw.fDataX[0], sRealDraw.fDataY[0], sRealDraw.fDataX[1], sRealDraw.fDataY[1]);
		glPushMatrix();// ����� �����Ѵ�.
		glTranslatef(fMoveDataX, fMoveDataY, 0.0f);
		vDrawTriangles(fDataX[0], fDataY[0]);
		glPopMatrix();// ����� �ҷ��´�.

	}
	//---------------------------------------------------------------------
	// ȸ���� �׸���
	if (bDrawCircleReadyTwo == true){
		for (int i = 0; i < dCircleData; ++i){
			vDrawCircle(isTC[i].icSX, isTC[i].icSY, 3);
		}

		glPushMatrix();// ����� �����Ѵ�.
		glTranslatef(fCircleSpreadX, fCircleSpreadY, 0.0f);
		vDrawTriangles(isTC[199].icSX, isTC[199].icSY);
		glPopMatrix();// ����� �ҷ��´�.
	}
	//---------------------------------------------------------------------
	//������� �׸���
	if (bDrawZigZagReadyTwo == true){

		for (int i = 0; i < dZigZagTotal; ++i){
			if (i + 1 >= dZigZagTotal){
				vDrawline(fZigZagX[i], fZigZagY[i], fZigZagX[i], fZigZagY[i]);
			}
			else{
				vDrawline(fZigZagX[i], fZigZagY[i], fZigZagX[i + 1], fZigZagY[i + 1]);
			}
		}
		glPushMatrix();// ����� �����Ѵ�.
		glTranslatef(fMoveZigZagX, fMoveZigZagY, 0.0f);
		vDrawTriangles(fZigZagX[iMoveNum], fZigZagY[iMoveNum]);
		glPopMatrix();// ����� �ҷ��´�.

	}
	//---------------------------------------------------------------------

	glFlush(); // ȭ�鿡 ����ϱ�

}

void TimerFunction(int value){
	glutPostRedisplay(); // ȭ�� �� ���
	if (sRealDraw.bDraw == true){
		vMoveLineT();
	}
	if (bDrawCircleReadyTwo == true){
		vMoveLineC();
	}

	if (bDrawZigZagReadyTwo == true){
		if (bReverse == false){
			vMovePZigZag();
		}
		else{
			vMoveMZigZag();
		}
	}

	glutTimerFunc(10, TimerFunction, 1); // Ÿ�̸��Լ� �� ����
}

void Keyboard(unsigned char key, int x, int y){
	printf("InPut Key = %c\n", key);

	if (key == 'l' || key == 'L'){
		printf("vDrawline is Ready..!\n");
		bDrawReady = true;
		bDrawCircleReady = false;
		bDrawCircleReadyTwo = false;
		bDrawZigZagReady = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'c' || key == 'C'){
		printf("vDrawCircle is Ready..!\n");
		bDrawCircleReady = true;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawZigZagReady = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'z' || key == 'Z'){
		printf("vDrawZigZag is Ready..!\n");
		bDrawZigZagReady = true;
		bDrawCircleReady = false;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawCircleReadyTwo = false;
		bDrawZigZagReadyTwo = false;
	}

	if (key == 'q' || key == 'Q'){
		bDrawZigZagReadyTwo = true;
		bDrawZigZagReady = false;
		bDrawCircleReady = false;
		bDrawReady = false;
		sRealDraw.bDraw = false;
		bDrawCircleReadyTwo = false;

		fZigZagX[0] = 100, fZigZagY[0] = 550;
		fZigZagX[1] = 700, fZigZagY[1] = 550;
		fZigZagX[2] = 700, fZigZagY[2] = 350;
		fZigZagX[3] = 100, fZigZagY[3] = 350;
		fZigZagX[4] = 100, fZigZagY[4] = 150;
		fZigZagX[5] = 700, fZigZagY[5] = 150;
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

	imX = x, imY = y;	// ���콺 ��ǥ �־���´�.

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		printf("Left = (%d, %d)\n", x, y);
		//----------------------------------------------------------------------------------------------------
		// ������ ���� �����δ�.
		if (bDrawReady == true){
			if (sRealDraw.iStartNum == 0){
				sRealDraw.fDataX[sRealDraw.iStartNum] = x;
				sRealDraw.fDataY[sRealDraw.iStartNum] = y;
				printf("RealDraw0 = (%f, %f)\n", sRealDraw.fDataX[sRealDraw.iStartNum], sRealDraw.fDataY[sRealDraw.iStartNum]);
				sRealDraw.bDraw = false;
				sRealDraw.iStartNum += 1;
			}
			else{
				sRealDraw.fDataX[sRealDraw.iStartNum] = x;
				sRealDraw.fDataY[sRealDraw.iStartNum] = y;
				printf("RealDraw1 = (%f, %f)\n", sRealDraw.fDataX[sRealDraw.iStartNum], sRealDraw.fDataY[sRealDraw.iStartNum]);
				sRealDraw.iStartNum = 0;
				sRealDraw.bDraw = true;
				fMoveDataY = 0.1;
				fMoveDataX = 0.1;
				for (int i = 0; i < 2; ++i){
					fTDataX[i] = sRealDraw.fDataX[i];
					fTDataY[i] = sRealDraw.fDataY[i];
				}
			}
		}
		//----------------------------------------------------------------------------------------------------
		// ȸ������  ���� �����δ�.
		if (bDrawCircleReady == true){
			vMakeCircle();
			iMoveTemp = 199;
			fCircleSpreadX = 0.1;
			fCircleSpreadY = 0.1;
		}
		//----------------------------------------------------------------------------------------------------
		// ������׸� ���� �����δ�.
		if (bDrawZigZagReady == true){

			fZigZagX[iZigZagNum] = x;
			fZigZagY[iZigZagNum] = y;
			printf("fZigZag[%d] = (%f, %f)\n", iZigZagNum, fZigZagX[iZigZagNum], fZigZagY[iZigZagNum]);
			iZigZagNum += 1;
			if (iZigZagNum >= dZigZagTotal){
				bDrawZigZagReadyTwo = true;
				iZigZagNum = 0;
				iMoveNum = 0;
				bReverse = false;
				fCopyZigZagX = fZigZagX[iMoveNum];
				fCopyZigZagY = fZigZagY[iMoveNum];
			}



		}
		//----------------------------------------------------------------------------------------------------

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


void vDrawline(float fDataX0, float fDataY0, float fDataX1, float fDataY1){
	//---------------------------------------------------------------------
	glBegin(GL_LINES); // ��
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	//glVertex2i(sRealDraw.fDataX[0], sRealDraw.fDataY[0]);
	//glVertex2i(sRealDraw.fDataX[1], sRealDraw.fDataY[1]);
	glVertex2i(fDataX0, fDataY0);
	glVertex2i(fDataX1, fDataY1);

	glEnd();
	//---------------------------------------------------------------------
}

void vDrawTriangles(float fDataX, float fDataY){
	//---------------------------------------------------------------------
	glBegin(GL_TRIANGLES); //�ﰢ��
	glColor3f(1.0f, 1.0f, 1.0f); // �׸��� ���� 'White' ���� ����
	glVertex2f(fDataX, fDataY + 30); //�ﰢ���� ù��° �������� ��ǥ�� �����Ѵ�.
	glVertex2f(fDataX - 30, fDataY - 30); //�ﰢ���� �ι�° �������� ��ǥ�� �����Ѵ�.
	glVertex2f(fDataX + 30, fDataY - 30); //�ﰢ���� ����° �������� ��ǥ�� �����Ѵ�.
	glEnd(); //�׸��⸦ �����Ѵ�.
	//---------------------------------------------------------------------
}

void vMoveLineT(){
	float ftempX = abs(fTDataX[1] - fTDataX[0]) / 40;
	float ftempY = abs(fTDataY[1] - fTDataY[0]) / 40;

	if (fTDataX[1] > fTDataX[0]){

		fMoveDataX += ftempX;
		fTDataX[0] += ftempX;
	}
	else{
		fMoveDataX -= ftempX;
		fTDataX[0] -= ftempX;
	}


	if (fTDataY[1] > fTDataY[0]){

		fMoveDataY += ftempY;
		fTDataY[0] += ftempY;
	}
	else{
		fMoveDataY -= ftempY;
		fTDataY[0] -= ftempY;
	}


}

void vMoveLineC(){
	float ftempX = abs(isTC[iMoveTemp].icSX - isTC[iMoveTemp - 1].icSX);
	float ftempY = abs(isTC[iMoveTemp].icSY - isTC[iMoveTemp - 1].icSY);

	if (isTC[iMoveTemp].icSX > isTC[iMoveTemp - 1].icSX){
		fCircleSpreadX -= ftempX;
	}
	else{
		fCircleSpreadX += ftempX;
	}

	if (isTC[iMoveTemp].icSY > isTC[iMoveTemp - 1].icSY){
		fCircleSpreadY -= ftempY;
	}
	else{
		fCircleSpreadY += ftempY;
	}

	iMoveTemp -= 1;

	if (iMoveTemp <= 0){
		iMoveTemp = 199;
		fCircleSpreadX = 0.1;
		fCircleSpreadY = 0.1;
	}
}

void vMakeCircle(){
	int isRkreh = 0;
	bDrawCircleReadyTwo = false;
	iSize = 30;
	for (int i = 0; i < dCircleData; ++i){

		isTC[i].icSX = iSize * sin(i*(3.141592 / 18));
		isTC[i].icSX += imX;

		isTC[i].icSY = iSize * cos(i*(3.141592 / 18));
		isTC[i].icSY += imY;
		isRkreh += 10;
		iSize++;
	}
	bDrawCircleReadyTwo = true;
}

void vDrawCircle(int isMX, int isMY, int iSize){
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f); // �׸��� ���� 'Red' ���� ����
	for (int i = 0; i < 360; ++i){
		int icX = iSize * cos(i*(3.141592 / 180)), icY = iSize * sin(i*(3.141592 / 180));

		icX += isMX;
		icY += isMY;

		glVertex3f(icX, icY, 0);
	}
	glEnd();
}

void vinit(){
	for (int i = 0; i < 2; ++i){
		fDataX[i] = sRealDraw.fDataX[i];
		fDataY[i] = sRealDraw.fDataY[i];
	}
}

void vMovePZigZag(){
	float ftempX = abs(fZigZagX[iMoveNum + 1] - fZigZagX[iMoveNum]) / 100;
	float ftempY = abs(fZigZagY[iMoveNum + 1] - fZigZagY[iMoveNum]) / 100;

	float ftempCX = ftempX * 100;
	float ftempCY = ftempY * 100;

	if (abs(fMoveZigZagX) >= ftempCX){
		bOkayX = true;
		//printf("\n\nbOkayX = True\n\n");
	}
	else{
		if (fZigZagX[iMoveNum + 1] > fZigZagX[iMoveNum]){
			fMoveZigZagX += ftempX;
			fCopyZigZagX += ftempX;
		}
		else{
			fMoveZigZagX -= ftempX;
			fCopyZigZagX -= ftempX;
		}
	}


	if (abs(fMoveZigZagY) >= ftempCY){
		bOkayY = true;
		//printf("\n\nbOkayY = True\n\n");
	}
	else{
		if (fZigZagY[iMoveNum + 1] > fZigZagY[iMoveNum]){
			fMoveZigZagY += ftempY;
			fCopyZigZagY += ftempY;
		}
		else{
			fMoveZigZagY -= ftempY;
			fCopyZigZagY -= ftempY;
		}
	}


	if (bOkayX == true && bOkayY == true){
		iMoveNum += 1;
		if (iMoveNum == dZigZagTotal - 1){
			bReverse = true;
		}
		//printf("\n\nChange!!!\n\n");
		fCopyZigZagX = fZigZagX[iMoveNum];
		fCopyZigZagY = fZigZagY[iMoveNum];
		fMoveZigZagY = 0.1;
		fMoveZigZagX = 0.1;
		bOkayX = false, bOkayY = false;
	}
	//printf("(%f, %f) => (%f, %f)\n", fMoveZigZagX, fMoveZigZagY, ftempCX, ftempCY);
}

void vMoveMZigZag(){
	float ftempX = abs(fZigZagX[iMoveNum - 1] - fZigZagX[iMoveNum]) / 100;
	float ftempY = abs(fZigZagY[iMoveNum - 1] - fZigZagY[iMoveNum]) / 100;

	float ftempCX = ftempX * 100;
	float ftempCY = ftempY * 100;

	if (abs(fMoveZigZagX) >= ftempCX){
		bOkayX = true;
		//printf("\n\nbOkayX = True\n\n");
	}
	else{
		if (fZigZagX[iMoveNum - 1] > fZigZagX[iMoveNum]){
			fMoveZigZagX += ftempX;
			fCopyZigZagX += ftempX;
		}
		else{
			fMoveZigZagX -= ftempX;
			fCopyZigZagX -= ftempX;
		}
	}


	if (abs(fMoveZigZagY) >= ftempCY){
		bOkayY = true;
		//printf("\n\nbOkayY = True\n\n");
	}
	else{
		if (fZigZagY[iMoveNum - 1] > fZigZagY[iMoveNum]){
			fMoveZigZagY += ftempY;
			fCopyZigZagY += ftempY;
		}
		else{
			fMoveZigZagY -= ftempY;
			fCopyZigZagY -= ftempY;
		}
	}


	if (bOkayX == true && bOkayY == true){
		iMoveNum -= 1;
		if (iMoveNum == 0){
			bReverse = false;
		}
		//printf("\n\nChange!!!\n\n");
		fCopyZigZagX = fZigZagX[iMoveNum];
		fCopyZigZagY = fZigZagY[iMoveNum];
		fMoveZigZagY = 0.1;
		fMoveZigZagX = 0.1;
		bOkayX = false, bOkayY = false;
	}
	//printf("(%f, %f) => (%f, %f)\n", fMoveZigZagX, fMoveZigZagY, ftempCX, ftempCY);
}