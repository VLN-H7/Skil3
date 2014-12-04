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
        was_built boolean
);


CREATE TABLE IF NOT EXISTS scientist_computer (
    FOREIGN KEY(scientist_id) REFERENCES scientists(id),
    FOREIGN KEY(computer_id) REFERENCES computers(id)
);
