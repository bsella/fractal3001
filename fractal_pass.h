#ifndef FRACTALRENDERPASS_H
#define FRACTALRENDERPASS_H

#include "framebuffer_pass.h"

class FractalPass : public FramebufferPass
{
public:
	FractalPass();

	void render()const override;

	float zoom     = 2.5f;
	float center_x = -.5f;
	float center_y = 0.0f;

private:
	GLint m_zoom_location;
	GLint m_x_location;
	GLint m_y_location;
};

#endif // FRACTALRENDERPASS_H
