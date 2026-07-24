# Stage 001 — REPL

## Goal

Build the frontend of the database.

At this stage the database does not store any data.

It only accepts user input repeatedly until the user exits.

---

## New Concepts

- REPL (Read Evaluate Print Loop)
- Dynamic memory allocation
- Input buffer
- getline()
- Command loop
- Resource cleanup

---

## Program Flow

Program Starts

↓

Allocate InputBuffer

↓

Print Prompt

↓

Read User Input

↓

If ".exit"

    Free Memory

    Exit

Else

    Print Unknown Command

↓

Repeat

---

## Files

main.cpp

Contains

- REPL loop
- Input handling
- Exit handling

---

## Data Structure

InputBuffer

buffer

Stores user input

buffer_size

Capacity allocated for getline()

input_size

Actual length of the command

---

## Memory Ownership

set_input_buffer()

creates

↓

main()

owns

↓

read_input()

updates

↓

free_input_buffer()

destroys

---

## What I Learned

A database frontend is simply a loop that continually accepts commands.

Instead of allocating a new string every iteration, one reusable InputBuffer is maintained.

getline() automatically resizes the buffer when necessary.

The frontend is completely separated from the database engine.

At this stage there is no parser or storage layer.