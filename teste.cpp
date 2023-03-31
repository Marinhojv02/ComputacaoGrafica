#include <GL/glut.h>
#include <cmath>
void drawPixel(int x, int y, int size, float r, float g, float b) {
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(y, x, 0);
    glutSolidSphere(size/2.f, 50, 50);
    glPopMatrix();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPixel(200, 200, 1, 0, 0, 0);
    glutSwapBuffers();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("DrawPixel");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 400, 400, 0, -1, 1);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}