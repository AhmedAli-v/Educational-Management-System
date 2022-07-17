#include "user-flow-control.h"
#include "student-flow-control.h"
#include "doctor-flow-control.h"
#include <iostream>
#include <cassert>
#include "helper.h"
using std::cout;
using std::cin;


namespace Faculty {

shared_ptr<UserFlowController> gUserFlowController(new UserFlowController());

void UserFlowController::ShowMainMenu()
{
vector <string> mmenu={"\n\nPlease make a choice:\n","\t1 - Login\n","\t2 - Sign up\n","\t3 - Shutdown system\n","\tEnter Choice: "};

  while(true)
  {

    for(auto m : mmenu) cout <<m;
    int option;
    cin >> option;

    if(option == 1)
      Login();
    else if(option == 2)
      SignUp();
    else if(option == 3)
      break;
    else{
        cout<<"Enter a Valid Choice..";
        continue; // Shouldn't happen or code bug!
  }}
}
void UserFlowController::Login()
{
     cout<<"\nPlease enter user name and password:\n";

  string username;
  string password;

  cout<<"User Name: ";
  cin>>username;

  cout<<"Password: ";
  cin>>password;
if(gStudentFlowController->IsValidUser(username,password)){
    gStudentFlowController->TakeControl(username,password);
}
else if (gDoctorFlowController->IsValidUser(username,password)){
    gDoctorFlowController->TakeControl(username,password);
}
 else
  {
    cout<<"ERROR: Invalid login data...Try again, or If You Want To Get Back To The Main Menu Enter 1 \n ";
    int back;
    cin >> back;
    if(back==1)ShowMainMenu();
    else Login();

}
}
void UserFlowController::SignUp()
{
  cout<<"Please enter user type: (1 - student), (2 - doctor):\n";
  int type=Helper::ReadInt(1, 2);
  do{
  cin >> type;
  }
  while(type!= 1 && type!= 2);

  switch(type){
  case 1:
    gStudentFlowController->SignUp();
    break;
  case 2:
    gDoctorFlowController->SignUp();
    break;

  default:
    cout<<"wrong choice\n Try Again...\n";
    break;



  }
}
}

