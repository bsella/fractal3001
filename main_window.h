#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window.h"
#include <memory>

class FractalPass;
class Framebuffer;

class MainWindow : public Window
{
public:
	MainWindow();

	void on_mouse_down(int button)override;
	void on_mouse_up(int button)override;
	void on_mouse_move(int x, int y)override;
	void on_mouse_wheel(int wheel)override;

	void redraw()const override;
	void init() override;

private:
	std::unique_ptr<FractalPass> m_fractal_pass;
	std::unique_ptr<Framebuffer> m_framebuffer;
};

#endif // MAINWINDOW_H
