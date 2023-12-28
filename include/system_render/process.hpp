#ifndef __SYSTEM_RENDER_PROCESS_HPP__
#define __SYSTEM_RENDER_PROCESS_HPP__

#include <memory>
#include "renderer.hpp"
#include "system.hpp"
#include "text_line.hpp"

namespace SystemRender{
class ProcessList : public Renderee{
protected: 
	std::shared_ptr<Buffer> _buffer;
	class Process : public TextLine{
	protected:
		Sys::Process& _proc;
		TextLine _pid;
		TextLine _name;
		TextLine _mem;
	public:
		Process(Sys::Process& proc): TextLine(100),
		_proc(proc), _pid(10), _name(10), _mem(10)
		{ }
		void write() override{
			
		}
		Buffer& get_buffer() override;
	};
public:
	void write() override;
	Buffer& get_buffer() override;
};
}

#endif
