#ifndef USER_INTERFACE_HH
# define USER_INTERFACE_HH

# include <string>

class Road;

class UserInterface
{
public:

  virtual void showMessage(const std::string msg) const = 0;
  virtual int getInt() const = 0;
  virtual std::string getString() const = 0;
  virtual int getBuilding(const Road&, bool) const = 0;
  virtual std::string askName() const = 0;
  virtual int askWorkerPlacement(const Road&, bool = true) const = 0;
  virtual ResourceMap askResources(const ResourceMap& choices) const = 0;
  virtual bool askYesNo() const = 0;

};

#endif
