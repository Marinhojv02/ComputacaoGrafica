#include <GL/glut.h>
#include <iostream>
#include <tuple>
#include <cmath>

int WindowWidth = 1000;
int WindowHeight = 1000;

int ScreenWidth = 1920;
int ScreenHeight = 1080;

using namespace std;

float inp_to_display_zero(double value, double resolutionDisplay, double resolutionScreen){

    float xMax, x;

    x = value - 0;
    xMax = resolutionScreen - 0;

    float ndcX = x/xMax;

    float dcx = round(ndcX * (resolutionDisplay-1));

    return dcx;

}

int inp_to_display_um(double value, double resolutionDisplay, double resolutionScreen){

    float xMax, x;

    x = value - (-1);
    xMax = resolutionScreen - (-1);

    float ndcX = x/xMax;

    float dcx = round(ndcX * (resolutionDisplay-1));

    return dcx;

}

tuple<float, float> inputPixel(){

    float x;
    float y;

    cout << "insira o valor de x: ";
    cin >> x;
    cout << "insira o valor de y: ";
    cin >> y;

//    x = inp_to_display_zero( x,  WindowWidth, ScreenWidth);
//    y = inp_to_display_zero( y,  WindowHeight, ScreenHeight);

    x = inp_to_display_um( x,  WindowWidth, ScreenWidth);
    y = inp_to_display_um( y,  WindowHeight, ScreenHeight);

    cout << "X em DC: " << x << endl;
    cout << "y em DC: " << y << endl;

    cout << "X zero a um: " <<  inp_to_display_zero( x,  WindowWidth, ScreenWidth) << endl;
    cout << "y zero a um: " <<  inp_to_display_zero( y,  WindowHeight, ScreenHeight) << endl;

    return {x,y};
}

tuple<float, float, float, float > inputReta(){

    float x1;
    float y1;
    float x2;
    float y2;

    cout << "insira o valor de x1: ";
    cin >> x1;
    cout << "insira o valor de y1: ";
    cin >> y1;
    cout << "insira o valor de x2: ";
    cin >> x2;
    cout << "insira o valor de y2: ";
    cin >> y2;

//    x1 = inp_to_display_zero( x1,  WindowWidth, ScreenWidth);
//    y1 = inp_to_display_zero( y1,  WindowHeight, ScreenHeight);
//    x2 = inp_to_display_zero( x2,  WindowWidth, ScreenWidth);
//    y2 = inp_to_display_zero( y2,  WindowHeight, ScreenHeight);

    x1 = inp_to_display_um( x1,  WindowWidth, ScreenWidth);
    y1 = inp_to_display_um( y1,  WindowHeight, ScreenHeight);
    x2 = inp_to_display_um( x2,  WindowWidth, ScreenWidth);
    y2 = inp_to_display_um( y2,  WindowHeight, ScreenHeight);

    cout << "X1 em DC: " << x1 << endl;
    cout << "y1 em DC: " << y1 << endl;
    cout << "X2 em DC: " << x2 << endl;
    cout << "y2 em DC: " << y2 << endl;

    cout << "X1 zero a um: " << inp_to_display_um( x1,  WindowWidth, ScreenWidth) << endl;
    cout << "y1 zero a um: " << inp_to_display_um( y1,  WindowHeight, ScreenHeight) << endl;
    cout << "X2 zero a um: " << inp_to_display_um( x2,  WindowWidth, ScreenWidth) << endl;
    cout << "y2 zero a um: " << inp_to_display_um( y2,  WindowHeight, ScreenHeight) << endl;

    return {x1,y1,x2,y2};
}

void init(float dotSize)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(dotSize);  // tamanho do ponto a ser desenhado
    glColor3f(1.0f, 1.0f, 1.0f);  // cor do ponto a ser desenhado (branco)
}

void draw_pixel(double xPos,double yPos)
{
    glBegin(GL_POINTS);
    glVertex2f(xPos, yPos);  // coordenadas do ponto a ser desenhado (no centro da tela)
    glEnd();
}

void ponto_circulo(float xPos, float yPos){
    draw_pixel(xPos,yPos);
    draw_pixel(yPos,xPos);
    draw_pixel(yPos,-xPos);
    draw_pixel(xPos,-yPos);
    draw_pixel(-xPos,-yPos);
    draw_pixel(-yPos,-xPos);
    draw_pixel(-yPos,xPos);
    draw_pixel(-xPos,yPos);
}

void circle(float xPos, float yPos, float raio){
    float xAux = xPos;
    float yAux = yPos + raio;

    float d = 1-yAux;

    while(yAux > xAux){
        if (d < 0) {
            d += (2*xAux) + 3;
        }else{
            d += ((2*xAux)-(2*yAux)) +5;
            yAux--;
        }
        xAux++;
        ponto_circulo(xAux,yAux);
    }
}

void draw_line_DDA(float xPos1, float yPos1, float xPos2, float yPos2){
    float dx = xPos2 - xPos1;
    float dy = yPos2 - yPos1;

    float xAux = xPos1;
    float yAux = yPos1;

    float length = dx;

    if(abs(dy) > length){
        length = abs(dy);
    }

    float xInc = dx/length;
    float yInc = dy/length;

    draw_pixel(round(xAux), round(yAux));

    while(xAux < xPos2){
        xAux += xInc;
        yAux += yInc;
        draw_pixel(round(xAux), round(yAux));
    }
}

void draw_linePontoMedio(float xPos1, float yPos1, float xPos2, float yPos2){

    float xAux2 = xPos2;
    float yAux2 = yPos2;

    float xAux1 = xPos1;
    float yAux1 = yPos1;

    if(xPos1 > xPos2){
        xAux1 = xPos2;
        xAux2 = xPos1;
    }
    if(yPos1 > yPos2){
        yAux1 = yPos2;
        yAux2 = yPos1;
    }

    float dx = xAux2 - xAux1;
    float dy = yAux2 - yAux1;

    float m = dy/dx;

    float IncE;
    float IncNE;
    float ds;

    if(m < 1 && m > 0){
        IncE = 2 * (dy);
        IncNE = 2 * (dy - dx);
        ds = (2 * dy) - dx;
    }
    else{
        IncE = 2 * (dx);

        IncNE = 2 * (dx - dy);
        ds = (2 * dx) - dy;
    }

    float d = ds;

    if(m < 1 && m > 0){
        while(xAux1 < xAux2) {
            if (d >= 0) {
                xAux1 += 1;
                yAux1 += 1;
                d += IncNE;
                draw_pixel(xAux1, yAux1);
            } else {
                xAux1 += 1;

                d += IncE;
                draw_pixel(xAux1, yAux1);
            }
        }
    }else{
        while(yAux1 < yAux2){
            if ( d >= 0 ){
                xAux1 += 1;
                yAux1 += 1;
                d += IncNE;
                draw_pixel(xAux1, yAux1);
            }

            else{
                yAux1+=1;

                d+=IncE;
                draw_pixel(xAux1, yAux1);
            }
        }
    }


}

void display()
{

//    auto [x, y] = inputPixel();
//    draw_pixel(x, y);

   // auto [x1,y1,x2,y2] = inputReta();
    //draw_line_DDA(x1,y1,x2,y2);
    //draw_linePontoMedio(x1,y1,x2,y2  );

    circle(100,100,200);

    glFlush();

}

int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WindowWidth, WindowHeight);         //Tamanho da janela

    glutCreateWindow("Desenho de um pixel");        //Nome da janela

    init(2);       //clear display and define size of dot
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