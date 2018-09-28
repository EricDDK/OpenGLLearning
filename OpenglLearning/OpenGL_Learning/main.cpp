#include "glad.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "KHR/khrplatform.h"
#include "iostream"
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//顶点着色代码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec3 outColor;"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	outColor = vec3(0.5f, 0.0f, 0.0f);\n"
"}\0";	//千万别忘记这个\0

//片元着色器代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
//"in vec3 outColor;\n"
"uniform vec4 outColor;\n"
"void main()\n"
"{\n"
"	FragColor = outColor;\n"
"}\0";	//千万别忘记这个\0

////片元着色器代码1
//const char* fragmentShaderSource1 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
//"}\0";	//千万别忘记这个\0

float vertices[] = {
	-0.5f, -0.5f, 0.0f,		//左
	0.5f, -0.5f, 0.0f,		//右
	0.0f, 0.5f, 0.0f,		//上
	1.0f, 0.0f, 0.0f,
	0.75f, 0.5f, 0.0f,
	0.5, 0.0f, 0.0f
};
float rectVertices[] = {
	0.5f, 0.5f, 0.0f,   //右上角
	0.5f, -0.5f, 0.0f,  //右下角
	-0.5f, -0.5f, 0.0f, //左下角
	-0.5f, 0.5f, 0.0f   //左上角
};
unsigned int indices[] = {
	0, 1, 3,    //第一个三角形
	1, 2, 3 //第二个三角形
};

// 设置长宽
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

	//获取最大属性数量
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "最大支持的属性数量为：" << nrAttributes << std::endl;

	//！创建我们的着色器
	Shader shader("Shader.vs", "Shader.ff");

	//第一个
	unsigned int VBO, VAO;
	//VAO 顶点数组对象,保存对顶点属性的调用
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);  //生成唯一ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  //指定为顶点缓存
	//参数1：我们的顶点数据需要拷贝到的地方。（之前我们绑定的VBO）
	//参数2：数组的大小
	//参数3：数组的地址
	//参数4：指定显卡要采用什么方式来管理我们的数据，GL_STATIC_DRAW表示这些数据不会经常改变。
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, vertices, GL_STATIC_DRAW);  //将顶点数据复制到VBO
	//指明顶点格式
	//起始顶点的偏移为0，每个位置分量占用4字节的空间，一个顶点占用12字节空间。是连续的
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	//////第二个
	////unsigned int VBO1, VAO1;
	////glGenVertexArrays(1, &VAO1);
	////glBindVertexArray(VAO1);
	////glGenBuffers(1, &VBO1);  //生成唯一ID
	////glBindBuffer(GL_ARRAY_BUFFER, VBO1);  //指定为顶点缓存
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
		* 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
		* 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
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