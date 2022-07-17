#ifndef DOCTOR_H_INCLUDED
#define DOCTOR_H_INCLUDED
#include <string>
#include <memory>
#include <vector>
using std::vector;
using std::string;
using std::shared_ptr;

#include "course.h"

namespace Faculty {

struct Doctor {
  string user_name_;
  string password_;
  string name_;
  string id_;
  string email_;

  vector<shared_ptr<Course>> teaching_courses_;

};

}



#endif // DOCTOR_H_INCLUDED
