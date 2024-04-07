#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "common1.hpp"

class Students
{
    private:
        std::string username;           //String Data Member for Username
        std::string password;           //String Data Member for password
        bool loggedIn;                  //Boolean Data Member for log in status
        std::vector<combine<std::string,std::string>> Subject_Codes;    //Vector Data Member of structures 'combine' which contain subject names and subject codes
        std::vector<combine<combine<std::string,double>,std::vector<combine<Date,std::string>>>> subject_attendance;    //A vector data member of structures that contains entire attendance record of a subject
        bool check_username(const std::string&);        //Member Function Declaration to check username
        bool check_password(const std::string&);        //Member Function Declaration to check password
        void loadSubjects();                            //Member Function Declaration to store subjects from database inside data structure (Vector Subject_Codes)
        void loadAttendance();                          //Member Function Declaration to calculate and store attendance records and percentage from database inside data structure (Vector subject_attendance)
    public:
        Students(): username(""),password(""),loggedIn(false) {}    //Default Constructor to initialize empty username and password and set log-in-flag to false
        ~Students();            //Destructor
        void logout();          //Logout function inside destructor to clear memory given to data members of objects
        bool loguser(const std::string&,const std::string&);        //Member Function Declaration to authenticate user login
        std::vector<std::string> getSubjects();         //Member Function Declaration to fetch the user's subjects from the data structure (Vector Subject_Codes)
        bool changepass(const std::string&);            //Member Function Declaration to change the password
        std::vector<combine<Date,std::string>> getAttendance(const int&);   //Member Function Declaration to fetch the user's attendance from the data structure (Vector subject_attendance)
        double getpercent(const int&);          //Member Function Declaration to fetch attendance from the data structure, Vector subject_attendance
};
    
    Students::~Students()       //Destructor
    {
        logout();               //Function call to logout()
    }
    
    void Students::logout()     //Member Function Definition to set the data members' values to default values
    {
        username.clear();       //Empties the username variable
        password.clear();       //Empties the password variable
        loggedIn = false;       //Resets log-in-flag to false
        Subject_Codes.clear();  //Empties the vector contaning subject names and codes
    }
    bool Students::check_username(const std::string& username)      //Member Function Definition to check username
    {
        std::ifstream instream;             //Creating input file pointer
        try                                 //try block begins
        {
            instream.open("studentlist.lis");   //Opens file for input operations
            if (!instream)
                throw std::runtime_error("Error opening file: studentlist.lis");    //Throws a runtime error if file doesn't open
        }
        catch(const std::exception& e)      //Catch block begins
        {
            std::cerr << e.what() << '\n';  //Catches the error thrown above and prints it to the Error stream
            return false;                   //Returns false, signifying that file coulen't be opened
        }
    
        std::string line;                   //Creates a string variable to parse the file line by line
        while(std::getline(instream,line))  //Stores the line and returns true if a line was present which keeps the loop going. Returns False as soon as the cursor reaches the end, thereby terminating the loop by acting as the exit criteria as well
        {
            if(line == username)
            {                                   //Enters the 'if block' if entered username matches the username in the file
                std::getline(instream,line);    //Reads the next line that contains the user's password
                this->password = line;          //Stores that password in the data member for password
                instream.close();               //Closes the file pointer
                return true;                    //Returns true signifying that the username has been found
            }
            else
                std::getline(instream,line);    //If the username is not matched, reads the next line of password so that the getline() function in the while loop condition only picks up the username and matches only the username in the 'if block' of the next iteration
        }
        instream.close();           //Closes the file pointer if the username isn't found in the entire file
        return false;               //Returns false, signifying that the username entered is either incorrect or not present in the database
    }
    
    bool Students::check_password(const std::string& password)  //Member Function Definition to check the password of the user
    {
        if(this->password == password)
        {                               //Enters the 'if block' if the entered password matche sthe password found in the database
            this->password.clear();     //Clears the data member for password after authenticating, for security purposes
            return true;                //Returns true, signifying that the password has been correctly entered
        }
        else
            this->password.clear();     //If the password isn't found, clear the password variable still, for security reasons
            return false;               //Returns false, signifying that the password entered was incorrect
    }
    
    bool Students::loguser(const std::string& username, const std::string& password)    //Member Function Definition to log in the user by taking username and password as arguments
    {
        if(check_username(username) && check_password(password))        //Calls the check functions to log in the user
        {                                   //Enters the 'if block' if both check functions return true
            this->username = username;      //Stores the entered username in the data member for username
            loggedIn = true;                //Sets the log-in-flag to true, signifying that the log in was succesful. This flag will be used by other functions at the backend to work
            
            loadSubjects();                 //After succesful log-in, calls this function to extract the user's subjects from the database into the program's data structures (Vector Subject_Codes)
            return true;                    //Returns true. This return type will be used by the front-end to confirm the login status
        }
        else
            return false;                   //Returns false, signifying that log in was unsuccessful
    }
    
    void Students::loadSubjects()           //Member Function Definition to extract the user's subjects from the database into the program's data structures (Vector Subject_Codes)
    {
        if(!loggedIn)
            return;                         //If log in was unsuccessful, then terminate the function call

        else
        {
            std::ifstream instream;         //Creates input file pointer
            try                             //Try block begins
            {
                instream.open(username + ".sub");       //Opens file for input operations
                if (!instream)
                    throw std::runtime_error("Error opening file: " + username + ".sub");   //Throws a runtime error if file doesn't open
            }
            catch(const std::exception& e)      //Catch block begins
            {
                std::cerr << e.what() << '\n';  //Catches the error thrown above and prints it to the Error stream
            }
    
            std::string line;                                   //Creates a string variable to parse the file line by line
            combine<std::string, std::string> subject_and_code; //Creates a 'combine' structure to store the subject name and code
            while(std::getline(instream,line))                  //Stores the line and returns true if a line was present which keeps the loop going. Returns False as soon as the cursor reaches the end, thereby terminating the loop by acting as the exit criteria as well
            {
                subject_and_code.first = line;                  //Stores the subject name in the structure
                std::getline(instream,line);                    //Reads the next line
                subject_and_code.second = line;                 //Stores the subject code in the structure
                Subject_Codes.push_back(subject_and_code);      //Pushes the structure with the name and code into the vector of subjects
            }
            instream.close();           //Closes the file pointer
            loadAttendance();           //Calls the function to fetch the attendance of the student from the database into the program's data structures (Vector subject_attendance)
        }
    }
    
    std::vector<std::string> Students::getSubjects()        //Member Function Definition to fetch the user's subjects from the data structure (Vector Subject_Codes)
    { 
        std::vector<std::string> subjects;                  //Creates a vector of strings to store the subject names
        for(int i = 0; i<Subject_Codes.size(); i++)         //Iterates as many times as the size of the vector that contains the subject names
        {
            subjects.push_back(Subject_Codes[i].first);     //Stores the subject names from the vector data member into the newly created vector above that is to be returned
        }
        return subjects;        //Returns the vector of strings containing subjects
    }
    
    bool Students::changepass(const std::string& newpass)   //Member FUnction Definition to change the password
    {
        if(!loggedIn)
            return false;               //Returns false, signifying that log-in was unsuccessful earlier and hence password can't be changed
        
        else
        {
            std::ifstream instream;                 //Creates input file pointer
            std::ofstream outstream;                //Creates output file pointer
            try                                     //try block begins
            {
                instream.open("studentlist.lis");   //Opens student list file for input operations
                outstream.open("temp.tmp");         //Opens a temporary file for output operations
                if (!instream || !outstream)
                    throw std::runtime_error("Error opening files: studentlist.lis or temp.tmp");   //Throws a runtime error if either file can't be opened
            }
            catch(const std::exception& e)          //Catch block begins
            {
                std::cerr << e.what() << '\n';      //Catches the error thrown above and prints it to the Error stream
                return false;                       //Returns false, signifying that files couldn't be opened
            }
    
            std::string line;                       //String variable to parse the file line by line
            while(std::getline(instream,line))      //Stores the line and returns true if a line was present which keeps the loop going. Returns False as soon as the cursor reaches the end, thereby terminating the loop by acting as the exit criteria as well
            {
                outstream << line << std::endl;         //Prints the line to the temporary file
                if(line == username)
                {                                       //Enters the 'if block' if username is found in the student list database
                    outstream << newpass << std::endl;  //Writes the new password to the output temporary file
                    std::getline(instream,line);        //Reads the password line in the old file to skip it from the coming iterations
                    continue;                           //Skips the remaining itearation of the while loop and starts the next loop
                }
                std::getline(instream,line);            //If match isn't found, reads the next password line from the student list file
                outstream << line << std::endl;         //and prints it into the temporary file
            }
            instream.close();                           //Closes both file pointers
            outstream.close();                          //after the loop finishes
            instream.open("temp.tmp");                  //Now opens the temporary file for input
            outstream.open("studentlist.lis");          //and student list file for output
            while(std::getline(instream,line))          //Reads the line from the temporary file and serves as exit criteria
            {
                outstream << line << std::endl;         //Prints the line to the student list file
            }
            this->password = newpass;                   //Sets the new password into the data member for password
            return true;                                //Returns true, signifying that the password change was successful
        }
    }
    
    std::vector<combine<Date,std::string>> Students::getAttendance(const int& number)
    {
        return subject_attendance[number-1].second;
    }
    
    double Students::getpercent(const int& number)
    {
        return subject_attendance[number-1].first.second;
    }
    
    void Students::loadAttendance()
    {
        for(int i = 0; i<Subject_Codes.size();i++)
        {
            std::string code = Subject_Codes[i].second;
            std::ifstream instream;
            try
            {
                instream.open(username + code + ".att");
                if (!instream)
                    throw std::runtime_error("Error opening file: " + username + code + ".att");
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
    
            std::string line;
            std::vector<combine<Date,std::string>> attendance_record;
            combine<Date,std::string> attendance;
            std::string p_a;
            int total = 0;
            int count = 0;
            while(std::getline(instream,line))
            {
                Date date(line.substr(0,8));
                p_a = line[9];
                attendance.first = date;
                attendance.second = p_a;
                attendance_record.push_back(attendance);
                total++;
                p_a == "p"? count++: count;
            }
    
            double percent = ((double)count/total)*100;
            
            combine<std::string, double> code_percent;
            code_percent.first = code;
            code_percent.second = percent;
            combine<combine<std::string,double>,std::vector<combine<Date,std::string>>> subjectRecord;
            subjectRecord.first = code_percent;
            subjectRecord.second = attendance_record;
            subject_attendance.push_back(subjectRecord);
            instream.close(); 
        }
}