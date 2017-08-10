/**
 *  This header file defines the Task class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _RULER_TASK_H_
#define _RULER_TASK_H_

#include <ros/time.h>
#include "ruler/resource_interface.h"
#include "ruler/task_event.h"
#include "ruler_msgs/Task.h"
#include "utilities/interval.h"
#include "utilities/ros_message_converter.h"
#include "utilities/subject.h"

namespace ruler
{
class ResourceReservationRequest;

template <typename T> class Resource;

class Task : public utilities::Subject<TaskEvent>,
             public utilities::ROSMessageConverter<ruler_msgs::Task>
{
public:
  Task(std::string id, std::string name, ros::Duration expected_duration,
       bool preemptive = false,
       utilities::Interval<ros::Time>* start_timestamp_bounds = NULL,
       utilities::Interval<ros::Time>* end_timestamp_bounds = NULL);
  Task(const ruler_msgs::Task& msg);
  Task(const Task& task);
  virtual ~Task();
  void addResourceReservationRequest(ResourceReservationRequest* request);
  void addResource(ResourceInterface* resource);
  void removeResource(ResourceInterface* resource);
  void start(ros::Time timestamp = ros::Time::now());
  void interrupt(ros::Time timestamp = ros::Time::now());
  void resume(ros::Time timestamp = ros::Time::now());
  void finish(ros::Time timestamp = ros::Time::now());
  void clearResources();
  double getDuration(ros::Time t = ros::Time::now()) const;
  std::string getName() const;
  ros::Duration getExpectedDuration() const;
  bool isPreemptive() const;
  ros::Time getStartTimestamp() const;
  ros::Time getLastInterruptionTimestamp() const;
  ros::Time getLastResumeTimestamp() const;
  ros::Time getEndTimestamp() const;
  bool hasStarted() const;
  bool isInterrupted() const;
  bool isRunning() const;
  bool hasFinished() const;
  virtual ruler_msgs::Task toMsg() const;
  using Subject<TaskEvent>::operator==;
  virtual bool operator==(const ruler_msgs::Task& msg) const;
  using Subject<TaskEvent>::operator!=;

private:
  std::string name_;
  ros::Duration expected_duration_;
  bool preemptive_;
  ros::Time start_timestamp_;
  ros::Time last_interruption_timestamp_;
  ros::Time end_timestamp_;
  ros::Time last_event_timestamp_;
  utilities::Interval<ros::Time>* start_timestamp_bounds_;
  utilities::Interval<ros::Time>* end_timestamp_bounds_;
  std::list<utilities::Interval<ros::Time>*> interruption_intervals_;
  std::list<ResourceReservationRequest*> resource_reservation_requests_;
};
}

#endif // _RULER_TASK_H_
