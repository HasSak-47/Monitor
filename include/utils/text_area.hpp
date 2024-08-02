#ifndef __TEXT_AREA_HPP__
#define __TEXT_AREA_HPP__

#include <string>
#include "../render/render.hpp"

namespace Utility{
class TextArea : public virtual Render::Widget{
public:
	std::string text;
	TextArea(size_t width);
	void render(Render::Buffer& buffer) override;
};
}

#endif
