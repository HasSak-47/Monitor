#ifndef __RENDER_RENDERER__
#define __RENDER_RENDERER__

#include <vector>

#include "render.hpp"
#include "renderee.hpp"

namespace Render{

class Renderer{
private:
	Buffer _back_buffer;
	std::vector<Renderee*> renders;
public:
	void render();
	void bind(Renderee* renderee);
	void clear();
};

}

#endif
