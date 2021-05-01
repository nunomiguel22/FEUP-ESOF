begin transaction;

drop table if exists votes;
create table votes
(
    question text primary key,
    option1 text,
    option1_votes int,
    option2 text,
    option2_votes int
);

commit transaction;
