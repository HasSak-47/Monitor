#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <string>

namespace logs{
template<typename OutT>
class Logger{
public:
	enum WarningLevel{
		Log = 0,
		Warning = 1,
		Error = 2,
	} warning_level = Log;

private:
	OutT _out;

	void _write(std::string fmt, size_t start, size_t end){
		_out << fmt.substr(start, end);
	}

	template<typename Arg, typename... Args>
	void _write(std::string fmt, size_t start, size_t end, Arg arg, Args... args){
		for(size_t i = start; i < end; ++i){
			if(fmt[i] == '%'){
				_out << arg;
				_write(fmt, i + 1, end, args...);
				return;
			}
			_out << fmt[i];
		}
	}

	template<typename... Args>
	void _log(WarningLevel level, std::string fmt, Args... args){
		if(level >= warning_level)
		_write(fmt, 0, fmt.size(), args...);
	}

public:
	Logger(OutT out) : _out (std::move(out)){}

	template<typename... Args>
	void log(std::string fmt, Args... args){ _log(Log, fmt, args...); }
	template<typename... Args>
	void warning(std::string fmt, Args... args){ _log(Warning, fmt, args...); }
	template<typename... Args>
	void errro(std::string fmt, Args... args){ _log(Error, fmt, args...); }
};
}

#endif
