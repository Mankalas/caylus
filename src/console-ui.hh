/**
 * @file   console-ui.hh
 * @author  <mankalas@localhost,>
 * @date   Tue Jan 20 21:14:58 2009
 *
 * @brief
 *
 *
 */

#ifndef CONSOLE_UI_HH
# define CONSOLE_UI_HH

# include <string>
# include <vector>
# include "resource-map.hh"
# include "user-interface.hh"

class Road;

class ConsoleUI : public UserInterface
{
public:
  static ConsoleUI* inst();

  int askProvostShift() const;
  int askChoice(int, int) const;
  int askChoice(std::vector<int>&) const;

  // Inherited from UserInterface
  virtual void showMessage(const std::string) const;
  virtual int getInt() const;
  virtual std::string getString() const;
  virtual int getBuilding(const Road&, bool = true) const;
  virtual std::string askName() const;
  virtual int askWorkerPlacement(const Road&, bool = true) const;
  virtual ResourceMap askResources(const ResourceMap& choices) const;
  virtual bool askYesNo() const;

private:
  static ConsoleUI* instance_;

  ConsoleUI();
};

#endif //CONSOLE_UI_HH
