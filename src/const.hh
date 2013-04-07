/**
 * @file   const.hh
 * @author Vincent Boucheny <mankalas@gmail.com>
 * @date   Sun Nov  6 19:33:26 2011
 *
 * @brief  Declaration of constants, shared by the view and the controller.
 */

#ifndef CONST_HH
#define CONST_HH

#define STATUE "Statue"
#define THEATER "Theater"
#define COLLEGE "College"
#define MONUMENT "Monument"
#define GRANARY "Granary"
#define WEAVER "Weaver"
#define CATHEDRAL "Cathedral"
#define GOLD_MINE "Gold mine"
#define NEUTRAL_QUARRY "Neutral quarry"
#define WOOD_QUARRY "Wood quarry"
#define WORKSHOP "Workshop"
#define NEUTRAL_FARM "Neutral farm"
#define FOOD_CLOTH_FARM "Food/Cloth farm"
#define CLOTH_FOOD_FARM "Cloth/Food farm"
#define STONE_FARM "Stone farm"
#define FOREST "Forest"
#define NEUTRAL_FOREST "Forest"
#define PARK "Park"
#define NEUTRAL_SAWMILL "Neutral sawmill"
#define WOOD_SAWMILL "Wood sawmill"
#define RESIDENCE "Residence"
#define LIBRARY "Library"
#define HOTEL "Hotel"
#define CHURCH "Church"
#define FIXED_PEDDLER "Fixed peddler"
#define WOOD_PEDDLER "Wood peddler"
#define JEWELLER "Jeweller"
#define TAILOR "Tailor"
#define ALCHEMIST "Alchemist"
#define BANK "Bank"
#define TRADING_POST "Trading post"
#define NEUTRAL_CARPENTER "Neutral carpenter"
#define FIXED_CARPENTER "Fixed carpenter"
#define LAWYER "Lawyer"
#define ARCHITECT "Architect"
#define MASON "Mason"
#define NEUTRAL_MARKETPLACE "Neutral marketplace"
#define WOOD_MARKETPLACE "Wood marketplace"
#define CASTLE "Castle"
#define BRIDGE "Bridge"
#define GATE "Gate"
#define MERCHANT_GUILD "Merchant guild"
#define JOUST_FIELD "Joust field"
#define STABLES "Stables"
#define INN "Inn"
#define FARM_CLOTH "Farm cloth"
#define FARM_FOOD "Farm food"
#define FARM_STONE "Farm stone"

#ifndef foreach
# include <boost/foreach.hpp>
# define foreach BOOST_FOREACH
#endif

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define GRAY		"\033[0m\033[37m" /* Light Gray */
#endif
