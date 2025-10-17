# len

A simple command-line utility to count characters in text

## Usage

### Basic character counting
```bash
len "hello world"
len hello world
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
