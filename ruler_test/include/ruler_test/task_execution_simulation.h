/**
 *  This header file defines the TaskExecutionSimulation class.
 *
 *  Author: Adriano Henrique Rossette Leite (adrianohrl@unifei.edu.br)
 *  Maintainer: Expertinos UNIFEI (expertinos.unifei@gmail.com)
 */

#ifndef _RULER_TEST_TASK_EXECUTION_SIMULATION_H_
#define _RULER_TEST_TASK_EXECUTION_SIMULATION_H_

#include <ruler/task.h>
#include <utilities/simulation.h>

namespace ruler_test
{
class TaskExecutionSimulation : public utilities::Simulation
{
public:
  TaskExecutionSimulation(ruler::Task* task);
  virtual ~TaskExecutionSimulation();
  virtual void update(ros::Time timestamp = ros::Time::now());

private:
  double interruption_probability_;
  double resume_probability_;
  utilities::functions::TimeProbabilityDensityFunction* start_pdf_;
  utilities::functions::TimeProbabilityDensityFunction* interruption_pdf_;
  utilities::functions::TimeProbabilityDensityFunction* resuming_pdf_;
  utilities::functions::TimeProbabilityDensityFunction* end_pdf_;
  ruler::Task* task_;
  virtual void start(ros::Time timestamp);
  virtual void finish(ros::Time timestamp);
  virtual bool hasStarted(ros::Time timestamp) const = 0;
  virtual bool hasFinished(ros::Time timestamp) const = 0;
};
}

#endif // _RULER_TEST_TASK_EXECUTION_SIMULATION_H_
