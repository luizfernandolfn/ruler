#include "alliance/impatience.h"
#include "alliance/robot.h"

namespace alliance
{
Impatience::Impatience(Robot* robot, BehaviourSet* behaviour_set,
                       InterCommunication* monitor)
    : robot_(robot), monitor_(monitor)
{
  fast_rate_ = new utilities::functions::ContinuousSampleHolder(
      behaviour_set->getId() + "/impatience/fast_rate", 0.0,
      ros::Duration(10 * robot_->getTimeoutDuration().toSec()));
}

Impatience::Impatience(const Impatience& impatence)
    : robot_(impatence.robot_), monitor_(impatence.monitor_)
{
  fast_rate_ =
      new utilities::functions::ContinuousSampleHolder(*impatence.fast_rate_);
  // implementar a copia dos mapas de slow_rates_ e reliability_durations_
}

Impatience::~Impatience()
{
  std::map<std::string, utilities::functions::ContinuousSampleHolder*>::iterator
      it;
  it = slow_rates_.begin();
  while (it != slow_rates_.end())
  {
    if (it->second)
    {
      delete it->second;
      it->second = NULL;
    }
    it++;
  }
  if (fast_rate_)
  {
    delete fast_rate_;
    fast_rate_ = NULL;
  }
  it = reliability_durations_.begin();
  while (it != reliability_durations_.end())
  {
    if (it->second)
    {
      delete it->second;
      it->second = NULL;
    }
    it++;
  }
  robot_ = NULL;
  monitor_ = NULL;
}

double Impatience::getSlowRate(const std::string& robot_id,
                               const ros::Time& timestamp) const
{
  utilities::functions::ContinuousSampleHolder* sample_holder =
      slow_rates_.at(robot_id);
  return sample_holder->getValue(timestamp);
}

double Impatience::getFastRate(const ros::Time& timestamp) const
{
  return fast_rate_->getValue(timestamp);
}

ros::Duration
Impatience::getReliabilityDuration(const std::string& robot_id,
                                   const ros::Time& timestamp) const
{
  utilities::functions::ContinuousSampleHolder* sample_holder =
      reliability_durations_.at(robot_id);
  return ros::Duration(sample_holder->getValue(timestamp));
}

double Impatience::getLevel(const ros::Time& timestamp) const
{
  double level(fast_rate_->getValue(timestamp));
  utilities::functions::ContinuousSampleHolder* sample_holder;
  std::map<std::string,
           utilities::functions::ContinuousSampleHolder*>::const_iterator
      slow_rates_it(slow_rates_.begin()),
      reliability_durations_it(reliability_durations_.begin());
  while (slow_rates_it != slow_rates_.end())
  {
    sample_holder = reliability_durations_it->second;
    if (monitor_->received(slow_rates_it->first,
                           timestamp - robot_->getTimeoutDuration(),
                           timestamp) &&
        !monitor_->received(
            slow_rates_it->first, ros::Time(),
            timestamp - ros::Duration(sample_holder->getValue(timestamp))))
    {
      sample_holder = slow_rates_it->second;
      if (sample_holder->getValue(timestamp) < level)
      {
        level = sample_holder->getValue(timestamp);
      }
    }
    slow_rates_it++;
    reliability_durations_it++;
  }
  return level;
}

void Impatience::setSlowRate(const std::string& robot_id, double slow_rate,
                             const ros::Time& timestamp)
{
  if (slow_rate <= 0.0)
  {
    throw utilities::Exception("The impatience slow rate must be positive.");
  }
  if (slow_rate >= fast_rate_->getValue(timestamp))
  {
    throw utilities::Exception(
        "The impatience slow rate must be greater than the fast one.");
  }
  utilities::functions::ContinuousSampleHolder* sample_holder;
  std::map<std::string, utilities::functions::ContinuousSampleHolder*>::iterator
      it(slow_rates_.find(robot_id));
  if (it == slow_rates_.end())
  {
    sample_holder = new utilities::functions::ContinuousSampleHolder(
        robot_->getId() + "/" + robot_id + "/slow_rate", slow_rate,
        robot_->getTimeoutDuration(), timestamp);
    slow_rates_[robot_id] = sample_holder;
  }
  else
  {
    sample_holder = it->second;
  }
  ROS_DEBUG_STREAM("Updating " << *sample_holder << " to "
                               << slow_rate << ".");
  sample_holder->update(slow_rate, timestamp);
}

void Impatience::setFastRate(double fast_rate, const ros::Time& timestamp)
{
  if (fast_rate <= 0.0)
  {
    throw utilities::Exception("The impatience fast rate must be positive.");
  }
  ROS_DEBUG_STREAM("Updating " << *fast_rate_ << " to " << fast_rate << ".");
  fast_rate_->update(fast_rate, timestamp);
}

void Impatience::setReliabilityDuration(
    const std::string& robot_id, const ros::Duration& reliability_duration,
    const ros::Time& timestamp)
{
  utilities::functions::ContinuousSampleHolder* sample_holder;
  std::map<std::string, utilities::functions::ContinuousSampleHolder*>::iterator
      it(reliability_durations_.find(robot_id));
  if (it == slow_rates_.end())
  {
    sample_holder = new utilities::functions::ContinuousSampleHolder(
        robot_->getId() + "/" + robot_id + "/reliability_duration",
        reliability_duration.toSec(), robot_->getTimeoutDuration(), timestamp);
    reliability_durations_[robot_id] = sample_holder;
  }
  else
  {
    sample_holder = it->second;
  }
  ROS_DEBUG_STREAM("Updating " << *sample_holder << " to "
                               << reliability_duration.toSec() << " [s].");
  sample_holder->update(reliability_duration.toSec(), timestamp);
}
}
