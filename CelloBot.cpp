// Cello with a holonomic drivetrain
// YOLO


#include "WPILib.h"
#include <cmath>

using namespace std;

namespace dreadbot {
  class CelloBot : IterativeRobot {
  private:
    DriverStation* ds;
    RobotDrive* drivebase;
    PowerDistributionPanel *pdp;
    Joystick* gamepad;
    
  public:
    void RobotInit() {
      SmartDashboard::init();
      ds = DriverStation::GetInstance();
      gamepad = new Joystick(0);
      pdp = new PowerDistributionPanel();
      drivebase = new RobotDrive(1, 2, 3, 4);
    }
    
    void AutonomousInit() { }
    void AutonomousPeriodic() { }
    
    void TeleopInit() {
      
    }
    void TeleopPeriodic() {
      drivebase->MecanumDrive_Polar(gamepad->GetRawAxis(0), gamepad->GetRawAxis(1), gamepad->GetRawAxis(2));
    }
  }
}

START_ROBOT_CLASS(dreadbot::CelloBot);
