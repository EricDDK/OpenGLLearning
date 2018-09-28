#include "Shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件到流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件
		vShaderFile.close();
		fShaderFile.close();
		//流转字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "错误，读取文件失败，请检查文件" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertex,512,NULL,infoLog);
		std::cout << "vertext shader init fail , info is " << infoLog << std::endl;
	}

	//片元着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "fragment shader init fail , info is " << infoLog << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID,fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID,GL_LINK_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "compile shader init fail , info is " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);


	////创建、附加、链接。
	////！创建、编译我们的着色器程序
	////顶点着色器
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////将源码附加到着色器对象上并且编译这个着色器对象
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////片元着色器
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//////片源着色器1
	////int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	////glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	////glCompileShader(fragmentShader1);
	////链接着色器
	//int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	///*int shaderProgram1 = glCreateProgram();
	//glAttachShader(shaderProgram1, vertexShader);
	//glAttachShader(shaderProgram1, fragmentShader1);
	//glLinkProgram(shaderProgram1);*/
	////别忘了释放着色器
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	////glDeleteShader(fragmentShader1);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
