#include "doctor-flow-control.h"
#include "doctors-manager.h"
#include "courses-manager.h"
#include "assignment.h"
#include "course.h"
#include "helper.h"
#include <iostream>
#include <cassert>
using std::cout;
using std::cin;
using std::endl;

namespace Faculty {

shared_ptr<DoctorsFlowController> gDoctorFlowController(new DoctorsFlowController());

bool DoctorsFlowController::IsValidUser(string user_name, string password) {
  return gDoctorsManager->GetUser(user_name, password) != nullptr;
}

void DoctorsFlowController::TakeControl(string user_name, string password) {
  current_doctor_ = gDoctorsManager->GetUser(user_name, password);

  cout << "\n\nWelcomme Doctor " << current_doctor_->name_ << ". You are logged in\n";

  ShowMainMenu();


}

void DoctorsFlowController::ShowMainMenu() {
  vector<string> menu = { "Create course", "List Courses", "View Course", "Log out" };

  while (true) {
    int choice= Helper::RunMenu(menu);

    if (choice == 1)
       AddCourse();
    else if (choice == 2)
      ListMyCourses();
    else if (choice == 3)
      ViewCourse();
    else
      break;  // log out
  }
}
void DoctorsFlowController::AddCourse(){
current_doctor_->teaching_courses_.push_back(gCoursesManager->AddCourse(current_doctor_));

}

void DoctorsFlowController::SignUp() {
  shared_ptr<Doctor> doctor(new Doctor());

  while (true) {
    // More clever handling is needed...e.hg. input spaces
    cout << "Enter user name: ";
    cin >> doctor->user_name_;

    cout << "Enter password: ";
    cin >> doctor->password_;

    if (IsValidUser(doctor->user_name_, doctor->password_))
      cout << "\nERROR: User already exist...Try again\n\n";
    else
      break;
  }

  cout << "Enter Full Name: ";
  // getline reads last \n
  do {
    getline(cin, doctor->name_);
  } while (doctor->name_.size() == 0);

  cout << "Enter Doctor ID: ";
  cin >> doctor->id_;

  cout << "Enter Email: ";
  cin >> doctor->email_;

  gDoctorsManager->doctors_vec_.push_back(doctor);
}
void DoctorsFlowController::ListMyCourses() {
  cout << "\n\nMy Courses list: \n";

  int pos = 1;

  for (auto course : current_doctor_->teaching_courses_)
    printf("%d) Course %s - Code %s\n", pos++, course->name_.c_str(), course->code_.c_str());

}

void DoctorsFlowController::ViewCourse(){
ListMyCourses();

cout <<"\nEnter Choice: ";
int choice;
cin >> choice;
// Gotta handle wrong input after,
shared_ptr <Course> current_course_= current_doctor_->teaching_courses_[choice-1];
cout << current_course_->name_<<"\n";

ShowCourseOperationsMenu(current_course_);
}


 //Run it when user selects View Course...when finish..should back to the Main menu
void DoctorsFlowController::ShowCourseOperationsMenu(shared_ptr<Course> current_course_) {
  vector<string> menu = { "List Assignments", "Create Assignment", "View Assignment", "Back" };

  int choice = Helper::RunMenu(menu);
  if(choice==1)ListAssignments(current_course_);
  else if(choice==2) CreateAssignment(current_course_);
  else if(choice==3) ViewAssignment(current_course_);


}

void DoctorsFlowController::ListAssignments(shared_ptr<Course> current_course_){

  cout << "\n\nAssignments list: \n";
    if((current_course_->assignments_.size())==0){
            cout<<"No Registered Assignments\n";
            return;
    }
  int pos = 1;

  for (auto as : current_course_->assignments_)
    cout<<"\n"<<as->content_;
  return;
}

void DoctorsFlowController::CreateAssignment(shared_ptr<Course> current_course_)
{
shared_ptr<Assignment> new_assignment_(new Assignment());
cout << "Enter The Content: \n";
string temp;
cin>>temp;
new_assignment_->content_=temp;
cout<<"Enter Max. Grade: ";
cin>>new_assignment_->max_grade_;
new_assignment_->course_=current_course_;
current_course_->assignments_.push_back(new_assignment_);
cout<<"Done \n";


}
void DoctorsFlowController::ViewAssignment(shared_ptr<Course> current_course_){
ListAssignments(current_course_);
cout <<"\nEnter Choice: ";
int choice=Helper::ReadInt(1,current_course_->assignments_.size())-1;
// Gotta handle wrong input after,
shared_ptr <Assignment> current_assignment_= current_course_->assignments_[choice-1];
ShowAssignmentOperationsMenu(current_assignment_);
}

void DoctorsFlowController::ShowAssignmentOperationsMenu(shared_ptr<Assignment> current_assignment_) {
  vector<string> menu = { "Show Info", "Show Grades Report", "List Solutions", "View Solution", "Back" };

  int choice = Helper::RunMenu(menu);
    if(choice==1)ShowInfo(current_assignment_);
    else if(choice==2) ShowGradesReport(current_assignment_);
    else if(choice==3) ListSolutions(current_assignment_);
    else if(choice==4) ViewSolution(current_assignment_);
}
void DoctorsFlowController::ShowInfo(shared_ptr<Assignment> current_assignment_){
cout << current_assignment_->content_<<"   "<<current_assignment_->max_grade_<<"\n";

}

void DoctorsFlowController::ShowGradesReport(shared_ptr<Assignment> current_assignment_){

    //Needs Improvements

    int size=current_assignment_->assignment_solutions_.size();
    if(!size){
        cout<<"No Solutions Have Been Submitted Yet...\n";
        return;
    }
    else{
        cout <<size<<" Solutions Submitted\n";
    }
    size=0;
    long long total=0;

    for(auto a: current_assignment_->assignment_solutions_){
        if(a->is_graded){
        size++;
        total+=a->grade_;
        }
    }
    cout <<(total/current_assignment_->max_grade_ * size)*100<<" % \n";


}

void DoctorsFlowController::ListSolutions(shared_ptr<Assignment> current_assignment){
    int i=1;
for(auto a : current_assignment->assignment_solutions_){
printf("%d) Student: %s  \n Answer: %s \n",i, a->student_->name_.c_str(),a->answer_.c_str());
//if(a->is_graded)cout<<"Grade: "<<a->grade_<<"\n";
//else cout<<"Hasn't been graded yet..";
}
}
void DoctorsFlowController::ViewSolution(shared_ptr<Assignment> current_assignment){
ListSolutions(current_assignment);
cout <<"\nEnter Choice: ";
int choice;
cin >> choice;
// Gotta handle wrong input after,
shared_ptr <AssignmentSolution> current_assignment_solution_= current_assignment->assignment_solutions_[choice-1];
ShowAssignmentSolutionOperationsMenu(current_assignment_solution_);
}
void DoctorsFlowController::ShowAssignmentSolutionOperationsMenu(shared_ptr <AssignmentSolution> current_assignment_solution_) {
  vector<string> menu = { "Show Info", "Set Grade", "Set a Comment", "Back" };

  int choice = Helper::RunMenu(menu);
   if(choice==1)ShowInfo(current_assignment_solution_);
    else if(choice==2) SetGrade(current_assignment_solution_);
    else if(choice==3) SetComment(current_assignment_solution_);
}
void DoctorsFlowController::ShowInfo(shared_ptr <AssignmentSolution> current_assignment_solution_){
cout <<"Answer: "<< current_assignment_solution_->answer_<<endl;
if(current_assignment_solution_->is_graded){
    printf("Grade: %d \n Student: %s \n",current_assignment_solution_->grade_,current_assignment_solution_->student_->name_.c_str());

}
else{
    printf("Grade: NA \n Student: %s \n",current_assignment_solution_->student_->name_.c_str());
}

}
void DoctorsFlowController::SetGrade(shared_ptr <AssignmentSolution> current_assignment_solution_){

cout<<"Enter Grade: ";
cin>>current_assignment_solution_->grade_;
cout<<"Done.. :)";
}
void DoctorsFlowController::SetComment(shared_ptr <AssignmentSolution> current_assignment_solution_){
cout<<"Enter Comment: ";
cin>>current_assignment_solution_->staff_comments;
cout<<"Done.. :)";


}


}
