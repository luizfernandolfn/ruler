/**
 *  This header file defines and implements the TaskFunction class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _RULER_TASK_FUNCTION_H_
#define _RULER_TASK_FUNCTION_H_

#include <list>
#include <ros/time.h>
#include "ruler/task_event.h"
#include "utilities/functions/function.h"

namespace ruler
{
template <typename T> class TaskFunction
{
public:
  TaskFunction(Task* task,
               utilities::functions::Function<T>* quantity_function);
  TaskFunction(const TaskFunction<T>& task_function);
  virtual ~TaskFunction();
  void update(const TaskEvent& notification);
  bool isNegated() const;
  T getLevel(ros::Time t) const;
  Task* getTask() const;

private:
  Task* task_;
  std::list<TaskEvent> events_;
  utilities::functions::Function<T>* quantity_function_;
};
}

#include "ruler/task.h"

namespace ruler
{
template <typename T>
TaskFunction<T>::TaskFunction(
    Task* task, utilities::functions::Function<T>* quantity_function)
    : task_(task), quantity_function_(quantity_function)
{
}

template <typename T>
TaskFunction<T>::TaskFunction(const TaskFunction<T>& task_function)
    : task_(task_function.task_),
      quantity_function_(task_function.quantity_function_)
{
}

template <typename T> TaskFunction<T>::~TaskFunction()
{
  task_ = NULL;
  if (quantity_function_)
  {
    delete quantity_function_;
    quantity_function_ = NULL;
  }
}

template <typename T>
void TaskFunction<T>::update(const TaskEvent& notification)
{
  events_.push_back(notification);
}

template <typename T> bool TaskFunction<T>::isNegated() const
{
  return quantity_function_->isNegated();
}

template <typename T> T TaskFunction<T>::getLevel(ros::Time t) const
{
  return quantity_function_->getValue(task_->getDuration(t));
}

template <typename T> Task* TaskFunction<T>::getTask() const { return task_; }
}

#endif // _RULER_TASK_FUNCTION_H_
