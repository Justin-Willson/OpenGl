#include "LUtil.h"

//The current color rendering mode
int gColorMode = COLOR_MODE_CYAN;

float gMoveVert = 0.f;
float gMoveHorz = 0.f;

//The projection scale
GLfloat gProjectionScale = 1.f;

bool initGL()
{
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
    glTranslatef( SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f, 0.f );

    //Render quad
    if( gColorMode == COLOR_MODE_CYAN )
    {
        //Solid Cyan
        glBegin( GL_QUADS );
            glColor3f( 0.f, 1.f, 1.f );
            glVertex2f( -50.f + gMoveHorz, -50.f + gMoveVert);
            glVertex2f(  50.f + gMoveHorz, -50.f + gMoveVert);
            glVertex2f(  50.f + gMoveHorz,  50.f + gMoveVert);
            glVertex2f( -50.f + gMoveHorz,  50.f + gMoveVert);
        glEnd();
    }
    else
    {
        //RYGB Mix
        glBegin( GL_QUADS );
            glColor3f( 1.f, 0.f, 0.f ); glVertex2f( -50.f + gMoveHorz, -50.f + gMoveVert);
            glColor3f( 1.f, 1.f, 0.f ); glVertex2f(  50.f + gMoveHorz, -50.f + gMoveVert);
            glColor3f( 0.f, 1.f, 0.f ); glVertex2f(  50.f + gMoveHorz,  50.f + gMoveVert);
            glColor3f( 0.f, 0.f, 1.f ); glVertex2f( -50.f + gMoveHorz,  50.f + gMoveVert);
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
        //Toggle color mode
        if( gColorMode == COLOR_MODE_CYAN )
        {
            gColorMode = COLOR_MODE_MULTI;
        }
        else
        {
            gColorMode = COLOR_MODE_CYAN;
        }
    }
    else if( key == 'e' )
    {
        //Cycle through projection scales
        if( gProjectionScale == 1.f )
        {
            //Zoom out
            gProjectionScale = 2.f;
        }
        else if( gProjectionScale == 2.f )
        {
            //Zoom in
            gProjectionScale = 3.f;
        }
        else if( gProjectionScale == 3.f )
        {
            //Zoom in
            gProjectionScale = 0.25f;
        }
        else if( gProjectionScale == 0.25f )
        {
            //Regular zoom
            gProjectionScale = 0.5f;
        }
        else if( gProjectionScale == 0.5f )
        {
            //Regular zoom
            gProjectionScale = 1.f;
        }

        //Update projection matrix
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        glOrtho( 0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale, 0.0, 1.0, -1.0 );
    }
    else if( key == 'w' )
    {
        gMoveVert -= 10.f * gProjectionScale;
    }
    else if( key == 's' )
    {
        gMoveVert += 10.f * gProjectionScale;
    }
    else if( key == 'd' )
    {
        gMoveHorz += 10.f * gProjectionScale;
    }
    else if( key == 'a' )
    {
        gMoveHorz -= 10.f * gProjectionScale;
    }
}