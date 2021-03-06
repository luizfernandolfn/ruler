/**
 *  This header file defines the UnaryPulseFunction class, which is
 *based on the PulseFunction templated class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _UTILITIES_UNARY_PULSE_FUNCTION_H_
#define _UTILITIES_UNARY_PULSE_FUNCTION_H_

#include "utilities/functions/unary_step_function.h"
#include "utilities/functions/pulse_function.h"

namespace utilities
{
namespace functions
{
class UnaryPulseFunction : public PulseFunction<utilities::UnarySignalType>
{
public:
  UnaryPulseFunction(const UnaryStepFunction& step_function, double df);
  UnaryPulseFunction(const UnaryStepFunction& step_function, ros::Duration df);
  UnaryPulseFunction(double d0, double df, bool ascending = false,
                     bool negated = false);
  UnaryPulseFunction(const ros::Duration& d0, const ros::Duration& df,
                     bool ascending = false, bool negated = false);
  UnaryPulseFunction(const UnaryPulseFunction& function);
  virtual ~UnaryPulseFunction();
};

typedef boost::shared_ptr<UnaryPulseFunction> UnaryPulseFunctionPtr;
typedef boost::shared_ptr<UnaryPulseFunction const> UnaryPulseFunctionConstPtr;
}
}

#endif // _UTILITIES_UNARY_PULSE_FUNCTION_H_
