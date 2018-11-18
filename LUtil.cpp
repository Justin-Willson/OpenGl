#include "LUtil.h"

//The current color rendering mode
int gColorMode = COLOR_MODE_CYAN;

float gMoveVert = 0.f;
float gMoveHorz = 0.f;

//Viewport mode
int gViewportMode = VIEWPORT_MODE_FULL;

//The projection scale
GLfloat gProjectionScale = 1.f;

bool initGL()
{
    //Set the viewport
    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0 );

    //Init Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.1f, 0.1f, 0.1f, 0.1f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );

    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Move to center of the screen
    glTranslatef( (SCREEN_WIDTH * gProjectionScale) / 2.f, (SCREEN_HEIGHT * gProjectionScale) / 2.f, 0.f );

    //Full View
    if( gViewportMode == VIEWPORT_MODE_FULL )
    {
        //Fill the screen
        glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
            glVertex2f( -SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
        glEnd();
    }
    else if( gViewportMode == VIEWPORT_MODE_HALF_CENTER )
    {
        //Center viewport
        glViewport( SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 4.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );

        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
            glVertex2f( -SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
        glEnd();
    }
    else if( gViewportMode == VIEWPORT_MODE_HALF_TOP )
    {
        //Viewport at top
        glViewport( SCREEN_WIDTH / 4.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f ); 

        glBegin( GL_QUADS );
            glColor3f( 0.f, 0.f, 1.f );
            glVertex2f( -SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f, -SCREEN_HEIGHT / 2.f );
            glVertex2f(  SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
            glVertex2f( -SCREEN_WIDTH / 2.f,  SCREEN_HEIGHT / 2.f );
        glEnd();
    }
    else if( gViewportMode == VIEWPORT_MODE_QUAD )
    {
        //Bottom left red quad
        glViewport( 0.f, 0.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
            glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
        glEnd();

        //Bottom right green quad
        glViewport( SCREEN_WIDTH / 2.f, 0.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
            glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
        glEnd();

        //Top left blue quad
        glViewport( 0.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 0.f, 0.f, 1.f );
            glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
            glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
        glEnd();

        //Top right yellow quad
        glViewport( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
            glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
        glEnd();
    }
    //Viewport with radar subview port
    else if( gViewportMode == VIEWPORT_MODE_RADAR )
    {
        //Full size quad
        glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 1.f );
            glVertex2f( -SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f );
            glVertex2f(  SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f );
            glVertex2f(  SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f );
            glVertex2f( -SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f );
            glColor3f( 0.f, 0.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f );
            glVertex2f(  SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f );
            glVertex2f(  SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f );
            glVertex2f( -SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f );
        glEnd();

        //Radar quad
        glViewport( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f );
        glBegin( GL_QUADS );
            glColor3f( 1.f, 1.f, 1.f );
            glVertex2f( -SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f );
            glVertex2f(  SCREEN_WIDTH / 8.f, -SCREEN_HEIGHT / 8.f );
            glVertex2f(  SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f );
            glVertex2f( -SCREEN_WIDTH / 8.f,  SCREEN_HEIGHT / 8.f );
            glColor3f( 0.f, 0.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f );
            glVertex2f(  SCREEN_WIDTH / 16.f, -SCREEN_HEIGHT / 16.f );
            glVertex2f(  SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f );
            glVertex2f( -SCREEN_WIDTH / 16.f,  SCREEN_HEIGHT / 16.f );
        glEnd();
    }
    //Update screen
    glutSwapBuffers();
}

void handleKeys( unsigned char key, int x, int y )
{
    //If the user presses q
    if( key == 'q' )
    {
        //Cycle through viewport modes
        gViewportMode++;
        if( gViewportMode > VIEWPORT_MODE_RADAR )
        {
            gViewportMode = VIEWPORT_MODE_FULL;
        }
    }
}