/**
 *  This header file defines the ContinuousPulseFunction class, which is
 *based on the PulseFunction templated class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _UTILITIES_CONTINUOUS_PULSE_FUNCTION_H_
#define _UTILITIES_CONTINUOUS_PULSE_FUNCTION_H_

#include "utilities/functions/continuous_step_function.h"
#include "utilities/functions/pulse_function.h"

namespace utilities
{
namespace functions
{
class ContinuousPulseFunction
    : public PulseFunction<utilities::ContinuousSignalType>
{
public:
  ContinuousPulseFunction(const ContinuousStepFunction& step_function,
                          double df);
  ContinuousPulseFunction(const ContinuousStepFunction& step_function,
                          ros::Duration df);
  ContinuousPulseFunction(double d0, double df, double qf,
                          bool ascending = false, bool negated = false);
  ContinuousPulseFunction(const ros::Duration& d0, const ros::Duration& df,
                          double qf, bool ascending = false,
                          bool negated = false);
  ContinuousPulseFunction(double d0, double df, double q0, double qf,
                          bool ascending = false, bool negated = false);
  ContinuousPulseFunction(const ros::Duration& d0, const ros::Duration& df,
                          double q0, double qf, bool ascending = false,
                          bool negated = false);
  ContinuousPulseFunction(const ContinuousPulseFunction& function);
  virtual ~ContinuousPulseFunction();
};

typedef boost::shared_ptr<ContinuousPulseFunction> ContinuousPulseFunctionPtr;
typedef boost::shared_ptr<ContinuousPulseFunction const>
    ContinuousPulseFunctionConstPtr;
}
}

#endif // _UTILITIES_CONTINUOUS_PULSE_FUNCTION_H_
