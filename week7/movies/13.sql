-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT DISTINCT people.name FROM people 
JOIN stars ON stars.person_id = people.id 
JOIN movies ON movies.id = stars.movie_id 
WHERE movies.id IN 
(SELECT stars.movie_id FROM stars WHERE stars.person_id IN 
(SELECT people.id FROM people WHERE people.name = 'Kevin Bacon' AND people.birth = 1958)) 
AND people.name <> 'Kevin Bacon';