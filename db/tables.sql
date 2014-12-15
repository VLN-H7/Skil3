CREATE TABLE IF NOT EXISTS scientists (
        id integer primary key,
        first_name varchar(255),
        last_name varchar(255),
        gender varchar(1),
        birth_date date,
        death_date date,
        nationality varchar(255),
        image varchar(255)
);

CREATE TABLE IF NOT EXISTS computers (
        id integer primary key,
        name varchar(255),
        build_year integer,
        type varchar(255),
        built boolean,
        image varchar(255)
);


CREATE TABLE IF NOT EXISTS scientist_computer (
    id integer primary key,
    scientist_id integer,
    computer_id integer,
    FOREIGN KEY(scientist_id) REFERENCES scientists(id),
    FOREIGN KEY(computer_id) REFERENCES computers(id)
);
