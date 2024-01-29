#ifndef __RENDER_RENDER__
#define __RENDER_RENDER__
#include <memory>

namespace Render{

class Color{
	void set_color(int r, int g, int b);	
};

struct Unit{
	int chr;
	Color color;
};

class Buffer{
private:
	std::unique_ptr<Unit[]> _buffer;
public:
	Buffer();
	~Buffer();

	Unit& get(size_t x, size_t y = 0);
};

}

#endif
