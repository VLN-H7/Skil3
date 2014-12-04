CREATE TABLE IF NOT EXISTS scientists (
        id integer primary key,
        first_name varchar(255),
        last_name varchar(255),
        gender varchar(1),
        birth_date date,
        death_date date,
        nationality varchar(255)
);

CREATE TABLE IF NOT EXISTS computers (
        id integer primary key,
        name varchar(25),
        build_year integer,
        type varchar(25),
        was_built bool
);


CREATE TABLE IF NOT EXISTS scientist_computer (
        computer_id integer foreign key,
        scientist_id integer foreign key
);
