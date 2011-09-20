#ifndef SIGNALS_HH
# define SIGNALS_HH

# include <boost/signals.hpp>

class Signals
{
public:

  typedef boost::signal<unsigned (unsigned)> nb_human_signal_t;
  typedef boost::signal<unsigned (unsigned, unsigned)> nb_ai_signal_t;

  typedef boost::signals::connection connection_t;

  boost::signal<unsigned (unsigned)> _ask_nb_humans;
  boost::signal<unsigned (unsigned, unsigned)> _ask_nb_ai;
}

#endif
