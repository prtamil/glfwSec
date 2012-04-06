#include "glUtil.h"

bool checkError(const char *Title)
{
    int Error;

    if((Error = glGetError()) != GL_NO_ERROR)
    {
        std::string ErrorString;
        switch(Error)
        {
        case GL_INVALID_ENUM:
            ErrorString = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            ErrorString = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            ErrorString = "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            ErrorString = "GL_OUT_OF_MEMORY";
            break;
        default:
            ErrorString = "UNKNOWN";
            break;
        }
        fprintf(stdout,"OpenGL Error :%s :Title %s",ErrorString.c_str(),Title);
//	qDebug()<<"OpenGL Error:"<<ErrorString.c_str()<<" :"<<Title<<"\n";
    }
    return Error == GL_NO_ERROR;
}

bool validateProgram(GLuint ProgramName)
{
    if(!ProgramName)
        return false;


    glValidateProgram(ProgramName);
    GLint Result = GL_FALSE;
    glGetProgramiv(ProgramName, GL_VALIDATE_STATUS, &Result);

    if(Result == GL_FALSE)
    {
        fprintf(stdout, "Validate program\n");
        int InfoLogLength;
        glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> Buffer(InfoLogLength);
        glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
        fprintf(stdout, "%s\n", &Buffer[0]);

    }

    return Result == GL_TRUE;
}

bool checkProgram(GLuint ProgramName)
{
    if(!ProgramName)
        return false;

    GLint Result = GL_FALSE;
    glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);

    fprintf(stdout, "Linking program\n");
    int InfoLogLength;
    glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> Buffer(std::max(InfoLogLength, int(1)));
    glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
    fprintf(stdout, "%s\n", &Buffer[0]);

    return Result == GL_TRUE;
}

bool checkShader(GLuint ShaderName, const char *Source)
{
    if(!ShaderName)
        return false;

    GLint Result = GL_FALSE;
    glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Result);

    fprintf(stdout, "Compiling shader\n%s...\n", Source);
    int InfoLogLength;
    glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> Buffer(InfoLogLength);
    glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
    fprintf(stdout, "%s\n", &Buffer[0]);


    return Result == GL_TRUE;
}




bool checkExtension(char const * String)
{
    GLint ExtensionCount = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
    for(GLint i = 0; i < ExtensionCount; ++i)
        if(std::string((char const*)glGetStringi(GL_EXTENSIONS, i)) == std::string(String))
            return true;
    return false;
}
GLuint  createShader(GLenum Type,std::string const & Source)
{
    bool bValidated = true;
    GLuint Name = 0;

    if(!Source.empty())
    {
        std::string SourceContent = loadFile(Source);
        char const * SourcePointer = SourceContent.c_str();
        Name = glCreateShader(Type);
        glShaderSource(Name, 1, &SourcePointer, NULL);
        glCompileShader(Name);
        bValidated = checkShader(Name, SourcePointer);
    }

    return Name;
}

std::string loadFile(std::string const & Filename)
{
    std::ifstream stream(Filename.c_str(), std::ios::in);

    if(!stream.is_open())
        return "";

    std::string Line = "";
    std::string Text = "";

    while(getline(stream, Line))
        Text += "\n" + Line;

    stream.close();

    return Text;
}

bool initGLEW()
{
        bool bRet = false;
        GLenum err = glewInit();
        if(err == GLEW_OK )
            bRet = true;
        if(bRet && GLEW_VERSION_3_3)
            bRet = true;
        if(bRet)
            bRet = glewGetExtension("GL_ARB_shader_objects");
        bRet = bRet && checkExtension("GL_ARB_viewport_array");
        bRet = bRet && checkExtension("GL_ARB_separate_shader_objects");
        return  bRet;
}
