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
		Exception(const std::string msg) :
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
		SystemException(const std::string msg) :
			Exception(msg)
		{
		}
	};

	class SignalNotConnected : public SystemException
	{
	public:
		SignalNotConnected(const std::string signal) :
			SystemException(signal)
		{
		}
	};

	class GameException : public Exception
	{
	public:
		GameException(const std::string msg)
			: Exception(msg){}
	};

	class GameOverException : public GameException
	{
	public:
		GameOverException()
			: GameException("Game Over"){}
	};

	class NotEnoughDenierEx : public GameException
	{
	public:
		NotEnoughDenierEx()
			: GameException("Not enough denier"){}
	};

	class NotEnoughResourceEx : public GameException
	{
	public:
		NotEnoughResourceEx()
			: GameException("Not enough resource"){}
	};

	class BuildingFullEx : public GameException
	{
	public:
		BuildingFullEx()
			: GameException("Building full"){}
	};

	class AlreadyPlacedEx : public GameException
	{
	public:
		AlreadyPlacedEx()
			: GameException("Worker already placed"){}
	};

	class UnactivableBuildingEx : public GameException
	{
	public:
		UnactivableBuildingEx()
			: GameException("The building cannot be activated"){}
	};

	class NoBuildingEx : public GameException
	{
	public:
		NoBuildingEx()
			: GameException("There's no building here."){}
	};

	class ImageNotFound : public GameException
	{
	public:
		ImageNotFound()
			: GameException("The required image has not been found."){}
	};

}
#endif //EXCEPTIONS_HH
