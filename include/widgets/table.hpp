#ifndef __WIDGETS_TABLE_HPP__
#define __WIDGETS_TABLE_HPP__

#include <optional>
#include <vector>
#include "../render/render.hpp"
#include "./text_area.hpp"

namespace Widgets{

class Table : public virtual Render::Widget{
private:
	struct Row: Render::Widget{
		std::vector<TextArea> _areas;
		Table& parent;

		Row(Table& parent);
		Row(Table& parent, size_t width);
		Row(Table& parent, std::vector<std::string>);
		~Row() {}
		void render(Render::Buffer& buf) override;
	};

	std::vector<std::optional<size_t>> _expected_width;

	Row _headers;
	std::vector<Row> _rows;
public:
	char vertical_separator = '|';
	Table(size_t width, size_t height = 0);
	~Table(){}

	void render(Render::Buffer& buf) override;
	void set_row_width(size_t w, size_t h);
	void set_dimentions(size_t w, size_t h);

	std::string& get_row_area(size_t row, size_t col);
	std::string& get_header(size_t col);
};

}

#endif
