# Security-pack

Security-pack is an encrypted messenger communicator working on the local machine. It features mainly:

- creating new accounts with RSA keys,
- a login system (only the hashes of passwords are stored),
- sending and receiving messages to and from other accounts,
- a simple console UI.

The encrypted messages, password hashes and RSA keys are stored in sqlite3 databases ([Database.h](./Security-pack/src/Database.h), [DatabaseConnection.h](./Security-pack/src/DatabaseConnection.h)).

In order to achieve a high level of encryption, a custom large int class is implemented ([INT.h](./Security-pack/src/INT.h)).