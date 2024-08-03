#include <vector>
#include "render/render.hpp"
#include "text_area.hpp"

namespace Widgets{

class Table : public virtual Render::Widget{
private:
	struct Row : public virtual Widgets::TextArea{
		Row(Table& parent) : _parent(parent) {}
		std::vector<std::string> _data;
		Table& _parent;

		void render(Render::Buffer& buf) override;
	};
	std::vector<std::string> _names;
	std::vector<size_t> _expected_width;
	std::vector<Row> _name_row;
	std::vector<Row> _rows;
public:
	Table(){}
	void add_col(std::string name);
	std::vector<std::string>& get_row(size_t id);

	void render(Render::Buffer& buf) override;
};

}
