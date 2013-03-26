//
// inn.hh for caylus_ia
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef INN_HH_
# define INN_HH_

# include "omniscient-building.hh"

namespace controller
{

	class Inn : public Building
	{
	public:
		Inn();

		Player * host();
		const Player * host() const;

		virtual bool has(const Player *) const;

	private:
		Player * host_;

		virtual void onActivate_();

		virtual bool canBeActivated_() const;
	};

}

std::ostream & operator<<(std::ostream &, const controller::Inn &);

# include "inn.hxx"

#endif /* !INN_HH_ */
