# Notes

## Biggest Idea

The REPL is becoming a Frontend.

Instead of immediately executing text,

User Input

↓

Preparation

↓

Execution

This is exactly how real databases work.

---

## What is a Meta Command?

Meta commands are commands for the database program itself.

Examples

.exit

.help

.tables

.constants

These are NOT SQL.

They control the database shell.

---

## Why check

buffer[0] == '.'

instead of strcmp() ?

Because every meta command starts with '.'

We can quickly separate them from SQL statements without parsing the whole input.

This is a very cheap classification.

---

## Why create StatementType?

Instead of carrying strings around

"insert"

"select"

the program converts them into enums.

String

↓

Enum

↓

Execution

Enums are

- Faster
- Safer
- Easier to compare

---

## Why have prepare_statement() ?

User input is unreliable.

prepare_statement()

acts like a parser.

Its job is

Text

↓

Internal Representation

If parsing fails

Nothing gets executed.

---

## Why separate preparation from execution?

Imagine the command

insert 1 Alice alice@mail.com

Preparation

↓

Extract id

Extract username

Extract email

↓

Store inside Statement

↓

Execution

Insert Row

The executor should never need to understand text.

---

## Why use return enums?

Instead of

true

false

we return

PREPARE_SUCCESS

PREPARE_UNRECOGNISED_STATEMENT

This makes code much easier to extend.

Later

PREPARE_SYNTAX_ERROR

PREPARE_NEGATIVE_ID

PREPARE_STRING_TOO_LONG

can all be added.

---

## Architecture Evolution

Stage 001

User

↓

REPL

↓

Unknown Command

--------------------------------

Stage 002

User

↓

REPL

↓

Classifier

↓

Meta Command

or

SQL Statement

↓

Executor
