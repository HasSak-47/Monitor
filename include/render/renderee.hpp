#ifndef __RENDER_RENDEREE__
#define __RENDER_RENDEREE__

#include "render.hpp"

namespace Render{

class Renderee{
public:
	virtual void write(Buffer& buffer) = 0;
};

}

#endif
