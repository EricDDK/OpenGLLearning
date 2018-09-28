#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// 设置
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

//顶点着色代码
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = vec3(0.5f, 0.0f, 0.0f);\n"
"}\0";	//千万别忘记这个\0

//片元着色器代码
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(ourColor, 1.0f);\n"
"}\0";	//千万别忘记这个\0

float vertices[] = {
	//位置				//颜色
	-0.5f, -0.5f, 0.0f, //1.0f, 0.0f, 0.0f,		//左
	0.5f, -0.5f, 0.0f,	//0.0f, 1.0f, 0.0f,		//右
	0.0f, 0.5f, 0.0f//,	0.0f, 0.0f, 1.0f		//上
};

//float rectVertices[] = {
//	0.5f, 0.5f, 0.0f,		//右上角
//	0.5f, -0.5f, 0.0f,		//右下角
//	-0.5f, -0.5f, 0.0f,		//左下角
//	-0.5f, 0.5f, 0.0f		//左上角
//};
//
//unsigned int indices[] = {
//	0, 1, 3,		//第一个三角形
//	1, 2, 3			//第二个三角形
//};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//获取最大属性数量
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "最大支持的属性数量为：" << nrAttributes << std::endl;

	//！创建、编译我们的着色器程序
	//顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//检查着色器是否编译成功
	int success;
	char infoLog[512] = { 0 };
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "错误：顶点着色器编译失败！" << std::endl;
	}

	//片元着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//检查着色器是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "错误：片元着色器编译失败！" << std::endl;
	}

	//链接着色器
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//第一个环境
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, /*6 * sizeof(float)*/0, (void*)0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//第二个环境
	//unsigned int VBO1, VAO1;
	//glGenVertexArrays(1, &VAO1);
	//glBindVertexArray(VAO1);
	//
	//glGenBuffers(1, &VBO1);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / 2, vertices + 9, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);

	//unsigned int EBO;
	//glGenBuffers(1, &EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int outColorLocation = glGetUniformLocation(shaderProgram, "outColor");
		glUseProgram(shaderProgram);
		//glUniform4f(outColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		/*
		* 这里是一个习惯，上面的操作把属性都保存到了VAO中，这里只需要绑定就可以
		* 如果要显示的东西不同，也只需要在这里绑定不同的东西就可以显示
		*/
		glBindVertexArray(VAO);	
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//glUseProgram(shaderProgram1);
		//glBindVertexArray(VAO1);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
