SELECT name FROM songs WHERE artist_id IN (SELECT id FROM artists WHERE name = 'Post Malone');

OR

SELECT songs.name FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'Post Malone';
-- this is because "name" fieldname is common in both tables, so using filename.fieldname basically helps avoid any confusion in what to consider