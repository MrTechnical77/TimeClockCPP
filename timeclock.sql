CREATE DATABASE IF NOT EXISTS timeclock;

USE timeclock;

DROP TABLE IF EXISTS admin;

CREATE TABLE admin (
    adminID INT UNIQUE NOT NULL AUTO_INCREMENT,
    user varchar(256) UNIQUE NOT NULL,
    password varchar(256) NOT NULL,
    PRIMARY KEY (adminID)
);

/*Create defualt admin account with hashed password*/
INSERT INTO admin(user, password) VALUES('admin', '8141937955048696534');