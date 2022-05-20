DROP DATABASE IF EXISTS timeclock;
CREATE DATABASE IF NOT EXISTS timeclock;

USE timeclock;

DROP TABLE IF EXISTS employeeType;
DROP TABLE IF EXISTS employee;
DROP TABLE If EXISTS punchType;
DROP TABLE If EXISTS punches;

/* Create Admin table */
DROP TABLE IF EXISTS admin;

CREATE TABLE admin (
    adminID INT UNIQUE NOT NULL AUTO_INCREMENT,
    user varchar(256) UNIQUE NOT NULL,
    password varchar(256) NOT NULL,
    PRIMARY KEY (adminID)
);

/*Create defualt admin account with hashed password*/
INSERT INTO admin(user, password) VALUES('admin', '8141937955048696534');

/* Table to store types of employees */

 CREATE TABLE employeeType(
    empTypeID int UNIQUE NOT NULL AUTO_INCREMENT,
    empType varchar(256) UNIQUE NOT NULL,
    PRIMARY KEY (empTypeID)
 );

 INSERT INTO employeeType(empType) VALUES('Manager');
 INSERT INTO employeeType(empType) VALUES('Team Member');


/* Create table to store employee information */

CREATE TABLE employee (
    employeeID INT UNIQUE NOT NULL AUTO_INCREMENT,
    fname varchar(256),
    lname varchar(256),
    startDate date,
    empType int,
    PRIMARY KEY (employeeID),
    FOREIGN KEY (empType) REFERENCES employeeType(empTypeID)
);

INSERT INTO employee(fname, lname, startdate, empType) VALUES('Jane', 'Doe', CURRENT_DATE(), 2);

 /* Table to store type of Punch */

 CREATE TABLE punchType (
    punchTypeID INT UNIQUE NOT NULL AUTO_INCREMENT,
    punchType varchar(256) UNIQUE NOT NULL,
    PRIMARY KEY (punchTypeID)
 );

 INSERT INTO punchType(punchType) VALUES('Start Shift');
 INSERT INTO punchType(punchType) VALUES('End Shift');
 INSERT INTO punchType(punchType) VALUES('Start Lunch');
 INSERT INTO punchType(punchType) VALUES('End Lunch');

 /* Table to store employee punches */

 CREATE TABLE punches (
    punchID int UNIQUE NOT NULL AUTO_INCREMENT,
    employeeID int NOT NULL,
    punchTime time NOT NULL,
    punchType int,
    PRIMARY KEY (punchID),
    FOREIGN KEY (employeeID) REFERENCES employee(employeeID),
    FOREIGN KEY (punchType) REFERENCES punchType(punchTypeID)
 );

INSERT INTO punches(employeeID, punchTime, punchType) VALUES(1, '8:00:00', 1);
INSERT INTO punches(employeeID, punchTime, punchType) VALUES(1, '12:00:00', 3);
INSERT INTO punches(employeeID, punchTime, punchType) VALUES(1, '12:30:00', 4);
INSERT INTO punches(employeeID, punchTime, punchType) VALUES(1, '4:00:00', 2);

 