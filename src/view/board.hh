/**
 * @file   board.hh
 * @author Vincent Boucheny <vincent.boucheny@hpc-sa.com>
 * @date   Sun Nov 18 18:01:55 2012
 *
 * @brief
 */

#ifndef VIEW_BOARD_HH
# define VIEW_BOARD_HH

# include <utility>
# include <vector>
# include <string>
# include <SFML/Graphics.hpp>
# include <SFML/System/Vector2.hpp>

namespace view
{
	class Board
	{
	public:
		Board();
		unsigned int getCaseFromCoordinates(int x, int y, bool & is_click_valid) const;
		sf::Vector2<unsigned int> getCoordinatesOfCase(unsigned int case_idx) const;
		bool isClickInCastle(int x, int y) const;
		bool isClickInBridge(int x, int y) const;
		sf::Vector2<unsigned int> caseSize() const;

		/** @name Accessors. */
		//@{

		const sf::Sprite & sprite() const;
		unsigned int caseHeight() const;
		unsigned int caseWidth() const;
		unsigned int width() const;

		//@}

	protected:
		// The board's sprite.
		sf::Sprite sprite_;

		unsigned int height_;
		unsigned int width_;
		std::string path_to_images_;
		// All cases
		unsigned int case_height_;
		unsigned int case_width_;
		// Neutral cases
		std::vector<sf::Vector2<unsigned int> > cases_;

		// Castle
		unsigned int house_height_;
		unsigned int house_width_;
		// Dungeon
		sf::Vector2<unsigned int> first_dungeon_house_coord_;
		unsigned int nb_house_line_dungeon_;
		unsigned int nb_line_dungeon_;
		// Walls
		sf::Vector2<unsigned int> first_walls_house_coord_;
		unsigned int nb_house_line_walls_;
		unsigned int nb_line_walls_;
		// Towers
		sf::Vector2<unsigned int> first_towers_house_coord_;
		unsigned int nb_house_line_towers_;
		unsigned int nb_line_towers_;

		// Bridge
		sf::Vector2<unsigned int> first_bridge_slot_coord_;
		int bridge_slots_gap_;

	};

	class LimitedEditionBoard : public Board
	{
	public :
		LimitedEditionBoard();
	};
}

# include "board.hxx"

#endif
