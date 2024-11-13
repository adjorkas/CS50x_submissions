SELECT title FROM movies
JOIN stars ON movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE name = "Jennifer Lawrence"
AND title IN (
SELECT title FROM movies
JOIN stars ON movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE name = "Bradley Cooper"
);
