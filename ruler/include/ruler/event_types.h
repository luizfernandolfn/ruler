/**
 *  This header file defines the EventType enumerateds and the EventTypes
 *helper class, which is based on the EnumConverter abstract class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _RULER_EVENT_TYPES_H_
#define _RULER_EVENT_TYPES_H_

#include "utilities/enum_converter.h"

namespace ruler
{
namespace types
{
enum EventType
{
  STARTED,
  INTERRUPTED,
  RESUMED,
  FINISHED
};
}

typedef types::EventType EventType;

class EventTypes : public utilities::EnumConverter<EventType>
{
public:
  EventTypes(const EventType& enumarated);
  virtual ~EventTypes();
  virtual EventType getEnumerated(int code) const;
  virtual EventType getEnumerated(const std::string& name) const;
  virtual int getCode(const std::string& name) const;
  virtual int getCode(const EventType& enumerated) const;
  virtual std::string str(const EventType& enumerated) const;

  static EventType toEnumerated(int code);
  static EventType toEnumerated(const std::string& name);
  static int toCode(const EventType& enumerated);
  static std::string toString(const EventType& enumerated);
  static const char* toCString(const EventType& enumerated);
  static EventType getDefault();
  static std::vector<EventType> getAll();
};
}

#endif // _RULER_EVENT_TYPES_H_
