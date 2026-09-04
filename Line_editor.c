#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LEN 256

// Document storage
char doc[MAX_LINES][MAX_LEN];
int line_count = 0;

// Function Prototypes
void display_doc(void);
void insert_line(int line_num, const char *text);
void delete_line(int line_num);
void save_file(const char *filename);
void load_file(const char *filename);
void search_word(const char *word);
void show_stats(void);
void print_help(void);

int main(void)
{
    char input[MAX_LEN];
    char cmd[16];

    printf("==========================================\n");
    printf("   Simple C Line Editor (Type 'h' for help)\n");
    printf("==========================================\n");

    while (1)
    {
        printf("\neditor> ");
        if (!fgets(input, sizeof(input), stdin))
        {
            break;
        }

        // Remove trailing newline
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        // Parse the initial command key
        sscanf(input, "%s", cmd);

        if (strcmp(cmd, "p") == 0)
        {
            display_doc();
        }
        else if (strcmp(cmd, "i") == 0)
        {
            int line_num;
            char text[MAX_LEN] = "";
            // Extract line number and remaining text
            if (sscanf(input, "%*s %d %[^\n]", &line_num, text) >= 1)
            {
                insert_line(line_num, text);
            }
            else
            {
                printf("Error: Syntax is 'i <line_number> [text]'\n");
            }
        }
        else if (strcmp(cmd, "d") == 0)
        {
            int line_num;
            if (sscanf(input, "%*s %d", &line_num) == 1)
            {
                delete_line(line_num);
            }
            else
            {
                printf("Error: Syntax is 'd <line_number>'\n");
            }
        }
        else if (strcmp(cmd, "s") == 0)
        {
            char filename[MAX_LEN];
            if (sscanf(input, "%*s %s", filename) == 1)
            {
                save_file(filename);
            }
            else
            {
                printf("Error: Syntax is 's <filename>'\n");
            }
        }
        else if (strcmp(cmd, "l") == 0)
        {
            char filename[MAX_LEN];
            if (sscanf(input, "%*s %s", filename) == 1)
            {
                load_file(filename);
            }
            else
            {
                printf("Error: Syntax is 'l <filename>'\n");
            }
        }
        else if (strcmp(cmd, "find") == 0)
        {
            char word[MAX_LEN];
            if (sscanf(input, "%*s %s", word) == 1)
            {
                search_word(word);
            }
            else
            {
                printf("Error: Syntax is 'find <word>'\n");
            }
        }
        else if (strcmp(cmd, "stats") == 0)
        {
            show_stats();
        }
        else if (strcmp(cmd, "h") == 0)
        {
            print_help();
        }
        else if (strcmp(cmd, "q") == 0)
        {
            printf("Exiting line editor. Goodbye!\n");
            break;
        }
        else
        {
            printf("Unknown command. Type 'h' for help.\n");
        }
    }

    return 0;
}

// Display all current lines with line numbers
void display_doc(void)
{
    if (line_count == 0)
    {
        printf("[Document is empty]\n");
        return;
    }
    printf("--- Document State (%d lines) ---\n", line_count);
    for (int i = 0; i < line_count; i++)
    {
        printf("%4d | %s\n", i + 1, doc[i]);
    }
    printf("----------------------------------\n");
}

// Insert line at line_num (1-based index)
void insert_line(int line_num, const char *text)
{
    if (line_count >= MAX_LINES)
    {
        printf("Error: Maximum line limit reached (%d lines).\n", MAX_LINES);
        return;
    }

    // Adjust out-of-bounds line numbers safely
    if (line_num < 1)
        line_num = 1;
    if (line_num > line_count + 1)
        line_num = line_count + 1;

    int idx = line_num - 1;

    // Shift existing lines down
    for (int i = line_count; i > idx; i--)
    {
        strcpy(doc[i], doc[i - 1]);
    }

    // Insert new text
    strncpy(doc[idx], text, MAX_LEN - 1);
    doc[idx][MAX_LEN - 1] = '\0';
    line_count++;

    printf("Line inserted successfully at position %d.\n", line_num);
}

// Delete line at line_num (1-based index)
void delete_line(int line_num)
{
    if (line_count == 0)
    {
        printf("Error: Document is empty.\n");
        return;
    }
    if (line_num < 1 || line_num > line_count)
    {
        printf("Error: Invalid line number. Valid range is 1 to %d.\n", line_count);
        return;
    }

    int idx = line_num - 1;

    // Shift lines up
    for (int i = idx; i < line_count - 1; i++)
    {
        strcpy(doc[i], doc[i + 1]);
    }

    doc[line_count - 1][0] = '\0';
    line_count--;

    printf("Line %d deleted successfully.\n", line_num);
}

// Save document to a text file
void save_file(const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return;
    }

    for (int i = 0; i < line_count; i++)
    {
        fprintf(fp, "%s\n", doc[i]);
    }

    fclose(fp);
    printf("Document successfully saved to '%s'.\n", filename);
}

// Load document from a text file
void load_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: Could not open file '%s' for reading.\n", filename);
        return;
    }

    line_count = 0;
    char buffer[MAX_LEN];

    while (fgets(buffer, sizeof(buffer), fp) && line_count < MAX_LINES)
    {
        buffer[strcspn(buffer, "\r\n")] = '\0'; // Strip newline characters
        strcpy(doc[line_count], buffer);
        line_count++;
    }

    fclose(fp);
    printf("Loaded %d lines from '%s'.\n", line_count, filename);
}

// Search for a word/phrase in the document
void search_word(const char *word)
{
    if (line_count == 0)
    {
        printf("[Document is empty]\n");
        return;
    }

    int matches = 0;
    printf("--- Search Results for '%s' ---\n", word);
    for (int i = 0; i < line_count; i++)
    {
        if (strstr(doc[i], word) != NULL)
        {
            printf("Line %4d: %s\n", i + 1, doc[i]);
            matches++;
        }
    }

    if (matches == 0)
    {
        printf("No occurrences found.\n");
    }
    else
    {
        printf("Found in %d line(s).\n", matches);
    }
}

// Calculate total lines and word count
void show_stats(void)
{
    long word_count = 0;

    for (int i = 0; i < line_count; i++)
    {
        char temp[MAX_LEN];
        strcpy(temp, doc[i]);

        char *token = strtok(temp, " \t\n");
        while (token != NULL)
        {
            word_count++;
            token = strtok(NULL, " \t\n");
        }
    }

    printf("--- Document Statistics ---\n");
    printf("Total Lines: %d\n", line_count);
    printf("Total Words: %ld\n", word_count);
    printf("---------------------------\n");
}

// Display available commands
void print_help(void)
{
    printf("\n=== Command Guide ===\n");
    printf("  p                    : Print the document state\n");
    printf("  i <line_no> [text]   : Insert line at given line number\n");
    printf("  d <line_no>          : Delete line at given line number\n");
    printf("  s <filename>         : Save document to text file\n");
    printf("  l <filename>         : Load document from text file\n");
    printf("  find <word>          : Search for a word/phrase\n");
    printf("  stats                : Show line and word count statistics\n");
    printf("  h                    : Display this help message\n");
    printf("  q                    : Quit the editor\n");
}