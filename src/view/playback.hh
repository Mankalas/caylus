/**
 * @file   playback.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun May 20 18:58:10 2012
 *
 * @brief  Declaration of the playback class.
 */

#ifndef PLAYBACK_HH
# define PLAYBACK_HH

# include "active-view.hh"
# include <fstream>

namespace view
{
	class FileReader;

	class Playback : public ActiveView
	{
	public:
		Playback(const controller::GameEngine * game_engine, const controller::Player * player,  FileReader & file_reader);
		~Playback();

		virtual std::string askName() const;

			//* @name Game signals. */
		// @{

		virtual int askProvostShift() const;
		virtual unsigned int askBoardElement() const;
		virtual controller::ResourceMap askResource(const std::vector<controller::ResourceMap>& resource_choice) const;
		virtual bool askInnRemoval() const;
		virtual unsigned int askBuildingToConstruct() const;

		// @}

		virtual unsigned int askChoice(unsigned int range) const;
		virtual bool askYesNo() const;

	private:
		FileReader & reader_;
	};
}

#endif
