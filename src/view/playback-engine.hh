/**
 * @file   playback-engine.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Mar 31 14:23:42 2013
 *
 * @brief  Declaration of the playback-engine class.
 */

#ifndef PLAYBACK_ENGINE_HH
#define PLAYBACK_ENGINE_HH

#include <vector>
#include "file-reader.hh"
#include "test-logger.hh"
#include "playback.hh"

namespace controller
{
	class GameEngine;
}

namespace view
{
	class PlaybackEngine
	{
	public:
		/** Constructor. */
		PlaybackEngine(const std::string & playback_dir);

		/** Destructor. */
		~PlaybackEngine();

		void linkGame(controller::GameEngine & g);

		bool doesOutputMatchReference() const;

	private:
		FileReader reader_;
		TestLogger * test_log_;
		std::string playback_dir_;
		std::vector<Playback *> playbacks_;
	};
}

#endif
