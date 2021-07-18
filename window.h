#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <thread>
#include <mutex>
#include <condition_variable>

class Window
{
public:
	explicit Window(const char* title, int width, int height);
	virtual ~Window();

	void set_resizable(bool)const;
	Uint32 id()const;

	virtual void on_mouse_enter(int x, int y);
	virtual void on_mouse_leave(int x, int y);
	virtual void on_mouse_move(int x, int y);
	virtual void on_mouse_down(int button);
	virtual void on_mouse_up(int button);
	virtual void on_mouse_wheel(int wheel);

	virtual void init();
	void validate();
	void invalidate();

protected:
	virtual void redraw()const;
	int m_width, m_height;

private:
	SDL_Window*   m_window;
	SDL_GLContext m_context;

	bool m_alive;
	bool m_valid;
	std::condition_variable m_cv;
	std::thread m_updating_thread;
	std::mutex  m_validation_mutex;

	bool make_current()const;
	void flush()const;
	void thread_worker();
};

#endif // WINDOW_H
