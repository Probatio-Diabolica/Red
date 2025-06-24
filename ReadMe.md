# Red - CLI Client for Violet

Red is a lightweight command-line interface (CLI) tool built in modern C++ for interacting with the Violet database server. It supports both IPv4 and IPv6 and communicates over the RESP (REdis Serialization Protocol).

## Features

* Supports IPv4 and IPv6
* Fully RESP-compliant
* Interactive REPL and one-shot command modes
* Built-in command hints (optional)

## Supported Commands

All commands are case-insensitive.

### Common

* `STATUS` – Returns connection status
* `ECHO <msg>` – Returns the same message
* `FLUSHALL` – Clears all stored data

### Key/Value Operations

* `SET <key> <value>` – Stores a string value
* `GET <key>` – Retrieves the value for the given key
* `DEL <key>` – Deletes the key
* `EXPIRE <key> <seconds>` – Sets TTL on a key
* `KEYS`  – Lists all keys
* `TYPE <key>` – Returns type of the key (string, list, hash, none)
* `RENAME <old> <new>` – Renames a key

### List Operations

* `LGET <key>` – Retrieves all list elements
* `LLEN <key>` – Returns list length
* `LPUSH <key> <v1> [v2 ...]` – Push values to head
* `RPUSH <key> <v1> [v2 ...]` – Push values to tail
* `LPOP <key>` / `RPOP <key>` – Pop from head/tail
* `LREM <key> <count> <value>` – Remove occurrences
* `LINDEX <key> <index>` – Get element at index
* `LSET <key> <index> <value>` – Set element at index

### Hash Operations

* `HSET <key> <field> <value>` – Set field in hash
* `HGET <key> <field>` – Get field from hash
* `HEXISTS <key> <field>` – Check if field exists
* `HDEL <key> <field>` – Delete field from hash
* `HLEN <key>` – Number of fields in hash
* `HKEYS <key>` – All field names
* `HVALS <key>` – All values
* `HGETALL <key>` – All field/value pairs
* `HMSET <key> <f1> <v1> [f2 v2 ...]` – Set multiple fields

### Built-in CLI Commands

* `help` – Displays help
* `quit` – Exits CLI

## Build and Run

1. Clone the repository:

```bash
git clone https://github.com/Probatio-Diabolica/Red.git
cd Red
```

2. Build the project:

```bash
./build.sh
```

3. Run the CLI:

```bash
./red -h <host> -p <port>
```

Omit flags to use defaults (127.0.0.1:6379).

## Requirements & Dependencies

* Unix/Linux or WSL environment
* CMake (>=3.10)
* C++17 compatible compiler (GCC or Clang)

## Note

Red is designed to work seamlessly with Violet, a custom Redis-like database server written in C++.
