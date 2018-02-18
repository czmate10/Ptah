#pragma once
#include <vector>

struct GLFWwindow;

namespace Ptah
{
	class input_handler;

	class Window
	{
	public:
		bool is_resizable = false;
		int width = 800;
		int height = 600;
		const char* title = "New window";
		
		Window();

		~Window();

		/**
		 * Creates the window with the given settings
		 */
		void Create();


		/**
		 * Makes this window current for the calling thread
		 */
		void MakeCurrent() const;

		/**
		 * Swaps front- and back buffers
		 */
		void SwapBuffers() const;

		/**
		 * Returns key status for given key
		 */
		int GetKey(const int key) const;

		/**
		 * Returns the current position of the cursor
		 */
		void GetCursorPos(double *x, double *y) const;

		/**
		 * Set title of window after it's already been created
		 */
		void SetTitle(const char* title) const;

		/**
		 * Resize window after it's already been created
		 */
		void Resize(const int width, const int height) const;

		/**
		 * Closes window, but doesn't free resources
		 */
		void Close() const;

		/**
		 * Returns whether the window should close.
		 * Should return true after close() is called
		 */
		bool ShouldClose() const;

	protected:
		GLFWwindow * window_ = nullptr;


		/**
		* Internal callback fetched to GLFW for keyboard callback
		*/
		static void key_callback_internal(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);

		/**
		* Internal callback fetched to GLFW for cursor position updates
		*/
		static void cursor_pos_callback_internal(GLFWwindow* glfw_window, double mouse_x, double mouse_y);

		/**
		 * Internal callback fetched to GLFW for mouse button presses
		 */
		static void mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);

		/**
		 * Internal callback fetched to GLFW for mouse scroll events
		 */
		static void mouse_scroll_callback(GLFWwindow* glfw_window, double offset_x, double offset_y);

		/**
		 * Internal callback fetched to GLFW for resize callback
		 */
		static void window_resize_callback(GLFWwindow* glfw_window, int width, int height);
	};
}