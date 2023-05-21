#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>


void drawCircle(float cx, float cy, float r, int num_segments)
{
    float theta = 3.1415926 * 2 / float(num_segments);
    float tangetial_factor = tanf(theta);//calculate the tangential factor 

    float radial_factor = cosf(theta);//calculate the radial factor 

    float x = r;//we start at angle = 0 

    float y = 0;
    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++)
    {
        glVertex2f(x + cx, y + cy);//output vertex 

        //calculate the tangential vector 
        //remember, the radial vector is (x, y) 
        //to get the tangential vector we flip those coordinates and negate one of them 

        float tx = -y;
        float ty = x;

        //add the tangential vector 

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        //correct using the radial factor 

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

void Draw(void)
{   
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.5, 0.5);
    drawCircle(250, 250, 100, 360);
}

int main(int argc, char** argv)
{   
    short int screenWidth = 1000;
    short int screenHeight = 700;
    // Positioning window in the middle of screen
    short int screenXPosition = 960 - .5*screenWidth;
    short int screenYPosition = 540 - .5*screenHeight;


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(screenXPosition, screenYPosition);
    glutCreateWindow("Engine");
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}