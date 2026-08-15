# Stage 002 — Meta Commands & Statement Preparation

## Goal

Transform the REPL into a command interpreter.

Instead of treating every input as plain text, the database now classifies user input into two categories:

1. Meta Commands
2. SQL Statements

This stage introduces the basic architecture used by almost every database engine.

---

## New Concepts

- Meta Commands
- Statement Preparation
- Statement Execution
- Enums as Return Status
- Command Dispatching
- Separation of Frontend and Backend

---

## Architecture

                     User
                       │
                       ▼
                  Input Buffer
                       │
               Is first char '.' ?
                  /             \
                Yes             No
                 │               │
                 ▼               ▼
        Meta Command        Prepare Statement
                 │               │
                 ▼               ▼
            Execute         Execute Statement
                 │
                 ▼
              Result

---

## Components

### InputBuffer

Stores user input.

Responsible only for keeping the command entered by the user.

---

### MetaCommandResult

Represents the result of processing internal database commands.

Examples

.exit

Later

.constants
.btree
.help

---

### PrepareResult

Represents whether the SQL statement could be parsed successfully.

Possible values

PREPARE_SUCCESS

PREPARE_UNRECOGNISED_STATEMENT

---

### Statement

Represents an internal version of a SQL statement.

Current supported statements

INSERT

SELECT

Later this structure will also contain row data.

---

## Program Flow

Start

↓

Allocate InputBuffer

↓

Read User Input

↓

Does command start with '.' ?

↓

Yes

↓

Execute Meta Command

↓

Continue Loop

-----------------------------

No

↓

Prepare Statement

↓

Preparation Successful ?

↓

No

↓

Print Error

↓

Continue

-----------------------------

Yes

↓

Execute Statement

↓

Print Executed

↓

Repeat

---

## Files

main.cpp

Contains

- REPL
- Meta Command Dispatcher
- Statement Preparation
- Statement Execution

---

## What Changed From Stage 001

Stage 001

Every command except .exit was treated as unknown.

Stage 002

The program can now distinguish

Meta Commands

and

SQL Statements.

This lays the foundation for a parser.

---

## Key Takeaway

A database should never execute raw user input directly.

Input is first classified.

Then converted into an internal representation.

Only after successful preparation is it executed.

This architecture makes the system modular and extensible.