#include <cstdlib>
#include <iostream>
#include <widgets/table.hpp>
#include <render/render.hpp>

using namespace Widgets;

Table::Row::Row(Table& parent) : parent(parent){ this->area = {}; }
Table::Row::Row(Table& parent, std::vector<std::string> names) : Row(parent){
	for(auto& name: names){
		this->area.push_back({name});
	}
}

void Table::Row::render(Render::Buffer& buf){
	auto& e = this->parent._expected_width;

	size_t w = buf.get_width() - 1;
	size_t h = buf.get_height();

	size_t index = 0, offset = 0;
	for(size_t i = 0; i < this->area.size(); ++i) {
		size_t width = std::min(e[i].value_or(this->area[i].text.size()) + 1, w - offset);

		buf.get(offset, 0).chr = '|';
		auto rbuf = buf.get_subbuffer(offset + 1, 0, width - 1, 1);
		this->area[i].render(rbuf);

		index++;
		offset += width;
	}
	buf.get(offset, 0).chr = '|';
}

Table::Table(std::vector<std::string> names) : _names(*this, names){
	this->_expected_width.resize(names.size(),{});
	// this->_expected_width.back() = 1000000;
}

void Table::set_size(size_t id, size_t s){
	this->_expected_width[id] = s;
}

void Table::set_col(size_t i, std::vector<std::string> cols){
	if(this->_rows.size() == 0){
		this->_rows.push_back({*this, cols});
		return;
	}

	auto& target = i < this->_rows.size() ? this->_rows[i] : *this->_rows.end();
	for (size_t i = 0; i < cols.size(); ++i) {
		if(i < target.area.size())
			target.area[i].text = cols[i];
		else{
			TextArea area(cols[i]);
			target.area.push_back(area);
		}
	}
	exit(-1);
}

void Table::render(Render::Buffer& buf){
	size_t ew = buf.get_width() - (this->_expected_width.size() + 1);
	size_t total_width = 0;
	size_t w_count = 0;
	for(auto& w : this->_expected_width){
		if(w.has_value()){
			total_width += w.value();
			w_count += 1;
		}
	}

	if (total_width < ew){
		size_t rem = ew - total_width;
		size_t w_rem = (this->_expected_width.size() - w_count);
		size_t wd = rem / w_rem;
		for(auto& w : this->_expected_width){
			if(!w.has_value()){
				w = wd;
			}
		}
		this->_expected_width.back().value() += rem % w_rem;
	}

	size_t w = buf.get_width();
	{
		auto sub = buf.get_subbuffer(0, 0, w, 1);
		this->_names.render(sub);
	}

	size_t h = std::min(buf.get_height(), this->_rows.size());
	for (size_t i = 1; i < h; ++i) {
		auto sub = buf.get_subbuffer(0, i, w, 1);
		this->_rows[i].render(sub);
	}
}

