#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <mysql/mysql.h>

// Hash function for password storage, not yet secure
std::hash <std::string> passwordHash;

// 1
// Function to create new admin account
void createUser(MYSQL* connection){

    std::string newUsername;
    std::string newPassword;
    std::stringstream usernameCheck;
    MYSQL_RES *userRES;
    
    std::cout << "Creating new user..." << std::endl << std::endl;
    std::cout << "Enter the new admin's USERNAME: ";
    std::cin >> newUsername;

    usernameCheck << "SELECT user FROM admin WHERE user = '" << newUsername << "';";
    std::string usernameCheckString = usernameCheck.str();
    int querycheck = mysql_query(connection, usernameCheckString.c_str());
    if(querycheck != 0){
        std::cout << "Error communicating with mysql database, no changes made to database." << std::endl << std::endl;
        return;
    }

    userRES = mysql_store_result(connection);

    if(mysql_num_rows(userRES) != 0){
        system("clear");
        std::cout << std::endl << "Username is taken, please try again." << std::endl << std::endl;
        return;
    }
    
    std::cout << std::endl << "Enter the new admin's PASSWORD: ";
    std::cin >> newPassword;
    std::cout << std::endl;

    std::stringstream newUserInsert;

    newUserInsert << "INSERT INTO admin(user, password) VALUES( '" << newUsername << "','" << passwordHash(newPassword) << "');";
    std::string userInsertString = newUserInsert.str();
    int insertErrno = mysql_query(connection, userInsertString.c_str());
    if(insertErrno == 0){
        system("clear");
        std::cout << "New User '" << newUsername << "' Created Sucessfully!" << std::endl << std::endl;
    } else {
        system("clear");
        std::cout << "Error creating new user, no changes made to database." << std::endl;
    }

    return;
}

// 2
void createEmployee(MYSQL* connection){

    std::string fname;
    std::string lname;  
    std::string empType;
    int empTypesCounter = 0;
    MYSQL_ROW empTypesROW;
    MYSQL_RES* empTypesRES;
    int empTypeChoice;
    char correct;
 
    // User inputs employee name
    std::cout << "Creating new employee...\nEnter the new employee's information:" << std::endl; 

    std::cout << "First name: ";
    std::cin >> fname;

    std::cout << std::endl << "Last name: ";
    std::cin >> lname;

    std::cout << std::endl << "Select employee type..." << std::endl;

    // Query to retieve employee types
    int empTypeErrno = mysql_query(connection, "SELECT empType FROM employeeType");

    // Check for non zero amount of employee types.
    if(empTypeErrno != 0){
        system("clear");
        std::cout << "Error retieving employee types, no changes made to database.\nPlease add new admin types to create new employees." << std::endl << std::endl;
        return;
    }

    empTypesRES = mysql_store_result(connection);

    // sql query error handling
    if(empTypesRES == NULL){
        system("clear");
        std::cout << "Error retreving database information.\nNo changes made to database." << std::endl << std::endl;
        return;
    }

    std::string empTypesArr[mysql_num_rows(empTypesRES)];


    // List employee types and assign to array
    while(empTypesROW = mysql_fetch_row(empTypesRES)){
        std::cout << empTypesCounter + 1 << ". " << empTypesROW[0] << std::endl;
        empTypesArr[empTypesCounter] = empTypesROW[0];
        empTypesCounter++;
    }

    // User selects employee type
    for(;;){
        std::cout << std::endl << "Select option: ";
        std::cin >> empTypeChoice;

        if(empTypeChoice < 1 || empTypeChoice > empTypesCounter){
            std::cout << "Invalid choice, please try again." << std::endl;
        } 
        else if(empTypeChoice > 1 || empTypeChoice < empTypesCounter){
            empType = empTypeChoice;     
            break;       
        }
    }

    std::stringstream createEmployeeStream;
    createEmployeeStream << "INSERT INTO employee(fname, lname, startdate, empType) VALUES('" << fname << "','" << lname << "', CURDATE()," << empType << ";";
    std::string createEmpString = createEmployeeStream.str();

    std::cout << "Employee Info...\nFirst Name: " << fname << "\nLast Name: " << lname << "\n" << empTypesArr[empTypeChoice - 1] << "\n\nIs this correct? Y/n" << std::endl;
    std::cin >> correct;

    for(;;){
        if(correct == 'y' || correct == 'Y'){
            break;
        }
        else if(correct == 'n' || correct == 'N'){
            system("clear");
            std::cout << "No has been selected, returning to main menu." << std::endl << std::endl;
        }
        else{
            std::cout << "Incorrect option, try again..." << std::endl;
        }
    }

    int createEmployee = mysql_query(connection, createEmpString.c_str());

    if(createEmployee != 0){
        system("clear");
        std::cout << "An SQL error has occured, no changes made to database.\nError Number: " << createEmployee << std::endl;
    }

    return;
}

// 3
void deleteAdmin(MYSQL* connection){

    std::cout << "Delete Admin Account" << std::endl << std::endl;

    std::cout << "Select Account to be deleted:" << std::endl;

    std::stringstream allAdminsStream;

    allAdminsStream << "SELECT user FROM admin";
    std::string allAdminsString = allAdminsStream.str();

    int retireveAdmins = mysql_query(connection, allAdminsString.c_str());

    // Error handling
    if(retireveAdmins){
        system("clear");
        std::cout << "Error retireveing admins. \nNo Changes made to database." << std::endl;
        return;
    }

    MYSQL_RES* adminRES = mysql_store_result(connection);
    if(adminRES == NULL){
        std::cout << "No accounts found\n";
    }


    MYSQL_ROW adminROW;


    // List Admin account and store in array
    int adminCounter = 0;
    std::string adminNames[mysql_num_rows(adminRES)];
    while(adminROW = mysql_fetch_row(adminRES)){
        std::cout << adminCounter + 1<< ". " << adminROW[0] << std::endl;
        adminNames[adminCounter] = adminROW[0];
        adminCounter++;
    }
        
    int deleteOption = 0;
    for(;;){
        std::cout << "Select which account you would like to delete: ";
        std::cin >> deleteOption;

        if(deleteOption > 0 && deleteOption <= adminCounter){
            std::cout << std::endl;
            break;
        }
        else{
            std::cout << "Invalid option, try again..." << std::endl << std::endl;
        }
    }

    char deleteContinue;
    std::cout << "You have selected to delete user " << adminNames[deleteOption - 1] << ", would you like to continue? Y/n" << std::endl;
    for(;;){
        std::cin >> deleteContinue;

        if(deleteContinue == 'y' || deleteContinue == 'Y'){
            break;
        }
        else if(deleteContinue == 'n' || deleteContinue == 'N'){
            system("clear");
            std::cout << "Deletion canceled, no changes made to database" << std::endl;
            return;
        }
        else{
            std::cout << "Invalid choice, try again" << std::endl << std::endl;
        }
    }

    std::stringstream deleteAdminQueryStream;
    deleteAdminQueryStream << "DELETE FROM admin WHERE user = '" << adminNames[deleteOption - 1] << "';";
    std::string deleteAdminQueryString = deleteAdminQueryStream.str();
    int deleteAdminErrno = mysql_query(connection, deleteAdminQueryString.c_str());

    system("clear");
    if(deleteAdminErrno == 0){
        std::cout << "User " << adminNames[deleteOption - 1] << " deleted sucessfully." << std::endl << std::endl;
    }
    else {
        std::cout << "Error deleting user " << adminNames[deleteOption - 1] << ", no changes made to database." << std::endl << std::endl;
    }


    return;
}

// 4
void deleteEmployee(MYSQL* connection){



    return;
}

// 5
void changeAdminUsername(MYSQL* connection, std::string oldUsername){

    std::cout << "What would you like to change your admin account username too?" << std::endl;
    std::cout << "New Username: ";

    std::string newUsername;
    std::cin >> newUsername;

    std::stringstream updateStream;
    updateStream << "UPDATE admin SET user = '" << newUsername << "' WHERE user = '" << oldUsername << "';";
    std::string updateString = updateStream.str();
    int updateErrno = mysql_query(connection, updateString.c_str());

    if(updateErrno == 0){
        system("clear");
        std::cout << "Username changed sucessfully from " << oldUsername << " to " << newUsername << "." << std::endl;
    }
    else {
        system("clear");
        std::cout << "Error changing username, no changes made to database" << std::endl;
    }

    return;
}

// 6
void listAdmins(MYSQL* connection){

    std::cout << "Current Admin Usernames: " << std::endl;

    int getAdminsErrno = mysql_query(connection, "SELECT adminID, user FROM admin");
    if(getAdminsErrno != 0){
        std::cout << "Error fetching users" << std::endl;
        return;
    }

    MYSQL_RES* adminRES = mysql_store_result(connection);

    MYSQL_ROW adminROW;
    std::cout << "ID\tUsername" << std::endl;
    while(adminROW = mysql_fetch_row(adminRES)){
        std::cout << adminROW[0] << "\t" << adminROW[1] << std::endl << std::endl;
    }


    return;
}


int main(){

    // Connecting to database
    MYSQL* connection;
    connection  = mysql_init(0);
    connection  = mysql_real_connect(connection, "localhost", "TCAdmin", "TCAdmin", "timeclock", 0, NULL, 0);

    if(connection){
        std::cout << "Connected!" << std::endl;
    } else {
        std::cout << "DATABASE CONNECTION ERROR" << std::endl;
        exit(1);
    }

    // Login routine
    std::cout << "Terminal Admin Acess Panel..." << std::endl;
    std::cout << "Enter Credentials" << std::endl << std::endl;

    std::string adminUsername;
    std::string adminPassword;
    MYSQL_RES *userCheckRES;
    MYSQL_ROW userCheckROW;

    // Enter username
    std::cout << "Username: ";
    std::cin >> adminUsername;
    std::cout << std::endl << std::endl;

    std::stringstream usernameCheck;
    usernameCheck << "SELECT * FROM admin WHERE user = '" << adminUsername << "';";
    std::string usernameCheckQuery = usernameCheck.str();
    mysql_query(connection, usernameCheckQuery.c_str());

    userCheckRES = mysql_store_result(connection);
    userCheckROW = mysql_fetch_row(userCheckRES);

    // Check to see if username exists
    if(mysql_num_rows(userCheckRES) != 1){
        std::cout << "Invalid Username" << std::endl;
        exit(1);
    }    

    // Enter password
    std::cout << "Password: ";
    std::cin >> adminPassword;

    system("clear");

    unsigned long hashedPassword = passwordHash(adminPassword);

    std::stringstream passwordStream;
    passwordStream << hashedPassword;
    std::string passwordCheck = passwordStream.str();

    // Check hashed password aginst hash in database
    if(passwordCheck == userCheckROW[2]){
        std::cout << "Login Success!" << std::endl << std::endl;
        mysql_free_result(userCheckRES);
    } else {
        std::cout << "Incorrect Password" << std::endl;
        mysql_free_result(userCheckRES);
        exit(1);
    }


    // Main loop
    for(;;){
        int userchoice = 0;
        std::cout << "What operation would you like to perform?" << std::endl << std::endl;

        std::cout << "1. Create New Admin Account" << std::endl;
        std::cout << "2. Create New Employee" << std::endl;
        std::cout << "3. Delete Admin Account" << std::endl;
        std::cout << "4. Delete Employee" << std::endl;
        std::cout << "5. Change Admin Username" << std::endl;
        std::cout << "6. List Admin Usernames" << std::endl;

        std::cout << "0. Exit Admin Panel" << std::endl << std::endl;

        std::cout << "Choice: ";
        std::cin >> userchoice;
        system("clear");


        if(userchoice == 1){
            createUser(connection);
        }

        else if(userchoice == 2){
            createEmployee(connection);
        }

        else if(userchoice == 3){
            deleteAdmin(connection);
        }

        else if(userchoice == 5){
            changeAdminUsername(connection, adminUsername);
        }

        else if(userchoice == 6){
            listAdmins(connection);
        }


        else if(userchoice == 0){
            std::cout << "Goodbye!" << std::endl;
            exit(1);
        }

        else{
            std::cout << "Invalid Choice" << std::endl << std::endl;
        }

    } // End main loop


    return 0;
}