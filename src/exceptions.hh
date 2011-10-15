/**
 * @file   exceptions.hh
 * @author  <mankalas@localhost,>
 * @date   Sun Jan 11 15:51:28 2009
 *
 * @brief
 *
 *
 */

#ifndef EXCEPTIONS_HH
# define EXCEPTIONS_HH

namespace controller
{

	class Exception
	{
	};

	class SystemException : public Exception
	{
	};

	class SignalNotConnected : public SystemException
	{
	};

	class GameException : public Exception
	{

	};

	class NotEnoughDenierEx : public GameException
	{
	};

	class OccupiedBuildingEx : public GameException
	{
	};

	class UnactivableBuildingEx : public GameException
	{
	};

	class NoBuildingEx : public GameException
	{
	};

	class MemAllocError : public GameException
	{
	};

	class ImageNotFound : public GameException
	{
	};

}
#endif //EXCEPTIONS_HH
