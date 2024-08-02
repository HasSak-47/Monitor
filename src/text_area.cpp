#include <text_area.hpp>

using namespace Utility;

TextArea::TextArea(size_t width) {
	this->text.resize(width, ' ');
}

void TextArea::render(Render::Buffer& buf){
	size_t len = this->text.size();
	size_t width = buf.get_width();
	size_t height = buf.get_height();
	for (size_t indx = 0; indx < len; ++indx) {
		size_t i = indx % width;
		size_t j = indx / width;
		buf.get(i, j).chr = this->text[indx];
	}
}

