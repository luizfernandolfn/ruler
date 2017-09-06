/**
 *  This header file defines the ROSNode class. It is highly recommended
 *  whenever an oriented-object programming ROS Node class is created
 *  to enhance this one.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _UTILITIES_ROS_NODE_H_
#define _UTILITIES_ROS_NODE_H_

#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>
#include "utilities/exception.h"

namespace utilities
{
class ROSNode
{
public:
  virtual ~ROSNode(); // destructor
  virtual void run(); // standard spin method (according to the given loop rate)
  friend std::ostream& operator<<(std::ostream& out, const ROSNode& node);

protected:
  ROSNode(ros::NodeHandlePtr nh, float loop_rate); // protected constructor
  ros::NodeHandlePtr getNodeHandle() const;
  std::string getName() const;
  bool ok() const;
  void shutdown(std::string message = "") const;
  virtual void reset();
  
private:
  float loop_rate_; // positive spin rate
  std::string name_; // ROS node name
  ros::NodeHandlePtr nh_; // private ros node handle (has-a relationship)
  virtual bool isSettedUp();
  virtual void init();
  virtual void controlLoop() = 0;
  virtual void readParameters();
};
}

#endif // _UTILITIES_ROS_NODE_H_
