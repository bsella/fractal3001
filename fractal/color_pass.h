#ifndef FRACTALCOLORPASS_H
#define FRACTALCOLORPASS_H

#include "../fullscreen_pass.h"

class FractalColorPass : public FullscreenPass
{
public:
	FractalColorPass();

	void render()const override;

private:
	GLint m_z0;
	GLint m_zn;
	GLint m_n;
};

#endif // FRACTALCOLORPASS_H
