#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <widgets/table.hpp>
#include <render/render.hpp>

using namespace Widgets;

Table::Row::Row(Table& parent) : parent(parent) {
	this->_areas = {};
}
Table::Row::Row(Table& parent, size_t width) : Row(parent){
	this->_areas.resize(width);
}
Table::Row::Row(Table& parent, std::vector<std::string> names) : Row(parent){
	for(auto& name: names)
		this->_areas.push_back({name});
}

void Table::Row::render(Render::Buffer& buf){
	auto& e = this->parent._expected_width;
    size_t offset = 0;
    size_t col = 0;
    while(offset < buf.get_width() && col < this->_areas.size()){
        size_t inc = e[col].value_or(this->_areas[col].text.size());
        auto sub = buf.get_subbuffer(offset, 0, inc, 1);
        this->_areas[col].render(sub);
        buf.get(offset + inc, 0).chr = '|';
        offset += inc + 1;
        col++;
    }
}

void Table::set_row_width(size_t id, size_t s){
	this->_expected_width[id] = s;
}

void Table::set_dimentions(size_t w, size_t h){
	this->_headers._areas.resize(w);
    for(size_t i = 0; i < h; ++i)
	    this->_rows.push_back({*this});

	for(auto& row : this->_rows)
		row._areas.resize(w);
}

void Table::render(Render::Buffer& buf){
    for(size_t i = 0; i < this->_expected_width.size(); ++i){
        if(this->_expected_width[i].has_value())
            continue;
        size_t max = this->_headers._areas[i].text.size();
        for(size_t j = 0; j < this->_rows.size(); ++j){
            size_t k = this->_rows[j]._areas[i].text.size();
            if(max < k)
                max = k;
        }
        this->_expected_width[i] = max;
    }
	auto sub = buf.get_subbuffer(0, 0, buf.get_width(), 1);
	this->_headers.render(sub);

    size_t max = std::min(buf.get_height() - 1, this->_rows.size());

    for(size_t i = 0; i < max; ++i){
        auto sub = buf.get_subbuffer(0, i + 1, buf.get_width(), 1);
        this->_rows[i].render(sub);
    }
}

std::string& Table::get_row_area(size_t row, size_t col){
	return this->_rows[row]._areas[col].text;
}

std::string& Table::get_header(size_t col){
	return this->_headers._areas[col].text;
}

Table::Table(size_t width, size_t height) : _headers(*this, width){
    this->_expected_width.resize(width, {});
    for(size_t i = 0; i < height; ++i)
        this->_rows.push_back({*this, width});
}

