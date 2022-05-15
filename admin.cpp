#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <mysql/mysql.h>

std::hash <std::string> passwordHash;

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
    mysql_query(connection, usernameCheckString.c_str());

    userRES = mysql_store_result(connection);

    if(mysql_num_rows(userRES) != 0){
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
        std::cout << "New User Created Sucessfully!" << std::endl << std::endl;
    } else {
        std::cout << "Error creating new user, no changes made to database." << std::endl;
    }

    return;
}

void createEmployee(MYSQL* connection){



    return;
}


int main(){

    MYSQL* connection;
    connection  = mysql_init(0);

    connection  = mysql_real_connect(connection, "localhost", "TCAdmin", "TCAdmin", "timeclock", 0, NULL, 0);

    if(connection){
        std::cout << "Connected!" << std::endl;
    } else {
        std::cout << "DATABASE CONNECTION ERROR" << std::endl;
        exit(1);
    }

    std::cout << "Terminal Admin Acess Panel..." << std::endl;
    std::cout << "Enter Credentials" << std::endl << std::endl;

    std::string adminUsername;
    std::string adminPassword;
    MYSQL_RES *userCheckRES;
    MYSQL_ROW userCheckROW;

    std::cout << "Username: ";
    std::cin >> adminUsername;
    std::cout << std::endl << std::endl;

    std::stringstream usernameCheck;
    usernameCheck << "SELECT * FROM admin WHERE user = '" << adminUsername << "';";
    std::string usernameCheckQuery = usernameCheck.str();
    mysql_query(connection, usernameCheckQuery.c_str());

    userCheckRES = mysql_store_result(connection);
    userCheckROW = mysql_fetch_row(userCheckRES);

    if(mysql_num_rows(userCheckRES) != 1){
        std::cout << "Invalid Username" << std::endl;
        exit(1);
    }

    

    std::cout << "Password: ";
    std::cin >> adminPassword;
    std::cout << std::endl << std::endl;

    unsigned long hashedPassword = passwordHash(adminPassword);

    std::stringstream passwordStream;
    passwordStream << hashedPassword;
    std::string passwordCheck = passwordStream.str();

    if(passwordCheck == userCheckROW[2]){
        std::cout << "Login Success!" << std::endl << std::endl;
        mysql_free_result(userCheckRES);
    } else {
        std::cout << "Incorrect Password" << std::endl;
        mysql_free_result(userCheckRES);
        exit(1);
    }

    for(;;){
        int userchoice = 0;
        std::cout << "What operation would you like to perform?" << std::endl << std::endl;

        std::cout << "1. Create New Admin Account" << std::endl;
        std::cout << "2. Create New Employee" << std::endl;

        std::cout << "0. Exit Admin Panel" << std::endl << std::endl;

        std::cout << "Choice: ";
        std::cin >> userchoice;
        std::cout << std::endl << std::endl;

        if(userchoice == 1){
            createUser(connection);
        }

        if(userchoice == 2){
            createEmployee(connection);
        }

        if(userchoice == 0){
            std::cout << "Goodbye!" << std::endl << std::endl;
            exit(1);
        }

        else{
            std::cout << "Invalid Choice" << std::endl << std::endl;
        }


    }


    return 0;
}