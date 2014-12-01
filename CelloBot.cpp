// IT IS A CELLO
// WITH A HOLONOMIC DRIVETRAIN
// YOLO


#include "WPILib.h"
#include <cmath>

using namespace std;

namespace dreadbot {
  class CelloBot : IterativeRobot {
  private:
    DriverStation ds;
    DriveBase drivebase;
    
  public:
    CelloBot() {
      
    }
    void RobotInit() {
    }
    void AutonomousInit() {}
  }
}
START_ROBOT_CLASS(dreadbot::CelloBot);
