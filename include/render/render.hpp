#ifndef __RENDER_RENDER__
#define __RENDER_RENDER__
#include <memory>
#include <vector>

namespace Render{

class Color{
private:
public:
	void set_color(int r, int g, int b);	
	void render_color();
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
	size_t start, end;
	size_t width;
public:
	Slice(size_t lenght);
	Slice(const Slice& other);

	Slice get_subslice(size_t start, size_t lenght);
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
	Unit& get(size_t x, size_t y = 0);

	Buffer get_subbuffer(size_t x, size_t y, size_t w, size_t h);
	size_t get_width();
	size_t get_height();
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
