#ifndef TEACHER_HPP
#define TEACHER_HPP

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<common.hpp>
#include<fstream>

class Teacher {
public:
	void set_subjects(std::vector <std::string> sub_list);     //Add subjects to a teacher's subject list file
	std::vector <std::string> get_subjects();                 //Get a vector of teacher_user's subjects
	
	std::map <std::string, double> attd_percent(std::string subject); //Get a map containing students attendance%
																	//Needs to be defined
																	//files containing attd% required

	void set_attendance(std::string subject_code, std::string date); //Marks present for selected date
																	//date in "dd-mm-yy"
																	//Hit ENTER key after each roll no 
																	//Hit F or f and ENTER to exit

private:
	std::string teacher_user;
	std::vector <std::string> student_list;
	std::map <std::string, double> attd_percent_map;


};

void Teacher::set_subjects(std::vector <std::string> sub_list) {
	std::ofstream sub_list_ofstream(teacher_user + ".subls", std::ios::app);
	for (auto i : sub_list) {
		sub_list_ofstream << i << std::endl;
	}
}

std::vector <std::string> Teacher::get_subjects() {
	std::ifstream sub_list_ifstream(teacher_user + ".subls");
	std::vector <std::string> sub_vector;
	std::string str;
	int i = 0;
	while (std::getline(sub_list_ifstream, str)) {
		sub_vector.push_back(str);
	}

	return sub_vector;
}

/*
std::map <std::string, double> Teacher::attd_percent(std::string subject) {
	std::ifstream sub_instream(______);

}
*/

void Teacher::set_attendance(std::string subject_code, std::string date) {
	std::vector <std::string> roll_no_list;
	std::string input;

	while (true) {
		std::cin >> input;
		if (input == "f" || input == "F") {
			break;
		}
		roll_no_list.push_back(input);
	}
	for (int i = 0; i < roll_no_list.size(); i++) {
		std::ofstream student_instream(("ue23c01" + roll_no_list[i] + subject_code + ".att"), std::ios::app);
		student_instream << std::endl << date + "-p";
	}
}


#endif
