#include "window.h"
#include "render_pass.h"
#include <thread>
#include <iostream>

Window::Window(const char* title, int width, int height)
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	glViewport(0,0, width, height);
	m_width = width;
	m_height = height;
	m_valid = false;
	m_alive = true;
	m_graphics_thread = std::thread(&Window::thread_worker, this);
}

void Window::thread_worker(){
	m_context = SDL_GL_CreateContext(m_window);

	glewExperimental = GL_TRUE;
	if(auto glew_init_error = glewInit()){
		std::cerr << glewGetErrorString(glew_init_error) << std::endl;
		m_alive = false;
	}

	init();

	while(m_alive){
		std::unique_lock<decltype(m_validation_mutex)> lock(m_validation_mutex);
		m_cv.wait(lock, [this]{return !m_valid;});

		if(make_current()){
			redraw();
			glFinish();
			flush();
		}
		m_valid = true;
	}

	SDL_GL_DeleteContext(m_context);
}

Window::~Window()
{
	{
		std::lock_guard<decltype(m_validation_mutex)> lock(m_validation_mutex);
		m_alive = false;
		m_valid = false;
	}
	m_cv.notify_one();
	m_graphics_thread.join();
	SDL_DestroyWindow(m_window);
}

void Window::set_resizable(bool res)const
{
	SDL_SetWindowResizable(m_window, res? SDL_TRUE : SDL_FALSE);
}

Uint32 Window::id()const
{
	return SDL_GetWindowID(m_window);
}

bool Window::make_current()const
{
	return SDL_GL_MakeCurrent(m_window, m_context) == 0;
}
void Window::flush()const
{
	SDL_GL_SwapWindow(m_window);
}
void Window::on_mouse_enter(int x, int y){}
void Window::on_mouse_leave(int x, int y){}
void Window::on_mouse_move(int x, int y){}
void Window::on_mouse_down(int button){}
void Window::on_mouse_up(int button){}
void Window::on_mouse_wheel(int wheel){}

void Window::validate(){
	m_cv.notify_one();
}
void Window::invalidate(){
	{
		//std::lock_guard<decltype(m_validation_mutex)> lock(m_validation_mutex);
		m_valid = false;
	}
	m_cv.notify_one();
}
void Window::init(){}
void Window::redraw()const{}
