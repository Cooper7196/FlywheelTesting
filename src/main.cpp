#include "main.h"
#include <bitset>
#include <string>
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */

double goal = 3600;
pros::Motor flywheel_mtr(20);

Flywheel flywheel(&flywheel_mtr, new VelPID(0, 0.05, 0.5, 3.5, -1740, 0.1), new EMAFilter(0.15), 21, 50);

void on_right_button()
{
	goal += 100;
}
void on_left_button()
{
	goal -= 100;
}

void on_center_button()
{
	flywheel.isRecovering = false;
}

void updateInfo()
{
	// pros::lcd::clear_line(1);
	// pros::lcd::set_text(1, "Current: " + std::to_string(flywheel.getCurrentRPM()));
	pros::lcd::clear_line(2);
	pros::lcd::set_text(2, "Goal: " + std::to_string(goal));
	pros::lcd::clear_line(3);
	pros::lcd::set_text(3, "Temp: " + std::to_string(flywheel_mtr.get_temperature()) + " C");
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	pros::lcd::initialize();
	pros::lcd::set_text(1, std::to_string(goal));

	pros::lcd::register_btn0_cb(on_left_button);
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn2_cb(on_right_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol()
{

	bool recovering = false;

	printf("Speed,Target,Voltage,Integral,Derivative\n");
	while (true)
	{
		updateInfo();
		// oldVelocity = filteredVelocity;
		flywheel.setTargetRPM(goal);
		// printf("%f\n", flywheel_mtr.get_actual_velocity());
		pros::delay(20);
	}
}
