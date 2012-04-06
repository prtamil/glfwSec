#include "renderer.h"

namespace
{

GLuint program_id;
GLuint vbo_id;
GLuint vao_id;
GLuint index_id;

GLuint uniform_mvp;
GLuint uniform_diffuse;
GLuint uniform_time;
};



bool init_Program()
{
    bool bValidated = true;
    if(bValidated)
    {
        GLuint vertex_shader = createShader(GL_VERTEX_SHADER,"./vertex.glsl");
        GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER,"./fragment.glsl");

        program_id = glCreateProgram();
        glAttachShader(program_id,vertex_shader);
        glAttachShader(program_id,fragment_shader);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glLinkProgram(program_id);

        bValidated = checkProgram(program_id);
    }
    if(bValidated)
    {
        uniform_mvp = glGetUniformLocation(program_id,"MVP");
        uniform_diffuse = glGetUniformLocation(program_id,"Diffuse");
        uniform_time = glGetUniformLocation(program_id,"Time_t");
    }
    return bValidated && checkError("init_Program");
}

bool init_Buffers()
{
    float fVertex[]={
        -1.0f,1.0f,
        1.0f,1.0f,
        -1.0f,-1.0f,
    };

    GLubyte ubIndex[]={
        0,1,2
    };

    glGenVertexArrays(1,&vao_id);
    glBindVertexArray(vao_id);

    glGenBuffers(1,&vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_id);
    glBufferData(GL_ARRAY_BUFFER,sizeof(fVertex),fVertex,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenBuffers(1,&index_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(ubIndex),ubIndex,GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER,vbo_id);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);

    return checkError("init_buffer");

}

bool InitGL(void)
{
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(0.0f);

    if(!initGLEW())
    {
        std::cout<<"Glew Error\n";
        glfwTerminate();
    }
    bool bValidated = true;
    if(bValidated)
        bValidated = init_Program();
    if(bValidated)
        bValidated = init_Buffers();

    if(!bValidated)
    {
        std::cout<<"Error";
        checkError("initializeGL");
        exit(0);
    }
 return bValidated;
}

void Delete_GL()
{
    glDeleteProgram(program_id);
    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vao_id);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glDeleteBuffers(1,&vbo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glDeleteBuffers(1,&index_id);
    glUseProgram(0);
    checkError("end");
}

void PaintGL(double time)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    draw(time);

}

void Translate(float x,float y,float z)
{
    glm::mat4 proj_Matrix = glm::perspective<float>(45.0f,4.0/3.0f,0.1f,100.0f);
    glm::mat4 view_Translate_Matrix = glm::translate(glm::mat4(1.0f),
                                                     glm::vec3(x,y,z));
    glm::mat4 view_Matrix = glm::rotate(view_Translate_Matrix,
                                        45.0f,
                                        glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 model_Matrix = glm::mat4(1.0f);
    glm::mat4 MVP = proj_Matrix * view_Matrix * model_Matrix;
    glProgramUniformMatrix4fv(program_id,
                              uniform_mvp,
                              1,
                              GL_FALSE,
                              &MVP[0][0]);
}

void draw(double time)
{



    glProgramUniform4fv(program_id,uniform_diffuse,1,
                        &glm::vec4(1.0f,0.5f,0.0f,1.0f)[0]);


   glProgramUniform1f(program_id,uniform_time,(float)time);

    float fDepth(1.0f);
    glClearBufferfv(GL_DEPTH,0,&fDepth);
    glClearBufferfv(GL_COLOR,0,&glm::vec4(0.0f,0.0f,0.0f,1.0f)[0]);


    glUseProgram(program_id);

    glBindVertexArray(vao_id);
    checkError("Bef Draw");
    Translate(0.0f,0.0f,-10.0f);
    glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_BYTE,0);


    checkError("draw");
}
