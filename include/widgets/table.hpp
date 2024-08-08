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
		std::vector<TextArea> area;
		Table& parent;

		Row(Table& parent);
		Row(Table& parent, std::vector<std::string>);
		~Row() {}
		void render(Render::Buffer& buf) override;
	};

	std::vector<std::optional<size_t>> _expected_width;

	Row _names;
	std::vector<Row> _rows;
public:
	char separator = '|';
	Table(std::vector<std::string> names);
	~Table(){}
	void set_col(size_t i, std::vector<std::string> name);
	std::string& get_area(size_t row, size_t col);

	void set_size(size_t id, size_t s);
	void render(Render::Buffer& buf) override;
};

}

#endif
