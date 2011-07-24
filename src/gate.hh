//
// gate.hh for caylus_ia
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef GATE_HH_
# define GATE_HH_


# include "omniscient-building.hh"


class Gate : public OmniscientBuilding
{
  public:
    Gate(GameEngine* ge);

    virtual void on_activate(void);
};


#endif /* !GATE_HH_ */
