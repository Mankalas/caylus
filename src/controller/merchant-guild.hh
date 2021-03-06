/**
 * @file   merchant-guild.hh
 * @author  Nicuveo
 * @date   Tue Feb  3 14:42:23 2009
 *
 * @brief Declaration of the MerchantGuild.
 *
 */

#ifndef MERCHANT_GUILD_HH_
# define MERCHANT_GUILD_HH_

# include "omniscient-building.hh"
# include "signals.hh"

namespace controller
{

	class MerchantGuild : public OmniscientBuilding
	{
	public:
		MerchantGuild(GameEngine * ge);

	private:
		i_v_signal_t ask_provost_shift_sig_;

		virtual void onActivate_();
	};

}
#endif /* !MERCHANT_GUILD_HH_ */
