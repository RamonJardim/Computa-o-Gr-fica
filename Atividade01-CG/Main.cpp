#define GLEW_STATIC
#define GLFW_INCLUDE_NONE



#include <GLFW/glfw3.h>
#include <GL/glew.h>


#include <fstream>
#include <sstream>


#include <iostream>

using namespace std;

float xVariation = 0.0f;
float yVariation = 0.0f;

struct Vertex {
	float x, y, r, g, b;
};

string readFile(string filename) {
	ifstream t(filename);
	stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}

void prepareShaders(Vertex v[])
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));

	glVertexPointer(2, GL_FLOAT, 0, nullptr);
	glEnableClientState(GL_VERTEX_ARRAY);


	string vss = readFile("vertex.sdr");
	string fss = readFile("fragment.sdr");
	const char* vertexShaderText = vss.c_str();
	const char* fragmentShaderText = fss.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

int askUser() {
	int choice;
	do {
		cout << "1 - Parte 1." << endl;
		cout << "2 - Parte 2." << endl;

		cin >> choice;
	} while (choice < 1 || choice > 2);

	return choice;
}

GLFWwindow* createWindow()
{
	GLFWwindow* window;
	/* Inicializa a biblioteca */
	if (!glfwInit())
		return NULL;
	/* Cria uma janela com contexto OpenGL */
	window = glfwCreateWindow(1280, 960, "Atividade 01", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return NULL;
	}
	/* Ativa o contexto OpenGL na janela */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		cout << "Erro ao iniciar GLEW";
		return NULL;
	}

	return window;
}


int parte1()
{
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return -1;

	Vertex v[] =
	{
		//x, y, r, g, b
		{+0.0f, +0.5f, 1.0f, 0.0f, 0.0	},
		{-0.5f, -0.5f, 0.0f, 1.0f, 0.0	},
		{+0.5f, -0.5f, 0.0f, 0.0f, 1.0	}
	};

	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	prepareShaders(v);

	/* Roda até que o usuário feche a janela */
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		/* Código de renderização OpenGL vai aqui */
		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);

		/* Captura e trata eventos do teclado */
		glfwPollEvents();

		//glEnd();
	}
	glfwTerminate();
	return 0;
}


int parte2()
{
	GLFWwindow* window = createWindow();
	if (window == NULL)
		return -1;

	Vertex v[] =
	{
		//x, y, r, g, b
		{0.0f, 0.0f, 1.0f, 1.0f, 1.0	},

		// Top
		{-0.2f, 0.8f, 0.0f, 1.0f, 0.0	},
		{ 0.2f, 0.8f, 0.0f, 0.0f, 1.0	},
		{ 0.0f, 0.8f, 0.0f, 1.0f, 1.0	},
		{ 0.0f, 1.0f, 1.0f, 0.0f, 0.0	},

		// Bottom
		{-0.2f, -0.8f, 0.0f, 0.0f, 1.0	},
		{ 0.2f, -0.8f, 0.0f, 1.0f, 0.0	},
		{ 0.0f, -0.8f, 0.0f, 1.0f, 1.0	},
		{ 0.0f, -1.0f, 1.0f, 0.0f, 0.0	},

		// Left
		{-0.8f, -0.2f, 0.0f, 1.0f, 0.0	},
		{-0.8f,  0.2f, 0.0f, 0.0f, 1.0	},
		{-0.8f,  0.0f, 0.0f, 1.0f, 1.0	},
		{-1.0f,  0.0f, 1.0f, 0.0f, 0.0	},

		// Right
		{0.8f, -0.2f, 0.0f, 0.0f, 1.0	},
		{0.8f,  0.2f, 0.0f, 1.0f, 0.0	},
		{0.8f,  0.0f, 0.0f, 1.0f, 1.0	},
		{1.0f,  0.0f, 1.0f, 0.0f, 0.0	},
	};

	GLuint VBO1;
	glGenBuffers(1, &VBO1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

	prepareShaders(v);

	unsigned short ind[] = {
		// Top
		0, 1, 3,
		0, 3, 2,
		3, 1, 4,
		3, 4, 2,

		// Bottom
		0, 5, 7,
		0, 7, 6,
		7, 5, 8,
		7, 8, 6,

		// Left
		0, 9, 11,
		0, 11, 10,
		11, 9, 12,
		11, 12, 10,

		// Right
		0, 13, 15,
		0, 15, 14,
		15, 13, 16,
		15, 16, 14
	};

	GLuint myIBO;
	glGenBuffers(1, &myIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);

	/* Roda até que o usuário feche a janela */
	while (!glfwWindowShouldClose(window))
	{

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		/* Código de renderização OpenGL vai aqui */
		glDrawElements(GL_TRIANGLES, 48, GL_UNSIGNED_SHORT, (GLvoid*)0);

		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);

		/* Captura e trata eventos do teclado */
		glfwPollEvents();

		//glEnd();
	};
	glfwTerminate();
	return 0;
}

int main(void)
{
	while (true)
	{
		int choice = askUser();
		if (choice == 1)
			parte1();
		else
			parte2();
	}
}