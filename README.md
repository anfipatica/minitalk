# minitalk

A small client-server program that sends text between two processes using
only UNIX signals (`SIGUSR1` and `SIGUSR2`). Built at
[42 Madrid](https://www.42madrid.com/).

## How it works

- The **server** prints its PID and waits for signals.
- The **client** receives the server's PID and a message, and sends it
  **bit by bit**, least significant bit first: `SIGUSR1` is a `1` and
  `SIGUSR2` is a `0`.
- The protocol has two phases: first the **length** of the message as ASCII
  digits ended by a NUL byte, then the **message** itself, also NUL-terminated.
- The server tracks the phase with a small state machine. It allocates a buffer
  of the announced length, rebuilds each character from its 8 bits, and prints
  the message when it is complete.

### Bonus

- The server **acknowledges every bit** by signalling back to the client. It
  gets the client's PID from `siginfo_t` (`SA_SIGINFO`).
- The client waits for each acknowledgement and, at the end, prints how many
  characters it sent and how many confirmations it received.

## Build and run

Requires `cc` and `make` on Linux.

```bash
git clone https://github.com/anfipatica/minitalk.git
cd minitalk
make

./bin/server              # prints the server PID
./bin/client <PID> "Hello, minitalk!"
```

For the bonus version:

```bash
make bonus
./bin/server_bonus
./bin/client_bonus <PID> "Hello, minitalk!"
```

## Project layout

| Path | Contents |
|---|---|
| `src/` | Mandatory client and server |
| `bonus/` | Bonus client and server (acknowledgements) |
| `inc/` | Headers |
| `libft/`, `ft_printf/` | Our own C libraries |

## What I learned

- Signal handling with `sigaction` and `siginfo_t`
- Inter-process communication using only signals
- Bitwise operations to encode and decode characters
- Designing a small communication protocol with a state machine
