#ifndef FRACTALMATHPASS_H
#define FRACTALMATHPASS_H

#include "../fullscreen_pass.h"

class FractalMathPass : public FullscreenPass
{
public:
	FractalMathPass();

	void render()const override;

	float zoom     = 2.5f;
	float center_x = -.5f;
	float center_y = 0.0f;

private:
	GLint m_zoom_location;
	GLint m_x_location;
	GLint m_y_location;
};

#endif // FRACTALMATHPASS_H
