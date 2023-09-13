#ifndef PROGRESS_HPP
#define PROGRESS_HPP

/**
* @brief Class Progress
*
* @details This class contains the a In-game progress info.
* @details If a sence has a value need to be returned, dump it into the property `info`.
*/
template <class T = int>
class progress {
public:
	bool isOk = false;
	bool hasExtraInfo = false;
	T info = 0;

	// Default constructor is not allowed.
	progress() = delete;
	progress(bool isOk, bool hasExtraInfo = false, T info = 0) :
		isOk(isOk), hasExtraInfo(hasExtraInfo), info(info) {}
};

#endif //PROGRESS_HPP