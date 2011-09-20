/*!
  \file   all-buildings.cc
  \brief  Implementation of buildings' constructors

  \author nicuveo
  \date   2009-01-06
*/

#include "all-buildings.hh"

using namespace controller;

Statue::Statue ()
  : Building("Statue",
             BuildingType::prestige,
             Resource::stone * 2 + Resource::gold,
             Resource::prestige * 7 + Resource::favor)
{
}

Theater::Theater ()
  : Building("Theater",
             BuildingType::prestige,
             Resource::wood * 3 + Resource::gold * 2,
             Resource::prestige * 14 + Resource::favor)
{
}

College::College ()
  : Building("College",
             BuildingType::prestige,
             Resource::stone * 3 + Resource::gold * 2,
             Resource::prestige * 14 + Resource::favor)
{
}

Monument::Monument ()
  : Building("Monument",
             BuildingType::prestige,
             Resource::stone * 4 + Resource::gold * 2,
             Resource::prestige * 14 + Resource::favor * 2)
{
}

Granary::Granary ()
  : Building ("Granary",
              BuildingType::prestige,
              Resource::food * 3 + Resource::gold,
              Resource::prestige * 10)
{
}

Weaver::Weaver ()
  : Building ("Weaver",
              BuildingType::prestige,
              Resource::cloth * 3 + Resource::gold,
              Resource::prestige * 12)
{
}

Cathedral::Cathedral ()
  : Building ("Cathedral",
              BuildingType::prestige,
              Resource::stone * 5 + Resource::gold * 3,
              Resource::prestige * 25)
{
}

GoldMine::GoldMine ()
  : Building("Gold mine",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0)),
    ProductionBuilding(boost::assign::list_of(Resource::gold),
                       ResourceMap(0))
{
}

NQuarry::NQuarry ()
  : Building("Neutral Quarry",
             BuildingType::neutral,
             ResourceMap(0),
             ResourceMap(0)),
    ProductionBuilding(boost::assign::list_of(Resource::stone),
                       ResourceMap(0))
{
}

WQuarry::WQuarry ()
  : Building("Wood Quarry",
             BuildingType::wood,
             Resource::food + Resource::wood,
             Resource::prestige * 2),
    ProductionBuilding(boost::assign::list_of(Resource::wood * 2),
                       ResourceMap(0))
{
}

Workshop::Workshop ()
  : Building("Workshop",
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
  : Building("Neutral Farm",
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
  : Building("Wood food Farm",
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
  : Building("Wood cloth Farm",
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
  : Building("Stone Farm",
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
  : Building("Forest",
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
  : Building("Park",
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
  : Building("Neutral Sawmill",
             BuildingType::neutral,
             ResourceMap(0),
             ResourceMap(0)),
    ProductionBuilding(boost::assign::list_of
                       (Resource::wood),
                       ResourceMap(0))
{
}

WSawmill::WSawmill ()
  : Building("Wood Sawmill",
             BuildingType::wood,
             Resource::food + Resource::wood,
             Resource::prestige * 2),
    ProductionBuilding(boost::assign::list_of
                       (Resource::wood * 2),
                       ResourceMap(0))
{
}

Residence::Residence ()
  : Building("Residence",
             BuildingType::residential,
             Resource::cloth + Resource::denier,
             Resource::prestige * 2)
{
}

Library::Library ()
  : Building("Library",
             BuildingType::prestige,
             Resource::wood * 3 + Resource::gold,
             Resource::prestige * 10)
{
}

Hotel::Hotel ()
  : Building("Hotel",
             BuildingType::prestige,
             Resource::stone * 3 + Resource::gold * 2,
             Resource::prestige * 16),
    ResidentialBuilding(2)
{
}

Church::Church ()
  : Building("Church",
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
  : Building("Fixed Peddler",
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
  : Building("Wood Peddler",
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
  : Building("Jeweller",
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
  : Building("Tailor",
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
  : Building("Alchemist",
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
  : Building("Bank",
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
  : Building("Trading post",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0)),
    ProductionBuilding(boost::assign::list_of(Resource::denier * 3),
                       ResourceMap(0))
{
}

NCarpenter::NCarpenter(GameEngine* ge)
  : Building("Neutral Carpenter",
             BuildingType::neutral,
             ResourceMap(0),
             ResourceMap(0)),
    ConstructionBuilding(ge, BuildingType::wood)
{
}

FCarpenter::FCarpenter(GameEngine* ge)
  : Building("Fixed Carpenter",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0)),
    ConstructionBuilding(ge, BuildingType::wood)
{
}

Lawyer::Lawyer(GameEngine* ge)
  : Building("Lawyer",
             BuildingType::wood,
             Resource::wood + Resource::cloth,
             Resource::prestige * 4),
    ConstructionBuilding(ge, BuildingType::residential)
{
}

Architect::Architect(GameEngine* ge)
  : Building("Architect",
             BuildingType::stone,
             Resource::food + Resource::stone,
             Resource::prestige * 6),
    ConstructionBuilding(ge, BuildingType::prestige)
{
}

Mason::Mason(GameEngine* ge)
  : Building("Mason",
             BuildingType::wood,
             Resource::wood + Resource::food,
             Resource::prestige * 4),
    ConstructionBuilding(ge, BuildingType::stone)
{
}

NMarketplace::NMarketplace ()
  : Building("Neutral Marketplace",
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
  : Building("Wood Marketplace",
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
