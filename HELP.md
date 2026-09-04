# Line Editor Command Guide

This document explains all available commands for the C Line Editor with usage examples.

## Commands Reference

### 1. Display Document (`p`)
Prints all document lines with their line numbers.
- **Syntax:** `p`
- **Example:** `p`

### 2. Insert Line (`i`)
Inserts a new line of text at a specified 1-based index.
- **Syntax:** `i <line_number> <text>`
- **Example:** `i 1 Hello World`

### 3. Delete Line (`d`)
Deletes a line at the specified line number and shifts remaining lines up.
- **Syntax:** `d <line_number>`
- **Example:** `d 2`

### 4. Save File (`s`)
Saves the current document state to a `.txt` file.
- **Syntax:** `s <filename>`
- **Example:** `s my_doc.txt`

### 5. Load File (`l`)
Loads lines from an existing text file into memory.
- **Syntax:** `l <filename>`
- **Example:** `l my_doc.txt`

### 6. Search Word (`find`)
Finds and displays all lines containing a given word or phrase.
- **Syntax:** `find <word>`
- **Example:** `find Hello`

### 7. Document Statistics (`stats`)
Displays total line count and total word count.
- **Syntax:** `stats`
- **Example:** `stats`

### 8. Quit (`q`)
Exits the editor.
- **Syntax:** `q`