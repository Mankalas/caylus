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

class MerchantGuild : public OmniscientBuilding
{
  public:
    MerchantGuild(GameEngine* ge);

    virtual void on_activate(void);
};

#endif /* !MERCHANT_GUILD_HH_ */
