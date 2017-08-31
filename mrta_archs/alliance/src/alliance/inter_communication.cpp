#include "alliance/inter_communication.h"
#include "alliance/behaviour_set.h"
#include "alliance/robot.h"

namespace alliance
{
InterCommunication::InterCommunication(Robot* robot,
                                       BehaviourSet* behaviour_set)
    : BeaconSignalObserver::BeaconSignalObserver(behaviour_set->getId() +
                                                 "/inter_communication"),
      robot_(robot), task_(behaviour_set->getTask())
{
}

InterCommunication::InterCommunication(
    const InterCommunication& inter_communication)
    : BeaconSignalObserver::BeaconSignalObserver(inter_communication),
      robot_(inter_communication.robot_), task_(inter_communication.task_)
{
}

InterCommunication::~InterCommunication()
{
  robot_ = NULL;
  task_ = NULL;
  std::map<std::string, utilities::functions::UnarySampleHolder*>::iterator it(
      robots_.begin());
  while (it != robots_.end())
  {
    if (it->second)
    {
      delete it->second;
      it->second = NULL;
    }
    it++;
  }
  robots_.clear();
}

bool InterCommunication::received(const std::string& robot_id,
                                  const ros::Time& t1,
                                  const ros::Time& t2) const
{
  std::map<std::string,
           utilities::functions::UnarySampleHolder*>::const_iterator
      it(robots_.find(robot_id));
  if (it == robots_.end())
  {
    return false;
  }
  utilities::functions::UnarySampleHolder* sample_holder = it->second;
  return sample_holder->updated(t1, t2);
}

void InterCommunication::update(utilities::BeaconSignalEvent* event)
{
  if (event->isRelated(*robot_))
  {
    return;
  }
  if (!event->isRelated(*task_))
  {
    ROS_DEBUG_STREAM("Received beacon signal that is not related to "
                     << *task_ << " task.");
    return;
  }
  std::string robot_id(event->getMsg().header.frame_id);
  std::map<std::string, utilities::functions::UnarySampleHolder*>::iterator it(
      robots_.find(robot_id));
  utilities::functions::UnarySampleHolder* sample_holder;
  if (it != robots_.end())
  {
    sample_holder = it->second;
  }
  else
  {
    sample_holder = new utilities::functions::UnarySampleHolder(
        robot_id + "/function", robot_->getTimeoutDuration(),
        event->getTimestamp());
    robots_[robot_id] = sample_holder;
  }
  sample_holder->update(event->getTimestamp());
}
}
