#include "alliance_test/border_protection.h"
#include <pluginlib/class_list_macros.h>

PLUGINLIB_EXPORT_CLASS(alliance_test::BorderProtection, alliance::Layer)

namespace alliance_test
{
BorderProtection::BorderProtection() : sonars_(NULL) {}

BorderProtection::~BorderProtection()
{
  if (sonars_)
  {
    delete sonars_;
    sonars_ = NULL;
  }
}

void BorderProtection::initialize(const std::string& name)
{
  Layer::initialize(name);
  sonars_ = new nodes::ROSSensorMessage<sensor_msgs::PointCloud>(
      nh_, "sonar", ros::Duration(1.0));
}

void BorderProtection::process()
{
  Layer::process();
  sonars_->publish();
}
}