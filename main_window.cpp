#include "main_window.h"
#include "fractal/gbuffer.h"
#include "fractal/math_pass.h"
#include "fractal/color_pass.h"

MainWindow::MainWindow() : Window("frac3k1", 640,640)
{
}
bool mouse_down = false;
int last_mouse_x, last_mouse_y;
float last_center_x, last_center_y;
void MainWindow::on_mouse_down(int button)
{
	mouse_down = true;
	last_center_x = m_fractal_math_pass->center_x;
	last_center_y = m_fractal_math_pass->center_y;
}
void MainWindow::on_mouse_up(int button)
{
	mouse_down = false;
}
void MainWindow::on_mouse_move(int x, int y)
{
	if(!mouse_down){
		last_mouse_x = x;
		last_mouse_y = y;
	}else{
		float zoom = m_fractal_math_pass->zoom;
		m_fractal_math_pass->center_x= last_center_x + ((last_mouse_x-x)/static_cast<float>(m_width))*zoom;
		m_fractal_math_pass->center_y= last_center_y + ((y-last_mouse_y)/static_cast<float>(m_height))*zoom;
		invalidate();
	}
}
void MainWindow::on_mouse_wheel(int wheel)
{
	m_fractal_math_pass->zoom *= 1 + 0.1 * -wheel;
	invalidate();
}

void MainWindow::redraw()const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_gbuffer->id());
	m_fractal_math_pass->use();
	m_fractal_math_pass->render();
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_gbuffer->id());
	//
	m_fractal_color_pass->use();
	m_gbuffer->bind_textures();
	m_fractal_color_pass->render();
}

void MainWindow::init(){
	m_fractal_math_pass = std::make_unique<FractalMathPass>();
	m_fractal_color_pass = std::make_unique<FractalColorPass>();
	m_gbuffer = std::make_unique<GBuffer>();
	//m_framebuffer = std::make_unique<Framebuffer>(640,640);
}
