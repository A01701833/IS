#include <stdlib.h>
#include <stdio.h>
#include <string.h>    

struct position
{
    int row;
    int column;
};

void createTable(char **table)
{
    table[0] = "ENCRY";
    table[1] = "PTABD";
    table[2] = "FGHIK";
    table[3] = "LMOQS";
    table[4] = "UVWXZ";
}

struct position* tIndexes(char** table, char* msg, int tableSize){
    struct position * pos;
    int i, x, y, w = 0, spaces = 0, msgS, s_len = strlen(msg);

    for(i=0; i<s_len; i++)
    {
        if(msg[i] == ' ')
            ++spaces;
    }

    msgS = s_len - spaces;
    pos = malloc(sizeof(struct position)*msgS);

    for(i=0; i < s_len; i++)
    {
        for(x = 0; x < tableSize; x++)
        {
            for(y = 0; y < tableSize; y++)
            {
                if(msg[i] == ' ')
                {
                    ++w;
                    ++i;
                }
                if(msg[i] == table[x][y])
                {
                    pos[i - w].row = x;
                    pos[i - w].column = y;                    
                }

            }
        }
    }
    return pos;
}

char* decypher(char** table, char* msg, struct position *pos, int tableSize)
{
    int i, x, y, w=0, spaces=0, msgS, s_len = strlen(msg);
    char* new_sen = malloc(sizeof(char)*s_len);
    struct position *decr_pos;

    for(i=0; i<s_len; i++){
        if(msg[i] == ' ')
            ++spaces;
    }

    msgS = s_len - spaces; 

    decr_pos = malloc(sizeof(struct position)*msgS);
        memcpy(decr_pos, pos, sizeof(struct position)*msgS);

        if(msgS % 2 == 0)
        {
            for(x = 0, w = 0; x < (msgS / 2); x++, w += 2)
            {
                decr_pos[w].row = pos[x].row;
                decr_pos[w + 1].row = pos[x].column;
            }

            for(y = x, w = 0; y < (x + (msgS / 2)); y++, w += 2)
            {
                decr_pos[w].column = pos[y].row;
                decr_pos[w+1].column = pos[y].column;
            }            
        }
        else
        {
            for(x = 0, w = 0; x < (msgS / 2); x++, w += 2)
            {
                decr_pos[w].row = pos[x].row;
                decr_pos[w+1].row = pos[x].column;
            }

            decr_pos[w].row = pos[x].row;
            decr_pos[0].column = pos[x].column;

            for(y = x+1, w = 1; y < (x + 1 + (msgS / 2)); y++, w += 2)
            {
                decr_pos[w].column = pos[y].row;
                decr_pos[w+1].column = pos[y].column;
            }            
        }

        for(x = 0, w = 0; x < s_len; x++, w++)
        {  
            new_sen[x] = table[decr_pos[w].row][decr_pos[w].column];
        }
        return new_sen;
}

char* cypher(char** table, char* msg, struct position *pos, int tableSize)
{
    int i, x, y, w = 0, spaces = 0, msgS, s_len = strlen(msg);
    char* new_sen = malloc(sizeof(char)*s_len);
    struct position *decr_pos;

    for(i = 0; i < s_len; i++){
        if(msg[i] == ' ')
            ++spaces;
    }

    msgS = s_len - spaces; 

    decr_pos = malloc(sizeof(struct position)*msgS);
    memcpy(decr_pos, pos, sizeof(struct position)*msgS);

    if(msgS % 2 == 0)
    { 
        for(x = 0, w = 0; x < (msgS / 2); x++, w += 2)
        {
            new_sen[x] = table[decr_pos[w].row][decr_pos[w+1].row];            
        }

        for(y = x, w = 0; y < (x + (msgS / 2)); y++, w += 2)
        {
            new_sen[y] = table[decr_pos[w].column][decr_pos[w+1].column];           
        }
    }
    else
    {
        for(x = 0, w = 0; x < (msgS / 2); x++, w += 2)
        {      
            new_sen[x] = table[decr_pos[w].row][decr_pos[w+1].row];            
        }

        new_sen[x] = table[decr_pos[w].row][decr_pos[0].column];


        for(y = x + 1, w = 1; y < (x + 1 + (msgS/2)); y++, w += 2)
        {
            new_sen[y] = table[decr_pos[w].column][decr_pos[w + 1].column];            
        }
    } 
    return new_sen;
}


int main()
{
    char **table;
    struct position *pos;
    int tableSize = 5, i;
    char* result;
    char msg[100];
    char* opc;

    scanf("%s", opc);
    scanf(" %[^\n]s", msg);

    table = malloc(tableSize * sizeof(char*));

    for (i = 0; i < tableSize; i++)
    {
        table[i] = malloc((tableSize + 1) * sizeof(char));
    }
    printf("opc= %s", opc);
    createTable(table);
    pos = tIndexes(table, msg, tableSize);    
    if((void *)opc == "ENCRYPT")
    {
        result = cypher(table, msg, pos, tableSize);  
    }  
    else decypher(table, msg, pos, tableSize);   
    printf("%s", result);

    return 0;
}