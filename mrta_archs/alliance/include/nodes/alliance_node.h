#ifndef _ALLIANCE_NODE_H_
#define _ALLIANCE_NODE_H_

#include "alliance/robot.h"
#include <alliance_msgs/BeaconSignal.h>
#include "utilities/beacon_signal_subject.h"
#include <utilities/ros_node.h>

namespace nodes
{
class AllianceNode : public utilities::ROSNode,
                     public utilities::BeaconSignalSubject
{
public:
  AllianceNode(ros::NodeHandlePtr nh,
               float loop_rate = 30.0);
  virtual ~AllianceNode();

private:
  bool started_broadcasting_;
  alliance::RobotPtr robot_;
  ros::Publisher beacon_signal_pub_;
  ros::Subscriber beacon_signal_sub_;
  ros::Timer broadcast_timer_;
  virtual void readParameters();
  virtual void init();
  virtual void controlLoop();
  void beaconSignalCallback(const alliance_msgs::BeaconSignal& msg);
  void broadcastTimerCallback(const ros::TimerEvent& event);
};

typedef boost::scoped_ptr<AllianceNode> AllianceNodePtr;
}

#endif // _ALLIANCE_NODE_H_
