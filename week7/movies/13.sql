SELECT name FROM people
JOIN stars ON person_id = people.id
JOIN movies ON movie_id = movies.id
WHERE title IN (
SELECT title FROM people
JOIN stars ON person_id = people.id
JOIN movies ON movie_id = movies.id
WHERE name = "Kevin Bacon" AND birth = 1958)
AND name != "Kevin Bacon";
