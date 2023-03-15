#include <GL/glut.h>

void init(float dotSize)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(dotSize);  // tamanho do ponto a ser desenhado
    glColor3f(1.0f, 1.0f, 1.0f);  // cor do ponto a ser desenhado (branco)
}

void draw_pixel(float xPos,float yPos)
{
    glBegin(GL_POINTS);
    glVertex2f(xPos, yPos);  // coordenadas do ponto a ser desenhado (no centro da tela)
    glEnd();
}

void draw_line(float xPos1, float yPos1, float xPos2, float yPos2){
    float dx = xPos2 - xPos1;
    float dy = yPos2 - yPos1;

    float IncE = 2 * (dy);
    float IncNE = 2 * (dy - dx);
    float ds = (2 * dy) - dx;

    int xAux = xPos1;
    int yAux = yPos1;

    float d = ds;

    while(xAux < xPos2){
        if ( d >= 0 ){
            xAux += 1;
            yAux += 1;
            d += IncNE;
            draw_pixel(xAux, yAux);
        }
        else{
            xAux+=1;

            d+=IncE;
            draw_pixel(xAux, yAux);
        }
    }

}

void display()
{
//    draw_pixel(500,0);
    draw_line(0,0,500,500);
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

    init(1);       //clear display and define size of dot
    glutDisplayFunc(
        []() {
                display();
            }
    ); //Desenha o pixel

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WindowWidth/2, WindowWidth/2, -WindowHeight/2, WindowHeight/2, -1.0, 1.0);  // definindo as coordenadas do plano cartesiano

    glutMainLoop();
    return 0;
}