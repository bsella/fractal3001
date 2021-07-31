#include "app.h"
#include "main_window.h"

#include <SDL2/SDL.h>
#include <iostream>

App::App(int argc, const char *argv[]){
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	m_main_window = new MainWindow;

	m_running = true;

	//m_main_window->init();
}

App::~App(){
	delete m_main_window;
	SDL_Quit();
}

int App::run(){
	int x, y;
	SDL_Event event;
	while (m_running){
		if(SDL_WaitEvent(&event)){
			switch(event.type){
				case SDL_QUIT: return 0;
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_RESIZED){
						//resize
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					m_main_window->on_mouse_down(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					m_main_window->on_mouse_up(event.button.button);
					break;
				case SDL_MOUSEWHEEL:
					m_main_window->on_mouse_wheel(event.wheel.y);
					break;
				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&x, &y);
					m_main_window->on_mouse_move(x,y);
					break;
				default: break;
			}
			m_main_window->validate();
		}
	}
	return 0;
}
