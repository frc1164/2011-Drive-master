

//left two motors need to be inverted




#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <CANJaguar.h>
#include <JoyStick.h>

class Robot: public frc::IterativeRobot {
public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		//assigns CANJaguar addresses
		frontLeft = new CANJaguar(8);
		frontRight = new CANJaguar(7);
		rearLeft = new CANJaguar(6);
		rearRight = new CANJaguar(4);

		Stick = new Joystick(0);

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

		//allows us to control the motors

		frontLeft->EnableControl();
		frontRight->EnableControl();
		rearLeft->EnableControl();
		rearRight->EnableControl();
	}

	void TeleopPeriodic() {

		//retrieves joystick axis values
		LeftX = Stick->GetRawAxis(0);
		LeftY = Stick->GetRawAxis(1);
		RightX = Stick->GetRawAxis(2);
		RightY = Stick->GetRawAxis(3);

		//math for wheel power
		forward = -LeftY;
		right = LeftX;
		clockwise = RightX;
		front_left = forward + clockwise + right;
		front_right = forward - clockwise - right;
		rear_left = forward + clockwise - right;
		rear_right = forward - clockwise + right;

		//sets wheels to calculated power
		frontLeft->Set(front_left);
		frontRight->Set(-front_right);
		rearLeft->Set(rear_left);
		rearRight->Set(-rear_right);

		SmartDashboard::PutNumber("LeftStick X value", LeftX);
		SmartDashboard::PutNumber("LeftStick Y value", LeftY);
		SmartDashboard::PutNumber("RightStick X value", RightX);




	}


	void TestPeriodic() {
		lw->Run();
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
	CANJaguar *frontLeft, *frontRight, *rearLeft, *rearRight;
	Joystick *Stick;
	double RightX, RightY, LeftX, LeftY, forward, right, clockwise, front_left, front_right, rear_left, rear_right;
};

START_ROBOT_CLASS(Robot)
