#ifndef PROGRESS_HPP
#define PROGRESS_HPP

/**
* @brief Class Progress
*
* @details This class contains the a In-game Progress info.
* @details If a sence has a value need to be returned, dump it into the property `info`.
*/
template <class T = int>
class Progress {
public:
	bool isOk = false;
	bool hasExtraInfo = false;
	T info = 0;

	Progress(bool isOk, bool hasExtraInfo = false, T info = 0) :
		isOk(isOk), hasExtraInfo(hasExtraInfo), info(info) {}
};

#endif //PROGRESS_HPP