#ifndef FPS_H
#define FPS_H

#include <deque>
#include <numeric>

template<typename ElementType, typename Container = std::deque<ElementType> >
class FPS
{
	typedef ElementType element_type;
	typedef Container container_type;

	// Fields
	Container container;
	unsigned int history_size;
	ElementType sum;

public:
	// constructors
	FPS():history_size(10),sum(0){}

	FPS(unsigned int historySize)
		:history_size(historySize),sum(0){}

	// methods
	inline bool empty()
	{
		return container.empty();
	} // end function empty


	inline unsigned int size()
	{
		return container.size();
	} // end function size


	inline FPS &clear()
	{
		container.clear();
		sum = 0;
		return *this;
	} // end function clear


	inline FPS &setHistorySize(unsigned int historySize)
	{
		history_size = historySize;
		return *this;
	} // end function setHistorySize


	inline unsigned int getHistorySize()
	{
		return history_size;
	} // end function getHistorySize


	FPS &push(double frameDuration)
	{
		if(container.size() >= history_size)
		{
			sum -= container.front();
			container.pop_front();
		} // end if
		sum += frameDuration;
		container.push_back(frameDuration);
		return *this;
	} // end function push


	inline FPS &recalculateSum()
	{
		sum = std::accumulate(container.begin(),container.end(),0.0);
		return *this;
	} // end function recalculateSum


	inline double fps()
	{						// note that this is the inverse of the average period
		return size()/sum;	// of a frame. the average frequency will be greater.
	} // end function fps

}; // end class FPS
#endif // FPS_H