-- Keep a log of any SQL queries you execute as you solve the mystery.
-- FIND: thief, escape place, accomplice for escape

-- Check all tables
.tables

-- Check crime_scene_reports table
SELECT * FROM crime_scene_reports LIMIT 3;

-- Select rows that correspond to July 28, Humphrey Street
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";

-- 10:15 am stolen at bakery, three witnesses where interview mentions this place. Year 2021

SELECT name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";
-- Ruth: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene:  I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond:  As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Find thief name according to Ruth
SELECT name, phone_number, passport_number FROM bakery_security_logs JOIN people ON people.license_plate = bakery_security_logs.license_plate WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;
-- Possible thieves: Vanessa, Bruce, Barry, Luca, Sofia, Iman, Diana, Kelsey

-- Check people who withdrew money that morning (Eugene)
SELECT name FROM atm_transactions JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number JOIN people ON people.id = bank_accounts.person_id WHERE atm_location = "Leggett Street" AND transaction_type = "with
draw" AND month = 7 AND day = 28;
-- Bruce, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista
-- So far the intersection is: Bruce, Luca, Iman, Diana

-- Check callers for less than a minute (Raymond)
SELECT caller, receiver, name FROM phone_calls JOIN people ON caller = phone_number wHERE month = 7 AND day = 28 AND duration < 60;
-- Callers: Sofia, Kelsey, Bruce, Taylor, Diana, Carina, Kenny, Benista
-- So far thief intersection: Bruce ((367) 555-5533), Diana ((770) 555-1861)

-- One of the speakers bought the plane ticket
SELECT caller, receiver, name FROM phone_calls JOIN people ON receiver = phone_number wHERE month = 7 AND day = 28 AND duration < 60 AND (caller = "(367) 555-
5533" OR caller = "(770) 555-1861");
-- Possible accomplices: Robin, Philip

-- Find possible flights:
SELECT * FROM flights JOIN airports ON origin_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
-- Earliest flight is 8:20 with destination to...
SELECT full_name, city FROM flights JOIN airports ON destination_airport_id = airports.id WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1;
-- LaGuardia Airport, New York City (flight id = flights.id(36))

-- People in flight 36...
SELECT name FROM passengers JOIN people ON people.passport_number = passengers.passport_number WHERE flight_id = 36;
-- Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca

-- Check Bruce's accomplice
SELECT name FROM phone_calls JOIN people ON receiver = phone_number wHERE month = 7 AND day = 28 AND duration < 60 AND caller = "(367) 555-5533";

-- THIEF: BRUCE
-- ACCOMPLICE: ROBIN
-- CITY: NEW YORK CITY
