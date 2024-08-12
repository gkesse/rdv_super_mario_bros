use db_super_mario_bros;

drop table _users;

create table _users (
    _id int not null auto_increment,
	_username varchar(255),
    _password varchar(255),
    primary key(_id),
    unique(_username)
);
