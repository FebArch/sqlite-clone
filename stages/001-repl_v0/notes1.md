# Notes

## Why InputBuffer exists

Instead of creating a new string every iteration,
we reuse one structure that owns the input memory.

getline() can automatically resize this buffer.

---

## Why REPL?

A database server continuously waits for commands.

The REPL models this behavior.

Read

↓

Parse

↓

Execute

↓

Repeat

---

## Why Meta Commands?

Commands beginning with '.'

Examples

.exit

.help

.schema

These are handled by the database itself.

They are NOT SQL.

---

## Why Prepare Statement?

The database shouldn't execute raw strings.

The input is first converted into an internal representation
called Statement.

Current Statement types

INSERT

SELECT

Later this becomes a complete parser.

---

## Why execute_statement()?

Separates parsing from execution.

Later execution will interact with:

Pager

↓

Table

↓

BTree

instead of printing messages.

---

## Memory Ownership

InputBuffer owns:

buffer

buffer_length

input_length

new_input_buffer()

↓

malloc()

↓

getline()

↓

free_input_buffer()

↓

free(buffer)

↓

free(InputBuffer)

No memory leaks.