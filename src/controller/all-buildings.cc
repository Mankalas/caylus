/**
 * @file   all-buildings.cc
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun 6 23:58:02 2011
 *
 * @brief  Implementation of the all-buildings class.
 */

#include "all-buildings.hh"
#include "const.hh"

using namespace controller;

Statue::Statue ()
	: Building(STATUE,
	           BuildingType::prestige,
	           Resource::stone * 2 + Resource::gold,
	           Resource::prestige * 7 + Resource::favor)
{
}

Theater::Theater ()
	: Building(THEATER,
	           BuildingType::prestige,
	           Resource::wood * 3 + Resource::gold * 2,
	           Resource::prestige * 14 + Resource::favor)
{
}

College::College ()
	: Building(COLLEGE,
	           BuildingType::prestige,
	           Resource::stone * 3 + Resource::gold * 2,
	           Resource::prestige * 14 + Resource::favor)
{
}

Monument::Monument ()
	: Building(MONUMENT,
	           BuildingType::prestige,
	           Resource::stone * 4 + Resource::gold * 2,
	           Resource::prestige * 14 + Resource::favor * 2)
{
}

Granary::Granary ()
	: Building (GRANARY,
	            BuildingType::prestige,
	            Resource::food * 3 + Resource::gold,
	            Resource::prestige * 10)
{
}

Weaver::Weaver ()
	: Building (WEAVER,
	            BuildingType::prestige,
	            Resource::cloth * 3 + Resource::gold,
	            Resource::prestige * 12)
{
}

Cathedral::Cathedral ()
	: Building (CATHEDRAL,
	            BuildingType::prestige,
	            Resource::stone * 5 + Resource::gold * 3,
	            Resource::prestige * 25)
{
}

GoldMine::GoldMine ()
	: Building(GOLD_MINE,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of(Resource::gold),
	                   ResourceMap(0))
{
}

NQuarry::NQuarry ()
	: Building(NEUTRAL_QUARRY,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of(Resource::stone),
	                   ResourceMap(0))
{
}

WQuarry::WQuarry ()
	: Building(WOOD_QUARRY,
	           BuildingType::wood,
	           Resource::food + Resource::wood,
	           Resource::prestige * 2),
	ProductionBuilding(boost::assign::list_of(Resource::wood * 2),
	                   ResourceMap(0))
{
}

Workshop::Workshop ()
	: Building(WORKSHOP,
	           BuildingType::stone,
	           Resource::food + Resource::stone,
	           Resource::prestige * 3),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::stone * 2 + Resource::cloth),
	                   boost::assign::list_of
	                   (Resource::stone)
	                   (Resource::cloth))
{
}

NFarm::NFarm ()
	: Building(NEUTRAL_FARM,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::food)
	                   (Resource::cloth),
	                   ResourceMap(0))
{
}

WFFarm::WFFarm ()
	: Building(WOOD_FOOD_FARM,
	           BuildingType::wood,
	           Resource::food + Resource::wood,
	           Resource::prestige * 2),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::food * 2)
	                   (Resource::cloth),
	                   ResourceMap(0))
{
}

WCFarm::WCFarm ()
	: Building(WOOD_CLOTH_FARM,
	           BuildingType::wood,
	           Resource::food + Resource::wood,
	           Resource::prestige * 2),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::cloth * 2)
	                   (Resource::food),
	                   ResourceMap(0))
{
}

SFarm::SFarm ()
	: Building(STONE_FARM,
	           BuildingType::stone,
	           Resource::food + Resource::stone,
	           Resource::prestige * 3),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::food * 2 + Resource::cloth),
	                   boost::assign::list_of
	                   (Resource::food)
	                   (Resource::cloth))
{
}

Forest::Forest ()
	: Building(FOREST,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::food)
	                   (Resource::wood),
	                   ResourceMap(0))
{
}

Park::Park ()
	: Building(PARK,
	           BuildingType::stone,
	           Resource::food + Resource::stone,
	           Resource::prestige * 3),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::wood * 2 + Resource::wood),
	                   boost::assign::list_of
	                   (Resource::wood)
	                   (Resource::food))
{
}

NSawmill::NSawmill ()
	: Building(NEUTRAL_SAWMILL,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::wood),
	                   ResourceMap(0))
{
}

WSawmill::WSawmill ()
	: Building(WOOD_SAWMILL,
	           BuildingType::wood,
	           Resource::food + Resource::wood,
	           Resource::prestige * 2),
	ProductionBuilding(boost::assign::list_of
	                   (Resource::wood * 2),
	                   ResourceMap(0))
{
}

Residence::Residence ()
	: Building(RESIDENCE,
	           BuildingType::residential,
	           Resource::cloth + Resource::denier,
	           Resource::prestige * 2)
{
}

Library::Library ()
	: Building(LIBRARY,
	           BuildingType::prestige,
	           Resource::wood * 3 + Resource::gold,
	           Resource::prestige * 10)
{
}

Hotel::Hotel ()
	: Building(HOTEL,
	           BuildingType::prestige,
	           Resource::stone * 3 + Resource::gold * 2,
	           Resource::prestige * 16),
	ResidentialBuilding(2)
{
}

Church::Church ()
	: Building(CHURCH,
	           BuildingType::stone,
	           Resource::stone + Resource::cloth,
	           Resource::favor + Resource::prestige * 3),
	TradeBuilding(Resource::denier,
	              Resource::prestige,
	              boost::assign::list_of
	              (std::make_pair (2, 4))
	              (std::make_pair (4, 5)))
{
}

FPeddler::FPeddler ()
	: Building(FIXED_PEDDLER,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	TradeBuilding(Resource::denier,
	              Resource::food  +
	              Resource::wood  +
	              Resource::cloth +
	              Resource::stone,
	              boost::assign::list_of
	              (std::make_pair (2, 1)))
{
}

WPeddler::WPeddler ()
	: Building(WOOD_PEDDLER,
	           BuildingType::wood,
	           boost::assign::list_of
	           (Resource::wood + Resource::food)
	           (Resource::wood + Resource::wood)
	           (Resource::wood + Resource::gold)
	           (Resource::wood + Resource::cloth)
	           (Resource::wood + Resource::stone),
	           Resource::prestige * 4),
	TradeBuilding(Resource::denier,
	              Resource::food  +
	              Resource::wood  +
	              Resource::cloth +
	              Resource::stone,
	              boost::assign::list_of
	              (std::make_pair (1, 1))
	              (std::make_pair (2, 2)))
{
}

Jeweller::Jeweller ()
	: Building(JEWELLER,
	           BuildingType::stone,
	           Resource::stone + Resource::cloth,
	           Resource::prestige * 6),
	TradeBuilding(Resource::gold,
	              Resource::prestige,
	              boost::assign::list_of
	              (std::make_pair (1, 5))
	              (std::make_pair (2, 9)))
{
}

Tailor::Tailor ()
	: Building(TAILOR,
	           BuildingType::stone,
	           Resource::stone + Resource::cloth,
	           Resource::prestige * 6),
	TradeBuilding(Resource::cloth,
	              Resource::prestige,
	              boost::assign::list_of
	              (std::make_pair (2, 4))
	              (std::make_pair (3, 6)))
{
}

Alchemist::Alchemist ()
	: Building(ALCHEMIST,
	           BuildingType::stone,
	           Resource::food + Resource::stone,
	           Resource::prestige * 6),
	TradeBuilding(Resource::food  +
	              Resource::wood  +
	              Resource::cloth +
	              Resource::stone,
	              Resource::gold,
	              boost::assign::list_of
	              (std::make_pair (2, 1))
	              (std::make_pair (4, 2)))
{
}

Bank::Bank ()
	: Building(BANK,
	           BuildingType::stone,
	           Resource::wood + Resource::stone,
	           Resource::prestige * 6),
	TradeBuilding(Resource::denier,
	              Resource::gold,
	              boost::assign::list_of
	              (std::make_pair (2, 1))
	              (std::make_pair (5, 2)))
{
}

TradingPost::TradingPost ()
	: Building(TRADING_POST,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	ProductionBuilding(boost::assign::list_of(Resource::denier * 3),
	                   ResourceMap(0))
{
}

NCarpenter::NCarpenter(GameEngine *ge)
	: Building(NEUTRAL_CARPENTER,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	ConstructionBuilding(ge, BuildingType::wood)
{
}

FCarpenter::FCarpenter(GameEngine *ge)
	: Building(FIXED_CARPENTER,
	           BuildingType::fixed,
	           ResourceMap(0),
	           ResourceMap(0)),
	ConstructionBuilding(ge, BuildingType::wood)
{
}

Lawyer::Lawyer(GameEngine *ge)
	: Building(LAWYER,
	           BuildingType::wood,
	           Resource::wood + Resource::cloth,
	           Resource::prestige * 4),
	ConstructionBuilding(ge, BuildingType::residential)
{
}

Architect::Architect(GameEngine *ge)
	: Building(ARCHITECT,
	           BuildingType::stone,
	           Resource::food + Resource::stone,
	           Resource::prestige * 6),
	ConstructionBuilding(ge, BuildingType::prestige)
{
}

Mason::Mason(GameEngine *ge)
	: Building(MASON,
	           BuildingType::wood,
	           Resource::wood + Resource::food,
	           Resource::prestige * 4),
	ConstructionBuilding(ge, BuildingType::stone)
{
}

NMarketplace::NMarketplace ()
	: Building(NEUTRAL_MARKETPLACE,
	           BuildingType::neutral,
	           ResourceMap(0),
	           ResourceMap(0)),
	TradeBuilding(Resource::food  +
	              Resource::wood  +
	              Resource::gold  +
	              Resource::cloth +
	              Resource::stone,
	              Resource::denier,
	              boost::assign::list_of
	              (std::make_pair (1, 4)))
{
}

WMarketplace::WMarketplace ()
	: Building(WOOD_MARKETPLACE,
	           BuildingType::wood,
	           boost::assign::list_of
	           (Resource::wood + Resource::food)
	           (Resource::wood + Resource::wood)
	           (Resource::wood + Resource::gold)
	           (Resource::wood + Resource::cloth)
	           (Resource::wood + Resource::stone),
	           Resource::prestige * 4),
	TradeBuilding(Resource::food  +
	              Resource::wood  +
	              Resource::gold  +
	              Resource::cloth +
	              Resource::stone,
	              Resource::denier,
	              boost::assign::list_of
	              (std::make_pair (1, 6)))
{
}
