INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Blaise','Pascal','M','1623-06-19','1662-08-19','French','http://history-computer.com/People/images/Blaise_Pascal2.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Alan','Turing','M','1912-06-23','1954-06-07','English','http://upload.wikimedia.org/wikipedia/en/c/c8/Alan_Turing_photo.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Daniel','Brandur','M','1987-07-23','1987-06-22','Icelandic','https://fbcdn-sphotos-a-a.akamaihd.net/hphotos-ak-xpa1/t31.0-8/10580960_10152319146782087_5075081791575519251_o.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Charles','Babbage','M','1791-12-26','1871-10-18','English','http://upload.wikimedia.org/wikipedia/commons/6/6b/Charles_Babbage_-_1860.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Edsger','Djikstra','M','1930-05-11','2002-08-06','Dutch','http://upload.wikimedia.org/wikipedia/commons/d/d9/Edsger_Wybe_Dijkstra.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Chuck','Norris','M','1940-03-10','','American','http://upload.wikimedia.org/wikipedia/commons/3/3e/Chuck_Norris_2007_%28cropped%29.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Ada','Lovelace','F','1815-12-10','1852-11-27','English','http://upload.wikimedia.org/wikipedia/commons/a/a4/Ada_Lovelace_portrait.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Leonhard','Euler','M','1707-04-15','1783-09-18','Swiss','http://upload.wikimedia.org/wikipedia/commons/d/d7/Leonhard_Euler.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Donald','Knuth','M','1938-01-10', '','American','http://upload.wikimedia.org/wikipedia/commons/4/4f/KnuthAtOpenContentAlliance.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Tim','Berners-Lee','M','1955-06-08', '','English','http://upload.wikimedia.org/wikipedia/commons/c/c2/Tim_Berners-Lee_2012.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Larry','Page','M','1973-03-26', '','American','http://upload.wikimedia.org/wikipedia/commons/2/26/Larry_Page_in_the_European_Parliament%2C_17.06.2009.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Sergey','Brin','M','1973-08-21', '','American','http://upload.wikimedia.org/wikipedia/commons/a/a2/Sergey_Brin_cropped.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Steve','Wozniak','M','1950-08-11', '','American','http://upload.wikimedia.org/wikipedia/commons/f/f6/Steve_Wozniak.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('John','Backus','M','1924-12-03', '2007-03-17','American','http://www.computerhistory.org/fellowawards/media/img/fellows/1997_john_backus.jpg');
INSERT INTO scientists(first_name, last_name, gender, birth_date, death_date, nationality, image) VALUES ('Tony','Hoare','M','1934-01-11', '','British','http://upload.wikimedia.org/wikipedia/commons/2/2c/Sir_Tony_Hoare_IMG_5125.jpg');

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
