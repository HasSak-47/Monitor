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

    const size_t max_width = buf.get_width() - 2;
    while(offset < max_width && col < this->_areas.size()){
        buf.get(offset++).chr = '|';
        if(offset > max_width)
            return;

        size_t inc = e[col].value_or(this->_areas[col].text.size());
        if(offset + inc >= max_width)
            inc = buf.get_width() - offset;

        auto sub = buf.get_subbuffer(offset, 0, inc, 1);
        this->_areas[col].render(sub);
        offset += inc + 1;
        col++;
    }
    buf.get(max_width + 1).chr = '|';
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
    size_t used_size = 0;
    size_t to_expand = 0;
    for(size_t i = 0; i < this->_expected_width.size(); ++i){
        if(this->_expected_width[i].has_value()){
            used_size += 2 + this->_expected_width[i].value();
            continue;
        }

        to_expand++;
    }

    for(size_t i = 0; i < this->_expected_width.size(); ++i){
        if(this->_expected_width[i].has_value())
            continue;

        this->_expected_width[i] = (buf.get_width() - used_size - 2) / to_expand;
    }

	auto ln1 = buf.get_subbuffer(0, 0, buf.get_width(), 1);
	auto sub = buf.get_subbuffer(0, 1, buf.get_width(), 1);
	auto ln2 = buf.get_subbuffer(0, 2, buf.get_width(), 1);
	auto ln3 = buf.get_subbuffer(0, buf.get_height() - 1, buf.get_width(), 1);
	this->_headers.render(ln1);
	this->_headers.render(sub);
	this->_headers.render(ln2);
	this->_headers.render(ln3);
    for(size_t i = 0; i < buf.get_width(); ++i){
        if(ln1.get(i, 0).chr != '|'){
            ln1.get(i, 0).chr = '-';
            ln2.get(i, 0).chr = '-';
            ln3.get(i, 0).chr = '-';
        }

    }

    size_t max = std::min(buf.get_height() - 4, this->_rows.size());

    for(size_t i = 0; i < max; ++i){
        auto sub = buf.get_subbuffer(0, i + 3, buf.get_width(), 1);
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

