#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  //dis

int WriteToSave(char buf[], int pos, int isnew) {
    int maxlength = 10;
    
    FILE* savedfp = fopen("saved", "w");
    if(savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }

    if (isnew == 1)
        pos = 0;
    
    char tmp[512];
    int offset = (int)strlen(buf) - 1 - pos;
    
    for (int i=0; i < offset; i++) 
        tmp[i + pos] = buf[i];
    
    for (int in=0; in < pos; in++)
        tmp[in] = buf[in + offset];
    
    
    printf("|%s", tmp);
    printf("|");

    pos++;
    if (pos >= (int)strlen(buf) - 1) 
        pos = 0;
    
    char posstr[100];
    sprintf(posstr, "%d", pos);
    
    // DEUBUG 
    //printf("%s", posstr);
    
    fwrite(buf, strlen(buf), 1, savedfp);  
    fwrite(&posstr, strlen(posstr), 1, savedfp);  
    
    fclose(savedfp);
    return 0;
}


int main (void) {
    
    int maxLength = 100;
    char delim[] = "||  \n";

    char buf[maxLength + 1 + strlen(delim)];
    int size = sizeof(buf);
    fgets(buf, size, stdin); // Put input into buff
    size_t buflen = strlen(buf);

    
    strcat(buf, delim);
    buf[buflen - 1] = ' ';

    FILE* savedfp = fopen("saved", "r");
    if (savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }
    
    char savedstr[512];
    char savedstrpos[512], *endp;
    fgets(savedstr, 512, savedfp);    // Line 1 of saved file into savedstr
    fgets(savedstrpos, 512, savedfp); // Line 2 of saved file into savedpos
    
    int pos = strtol(savedstrpos, &endp, 0);
    if (strcmp(buf, savedstr) == 0) {
        WriteToSave(buf, pos, 0);
        fclose (savedfp);
        return 0;
    }
    WriteToSave(buf, pos, 1);
    fclose (savedfp);
    
    return 0;
}