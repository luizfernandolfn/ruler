/**
 *  This header file defines and implements the LinearFunction class, which is
 *based on the Function abstract class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _UTILITIES_LINEAR_FUNCTION_H_
#define _UTILITIES_LINEAR_FUNCTION_H_

#include "utilities/functions/function.h"

namespace utilities
{
namespace functions
{
template <typename T> class LinearFunction : public Function<T>
{
public:
  virtual ~LinearFunction();

protected:
  LinearFunction(double d0, double df, double q0, double qf,
                 bool ascending = false);
  LinearFunction(ros::Duration d0, ros::Duration df, double q0, double qf,
                 bool ascending = false);
  LinearFunction(const LinearFunction<T>& function);

private:
  virtual double calculate(double d) const;
};

template <typename T>
LinearFunction<T>::LinearFunction(double d0, double df, double q0, double qf,
                                  bool ascending)
    : Function<T>::Function(d0, df, q0, qf, ascending)
{
}

template <typename T>
LinearFunction<T>::LinearFunction(ros::Duration d0, ros::Duration df, double q0,
                                  double qf, bool ascending)
    : Function<T>::Function(d0, df, q0, qf, ascending)
{
}

template <typename T>
LinearFunction<T>::LinearFunction(const LinearFunction<T>& function)
    : Function<T>::Function(function)
{
}

template <typename T> LinearFunction<T>::~LinearFunction() {}

template <typename T> double LinearFunction<T>::calculate(double d) const
{
  double rate((Function<T>::qf_ - Function<T>::q0_) /
              (Function<T>::df_ - Function<T>::d0_));
  return rate * (d - Function<T>::d0_) + Function<T>::q0_;
}
}
}

#endif // _UTILITIES_LINEAR_FUNCTION_H_