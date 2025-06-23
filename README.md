# len

A simple command-line utility to count characters in text

## Features

- Count characters from arguments, files, or piped input
- Character breakdown summary (letters, digits, spaces, special)

## Installation

### Option 1: Install to /usr/local/bin (system-wide)
```bash
# Compile and install
gcc -O2 -o len len.c
sudo cp len /usr/local/bin/
```

### Option 2: Install to ~/.local/bin (user-only)
```bash
# Create directory if it doesn't exist
mkdir -p ~/.local/bin

# Compile and install
gcc -O2 -o len len.c
cp len ~/.local/bin/

# Add to PATH if not already
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

## Usage

### Basic character counting
```bash
len "hello world"           # Output: 11
len hello world             # Output: 11
```

### Detailed summary
```bash
len -s "hello world"
┌──────────┬───────┐
│ Type     │ Count │
├──────────┼───────┤
│ Total    │    11 │
│ Letters  │    10 │
│ Digits   │     0 │
│ Spaces   │     1 │
│ Special  │     0 │
└──────────┴───────┘
```

### File input
```bash
len -f myfile.txt           # Count characters in file
len -sf myfile.txt          # Show detailed summary of file
```

### Piped input
```bash
echo "hello world" | len    # Output: 12 (includes newline)
cat file.txt | len -s       # Detailed summary of piped content
```

## Uninstallation

```bash
# Remove from system
sudo rm /usr/local/bin/len

# Or remove from user directory
rm ~/.local/bin/len
```