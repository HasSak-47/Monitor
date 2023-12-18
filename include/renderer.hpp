#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <cstdint>
#include <memory>
#include <vector>
#include <optional>

#include "utils.hpp"

class Window;
class Renderee;
class Renderer;
class Buffer;

class Color{
	size_t color_id = 0;

public:
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Yellow;
	static const Color Blue;
	static const Color Cyan;
	static const Color Magenta;
	static const Color White;
	Color();
	Color(size_t id);

	size_t get_color();
};

class UnitColor{
private:
	static std::vector<size_t> _colors;
public:
    Color foreground, background;

	void set_color();
	void unset_color();
	void init_color();
	UnitColor(Color fg, Color bg = Color::Black);
	UnitColor();
};

struct Unit{
    UnitColor colors;
    char32_t c;

    static const Unit default_unit;
};

class Buffer{
private:
    std::unique_ptr<Unit[]> data;
    size_t _width, _height;
public:
    Buffer();
    Buffer(size_t width, size_t height = 1);
    std::optional<Unit*> get(size_t x, size_t y);
    Vector2<size_t> size();
    size_t len();

    void clear();
};

class Renderee;

class Window{
private:
    Buffer _present_buffer;
    struct Renderees{
        Renderee* parent;
        Vector2<size_t> pos;
    };
    std::vector<Renderees> _renderees;
public:
    Window();
    void bind_buffer(Renderee* parent, size_t x, size_t y);
    void unbind_buffer(Renderee* parent);
    void render();
    Vector2<size_t> get_size();
    ~Window();
};

class Renderee{
public:
    virtual void write() = 0;
    virtual void bind(Window& window, size_t x, size_t y) { window.bind_buffer(this, x, y); }
    virtual void unbind(Window& window) { window.unbind_buffer(this); };
    virtual Buffer& get_buffer() = 0;
};
#endif
