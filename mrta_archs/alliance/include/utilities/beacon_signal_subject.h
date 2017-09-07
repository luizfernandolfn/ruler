#ifndef _UTILITIES_BEACON_SIGNAL_SUBJECT_H_
#define _UTILITIES_BEACON_SIGNAL_SUBJECT_H_

#include <boost/enable_shared_from_this.hpp>
#include <alliance_msgs/BeaconSignal.h>
#include "utilities/beacon_signal_event.h"
#include "utilities/beacon_signal_observer.h"
#include <utilities/subject.h>

namespace utilities
{
class BeaconSignalSubject
    : public Subject,
      public boost::enable_shared_from_this<BeaconSignalSubject>
{
public:
  BeaconSignalSubject(const std::string& id);
  BeaconSignalSubject(const BeaconSignalSubject& subject);
  virtual ~BeaconSignalSubject();

protected:
  void notify(const alliance_msgs::BeaconSignal& msg);
  void registerObserver(const BeaconSignalObserverPtr& observer);
};

typedef boost::shared_ptr<BeaconSignalSubject> BeaconSignalSubjectPtr;
typedef boost::shared_ptr<BeaconSignalSubject const>
    BeaconSignalSubjectConstPtr;
}

#endif // _UTILITIES_BEACON_SIGNAL_SUBJECT_H_
