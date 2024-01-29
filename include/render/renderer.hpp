#ifndef __RENDER_RENDERER__
#define __RENDER_RENDERER__

#include "renderee.hpp"

namespace Render{

class Renderer{
public:
	virtual void render() = 0;
	virtual void bind(Renderee* renderee) = 0;
	virtual void clear() = 0;
};

}

#endif
