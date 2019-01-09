#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "samples/SampleManager.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 800;

static GLFWwindow* CreateGLWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OGLPS", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}

int main()
{
	GLFWwindow* window = CreateGLWindow();
	if (window == nullptr)
	{
		return 0;
	}

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER interval;
	interval.QuadPart = (LONGLONG)(1.0f / 60 * freq.QuadPart);

	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);

	LONGLONG frameInterval = 0LL;
	LONG waitMS = 0L;

	// render loop
	SampleManager manager;
	while (!glfwWindowShouldClose(window))
	{
		QueryPerformanceCounter(&nNow);
		frameInterval = nNow.QuadPart - nLast.QuadPart;
		if (frameInterval >= interval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart;
			// render
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// input
			int pressKey = processInput(window);

			manager.DrawSample(pressKey);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		else
		{
			// The precision of timer on Windows is set to highest (1ms) by 'timeBeginPeriod' from above code,
			// but it's still not precise enough. For example, if the precision of timer is 1ms,
			// Sleep(3) may make a sleep of 2ms or 4ms. Therefore, we subtract 1ms here to make Sleep time shorter.
			// If 'waitMS' is equal or less than 1ms, don't sleep and run into next loop to
			// boost CPU to next frame accurately.
			waitMS = (interval.QuadPart - frameInterval) * 1000LL / freq.QuadPart - 1L;
			if (waitMS > 1L)
				Sleep(waitMS);
		}
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);*/

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
int processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		std::cout << "key 1 has been pressed!" << std::endl;
		return GLFW_KEY_1;
	}

	return -1;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}