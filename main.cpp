#include "renderer.h"

int main( void )
{
    int width, height, x;
    double t;
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( 640, 480, 0,0,0,0, 0,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );

        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    glfwSetWindowTitle( "Spinning Triangle" );
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 1 );
    //Initialize OpenGL Shaders/Buffers/GLEW etc..
    InitGL();
    do
    {
        t = glfwGetTime();
        glfwGetMousePos( &x, NULL );
        glfwGetWindowSize( &width, &height );
        // Special case: avoid division by zero below
        height = height > 0 ? height : 1;
        PaintGL(t);
        glfwSwapBuffers();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
           glfwGetWindowParam( GLFW_OPENED ) );
    //Clear Buffers/Shaders etc..
    Delete_GL();
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    exit( EXIT_SUCCESS );
}

