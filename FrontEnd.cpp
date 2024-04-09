#include <iostream>
#include <string>
#include "students.hpp"
#include "frontend.hpp"
#include "teachers.hpp"

void choose_designation(int, char, char);
bool log_in_student(int, char, char, Students&);
bool log_in_teacher(int TableWidth, char borderChar, char intersectionChar, Teachers& obj);
void subject_list(int, char, char, std::vector<std::string>&, Students&);
void subject_list_teacher(int TableWidth, char borderChar, char intersectionChar, std::vector<std::string>& subjects, Teachers& obj);
void menu(int, char, char);
void teacher_menu(int TableWidth, char borderChar, char intersectionChar);

Teachers t1;
Students s1;


int main()
{
    choose_designation(51, '-', '+');


    return 0;
}

void choose_designation(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Choose Designation", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1", "Teacher", false);
    printRow(TableWidth, "2", "Student", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
        bool is_logged_in;
        is_logged_in = log_in_teacher(51, '-', '+', t1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = t1.getSubjects();
            subject_list_teacher(100, '-', '+', subjects, t1);
            teacher_menu(61, '-', '+');


        }

        break;

    case 2:
    {
        bool is_logged_in;
        is_logged_in = log_in_student(51, '-', '+', s1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }
    }
    break;

    default:
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl << "Please try again." << std::endl;
        choose_designation(51, '-', '+');
        break;
    }
}

bool log_in_student(int TableWidth, char borderChar, char intersectionChar, Students& obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Welcome to Student Login Page", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::string username, password;
    printRow(TableWidth, "Enter Username:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> username;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Enter Password:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> password;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    if (obj.loguser(username, password) == true)
    {
        std::cout << "\033[0;32m" << std::endl;
        printRow(TableWidth, "Login Successful", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        system("cls");
        return true;
    }
    else
    {
        system("cls");
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "Login Unsuccessful", false);
        printRow(TableWidth, "Please try again", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        bool is_logged_in;
        is_logged_in = log_in_student(51, '-', '+', s1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }
        return false;
    }
}

void subject_list(int TableWidth, char borderChar, char intersectionChar, std::vector<std::string>& subjects, Students& obj)
{
    double percentage;
    std::string remarks;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow("SERIAL NO.", "SUBJECT", "ATTENDANCE", "ATTENDANCE%", "COMMENTS", true, false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    for (int i = 0; i < subjects.size(); i++)
    {
        percentage = obj.getpercent(i + 1);
        bool flag1;
        if (percentage < 65)
        {
            remarks = "DETAINED";
            flag1 = false;
        }
        else
        {
            remarks = "CLEAR";
            flag1 = true;
        }
        printRow(std::to_string(i + 1), subjects[i], std::to_string(7) + "/" + std::to_string(24), std::to_string(percentage), remarks, false, flag1);
    }
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
}

void menu(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "MENU", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1.", "Change Password", false);
    printRow(TableWidth, "2.", "Check Attendance Record", false);
    printRow(TableWidth, "3.", "Exit", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter the choice: ";
    std::cin >> choice;
    switch (choice) {
    case 1:
    {
        std::string new_pass;
        std::cout << "\nEnter new password: ";
        std::cin >> new_pass;
        if (s1.changepass(new_pass)) {
            system("cls");
            std::cout << "\033[0;32m" << std::endl;
            printRow(TableWidth, "Password changed successfully!", false);
            menu(61, '-', '+');
        }

        else {
            std::cout << "Something went wrong!" << std::endl << std::endl;
            menu(61, '-', '+');
        }

    }
    break;

    case 2:
    
        
        
        ///////////////////////////////////////////////
        ////////////////////////////////////////







    case 3:
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "--------------------------Exit--------------------------", false);
        exit(EXIT_SUCCESS);

    default:
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl << "Please try again." << std::endl;
        menu(61, '-', '+');
    }
}


bool log_in_teacher(int TableWidth, char borderChar, char intersectionChar, Teachers& obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Welcome to Teacher Login Page", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::string username, password;
    printRow(TableWidth, "Enter Username:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> username;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Enter Password:", false);
    std::cout << printCentre(TableWidth / 2, "            ");
    std::cin >> password;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    if (obj.loguser(username, password) == true)
    {
        std::cout << "\033[0;32m" << std::endl;
        printRow(TableWidth, "Login Successful", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        system("cls");
        return true;
    }
    else
    {
        system("cls");
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "Login Unsuccessful", false);
        printRow(TableWidth, "Please try again", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        bool is_logged_in;
        is_logged_in = log_in_teacher(51, '-', '+', t1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = t1.getSubjects();
            subject_list_teacher(60, '-', '+', subjects, t1);  
            menu(61, '-', '+');
        }
        return false;
    }
}


void subject_list_teacher(int TableWidth, char borderChar, char intersectionChar, std::vector<std::string>& subjects, Teachers& obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "SERIAL NO.", "SUBJECT", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);

    for (int i = 0; i < subjects.size(); i++)
    {
        printRow( TableWidth,std::to_string(i + 1), subjects[i], false);
    }
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
}

void teacher_menu(int TableWidth, char borderChar, char intersectionChar)
{
    int choice;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "MENU", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1.", "Mark Attendance", false);
    printRow(TableWidth, "2.", "Check Attendance Record", false);
    printRow(TableWidth, "3.", "Logout", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::cout << "Enter the choice: ";
    std::cin >> choice;
    switch (choice) {
    case 1:
    {
        int sub_choice;
        std::string date;
        std::vector<std::string> subjects = t1.getSubjects();
        subject_list_teacher(100, '-', '+', subjects, t1);
        std::cout << "\nChoose Subject: ";
        std::cin >> sub_choice;
        std::cout << "\nEnter date in DD/MM/YY format: ";
        std::cin >> date;

        
        int  mark_choice;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        printRow(TableWidth, "1.", "Mark Present", false);
        printRow(TableWidth, "2.", "Mark Absent", false);
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        std::cout << "\nEnter your choice: ";
        std::cin >> mark_choice;
        switch (mark_choice) 
        {
        case 1:
        {
            int roll = 0;
            std::vector<int> roll_no_vec;
            std::cout << "Enter the roll numbers of present students (Enter -1 to stop): ";

            while (roll != -1) {
                std::cin >> roll;
                roll_no_vec.push_back(roll);
            }

            t1.setPresentAttendance(date, sub_choice, roll_no_vec);
            system("cls");
            std::cout << "ATTENDANCE MARKED\n";
            teacher_menu(61, '-', '+');
            break;
        }

        case 2:
        {
            int rollno = 0;
            std::vector<int> roll_no_vector;
            std::cout << "Enter the roll numbers of absent students (Enter -1 to stop): ";

            while (rollno != -1) {
                std::cin >> rollno;
                roll_no_vector.push_back(rollno);
            }

            t1.setAbsentAttendance(date, sub_choice, roll_no_vector);
            system("cls");
            std::cout << "ATTENDANCE MARKED\n";
            teacher_menu(61, '-', '+');
            break;

        }



        }
    }
    break;

    case 2:
    {
        int sub_choice;
        std::vector <std::string> students;
        std::vector<std::string> subjects = t1.getSubjects();
        subject_list_teacher(100, '-', '+', subjects, t1);
        std::cout << "\nChoose Subject: ";
        std::cin >> sub_choice;
        students = t1.getStudents(sub_choice);
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        printRow(TableWidth, "SERIAL NO.", "STUDENT", false);
        printHorizontalLine(TableWidth, borderChar, intersectionChar);

        for (int i = 0; i < students.size(); i++)
        {
            printRow(TableWidth, std::to_string(i + 1), students[i], false);
        }
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
        int student;
        std::cout << "Enter serial number of the student: ";
        std::cin >> student;
        system("cls");
        printHorizontalLine(61, '-', '+');
        printRow(TableWidth, "Attendance Record ", true);
        printHorizontalLine(61, '-', '+');
        std::vector<combine<Date, std::string>> student_data;
        student_data = t1.getStudentAttendance(sub_choice, student);
        
        for (int i = 0; i < student_data.size(); i++) {
            std::string p_a = (student_data[i].second == "p") ? "Present" : "Absent";
            int day = student_data[i].first.getDay();
            int month = student_data[i].first.getMonth();
            int year = student_data[i].first.getYear();
            std::string stringDay = std::to_string(day);
            std::string stringMonth = std::to_string(month);
            std::string stringYear = std::to_string(year);
            std::string date = stringDay + "-" + stringMonth + "-" + stringYear;
            printRow(TableWidth, date, p_a, false);
        }
        teacher_menu(61, '-', '+');
       
    }
        
    
            
        break;

    case 3:
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "-----------------------LOGGED OUT-----------------------", false);
        exit(EXIT_SUCCESS);

    default:
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl << "Please try again." << std::endl;
        menu(61, '-', '+');
    }
}