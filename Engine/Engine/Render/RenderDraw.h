#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class RenderDraw
{
public:
	
	static RenderDraw* Instance();
	void Initialize();

	void Creat_FrameBuffer();
	void Bind_Framebuffer();
	void Unbinde_Frambuffer();
	void Rescale_frambuffer(float width, float height); // Rescale the frame buffer to the window size

private:
	GLuint FBO; // Frame Buffer Object
	GLuint RBO; // Render Buffer Object
	RenderDraw() = default; // Private constructor for singleton pattern
	RenderDraw(const RenderDraw&) = delete; // Delete copy constructor
	RenderDraw& operator=(const RenderDraw&) = delete; // Delete assignment operator

};

