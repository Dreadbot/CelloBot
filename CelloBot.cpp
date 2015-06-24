/* Code for a simple robot using a holonomic drivebase.
 * Drive speed is configurable in the Smart Dashboard.
 */

#include <WPILib.h>
#include <cmath>

//	settings
#define DEFAULT_DRIVESPEED 512.f
#define DEADZONE 0.01f
//	/settings

namespace dreadbot {
	class CelloBot : IterativeRobot {
	private:
		RobotDrive* drivebase;
		Joystick* gamepad;
		
	public:
		// Runs when the robot is first turned on
		void RobotInit() {
			SmartDashboard::init();
			gamepad = new Joystick(0);
			drivebase = new RobotDrive(1, 2, 3, 4);
		}
		
		// Runs once when the robot is enabled in teleop mode
		void TeleopInit() {
			// Send default value for DriveSpeed so it will show up on SD
			SmartDashboard::PutNumber("DriveSpeed", DEFAULT_DRIVESPEED);
		}
		
		// Runs every ~5ms during teleop period
		void TeleopPeriodic() {
			float speed = SmartDashboard::GetNumber("DriveSpeed", DEFAULT_DRIVESPEED);
			float x = speed*CurveInput(gamepad->GetRawAxis(0));
			float y = speed*CurveInput(gamepad->GetRawAxis(1));
			float r = speed*CurveInput(-gamepad->GetRawAxis(4));
			drivebase->MecanumDrive_Polar(x, y, r);
		}
		
		// Gives high precision at low magnitudes while scaling over the full control range. Also applies a deadzone to the input.
		// Significant flaw with y(x)=x*x was zero slope at x=0, resulting in very non-linear behavior. This formula should remedy that.
		static float CurveInput(float input) {
			return std::fabs(input) < DEADZONE ? 0.f : std::copysign(0.255000975f*(std::exp2(2.299113817f*std::fabs(input)) - 1.f), input);
		}
	};
}

START_ROBOT_CLASS(dreadbot::CelloBot);
