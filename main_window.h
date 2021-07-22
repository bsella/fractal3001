#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "window.h"
#include <memory>

class GBuffer;
class FractalMathPass;
class FractalColorPass;

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
	std::unique_ptr<GBuffer> m_gbuffer;
	std::unique_ptr<FractalMathPass> m_fractal_math_pass;
	std::unique_ptr<FractalColorPass> m_fractal_color_pass;
};

#endif // MAINWINDOW_H
