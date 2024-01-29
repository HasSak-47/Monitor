#ifndef __RENDER_RENDER__
#define __RENDER_RENDER__
#include <memory>
#include <optional>

namespace Render{

class Color{
private:
public:
	void set_color(int r, int g, int b);	
	void render_color();
};

struct Unit{
	int chr;
	Color color;
};

class Slice{
private:
	std::shared_ptr<Unit[]> _slice;
	size_t _beg = 0;
	size_t _end;
public:
	Slice(size_t len = 0);
	Slice(const Slice& slice);

	Slice& operator=(const Slice& slice);

	Slice get_subslice(size_t beg, size_t end);
	Unit& operator[](size_t index);
};

class Buffer{
private:
	std::shared_ptr<Slice[]> _buffer;
public:
	Buffer(size_t x, size_t y = 1);

	Unit& get(size_t x, size_t y = 0);
};

}

#endif
