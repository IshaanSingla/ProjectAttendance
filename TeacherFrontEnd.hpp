#ifndef TEACHER_FRONT
#define TEACHER_FRONT

#include "teacher.hpp"
#include <iomanip>


namespace teacher_namespace {
	
	Teacher t1;

	void view_subjects_page();
	void view_attd_page();
	void mark_attd_page();
	void attd_student_page();
	void ask_menu();

	void teacher_page() {
 
		t1.set_user("mintorattan");


		/*Login wala system nahi pata*/


		/*-------------------Menu---------------------------------*/

		int choice;

		std::cout << "User: " << t1.get_user() << std::endl << std::endl;

		std::cout << "Enter the no. to select an option: \n";
		std::cout << std::setw(7) << std::left << 1;
		std::cout << "View Subjects \n";
		std::cout << std::setw(7) << std::left << 2;
		std::cout << "View Attendance \n";
		std::cout << std::setw(7) << std::left << 3;
		std::cout << "Mark Attendance \n";
		std::cout << std::setw(7) << std::left << 4;
		std::cout << "Exit \n \n";

		std::cin >> choice;
		
		switch (choice) {
			case 1:
				system("cls");
				view_subjects_page();
				std::cout << "-----------------------------------------------------------" << std::endl ;
				ask_menu();
				break;

			case 2:
				system("cls");
				view_attd_page();
				std::cout << "-----------------------------------------------------------" << std::endl;
				ask_menu();
				break;

			case 3:
				system("cls");
				mark_attd_page();
				std::cout << "-----------------------------------------------------------" << std::endl;
				ask_menu();
				break;

			case 4:
				std::cout << "--------------------------------EXIT--------------------------------";
				exit(EXIT_SUCCESS);

			default:
				std::cout << "Invalid Input!";
				teacher_page();
				break;
		}







		/*---------------------------------------------------------*/
		/*------------------------------------------*/

	}


	void view_subjects_page() {
		std::cout << "-----------------------VIEW SUBJECTS-----------------------\n" << std::endl;
		std::cout << "Subject list: \n" << std::endl;
		std::vector <std::string> subjects_vec;

		for (int i = 0; i < t1.get_subjects().size(); i += 2) {
			subjects_vec.push_back(t1.get_subjects()[i]);
		}

		for (int i = 0; i < subjects_vec.size(); i++) {
			std::cout << std::setw(7) << i+1;
			std::cout << "     " << subjects_vec[i] << "\n";
		}
		std::cout << std::endl;
	}

	void view_attd_page() {
		std::cout << "-----------------------VIEW ATTENDANCE-----------------------\n" << std::endl;
		int choice;
		std::cout << "Select from the options: \n\n";
		std::cout << std::setw(7) << std::left << 1;
		std::cout << "View attendance % of students \n";

		std::cout << std::setw(7) << std::left << 2;
		std::cout << "View attendance of a student \n";

		std::cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			
			//Needs to be done.................................


			break;

		case 2:
			system("cls");
			view_subjects_page();
			attd_student_page();
			break;

		default:
			std::cout << "Invalid Input!";
			teacher_page();
			break;
		}


	}

	void mark_attd_page() {
		std::cout << "----------------------MARK ATTENDANCE----------------------\n" << std::endl;
		int sub_no;
		std::string date;

		view_subjects_page();

		std::cout <<'\n' << std::setw(20) << "Select the Subject no. : ";
		std::cin >> sub_no;

		std::string subject = t1.get_subjects()[sub_no-1];

		std::cout << '\n' << std::setw(20) << "Enter the Date in DD-MM-YY format: ";
		std::cin >> date;

		std::cout << "\nEnter the roll numbers (2-digits) to mark present (separated by ENTER KEY)\n";
		std::cout << "Enter f or F to finish" << std::endl;

		t1.set_attendance(t1.get_subject_code(subject), date);

		std::cout << "Updated Attendance: \n \n";
		

		
		//get_attendance(subject, date)............    //Needs to be done
	
	}

	void attd_student_page() {
		std::cout << "-----------------------VIEW ATTENDANCE---------------------" << std::endl;
		std::string roll_no;
		int sub_no;
		std::cout <<'\n' << std::setw(20) << "Select the Subject no. : ";
		std::cin >> sub_no;
		std::string subject = t1.get_subjects()[sub_no - 1];
		std::cout << "Enter Roll no. (2-digits) : ";
		std::cin >> roll_no;
		std::cout << std::endl << std::endl;
		std::cout << "Attendance : " << std::endl << std::endl;
		std::vector<std::string> st_attd_vec = t1.get_student_attendance(roll_no, t1.get_subject_code(subject));
		

		for (int i = 0; i < st_attd_vec.size()-1; i++) {
			for (int j = 0; j < 8; j++) {
				std::cout << st_attd_vec[i][j];
			}
			if (st_attd_vec[i][9] == 'p') {
				std::cout << std::setw(15) << std::uppercase << std::right << "PRESENT";
			}
			else {
				std::cout << std::setw(15) << std::uppercase << std::right << "ABSENT";
			}
		
			std::cout << std::endl;
		}

	}

	void ask_menu() {
		int choice;
		std::cout << "\n\nEnter 0 to go to Main Menu\n";
		std::cout << "Enter any other no. to exit\n";
		std::cin >> choice;
		if (choice == 0) {
			system("cls");
			teacher_page();
		}
		else {
			exit(EXIT_SUCCESS);
		}

	}
};

#endif TEACHER_FRONT

