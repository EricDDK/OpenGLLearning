#include "glad.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "KHR/khrplatform.h"
#include "iostream"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//������ɫ����
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec3 outColor;"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	outColor = vec3(0.5f, 0.0f, 0.0f);\n"
"}\0";	//ǧ����������\0

//ƬԪ��ɫ������
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"in vec3 outColor;\n"
"uniform vec4 outColor;\n"
"void main()\n"
"{\n"
"	FragColor = outColor;\n"
"}\0";	//ǧ����������\0

////ƬԪ��ɫ������1
//const char* fragmentShaderSource1 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
//"}\0";	//ǧ����������\0

float vertices[] = {
	-0.5f, -0.5f, 0.0f,		//��
	0.5f, -0.5f, 0.0f,		//��
	0.0f, 0.5f, 0.0f,		//��
	1.0f, 0.0f, 0.0f,
	0.75f, 0.5f, 0.0f,
	0.5, 0.0f, 0.0f
};
float rectVertices[] = {
	0.5f, 0.5f, 0.0f,   //���Ͻ�
	0.5f, -0.5f, 0.0f,  //���½�
	-0.5f, -0.5f, 0.0f, //���½�
	-0.5f, 0.5f, 0.0f   //���Ͻ�
};
unsigned int indices[] = {
	0, 1, 3,    //��һ��������
	1, 2, 3 //�ڶ���������
};

// ���ó���
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GL window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//��ȡ�����������
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "���֧�ֵ���������Ϊ��" << nrAttributes << std::endl;

	//���������ǵ���ɫ��
	Shader shader("Shader.vs", "Shader.ff");

	//��һ��
	unsigned int VBO, VAO;
	//VAO �����������,����Զ������Եĵ���
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);  //����ΨһID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //ָ��Ϊ���㻺��
	//����1�����ǵĶ���������Ҫ�������ĵط�����֮ǰ���ǰ󶨵�VBO��
	//����2������Ĵ�С
	//����3������ĵ�ַ
	//����4��ָ���Կ�Ҫ����ʲô��ʽ���������ǵ����ݣ�GL_STATIC_DRAW��ʾ��Щ���ݲ��ᾭ���ı䡣
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, vertices, GL_STATIC_DRAW);  //���������ݸ��Ƶ�VBO
	//ָ�������ʽ
	//��ʼ�����ƫ��Ϊ0��ÿ��λ�÷���ռ��4�ֽڵĿռ䣬һ������ռ��12�ֽڿռ䡣��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//////�ڶ���
	////unsigned int VBO1, VAO1;
	////glGenVertexArrays(1, &VAO1);
	////glBindVertexArray(VAO1);
	////glGenBuffers(1, &VBO1);  //����ΨһID
	////glBindBuffer(GL_ARRAY_BUFFER, VBO1);  //ָ��Ϊ���㻺��
	////glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);
	////glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	////glEnableVertexAttribArray(0);

	///*unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	/*	float greenValue = 1.0f;
		int outColorLocation = glGetUniformLocation(shaderProgram, "outColor");
		glUniform4f(outColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glUseProgram(shaderProgram);*/

		shader.use();

		/*
		* ������һ��ϰ�ߣ�����Ĳ��������Զ����浽��VAO�У�����ֻ��Ҫ�󶨾Ϳ���
		* ���Ҫ��ʾ�Ķ�����ͬ��Ҳֻ��Ҫ������󶨲�ͬ�Ķ����Ϳ�����ʾ
		*/
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/*glUseProgram(shaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);*/

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &VBO1);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}