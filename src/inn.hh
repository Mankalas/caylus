//
// inn.hh for caylus_ia
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef INN_HH_
# define INN_HH_


# include "omniscient-building.hh"


class Inn : public Building
{
  public:
    Inn();

    virtual void on_activate(void);
    Player* host();
    const Player* host() const;

  private:
    Player* host_;
};


std::ostream& operator<<(ostream&, const Inn&);


# include "inn.hxx"


#endif /* !INN_HH_ */
