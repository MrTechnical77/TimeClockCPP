Time clock application developed on Linux Ubuntu

Instructions for executions:

If MYSQL is not installed run these commands in your terminal

sudo apt update
sudo apt install mysql-server
sudo mysql_secure_installation
sudo mysql

mysql> CREATE USER 'TCAdmin'@'localhost' IDENTIFIED BY 'TCAdmin';
mysql> GRANT ALL PRIVILEGES ON *.* TO TCAdmin WITH GRANT OPTION;
mysql> exit