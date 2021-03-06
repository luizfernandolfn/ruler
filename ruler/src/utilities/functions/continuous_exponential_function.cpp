/**
 *  This source file implements the ContinuousExponentialFunction class, which
 *is based on the ExponentialFunction templated class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#include "utilities/functions/continuous_exponential_function.h"

namespace utilities
{
namespace functions
{
ContinuousExponentialFunction::ContinuousExponentialFunction(
    double d0, double df, double q0, double qf, double k, double base,
    bool ascending, bool negated)
    : ExponentialFunction<utilities::ContinuousSignalType>::ExponentialFunction(
          d0, df, q0, qf, k, base, ascending, negated)
{
}

ContinuousExponentialFunction::ContinuousExponentialFunction(
    const ros::Duration& d0, const ros::Duration& df, double q0, double qf,
    double k, double base, bool ascending, bool negated)
    : ExponentialFunction<utilities::ContinuousSignalType>::ExponentialFunction(
          d0, df, q0, qf, k, base, ascending, negated)
{
}

ContinuousExponentialFunction::ContinuousExponentialFunction(
    const ContinuousExponentialFunction& function)
    : ExponentialFunction<utilities::ContinuousSignalType>::ExponentialFunction(
          function)
{
}

ContinuousExponentialFunction::~ContinuousExponentialFunction() {}
}
}
