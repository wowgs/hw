#include <stdio.h>
#include <string.h>
#define COMMANDS 9
#define MAX_SIZE 1048576
#define MAX_LINES 1000
#define MAX_NAME 30

typedef struct
{
    int type;
    union
    {
        int number;
        char lbl[MAX_NAME];
    } arg;
} tcommand;
typedef struct
{
    char name[MAX_NAME];
    size_t line;
} tlabel;
typedef enum
{
	LD,
	ST,
	LDC,
	ADD,
	SUB,
	CMP,
	JMP,
	BR,
	RET,
} command; //to simplify work with case

char *commands[COMMANDS] = {"ld", "st", "ldc", "add", "sub", "cmp", "jmp", "br", "ret"}; //to simplify work with whatCommand
int data[MAX_SIZE];
int stack[MAX_SIZE];
char str[255];
char stInstr[MAX_NAME];
char stArg[MAX_NAME];
int arr_label = 0;
int countLines = 0;

tcommand instr[MAX_LINES];
tlabel label[MAX_LINES];

int find(char *stInstr, char *str, int i)
{
    while (str[i] == ' ')
    {
        i++;
    }
    if ((str[i] == ';') || (str[i] == '\0'))
    {
        return i;
    }
    int j = 0;
    while ((isalpha(str[i])) || (isdigit(str[i])) || (str[i] == '-'))
    {
        stInstr[j] = str[i];
        i++;
        j++;
    }
    stInstr[j] = '\0';
    return i;
}

int whatCommand(char *stInstr)
{
    int k;
    for (k = 0; k < COMMANDS; k++)
    {
        if (strcmp(stInstr, commands[k]) == 0)
        {
            return k;
        }
    }
}

int readFile(FILE *file)
{
    while (!feof(file))
    {
        fgets(str, 255, file);
        int i = 0;
        while (str[i] == ' ')
        {
            i++;
        }
        if ((str[i] == ';') || (str[i] == '\n') || (str[i] == '\0'))
        {
            continue;
        }
        i = 0;
        i = find(stInstr, str, i);
        instr[countLines].type = whatCommand(stInstr);
        int k;
        while (str[i] == ' ')
        {
            i++;
        }
        if (str[i] == ':')
        {
            strcpy(label[arr_label].name, stInstr);
            label[arr_label].line = countLines;
            arr_label++;
            i++;
            if (str[i] == '\0')
            {
                continue;
            }
            else
            {
                i = find(stInstr, str, i);
            }
        }
        while (str[i] == ' ')
        {
            i++;
        }
        instr[countLines].type = whatCommand(stInstr);
        int j = 0;
        i = find(stArg, str, i);
        if (isdigit(stArg[0]) || (stArg[0] == '-'))
        {
            instr[countLines].arg.number = atoi(stArg);
        }
        else
        {
            strcpy(instr[countLines].arg.lbl, stArg);
        }
        countLines++;
   }
   return 1;
}

int runProgram(FILE *file)
{
    int SP = -1;
    int i = -1;
    int arg;
    char lbl[MAX_NAME];
    int a, b, j;
    while (1)
    {
       i++;
       switch (instr[i].type)
       {
           case LD:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE) || (arg > MAX_SIZE) || (arg < 0))
               {
                  printf("ERROR_LD");
                  return 0;
               }
               stack[SP] = data[arg];
               break;
           case ST:
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE) || (arg > MAX_SIZE) || (arg < 0))
               {
                  printf("ERROR_ST");
                  return 0;
               }
               data[arg] = stack[SP];
               SP--;
               break;
           case LDC:
               SP++;
               arg = instr[i].arg.number;
               if ((SP < 0) || (SP > MAX_SIZE))
               {
                   printf("ERROR_LDC");
                   return 0;
               }
               stack[SP] = arg;
               break;
           case ADD:
               if (SP < 1)
               {
                   printf("ERROR_ADD");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a + b;
               break;
           case SUB:
                if (SP < 1)
               {
                   printf("ERROR_SUB");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a - b;
               break;
           case CMP:
               if (SP < 1)
               {
                   printf("ERROR_CMP");
                   return 0;
               }
               a = stack[SP];
               SP = SP - 1;
               b = stack[SP];
               stack[SP] = a > b ? 1 : a < b ? -1 : 0;
               break;
          case JMP:
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case BR:
               if ((stack[SP] == 0))
               {
                   break;
               }
               j = 0;
               strcpy(lbl, instr[i].arg.lbl);
               while (strcmp(lbl, label[j].name) != 0)
               {
                   j++;
               }
               i = label[j].line;
               i--;
               break;
           case RET:
               printf("result = %d\n", stack[SP]);
               fclose(file);
               return 1;
        }
    }
}

int main()
{
    printf("Enter name of file\n");
    char fileName[MAX_NAME];
    gets(fileName);
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
	printf("File not found\n");
	return;
    }
    if (!readFile(file))
    {
        fclose(file);
        return;
    }
    if (!runProgram(file))//error
    {
        fclose(file);
    }
    return;
}
