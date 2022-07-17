#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED


#include "course.h"
#include "assignment-solution.h"
#include "assignment.h"
#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <map>
using std::map;
using std::tuple;
using std::vector;
using std::vector;
using std::string;
using std::shared_ptr;

namespace Faculty{
struct Student {

  bool IsMyAuthData(string user_name, string password);
  vector<tuple<string, int, int, int>> ComputeGradesStatistic();



string user_name_;
  string password_;
  string name_;
  string id_;
  string email_;
  vector<shared_ptr<Course>> registered_courses_;
  vector<shared_ptr<AssignmentSolution>> assignments_solutions_;

  shared_ptr<AssignmentSolution> GetAssignmentSolution(shared_ptr<Assignment> assignment);

};



}
#endif // STUDENT_H_INCLUDED
