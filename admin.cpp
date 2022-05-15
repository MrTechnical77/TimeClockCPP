#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <mysql/mysql.h>


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
    std::hash <std::string> passwordHash;
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
    } else {
        std::cout << "Incorrect Password" << std::endl;
        exit(1);
    }


    return 0;
}