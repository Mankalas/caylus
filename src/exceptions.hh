/**
 * @file   exceptions.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Jan 11 15:51:28 2009
 *
 * @brief  Declaration of the exceptions class.
 */

#ifndef EXCEPTIONS_HH
# define EXCEPTIONS_HH

# include <string>

namespace controller
{

	class Exception
	{
	public:
		Exception() {}
		Exception(const std::string & msg) :
			msg_(msg)
		{}

		const std::string msg() const
		{
			return msg_;
		}
	protected:
		const std::string msg_;
	};

	class SystemException : public Exception
	{
	public:
		SystemException(const std::string & msg) :
			Exception(msg)
		{
		}
	};

	class SignalNotConnected : public SystemException
	{
	public:
		SignalNotConnected(const std::string & signal) :
			SystemException(signal)
		{
		}
	};

	class GameException : public Exception
	{

	};

	class GameOverException : public GameException
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
