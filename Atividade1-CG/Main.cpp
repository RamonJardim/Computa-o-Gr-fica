#define GLEW_STATIC
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <locale.h>
#include <cstdlib>
#include <iostream>

using namespace std;

const int resX = 1280;
const int resY = 960;

float xVariation = 0.0f;
float yVariation = 0.0f;

const float triangleSize = 0.1f;

enum class Direction {
	VERTICAL,
	HORIZONTAL,
	DIAGONAL
};

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_LEFT) xVariation -= 0.01f;
	if (key == GLFW_KEY_RIGHT) xVariation += 0.01f;
	if (key == GLFW_KEY_UP) yVariation += 0.01f;
	if (key == GLFW_KEY_DOWN) yVariation -= 0.01f;
}

GLFWwindow* generateWindow(int resolX, int resolY) {
	GLFWwindow* window;
	/* Inicializa a biblioteca */
	if (!glfwInit())
		return NULL;

	/* Cria uma janela com contexto OpenGL */
	window = glfwCreateWindow(resX, resY, "Hello World", NULL, NULL);
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

int askUser() {
	int choice;
	do {
		cout << "1 - Controlar triangulo com o teclado." << endl;
		cout << "2 - Animação triângulo na horizontal." << endl;
		cout << "3 - Animação triângulo na vertical." << endl;
		cout << "4 - Animação triângulo batendo nas extremidades." << endl << endl;

		cin >> choice;
	} while (choice < 1 || choice > 4);

	return choice;
}

void triangleKeyboardControl(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);

	/* Roda até que o usuário feche a janela */
	while (!glfwWindowShouldClose(window))
	{
		/* Código de renderização OpenGL vai aqui */
		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);


		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		//Definimos o estado de montagem de triângulos
		glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex2f(-triangleSize + xVariation, -triangleSize + yVariation);
		glColor3f(1, 1, 1);
		glVertex2f(0.0f + xVariation, triangleSize + yVariation);
		glColor3f(0, 1, 1);
		glVertex2f(triangleSize + xVariation, -triangleSize + yVariation);

		glEnd();

		/* Captura e trata eventos do teclado */
		glfwPollEvents();
	}
	xVariation = 0;
	yVariation = 0;
	glfwTerminate();
}

void animateTriangle(GLFWwindow* window, Direction d) {
	/* Roda até que o usuário feche a janela */
	float multiplierX = 1.0f;
	float multiplierY = 1.0f;

	if (d == Direction::DIAGONAL)
	{
		multiplierX += rand() / (3.0 * RAND_MAX);
		multiplierY += rand() / (3.0 * RAND_MAX);
	}


	while (!glfwWindowShouldClose(window))
	{
		/* Código de renderização OpenGL vai aqui */
		/* Troca o buffer de fundo com o buffer de exibição */
		glfwSwapBuffers(window);


		glClear(GL_COLOR_BUFFER_BIT);
		glLoadIdentity();
		//Definimos o estado de montagem de triângulos
		glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0);
		glVertex2f(-triangleSize + xVariation, -triangleSize + yVariation);
		glColor3f(1, 1, 1);
		glVertex2f(00.f + xVariation, triangleSize + yVariation);
		glColor3f(0, 1, 1);
		glVertex2f(triangleSize + xVariation, -triangleSize + yVariation);

		glEnd();

		/* Captura e trata eventos do teclado */
		glfwPollEvents();
		if (abs(xVariation) >= 1 - triangleSize) multiplierX *= -1;
		if (abs(yVariation) >= 1 - triangleSize) multiplierY *= -1;

		if(d == Direction ::HORIZONTAL)
			xVariation += 0.005f * multiplierX;
		else if(d == Direction::VERTICAL)
			yVariation += 0.005f * multiplierY;
		else if (d == Direction::DIAGONAL)
		{
			xVariation += 0.005f * multiplierX;
			yVariation += 0.005f * multiplierY;
		}
	}
	xVariation = 0;
	yVariation = 0;
	glfwTerminate();
}


int main(void)
{
	setlocale(LC_ALL, "");
	GLFWwindow* window;
	int choice = -1;

	while (true) {
		choice = askUser();

		window = generateWindow(resX, resY);

		if (window != NULL)
		{
			switch (choice)
			{
			case 1:
				triangleKeyboardControl(window);
				break;

			case 2:
				animateTriangle(window, Direction::HORIZONTAL);
				break;

			case 3:
				animateTriangle(window, Direction::VERTICAL);
				break;

			case 4:
				animateTriangle(window, Direction::DIAGONAL);
				break;

			default:
				cout << "Escolha inválida";
				break;
			}
		}
	}

	return 0;
}