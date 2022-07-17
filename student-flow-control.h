#ifndef STUDENT-FLOW-CONTROL_H_INCLUDED
#define STUDENT-FLOW-CONTROL_H_INCLUDED
#include <string>
#include <memory>
#include <vector>
using std::vector;
using std::string;
using std::shared_ptr;

#include "student.h"
#include "doctor.h"

namespace Faculty {

/*
 * Take care of flow for 1 student (e.g.show menu
 * / do operations for it)
 */
struct StudentFlowController {
  void ShowMainMenu();
  void TakeControl(string user_name, string password);
  void ShowCourseMenu();
  void SignUp();
  void ListMyCourses();
  void ViewCourse();
  void RegisterInCourse();
  bool IsValidUser(string user_name, string password);
  void UnRegisterFromCourse();
  void SubmitCourseAssignment();




  // Temporary variables
  shared_ptr<Student> current_student_;
  shared_ptr<Course> current_course_;


};

extern shared_ptr<StudentFlowController> gStudentFlowController;


}


#endif // STUDENT-FLOW-CONTROL_H_INCLUDED
