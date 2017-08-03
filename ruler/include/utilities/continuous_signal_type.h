/**
 *  This header file defines the ContinuousSignalType class, which is based on
 *the NonUnarySignalType abstract class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _UTILITIES_CONTINUOUS_SIGNAL_TYPE_H_
#define _UTILITIES_CONTINUOUS_SIGNAL_TYPE_H_

#include "utilities/signal_type.h"

namespace utilities
{
class ContinuousSignalType : public SignalType<double>
{
public:
  ContinuousSignalType(double value = 0.0);
  ContinuousSignalType(const ContinuousSignalType& signal_type);
  virtual ~ContinuousSignalType();
  virtual bool isContinuous() const;
  using SignalType<double>::operator-;
  virtual ContinuousSignalType& operator-();
};
}

#endif // _UTILITIES_CONTINUOUS_SIGNAL_TYPE_H_
