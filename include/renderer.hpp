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

    // void set_bg();
    // void set_fg();
    // void set_c();
};

class Buffer{
private:
    std::unique_ptr<Unit[]> data;
    size_t _width, _height;
public:
    Buffer();
    Buffer(size_t width, size_t height);
    std::optional<Unit&> get(size_t x, size_t y);
    Vector2<size_t> size();
};

class Renderee;

class Window{
private:
    Buffer _present_buffer;
    std::vector<std::shared_ptr<Buffer>> _buffers;
public:
    Window();
    void add_buffer(std::shared_ptr<Buffer> _buffer);
    ~Window();
};

class Renderee{
public:
    virtual void write() = 0;
    virtual void   bind(Window& window) = 0;
    virtual void unbind(Window& window) = 0;
};

class ProgressBar : public Renderee{
public: 
    void write() override;
    void bind(Window& window) override;
    void unbind(Window& window) override;
};

#endif
