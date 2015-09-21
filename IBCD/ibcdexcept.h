#pragma once

#include <stdexcept>

class file_not_found : public std::logic_error
{
public:
	explicit file_not_found(const std::string& what_arg):
		logic_error(what_arg)
	{

	}
	explicit file_not_found(const char* what_arg):
		logic_error(what_arg)
	{

	}
};

class shader_compile_error : public std::runtime_error
{
public:
	explicit shader_compile_error(const std::string& what_arg) :
		runtime_error(what_arg) {}
	explicit shader_compile_error(const char* what_arg) :
		runtime_error(what_arg) {}
};