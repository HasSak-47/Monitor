#include "render/render.hpp"
#include "text_area.hpp"

namespace Utility{

class Table : virtual TextArea, public virtual Render::Widget{
public:
	Table(){}
};

}
