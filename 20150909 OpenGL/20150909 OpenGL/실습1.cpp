#include <GL/glut.h> // includes gl.h glu.h
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

	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'green' ���� ����
	glRectf(-1.0f, -1.0f, -0.5f, -0.5f); // �簢�� �׸���

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f); // �׸��� ���� 'Blue' ���� ����
	glRectf(1.0f, 1.0f, 0.5f, 0.5f); // �簢�� �׸���

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f); // �׸��� ���� 'Red' ���� ����
	glRectf(-1.0f, 1.0f, -0.5f, 0.5f); // �簢�� �׸���

	glColor4f(1.0f, 1.0f, 0.0f, 1.0f); // �׸��� ���� 'Yellow' ���� ����
	glRectf(1.0f, -1.0f, 0.5f, -0.5f); // �簢�� �׸���

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // �׸��� ���� 'White' ���� ����
	glRectf(-0.25f, -0.25f, 0.25f, 0.25f);  // �簢�� �׸���

	glFlush(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h){
	glViewport(0, 0, w, h);
}