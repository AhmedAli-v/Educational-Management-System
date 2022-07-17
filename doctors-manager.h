#ifndef DOCTORS-MANAGER_H_INCLUDED
#define DOCTORS-MANAGER_H_INCLUDED

#include <string>
#include <vector>
#include <memory>
using std::vector;
using std::string;
using std::shared_ptr;

#include "doctor.h"

namespace Faculty {

struct DoctorsManager {

  shared_ptr<Doctor> GetUser(string user_name, string password);
  void ShowDoctors();
  void AddDummyData();
  vector<shared_ptr<Doctor>> doctors_vec_;

};

extern shared_ptr<DoctorsManager> gDoctorsManager;

}



#endif // DOCTORS-MANAGER_H_INCLUDED
