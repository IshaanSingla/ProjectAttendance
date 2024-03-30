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

	std::string get_user();           
	std::string set_user(std::string);

	std::vector <std::string> get_subjects();                 //Get a vector of teacher_user's subjects
	
	//std::map <std::string, double> attd_percent(std::string subject); //Get a map containing students attendance%
																	//Needs to be defined
																	//files containing attd% required

	void set_attendance(std::string subject_code, std::string date); //Marks present for selected date
																	//date in "dd-mm-yy"
																	//Hit ENTER key after each roll no 
																	//Hit F or f and ENTER to exit
	std::vector <std::string> get_student_attendance(std::string roll_no, std::string subject_code);    //Returns a vector
																						//containing attendance 
																						//of a student for a subject

	std::string get_subject_code(std::string subject);


private:
	std::string teacher_user; 
	std::vector <std::string> student_list;
	std::map <std::string, double> attd_percent_map;


};

std::string Teacher::get_user() {
	return teacher_user;
}

std::string Teacher::set_user(std::string username){
	teacher_user = username;
	return username;
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

std::vector <std::string> Teacher::get_student_attendance(std::string roll_no, std::string subject_code) {
	std::ifstream attd_instream("ue23c01" + roll_no + subject_code + ".att");
	std::vector <std::string> attd_vec;
	std::string attd;

	while (attd_instream) {
		std::getline(attd_instream, attd);
		attd_vec.push_back(attd);
	}

	return attd_vec;
}

std::string Teacher::get_subject_code(std::string subject) {
	std::vector <std::string> sublist= get_subjects();
	for (int i = 0; i < sublist.size(); i += 2) {
		if (sublist[i] == subject) {
			return sublist[i + 1];
		}
	}
}

#endif
