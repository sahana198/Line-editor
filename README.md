# C Line Editor - Coding Competition Project

## Team Members
- Member 1: Sahana
- Member 2: Spoorthi D Navaratna 
- Member 3: Yukta SV

## Features Implemented
- **Core Feature:** Display Document (`p`)
- **Core Feature:** Insert Line (`i`)
- **Core Feature:** Delete Line (`d`)
- **Core Feature:** Save & Load File (`s`, `l`)
- **Bonus Feature:** Search Word/Phrase (`find`)
- **Bonus Feature:** Word & Line Count Statistics (`stats`)

## Data Structure Choice
We selected a **Fixed 2D Character Array (`char doc[1000][256]`)**. This structure completely eliminates dynamic memory allocation overhead and memory leaks while providing fast O(1) line access and low implementation complexity under a strict time constraint.

## How to Compile and Run

### Compilation
```bash
gcc -Wall -Wextra line_editor.c -o editor# Line-editor