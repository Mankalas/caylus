//
// inn.hxx for caylus_ia
// Made by nicuveo <crucuny@gmail.com>
//

#ifndef INN_HXX_
# define INN_HXX_


inline Player * Inn::host()
{
	return host_;
}

inline const Player * Inn::host() const
{
	return host_;
}


inline std::ostream &
operator<<(std::ostream & o, const Inn & inn)
{
	o << inn.name();
	if (inn.host())
	{
		o << " (" << inn.host()->name() << ") ";
	}
	if (inn.worker())
	{
		o << " : " << inn.worker()->name();
	}
	return o;
}


#endif /* !INN_HXX_ */
