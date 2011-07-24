/**
 * @file   joust-field.cc
 * @author  <mankalas@localhost,>
 * @date   Wed Feb  4 11:40:25 2009
 *
 * @brief
 *
 *
 */

#include "joust-field.hh"
#include "console-ui.hh"

JoustField::JoustField()
  : Building("Joust field",
             BuildingType::fixed,
             ResourceMap(0),
             ResourceMap(0))
{
}

void JoustField::on_activate(void)
{
  if (worker_->resources()[Resource::denier] < 1 ||
      worker_->resources()[Resource::cloth] < 1)
  {
    std::cout << "Not enough resources. Try again." << std::endl;
    return;
  }
  worker_->askJoustField();
  if (worker_->askYesNo())
  {
    worker_->resources() -= ResourceMap(Resource::denier + Resource::cloth);
    worker_->resources() += Resource::favor;
  }
}
