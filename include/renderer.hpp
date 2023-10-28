#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <cstdint>
#include <memory>
#include <vector>
#include <optional>

#include "utils.hpp"

class Renderee;
class Renderer;
class Buffer;

struct Color{
    union {
        struct { short r; short g; short b; short a; };
        struct { short c[4]; };
    };

    Color(){}

    Color(short r,short g,short b,short a){
        self.r = r; self.g = g; self.b = b; self.a = a;
    }
};

struct UnitColor{
    Color background, foreground;
};

struct Unit{
    UnitColor colors;
    char32_t c;
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
