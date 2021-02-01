#pragma once

#include "Hazel/Renderer/RenderContext.h"

//  #include <GLFW/glfw3.h>
struct GLFWwindow;

namespace hazel
{
    /// <summary>
    /// The Render Context with OpenGL
    /// </summary>
    class OpenGLContext : public RenderContext
    {
    public:
        /// <summary>
        /// Create render context with OpenGL window
        /// </summary>
        /// <param name="windowHandle">Window handle with OpenGL</param>
        OpenGLContext(GLFWwindow* windowHandle);

        /// <summary>
        /// Init context from window handle; 
        /// Please check if window handle is not null before init
        /// </summary>
        virtual void Init() override;

        /// <summary>
        /// Swap the buffers in current context
        /// </summary>
        virtual void SwapBuffers() override;

    private:
        /// <summary>
        /// Window handle with OpenGL
        /// </summary>
        GLFWwindow* m_WindowHandle;
    };
}

