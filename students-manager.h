#ifndef STUDENTS-MANAGER_H_INCLUDED
#define STUDENTS-MANAGER_H_INCLUDED
#include <vector>
#include <string>
#include "student.h"
using std::vector;
using std::string;


namespace Faculty{
struct StudentsManager {
  void AddDummyData();
  void ShowStudents();
 shared_ptr<Student> GetUser(string user_name, string password);
  vector<shared_ptr<Student>> students_vec_;


};
extern shared_ptr<StudentsManager> gStudentsManager;

}
#endif // STUDENTS-MANAGER_H_INCLUDED
