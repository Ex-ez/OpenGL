#include <GL/glut.h> // includes gl.h glu.h
#include <stdio.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

void main(int argc, char *argv[]){
	//�ʱ�ȭ �Լ���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(100, 100); // �������� ��ġ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("WindowsHyun - 2012180004"); // ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene); // ��� �Լ��� ����
	glutReshapeFunc(Reshape);
	glutMainLoop();
}

// ������ ��� �Լ�
GLvoid drawScene(GLvoid){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // �������� 'blue' �� ����


	int isX = 0, isY = 50;

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	
	for (int i = 0; i < 6; ++i){
		if (i % 2 == 0){
			glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'Blue' ���� ����
			glRectf(0, isX, 50, isY); // �簢�� �׸��� (x1, y1, x2, y2)
			isX += 50, isY += 50;
		}
		else{
			glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'Green' ���� ����
			glRectf(0, isX, 50, isY); // �簢�� �׸��� (x1, y1, x2, y2)
			isX += 50, isY += 50;
		}
	}
	
	isX = 50, isY = 100;
	int isXT = 0, isYT = 50, isColor = 0;

	for (int j = 0; j < 6; ++j){
		for (int i = 0; i < 7; ++i){
			if (i % 2 == 0){
				if (isColor % 2 == 0){
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'Green' ���� ����
				}
				else{
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'Blue' ���� ����
				}
				glRectf(isX, isXT, isY, isYT); // �簢�� �׸��� (x1, y1, x2, y2)
				isX += 50, isY += 50;
			}
			else{
				if (isColor % 2 == 0){
					glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'Blue' ���� ����
				}
				else{
					glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'Green' ���� ����
				}
				glRectf(isX, isXT, isY, isYT); // �簢�� �׸��� (x1, y1, x2, y2)
				isX += 50, isY += 50;
			}
		}
		isXT += 50, isYT += 50;
		isX = 50, isY = 100;
		isColor += 1;
	}

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
	glOrtho(0, 400.0, 0, 300.0, -1.0, 1.0);
}