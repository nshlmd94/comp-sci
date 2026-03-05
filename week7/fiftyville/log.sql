-- Keep a log of any SQL queries you execute as you solve the mystery.

-- details of the crime itself; 10:15am at Humprey Street Bakery
SELECT crime_scene_reports.description, crime_scene_reports.id FROM crime_scene_reports 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28; 

-- get interview notes for more clues : 1. Left in 10 mins of theft; 2. Withdrew money from Leggett Street; 3. Spoke to someone for less than a minute and asked to book earliest flight out of Fiftyville tomorrow
SELECT id, name, transcript FROM interviews 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28; 

-- find how the earlier flight flying out on the next day of the theft - Flight id 36 is the earliest flying out tomorrow from Fiftyville
SELECT flights.id, airports.city, flights.origin_airport_id, flights.destination_airport_id, flights.hour, flights.minute FROM flights 
    JOIN airports ON airports.id = flights.origin_airport_id
    WHERE flights.day = 29 
        AND flights.month = 7 
        AND flights.year = 2025 
    ORDER BY flights.hour; 

-- capture details on entry and exit of licencse plates
SELECT id, activity, license_plate, minute FROM bakery_security_logs 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28 
        AND hour = 10 
        AND minute >= 15 
        AND minute <= 30; 

-- narrow down to the vehicle license plates exiting
SELECT id, license_plate, minute FROM bakery_security_logs 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28 
        AND hour = 10 
        AND minute >= 15 
        AND minute <= 30 
        AND activity = 'exit'; 

-- getting details on the above license plates
SELECT DISTINCT people.id, people.name, people.phone_number, people.passport_number, people.license_plate FROM people 
    JOIN bakery_security_logs 
        ON bakery_security_logs.license_plate = people.license_plate 
    WHERE bakery_security_logs.license_plate IN (
        SELECT license_plate FROM bakery_security_logs 
            WHERE year = 2025 
                AND month = 7 
                AND day = 28 
                AND hour = 10 
                AND minute >= 15 
                AND minute <= 30 
                AND activity = 'exit') 
            ORDER BY bakery_security_logs.minute; 

-- getting details on which of these folks flew on which flight : Bruce, Kelsey, Luca, Sofia flew on Flight 36
SELECT DISTINCT passengers.passport_number, people.name, passengers.seat FROM passengers 
    JOIN people 
        ON people.passport_number = passengers.passport_number 
    JOIN bakery_security_logs 
        ON bakery_security_logs.license_plate = people.license_plate 
    WHERE bakery_security_logs.license_plate IN (
        SELECT license_plate FROM bakery_security_logs 
            WHERE year = 2025 
                AND month = 7 
                AND day = 28 
                AND hour = 10 
                AND minute >= 15 
                AND minute <= 30 
                AND activity = 'exit') 
                AND passengers.flight_id = 36
            ORDER BY passengers.flight_id; 

-- figure out schema of the entries
SELECT id, account_number, atm_location, transaction_type, amount FROM atm_transactions 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28; 

-- get specific details to the location
SELECT id, account_number, amount FROM atm_transactions 
    WHERE year = 2025 
        AND month = 7 
        AND day = 28 
        AND atm_location = 'Leggett Street' 
        AND transaction_type = 'withdraw'; 

-- gets the names of people who withdrew money from the ATM : Bruce and Luca overlap
SELECT DISTINCT people.name FROM people 
    JOIN bank_accounts 
        ON bank_accounts.person_id = people.id 
    JOIN atm_transactions 
        ON atm_transactions.account_number = bank_accounts.account_number 
    WHERE bank_accounts.account_number IN (
        SELECT atm_transactions.account_number FROM atm_transactions 
        WHERE atm_transactions.year = 2025 
            AND atm_transactions.month = 7 
            AND atm_transactions.day = 28 
            AND atm_transactions.atm_location = 'Leggett Street' 
            AND atm_transactions.transaction_type = 'withdraw');

-- filter out with the licence plates we saw at the bakery: Bruce and Luca exit on similar times
SELECT bakery_security_logs.id, people.name, bakery_security_logs.license_plate, bakery_security_logs.minute FROM bakery_security_logs 
    JOIN people 
        ON people.license_plate = bakery_security_logs.license_plate
    WHERE year = 2025 
        AND month = 7 
        AND day = 28 
        AND hour = 10 
        AND minute >= 15 
        AND minute <= 30 
        AND activity = 'exit'; 

-- lets look into calls on that day with duration less than 60 seconds : looks like only Bruce called someone (Robin)
SELECT c.name, r.name, phone_calls.duration FROM phone_calls
    JOIN people AS c
        ON c.phone_number = phone_calls.caller
    JOIN people AS r
        ON r.phone_number = phone_calls.receiver
    WHERE phone_calls.year = 2025
        AND phone_calls.month = 7
        AND phone_calls.day = 28
        AND phone_calls.duration < 60;

-- destination airport : New York City
SELECT airports.city FROM airports
    JOIN flights
        ON flights.destination_airport_id = airports.id
    WHERE flights.id = 36;