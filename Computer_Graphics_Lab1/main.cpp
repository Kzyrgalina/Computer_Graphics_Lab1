#include <stdio.h>
#include <GL/glew.h> // подключаем заголовок GLEW'a
#include <GL/freeglut.h>
#include "math_3d.h" // подключаем заголовок 

GLuint VBO; // Назначим GLuint в качестве глобальной переменной для хранения указателя на буфер вершин

static void RenderSceneCB()
{
    glClear(GL_COLOR_BUFFER_BIT); // Это очистка буфера кадра

    glEnableVertexAttribArray(0); // Координаты вершин, используемые в буфере, рассматриваются как атрибут вершины с индексом 0
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Параметр GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин для отрисовки 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Вызов говорит конвейеру как воспринимать данные внутри буфера
    //Первый параметр указывает на индекс атрибута.
    //Второй параметр - это количество компонентов в атрибуте (3 для X, Y и Z)
    //Третий параметр - тип данных для каждого компонента
    //Следующий - хотим ли мы нормализовать атрибуты перед использованием в конвейере
    //Пятый параметр (названный "шаг") является числом байтов между 2 экземплярами атрибута

    glDrawArrays(GL_TRIANGLES, 0, 3); // Функция для отрисовки (для тругольника содержит 3 вершины)
    //glDrawArrays(GL_POINTS, 0, 1);

    glDisableVertexAttribArray(0); // Отключает каждый атрибут вершины, как только отпадает необходимость в нем

    glutSwapBuffers(); // Меняет местами буферы текущего окна при двойной буферизации
}


static void InitializeGlutCallbacks() //Просит GLUT поменять фоновый буфер и буфер кадра местами
{
    glutDisplayFunc(RenderSceneCB); // Задает отображение обратного вызова для текущего окна
}

static void CreateVertexBuffer()
{
    // Массив из экземпляров структуры Vector3f заголовка math_3d.h
    Vector3f Vertices[3]; // Вершины треугольника в координатаъх
    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);
    //Vertices[0] = Vector3f(0.0f, 0.0f, 0.0f); Задает точку по центру экрана из Tutorial 02

    glGenBuffers(1, &VBO); // функция для генерации объектов переменных типов
    //Параметры: (количество объектов, которые вы хотите создать, и ссылка на массив типа GLuints для хранения указателя, по которому будут храниться данные)
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // привязываем указатель к названию цели и затем запускаем команду на цель
    //Параметр GL_ARRAY_BUFFER означает, что буфер будет хранить массив вершин.
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);  //Параметры название цели (такое же как и при привязывании), размер данных в байтах, адрес массива вершин, и флаг, 
                                                                                //который обозначает использование паттернов для этих данных. 
                                                                                //Так как мы не собираемся изменять значения буфера, указываем GL_STATIC_DRAW.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv); // инициализируем GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);   // Настраиваются некоторые опции GLUT
                                                    //(отрисовка будет происходить в фоновый буфер, в то время как другой буфер отображается) 
   
    // Задаем параметры окна и создаем его.
    glutInitWindowSize(1024, 768); // Размер окна
    glutInitWindowPosition(100, 100); // Позиция
    glutCreateWindow("Tutorial 03"); // Название окна

    InitializeGlutCallbacks(); 

    // GLUT необходимо инициализировать раньше!
    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // (красный, зелёный, синий, альфа-канал) и принимает значения от 0.0 и до 1.0.

    CreateVertexBuffer(); // Создает буфер вершин

    glutMainLoop(); // Передаёт контроль GLUT'у

    return 0;
}
