#include <iostream>
#include "frontend.hpp"
#include "students1.hpp"

void choose_designation(int, char, char);
bool log_in(int, char, char, Students&);
void subject_list(int, char, char, std::vector<std::string>&, Students&);
void menu(int, char, char);

int main()
{
    Students s1;
    bool is_logged_in;
    choose_designation(51, '-', '+');
    is_logged_in = log_in(51 , '-', '+', s1);
    if (is_logged_in == true)
    {
        std::vector<std::string> subjects = s1.getSubjects();
        subject_list(125, '-', '+', subjects, s1);
    }
    menu(61, '-', '+');
    return 0;
}

void choose_designation(int TableWidth, char borderChar, char intersectionChar)
{
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "Choose Designation", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1", "Teacher", false);
    printRow(TableWidth, "2", "Student", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
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
        return true;
    }
    else
    {
        std::cout << "\033[0;31m" << std::endl;
        printRow(TableWidth, "Login Unsuccessful", false);
        std::cout << "\033[0m" << std::endl;
        printHorizontalLine(TableWidth, borderChar, intersectionChar);
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
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "MENU", true);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
    printRow(TableWidth, "1.", "Change Password", false);
    printRow(TableWidth, "2.", "Check Attendance Record", false);
    printRow(TableWidth, "3.", "Exit", false);
    printHorizontalLine(TableWidth, borderChar, intersectionChar);
}