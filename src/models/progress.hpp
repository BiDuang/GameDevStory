#ifndef PROGRESS_HPP
#define PROGRESS_HPP

template <class T = int>
class progress {
public:
	bool is_ok = false;
	bool is_extra_info = false;
	T info = 0;

	progress(bool is_ok, bool is_extra_info = false, T info = 0) :
		is_ok(is_ok), is_extra_info(is_extra_info), info(info) {}

};

#endif