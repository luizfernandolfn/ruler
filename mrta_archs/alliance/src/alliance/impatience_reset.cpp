#include "alliance/impatience_reset.h"
#include "alliance/robot.h"

namespace alliance
{
ImpatienceReset::ImpatienceReset()
{
}

ImpatienceReset::~ImpatienceReset() {}

void ImpatienceReset::init(const InterCommunicationPtr &monitor)
{
  if (!monitor_)
  {
    monitor_ = monitor;
  }
}

bool ImpatienceReset::isResetted(const ros::Time& timestamp) const
{
  return monitor_->received(monitor_->getLastUpdateTimestamp(), timestamp) &&
           !monitor_->received(ros::Time(), monitor_->getLastUpdateTimestamp());
}
}
