/**
 *  This source file implements the UnaryPulseFunction class, which
 *is based on the PulseFunction templated class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "utilities/functions/unary_pulse_function.h"

namespace utilities
{
namespace functions
{
UnaryPulseFunction::UnaryPulseFunction(double d0, double df, bool ascending,
                                       bool negated)
    : PulseFunction<utilities::UnarySignalType>::PulseFunction(
          d0, df, false, true, ascending, negated)
{
}

UnaryPulseFunction::UnaryPulseFunction(ros::Duration d0, ros::Duration df,
                                       bool ascending, bool negated)
    : PulseFunction<utilities::UnarySignalType>::PulseFunction(
          d0.toSec(), df.toSec(), false, true, ascending, negated)
{
}

UnaryPulseFunction::UnaryPulseFunction(const UnaryPulseFunction& function)
    : PulseFunction<utilities::UnarySignalType>::PulseFunction(function)
{
}

UnaryPulseFunction::~UnaryPulseFunction() {}
}
}
