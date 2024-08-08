#ifndef __TEXT_AREA_HPP__
#define __TEXT_AREA_HPP__

#include <string>
#include "../render/render.hpp"

namespace Widgets{
class TextArea : public virtual Render::Widget{
public:
	std::string text;
	TextArea() : TextArea(0) {}
	TextArea(size_t width);
	TextArea(std::string text);
	void render(Render::Buffer& buffer) override;
};
}

#endif
