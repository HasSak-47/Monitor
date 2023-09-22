#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <cstdint>
#include <memory>
#include <vector>
#include <optional>

class Renderee;
class Renderer;
class Buffer;

template<typename T>
struct Vector2{
    T x, y;

    Vector2(T _x, T _y):x(_x),y(_y){}
};

struct Unit{
    uint32_t bg[4];
    uint32_t fg[4];
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

class Window{
private:
    Buffer _present_buffer;
    struct BufferPos{
        Vector2<size_t> pos;
        std::shared_ptr<Buffer> _buffer;
    };
    std::vector<BufferPos> _buffers;
public:
    Window();
    std::shared_ptr<Buffer> init_buffer(size_t w, size_t h, size_t x = 0, size_t y = 0);
    void remove_buffer(std::shared_ptr<Buffer>& buffer);
    void render();
    Vector2<size_t> get_size();
    ~Window();
};

class Renderee{
public:
    virtual void write() = 0;
    virtual void   bind(Window& window) = 0;
    virtual void unbind(Window& window) = 0;
};
#endif
