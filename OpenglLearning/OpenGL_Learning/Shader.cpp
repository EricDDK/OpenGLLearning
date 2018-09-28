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
		//��ȡ�ļ�������
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();
		//��ת�ַ���
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "���󣬶�ȡ�ļ�ʧ�ܣ������ļ�" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertex,512,NULL,infoLog);
		std::cout << "vertext shader init fail , info is " << infoLog << std::endl;
	}

	//ƬԪ��ɫ��
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


	////���������ӡ����ӡ�
	////���������������ǵ���ɫ������
	////������ɫ��
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////��Դ�븽�ӵ���ɫ�������ϲ��ұ��������ɫ������
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	////ƬԪ��ɫ��
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//////ƬԴ��ɫ��1
	////int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	////glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
	////glCompileShader(fragmentShader1);
	////������ɫ��
	//int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	///*int shaderProgram1 = glCreateProgram();
	//glAttachShader(shaderProgram1, vertexShader);
	//glAttachShader(shaderProgram1, fragmentShader1);
	//glLinkProgram(shaderProgram1);*/
	////�������ͷ���ɫ��
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
