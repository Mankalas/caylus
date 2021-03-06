/**
 * @file   all-buildings.hh
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun 6 23:58:43 2011
 *
 * @brief  This file contains all "normal" buildings.
 *
 * As those building classes do not contain anything besides their
 * constructor, they're all listed in one file.
 */

#ifndef ALL_BUILDINGS_HH_
# define ALL_BUILDINGS_HH_

# include "residential-building.hh"
# include "production-building.hh"
# include "trade-building.hh"
# include "favor-building.hh"
# include "construction-building.hh"
# include "const.hh"

namespace controller
{

	class Statue : public FavorBuilding
	{
	public:
		Statue();
	};

	class Theater : public FavorBuilding
	{
	public:
		Theater();
	};

	class College : public FavorBuilding
	{
	public:
		College();
	};

	class Monument : public FavorBuilding
	{
	public:
		Monument();
	};

	class Granary : public Building
	{
	public:
		Granary();
	};

	class Weaver : public Building
	{
	public:
		Weaver();
	};

	class Cathedral : public Building
	{
	public:
		Cathedral();
	};

	class GoldMine : public ProductionBuilding
	{
	public:
		GoldMine();
	};

	class NQuarry : public ProductionBuilding
	{
	public:
		NQuarry();
	};

	class WQuarry : public ProductionBuilding
	{
	public:
		WQuarry();
	};

	class Workshop : public ProductionBuilding
	{
	public:
		Workshop();
	};

	class NFarm : public ProductionBuilding
	{
	public:
		NFarm();
	};

	class WFFarm : public ProductionBuilding
	{
	public:
		WFFarm();
	};

	class WCFarm : public ProductionBuilding
	{
	public:
		WCFarm();
	};

	class SFarm : public ProductionBuilding
	{
	public:
		SFarm();
	};

	class Forest : public ProductionBuilding
	{
	public:
		Forest();
	};

	class Park : public ProductionBuilding
	{
	public:
		Park();
	};

	class NSawmill : public ProductionBuilding
	{
	public:
		NSawmill();
	};

	class WSawmill : public ProductionBuilding
	{
	public:
		WSawmill();
	};

	class Residence : public ResidentialBuilding
	{
	public:
		Residence();
	};

	class Library : public ResidentialBuilding
	{
	public:
		Library();
	};

	class Hotel : public ResidentialBuilding
	{
	public:
		Hotel();
	};

	class Church : public TradeBuilding, public FavorBuilding
	{
	public:
		Church();
	};

	class FPeddler : public TradeBuilding
	{
	public:
		FPeddler();
	};

	class WPeddler : public TradeBuilding
	{
	public:
		WPeddler();
	};

	class Jeweller : public TradeBuilding
	{
	public:
		Jeweller();
	};

	class Tailor : public TradeBuilding
	{
	public:
		Tailor();
	};

	class Alchemist : public TradeBuilding
	{
	public:
		Alchemist();
	};

	class Bank : public TradeBuilding
	{
	public:
		Bank();
	};

	class TradingPost : public ProductionBuilding
	{
	public:
		TradingPost();
	};

	class NCarpenter : public ConstructionBuilding
	{
	public:
		NCarpenter(GameEngine * ge);
	};

	class FCarpenter : public ConstructionBuilding
	{
	public:
		FCarpenter(GameEngine * ge);
	};

	class Lawyer : public ConstructionBuilding
	{
	public:
		Lawyer(GameEngine * ge);
	};

	class Architect : public ConstructionBuilding
	{
	public:
		Architect(GameEngine * ge);
	};

	class Mason : public ConstructionBuilding
	{
	public:
		Mason(GameEngine * ge);
	};

	class NMarketplace : public TradeBuilding
	{
	public:
		NMarketplace();
	};

	class WMarketplace : public TradeBuilding
	{
	public:
		WMarketplace();
	};

}

#endif /* !ALL_BUILDINGS_HH_ */
