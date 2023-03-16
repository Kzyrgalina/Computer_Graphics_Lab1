#include <stdio.h>
#include <GL/glew.h> // ���������� ��������� GLEW'a
#include <GL/freeglut.h>
#include "math_3d.h" // ���������� ��������� 

GLuint VBO; // �������� GLuint � �������� ���������� ���������� ��� �������� ��������� �� ����� ������

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); // ��� ������� ������ �����

    glEnableVertexAttribArray(0); // ���������� ������, ������������ � ������, ��������������� ��� ������� ������� � �������� 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // �������� GL_ARRAY_BUFFER ��������, ��� ����� ����� ������� ������ ������ ��� ��������� 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // ����� ������� ��������� ��� ������������ ������ ������ ������
    //������ �������� ��������� �� ������ ��������.
    //������ �������� - ��� ���������� ����������� � �������� (3 ��� X, Y � Z)
    //������ �������� - ��� ������ ��� ������� ����������
    //��������� - ����� �� �� ������������� �������� ����� �������������� � ���������
    //����� �������� (��������� "���") �������� ������ ������ ����� 2 ������������ ��������

    glDrawArrays(GL_TRIANGLES, 0, 3); // ������� ��� ��������� (��� ����������� �������� 3 �������)
    //glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0); // ��������� ������ ������� �������, ��� ������ �������� ������������� � ���

    glutSwapBuffers(); // ������ ������� ������ �������� ���� ��� ������� �����������
}


static void InitializeGlutCallbacks() //������ GLUT �������� ������� ����� � ����� ����� �������
{
    glutDisplayFunc(RenderSceneCB); // ������ ����������� ��������� ������ ��� �������� ����
}

static void CreateVertexBuffer()
{
    // ������ �� ����������� ��������� Vector3f ��������� math_3d.h
    Vector3f Vertices[3]; // ������� ������������ � ������������
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
    //Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f); ������ ����� �� ������ ������ �� Tutorial 02

    glGenBuffers(1, &VBO); // ������� ��� ��������� �������� ���������� �����
    //���������: (���������� ��������, ������� �� ������ �������, � ������ �� ������ ���� GLuints ��� �������� ���������, �� �������� ����� ��������� ������)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // ����������� ��������� � �������� ���� � ����� ��������� ������� �� ����
    //�������� GL_ARRAY_BUFFER ��������, ��� ����� ����� ������� ������ ������.
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  //��������� �������� ���� (����� �� ��� � ��� ������������), ������ ������ � ������, ����� ������� ������, � ����, 
                                                                                //������� ���������� ������������� ��������� ��� ���� ������. 
                                                                                //��� ��� �� �� ���������� �������� �������� ������, ��������� GL_STATIC_DRAW.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); // �������������� GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   // ������������� ��������� ����� GLUT
                                                    //(��������� ����� ����������� � ������� �����, � �� ����� ��� ������ ����� ������������) 
   
    // ������ ��������� ���� � ������� ���.
    glutInitWindowSize(1024, 768); // ������ ����
    glutInitWindowPosition(100, 100); // �������
    glutCreateWindow("Tutorial 03"); // �������� ����

    InitializeGlutCallbacks(); 

    // GLUT ���������� ���������������� ������!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // (�������, ������, �����, �����-�����) � ��������� �������� �� 0.0 � �� 1.0.

    CreateVertexBuffer(); // ������� ����� ������

    glutMainLoop(); // ������� �������� GLUT'�

    return 0;
}
