#include <iostream>
#include <GLFW/glfw3.h>

// Обработчик изменения размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Обработчик ошибок GLFW
void error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

int main() {
    std::cout << "Starting OpenGL application..." << std::endl;
    
    // Устанавливаем обработчик ошибок
    glfwSetErrorCallback(error_callback);
    
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    // Настройка GLFW (используем совместимый профиль)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    
    // Создание окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "PTMS Project - OpenGL Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Делаем контекст текущим
    glfwMakeContextCurrent(window);
    
    // Устанавливаем обработчик изменения размера
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLFW version: " << glfwGetVersionString() << std::endl;
    std::cout << "Application started successfully!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  - ESC: Exit application" << std::endl;
    std::cout << "  - F11: Toggle fullscreen" << std::endl;
    
    // Основной цикл приложения
    while (!glfwWindowShouldClose(window)) {
        // Обработка ввода
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        
        if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS) {
            static bool fullscreen = false;
            fullscreen = !fullscreen;
            
            if (fullscreen) {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            } else {
                glfwSetWindowMonitor(window, nullptr, 100, 100, 800, 600, 0);
            }
            
            // Ждем, чтобы избежать множественного переключения
            glfwWaitEventsTimeout(0.5);
        }
        
        // Очистка экрана
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Рисуем простой треугольник (старый стиль OpenGL)
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);  // Красный
        glVertex3f(-0.5f, -0.5f, 0.0f);
        
        glColor3f(0.0f, 1.0f, 0.0f);  // Зеленый
        glVertex3f(0.5f, -0.5f, 0.0f);
        
        glColor3f(0.0f, 0.0f, 1.0f);  // Синий
        glVertex3f(0.0f, 0.5f, 0.0f);
        glEnd();
        
        // Рисуем квадрат
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f);  // Желтый
        glVertex3f(-0.8f, -0.8f, 0.0f);
        glVertex3f(-0.6f, -0.8f, 0.0f);
        glVertex3f(-0.6f, -0.6f, 0.0f);
        glVertex3f(-0.8f, -0.6f, 0.0f);
        glEnd();
        
        // Обмен буферов
        glfwSwapBuffers(window);
        
        // Обработка событий
        glfwPollEvents();
    }
    
    // Очистка ресурсов
    glfwDestroyWindow(window);
    glfwTerminate();
    
    std::cout << "Application closed successfully!" << std::endl;
    return 0;
}