/**
 * @file   playback-engine.cc
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Mar 31 17:14:16 2013
 *
 * @brief  Declaration of the playback-engine class.
 */

#include "playback-engine.hh"
#include "file-reader.hh"

#include "../debug-logger.hh"
#include "../controller/game-engine.hh"
#include "../controller/player.hh"

using namespace view;

PlaybackEngine::PlaybackEngine(const std::string & playback_dir)
		: reader_(playback_dir + "/input")
		, test_log_(NULL)
		, playback_dir_(playback_dir)
{
}

PlaybackEngine::~PlaybackEngine()
{
	foreach (Playback * playback, playbacks_)
	{
		delete playback;
		playback = NULL;
	}
	delete test_log_;
	test_log_ = NULL;
}

void PlaybackEngine::linkGame(controller::GameEngine & g)
	{
		unsigned nb_workers = reader_.next_uint();
		g.setMaxWorkers(nb_workers);

		unsigned int nb_players = reader_.next_uint();
		while (nb_players-- > 0)
		{
			DebugLogger::log("Adding new playback player.");

			controller::Player * player = g.newPlayer();
			Playback * playback = new Playback(&g, player, reader_);
			playbacks_.push_back(playback);

			std::string player_name = playback->askName();
			player->setName(player_name);
		}
		test_log_ = new TestLogger(&g, playback_dir_);
	}

	bool PlaybackEngine::doesOutputMatchReference() const
	{
		std::ifstream ref;
		std::ifstream output;

		ref.open((playback_dir_ + "/ref").c_str(), std::ios::in);
		if (ref.fail())
		{
			DebugLogger::log("Cannot open ref file.");
			return false;
		}
		output.open((playback_dir_ + "/output").c_str(), std::ios::in);
		if (output.fail())
		{
			DebugLogger::log("Cannot open output file.");
			return false;
		}

		std::string ref_line;
		std::string output_line;
		int line_number = 0;
		bool result = true;
		do
		{
			std::getline(ref, ref_line);
			std::getline(output, output_line);

			line_number++;
			if (ref_line != output_line)
			{
				std::cerr << "Lines " << line_number << " differ : " << std::endl
				          << "\t" << ref_line << std::endl
				          << "\t" << output_line << std::endl;
				result = false;
				break;
			}
		}
		while (ref && output);
		ref.close();
		output.close();
		return result;
	}
