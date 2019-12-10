#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "samples/SampleManager.h"
#include <iostream>
#include "util/Def.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

static GLFWwindow* CreateGLWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OGLPS", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

	return window;
}

SampleManager* g_manager = nullptr;

int main()
{
	GLFWwindow* window = CreateGLWindow();
	if (window == nullptr)
	{
		return 0;
	}
 
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
    //glEnable(GL_DEPTH_TEST);

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER interval;
	interval.QuadPart = (LONGLONG)(1.0f / 60 * freq.QuadPart);

	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceCounter(&nLast);

	LONGLONG frameInterval = 0LL;
	LONG waitMS = 0L;

    float deltaTime = 0.f;
    float lastFrame = 0.f;
    g_manager = new SampleManager;
	while (!glfwWindowShouldClose(window))
	{
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		QueryPerformanceCounter(&nNow);
		frameInterval = nNow.QuadPart - nLast.QuadPart;
		//if (frameInterval >= interval.QuadPart)
		{
			nLast.QuadPart = nNow.QuadPart;
			
			glClearColor(0.2f, 0.4f, 0.4f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			int pressKey = processInput(window);
			g_manager->KeyPress(pressKey, deltaTime);
            g_manager->Draw(pressKey);

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		/*else
		{
			waitMS = static_cast<LONG>((interval.QuadPart - frameInterval) * 1000LL / freq.QuadPart - 1L);
            if (waitMS > 1L)
            {
                Sleep(waitMS);
            }
		}*/
	}

	glfwTerminate();
	return 0;
}

int processInput(GLFWwindow *window)
{
    int key = -1;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        return GLFW_KEY_1;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        return GLFW_KEY_2;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        key = GLFW_KEY_W;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        key = GLFW_KEY_S;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        key = GLFW_KEY_A;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        key = GLFW_KEY_D;
    }
    else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        key = GLFW_KEY_P;
    }
    
    if (key != -1)
    {
        std::cout << "key has been pressed : " << key << std::endl;
    }
    
	return key;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow*, double x, double y)
{
    g_manager->OnMouse(x, y);
}

void scroll_callback(GLFWwindow*, double x, double y)
{
    g_manager->OnScroll(x, y);
}