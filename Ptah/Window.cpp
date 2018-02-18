#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Engine.h"

#include "Events/EventTypes/EventKeyPressed.h"
#include "Events/EventTypes/EventMouseClicked.h"
#include "Events/EventTypes/EventMouseScrolled.h"
#include "Events/EventTypes/EventCursorMoved.h"
#include "Events/EventTypes/EventWindowResized.h"

Ptah::Window::Window(): window_(nullptr)
{
}

Ptah::Window::~Window()
{
	Close();
}

void Ptah::Window::key_callback_internal(GLFWwindow* glfw_window, const int key, const int scancode, const int action, const int mods)
{
	const auto data = glfwGetWindowUserPointer(glfw_window);
	const auto window = static_cast<Ptah::Window*>(data);

	auto ev = new EventKeyPressed(key, scancode, action, mods);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(ev);
}

void Ptah::Window::cursor_pos_callback_internal(GLFWwindow* glfw_window, const double mouse_x, const double mouse_y)
{
	const auto data = glfwGetWindowUserPointer(glfw_window);
	const auto window = static_cast<Ptah::Window*>(data);

	auto ev = new EventCursorMoved(mouse_x, mouse_y);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(ev);
}

void Ptah::Window::mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods)
{
	const auto data = glfwGetWindowUserPointer(glfw_window);
	const auto window = static_cast<Ptah::Window*>(data);

	auto ev = new EventMouseClicked(button, action, mods);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(ev);
}

void Ptah::Window::mouse_scroll_callback(GLFWwindow* glfw_window, double offset_x, double offset_y)
{
	const auto data = glfwGetWindowUserPointer(glfw_window);
	const auto window = static_cast<Ptah::Window*>(data);

	auto ev = new EventMouseScrolled(offset_x, offset_y);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(ev);
}

void Ptah::Window::window_resize_callback(GLFWwindow* glfw_window, int width, int height)
{
	const auto data = glfwGetWindowUserPointer(glfw_window);
	const auto window = static_cast<Ptah::Window*>(data);

	auto ev = new EventWindowResized(width, height);
	Engine::Instance().GetEventDispatcher()->DispatchEvent(ev);
}

void Ptah::Window::Create()
{
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, is_resizable ? GL_TRUE : GL_FALSE);

	window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
	glfwSetWindowUserPointer(window_, this);

	glfwSetKeyCallback(window_, key_callback_internal);
	glfwSetCursorPosCallback(window_, cursor_pos_callback_internal);
	glfwSetMouseButtonCallback(window_, mouse_button_callback);
	glfwSetScrollCallback(window_, mouse_scroll_callback);
	glfwSetWindowSizeCallback(window_, window_resize_callback);
}

void Ptah::Window::MakeCurrent() const
{
	glfwMakeContextCurrent(window_);
}

void Ptah::Window::SwapBuffers() const
{
	glfwSwapBuffers(window_);
}

int Ptah::Window::GetKey(const int key) const
{
	return glfwGetKey(window_, key);
}

void Ptah::Window::GetCursorPos(double *x, double *y) const
{
	return glfwGetCursorPos(window_, x, y);
}

void Ptah::Window::SetTitle(const char* title) const
{
	glfwSetWindowTitle(window_, title);
}

void Ptah::Window::Resize(const int width, const int height) const
{
	glfwSetWindowSize(window_, width, height);
}

void Ptah::Window::Close() const
{
	glfwSetWindowShouldClose(window_, GL_TRUE);
}

bool Ptah::Window::ShouldClose() const
{
	return glfwWindowShouldClose(window_) == GL_TRUE;
}
