-- 12. Titles of all of movies in which both Jennifer Lawrence and Bradley Cooper starred
SELECT movies.title FROM movies 
JOIN stars AS s1 ON s1.movie_id = movies.id 
JOIN stars AS s2 ON s2.movie_id = movies.id 
WHERE s1.person_id = (SELECT people.id from people WHERE people.name = 'Jennifer Lawrence') 
AND s2.person_id = (SELECT people.id from people WHERE people.name = 'Bradley Cooper');