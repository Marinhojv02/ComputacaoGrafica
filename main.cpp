#include <GL/glut.h>

void draw_pixel(float xPos,float yPos, float dotSize)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(dotSize);  // tamanho do ponto a ser desenhado
    glColor3f(1.0f, 1.0f, 1.0f);  // cor do ponto a ser desenhado (branco)
    glBegin(GL_POINTS);
    glVertex2f(xPos, yPos);  // coordenadas do ponto a ser desenhado (no centro da tela)
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    int WindowWidth = 1920;
    int WindowHeight = 1080;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WindowWidth, WindowHeight);         //Tamanho da janela

    glutCreateWindow("Desenho de um pixel");        //Nome da janela

    glutDisplayFunc(
        []() {
            draw_pixel(500,0,5);
        }
    ); //Desenha o pixel

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WindowWidth/2, WindowWidth/2, -WindowHeight/2, WindowHeight/2, -1.0, 1.0);  // definindo as coordenadas do plano cartesiano

    glutMainLoop();
    return 0;
}