#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>

namespace logs{
template<typename OutT>
class Logger{
private:
	OutT _out;

	void _write(std::string fmt, size_t end, size_t start){
		_out << fmt.substr(start, end);
	}

	template<typename Arg, typename... Args>
	void _write(std::string fmt, size_t start, size_t end, Arg arg, Args... args){
		for(size_t i = start; i < end; ++i){
			if(fmt[i] == '%'){
				_out << arg;
				_write(fmt, i, end, args...);
				return;
			}
			_out << fmt[i];
		}
	}

public:
	Logger(OutT out) : _out (std::move(out)){}

	template<typename... Args>
	void log(std::string fmt, Args... args){
		_write(fmt, 0, fmt.size(), args...);
	}
};
}

#endif
