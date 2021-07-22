#ifndef FRACTALCOLORPASS_H
#define FRACTALCOLORPASS_H

#include "../fullscreen_pass.h"

class FractalColorPass : public FullscreenPass
{
public:
	FractalColorPass();

	void render()const override;

private:
	GLint m_last_z;
	GLint m_iterations;
};

#endif // FRACTALCOLORPASS_H
