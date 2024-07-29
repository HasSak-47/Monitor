#ifndef __RENDER_WINDOW__
#define __RENDER_WINDOW__

#include<vector>

#include "./renderer.hpp"

namespace Render{

class Window: Renderer{
private:
	Buffer _render_buffer;
	std::vector<Renderee*> _renderees;
	struct BindedRenderee{
		Renderee* _renderee;
		size_t x, y;
	};
public:
	Window();
	~Window();
	void render() override;
	void bind(Renderee* renderee, size_t x, size_t y, size_t w, size_t h) override;
	void clear() override;
};

}

#endif
