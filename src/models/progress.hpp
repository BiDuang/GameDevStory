#ifndef PROGRESS_HPP
#define PROGRESS_HPP

template <class T = int>
class progress {
public:
	bool isOk = false;
	bool is_extra_info = false;
	T info = 0;

	progress() = delete;
	progress(bool isOk, bool is_extra_info = false, T info = 0) :
		isOk(isOk), is_extra_info(is_extra_info), info(info) {}

};

#endif