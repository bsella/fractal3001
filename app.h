#ifndef APP_H
#define APP_H

class Window;

class App
{
public:
	App(int argc, const char* argv[]);
	~App();

	int run();

private:
	bool m_running;
	Window* m_main_window;
};

#endif // APP_H
