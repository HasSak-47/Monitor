#ifndef __RENDER_RENDER__
#define __RENDER_RENDER__
#include <memory>
#include <vector>

namespace Render{

class Color{
private:
public:
	float r = 1, g = 1, b = 1;
};

struct Unit{
	int chr = ' ';
	Color col;
};

class Buffer;
class Slice;

class Slice{
protected:
	std::shared_ptr<Unit[]> _slice;
	size_t _start, _end;
	size_t _width;
public:

	Slice(size_t lenght);
	Slice(const Slice& other);

	Slice get_subslice(size_t start, size_t lenght);
	Unit& get(size_t i);
	friend class Buffer;
};

class Buffer{
private:
	std::vector<Slice> _buffer;
	size_t _width, _height;
	static Buffer _init_empty(size_t width, size_t height);
public:
	Buffer();
	Buffer(size_t x, size_t y = 1);
	Buffer(const Buffer& other);
	Buffer(Buffer&& moved);
	Buffer& operator=(const Buffer& other);
	Buffer& operator=(Buffer&& moved);

	Unit& get(size_t x, size_t y = 0);

	Buffer get_subbuffer(size_t x, size_t y, size_t w, size_t h);
	size_t get_width();
	size_t get_height();
	void clean();
};

class Widget{
public:
	virtual void render(Buffer& buf) = 0;
};

class Target{
protected:
	struct WidgetBind{
		std::shared_ptr<Widget> widget;
		size_t x, y;
		size_t w, h;
	};

	std::vector<WidgetBind> _binds;
public:
	void bind(std::shared_ptr<Widget> widget, size_t x, size_t y, size_t w, size_t h);
	virtual void render() = 0;
};

}

#endif
