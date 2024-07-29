#ifndef __RENDER_RENDERER__
#define __RENDER_RENDERER__

#include "renderee.hpp"

namespace Render{

class Renderer{
public:
	virtual void queue(Renderee* render) = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
};

}

#endif
