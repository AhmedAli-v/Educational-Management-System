#ifndef DOCTOR-FLOW-CONTROL_H_INCLUDED
#define DOCTOR-FLOW-CONTROL_H_INCLUDED

#include <string>
#include <memory>
#include <vector>
using std::vector;
using std::string;
using std::shared_ptr;

#include "student.h"
#include "doctor.h"

namespace Faculty {

struct DoctorsFlowController {
  bool IsValidUser(string user_name, string password);
  void TakeControl(string user_name, string password);
  void ShowMainMenu();
  void AddCourse();
  void SignUp();
  void ListMyCourses();
  void ViewCourse();
  void ShowCourseOperationsMenu(shared_ptr<Course> current_course_);
  void ListAssignments(shared_ptr<Course> current_course_);
  void CreateAssignment(shared_ptr<Course> current_course_);
  void ViewAssignment(shared_ptr<Course> current_course_);
  void ShowAssignmentOperationsMenu(shared_ptr<Assignment> current_assignment_);
  void ShowInfo(shared_ptr <Assignment> current_assignment_);
  void ShowGradesReport(shared_ptr<Assignment> current_assignment);
  void ListSolutions(shared_ptr<Assignment> current_assignment);
  void ViewSolution(shared_ptr<Assignment> current_assignment);
  void ShowAssignmentSolutionOperationsMenu(shared_ptr <AssignmentSolution> current_assignment_solution_); // lesa
  void ShowInfo(shared_ptr <AssignmentSolution> current_assignment_solution_);
  void SetGrade(shared_ptr <AssignmentSolution> current_assignment_solution_);
  void SetComment(shared_ptr <AssignmentSolution> current_assignment_solution_);

  shared_ptr<Doctor> current_doctor_;
};

extern shared_ptr<DoctorsFlowController> gDoctorFlowController;


}


#endif // DOCTOR-FLOW-CONTROL_H_INCLUDED
