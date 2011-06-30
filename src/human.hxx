#include "human.hh"
#include "user-interface.hh"

inline const UserInterface* Human::userInterface() const
{
  return user_interface_;
}

inline UserInterface* Human::userInterface()
{
  return user_interface_;
}
