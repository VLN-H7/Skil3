INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Blaise','Pascal','M','1623-06-19','1662-08-19','French','http://history-computer.com/People/images/Blaise_Pascal2.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Alan','Turing','M','1912-06-23','1954-06-07','English');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Daniel','Brandur','M','1987-07-23','1987-06-22','Icelandic');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Charles','Babbage','M','1791-12-26','1871-10-18','English');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Edsger','Djikstra','M','1930-05-11','2002-08-06','Dutch');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Chuck','Norris','M','1940-03-10','','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Ada','Lovelace','F','1815-12-10','1852-11-27','English');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Leonhard','Euler','M','1707-04-15','1783-09-18','Swiss');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Donald','Knuth','M','1938-01-10', '','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Tim','Berners-Lee','M','1955-06-08', '','English');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Larry','Page','M','1973-03-26', '','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Sergey','Brin','M','1973-08-21', '','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Steve','Wozniak','M','1950-08-11', '','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('John','Backus','M','1924-12-03', '2007-03-17','American');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality) VALUES ('Tony','Hoare','M','1934-01-11', '','British');

INSERT INTO types(type) VALUES ('Mechanical');
INSERT INTO types(type) VALUES ('Electronic');
INSERT INTO types(type) VALUES ('Transistor');

INSERT INTO computers(name, build_year, type_id, built) VALUES ('Pascaline',1642, 1,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('ABC',1942, 2,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('Colossus',1943, 2,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('Difference Engine',1822, 1,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('Analytical Engine',1837, 1,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('Apple 1',1976, 2,1);
INSERT INTO computers(name, build_year, type_id, built) VALUES ('ENIAC',1946, 2,1);

INSERT INTO scientist_computer(scientist_id, computer_id) VALUES (1, 1);
INSERT INTO scientist_computer(scientist_id, computer_id) VALUES (4, 4);
INSERT INTO scientist_computer(scientist_id, computer_id) VALUES (4, 5);
INSERT INTO scientist_computer(scientist_id, computer_id) VALUES (13, 6);