#include <utils/table.hpp>
#include "render/render.hpp"

using namespace Utility;

void Table::Row::render(Render::Buffer& buf){
	auto& data = _parent._expected_width;
	size_t len = _data.size();

	for(size_t i = 0; i < len; ++i){

	}

}
