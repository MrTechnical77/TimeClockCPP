Time clock application developed on Linux Ubuntu

To donwload code:
git clone https://github.com/MrTechnical77/TimeClockCPP

Instructions for executions:

If MYSQL is not installed run these commands in your terminal

sudo apt update
sudo apt install mysql-server
sudo mysql_secure_installation
sudo mysql

mysql> SET GLOBAL validate_password.length = 3;
mysql> SET GLOBAL validate_password.policy = "LOW";
mysql> CREATE USER 'TCAdmin'@'localhost' IDENTIFIED BY 'TCAdmin';
mysql> GRANT ALL PRIVILEGES ON *.* TO TCAdmin WITH GRANT OPTION;
mysql> exit

After these steps are complete open a terminal in the folder you have stored the source code in and run the follwing commands:

sudo mysql
mysql> \. timeclock.sql
exit
sudo apt-get install libmysqlclient-dev
sudo apt-get install libqt5sql5-mysql

You can now run the source code provided you have a C++ compliler and make installed.
To do this run the following commands in a terminal opened in the folder with the source code.

make
./admin

If you do not have one of these installed, complete the following instructions:

For make:
sudo apt install make

For C++:
sudo apt install g++

By defualt, the username and password are both admin, but once installed you are encourced to update your admin account.
To reset the database run the timeclok.sql file again, but all data will be lost.
