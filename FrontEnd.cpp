#include <iostream>
#include <string>
#include "frontend.hpp"
#include "students1.hpp"
#include "TeacherFrontEnd.hpp"

void choose_designation(int, char, char);
bool log_in(int, char, char, Students&);
void subject_list(int, char, char, std::vector<std::string>&, Students&);
void menu(int, char, char);
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
        teacher_namespace::teacher_page();
        break;

    case 2:
        {
        bool is_logged_in;
        is_logged_in = log_in(51, '-', '+', s1);
        if (is_logged_in == true)
        {
            std::vector<std::string> subjects = s1.getSubjects();
            subject_list(125, '-', '+', subjects, s1);
            menu(61, '-', '+');
        }
        }
        break;
    
    default :
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl << "Please try again." << std::endl;
        choose_designation(51, '-', '+');
        break;
    }
}

bool log_in(int TableWidth, char borderChar, char intersectionChar, Students& obj)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Welcome to Student Login Page", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    std::string username, password;
    printRow(TableWidth, "Enter Username:", false);
    std::cout << printCentre(TableWidth/2, "            ");
    std::cin >> username;
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Enter Password:", false);
    std::cout << printCentre(TableWidth/2, "            ");
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
        is_logged_in = log_in(51, '-', '+', s1);
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

    for (int i=0; i<subjects.size(); i++)
    {
        percentage = obj.getpercent(i+1);
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
        printRow(std::to_string(i+1) , subjects[i], std::to_string(7)+"/"+std::to_string(24), std::to_string(percentage), remarks, false, flag1);
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
        
        ///////////////


    case 3:
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "--------------------------Exit--------------------------", false);
        exit(EXIT_SUCCESS);

    default :
        system("cls");
        std::cout << "INVALID RESPONSE!" << std::endl << "Please try again." << std::endl;
        menu(61, '-', '+');
    }
}

