/**
 * @file   trade-building.hh
 * @author Nicuvëo (crucuny@gmail.com)
 * @date   Jun  1 20:54:34 2009
 *
 * @brief  Declaration of the trade-building class.
 */

#ifndef TRADE_BUILDING_HH_
# define TRADE_BUILDING_HH_

# include "building.hh"

namespace controller
{
	/** \brief It represents all the buildings that, when activated, allow
	 * the worker to trade resouces. The constructor takes three additional
	 * arguments:
	 *   - supply: this is a vector containing the different resources
	 *     the worker must provide in the trade. For the peddler, this set
	 *     only contains deniers,
	 *   - demand: this is a vector containing the different resources
	 *     the owner obtain in the trade. For the peddler, this set
	 *     contains all four basic resources,
	 *   - ratios: this a vector containing pairs of unsigned ints that
	 *     give the ratios of the trade. For the church, it contains
	 *     (2, 3) and (4, 5) as two deniers may be traded against three
	 *     prestige points or four deniers against five pretige points.
	 */
	class TradeBuilding : virtual public Building
	{
	public:
		~TradeBuilding();

		const ResourceMap supply;
		const ResourceMap demand;
		const std::vector<std::pair<unsigned, unsigned> > ratios;

	protected:
		TradeBuilding(const ResourceMap & supply,
		              const ResourceMap & demand,
		              const std::vector<std::pair<unsigned, unsigned> > & ratios);

	private:
		std::vector<std::pair<ResourceMap, ResourceMap> > createExchangeVector() const;

		boost::signal<unsigned(void)> ask_resource_choice_;

		virtual void onActivate_();
	};

}

#endif /* !TRADE_BUILDING_HH_ */
