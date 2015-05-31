#include <WPILib.h>
#include <cmath>

namespace dreadbot {
	class CelloBot : IterativeRobot {
	private:
		DriverStation* ds;
		RobotDrive* drivebase;
		Joystick* gamepad;
		
	public:
		void RobotInit() {
			SmartDashboard::init();
			ds = DriverStation::GetInstance();
			gamepad = new Joystick(0);
			drivebase = new RobotDrive(1, 2, 3, 4);
		}
		
		void TeleopInit() {
			SmartDashboard::PutNumber("DriveSpeed", 512.f);
		}
		
		void TeleopPeriodic() {
			float speed = SmartDashboard::GetNumber("DriveSpeed", 512.f);
			float x = speed*TransformInput(gamepad->GetRawAxis(0));
			float y = speed*TransformInput(gamepad->GetRawAxis(1));
			float r = speed*TransformInput(-gamepad->GetRawAxis(4));
			drivebase->MecanumDrive_Polar(x, y, r);
		}
		
		static float TransformInput(float input) {
			// Similar to x*x, but with positive dOut/dIn at x=0.
			return std::fabs(input) < 0.01f ? 0.f : std::copysign(0.255000975f*(std::exp2(2.299113817f*std::fabs(input)) - 1.f), input);
		}
	};
}

START_ROBOT_CLASS(dreadbot::CelloBot);
