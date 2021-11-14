#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int WriteToSave(char buf[], int pos, int isnew) {
    int maxlength = 20; // Change this to your liking
    
    char newl = '\n';
    FILE* savedfp = fopen("/home/seth/tmp/saved", "w");
    if(savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }
    
    if (isnew == 1)
        pos = 0;
    
    // size of buffer 
    size_t mls;
    
    if ((sizeof(char) * maxlength) > strlen(buf)) {
        mls = (sizeof(char) * maxlength);
    }
    else {
        mls = strlen(buf);
    }
    
    
    char *altbuf = malloc(mls);
    
    for (int it=0; it < mls; it++) {
        altbuf[it] = ' ';
        
        if (it < strlen(buf)) {
            altbuf[it] = buf[it];
        }
    }
    int full = strlen(altbuf);
    
    
    // Don't scroll if input is smaller than available space.
    // Delete this if statement to always scroll regardless if input size.
    if (strlen(altbuf) <= maxlength) {
        fwrite(buf, strlen(buf), 1, savedfp); 
        fwrite(&newl, 1, 1, savedfp);
        putw(pos, savedfp);
        
        //printf("|");
        printf("%s",altbuf);
        //printf("|");
        
        return 0;
    }
    
    // Scrolling happens here    
    char tmp[full * 2];
    int offset = full - pos;
    
    for (int i=0; i < full; i++) 
        tmp[i + pos] = altbuf[i];
    
    for (int in=0; in < pos; in++)
        tmp[in] = altbuf[in + offset];
    
    for (int it=maxlength + 1; it < strlen(tmp); it++) {
        tmp[it] = '\0';
    }
    
    
    //printf("|");
    printf("%s\n", tmp);
    //printf("|");
    
    pos = pos + 1;
    if (pos > full) 
        pos = 0;
    
    
    // DEUBUG 
    //printf("Len:%i\n", full);
    //printf("POS:%i\n", pos);
    
    
    // Write new position to file
    fwrite(buf, strlen(buf), 1, savedfp); 
    fwrite(&newl, 1, 1, savedfp);
    putw(pos, savedfp);
    
    free(altbuf);
    fclose(savedfp);
    return 0;
}


int main (void) {
    
    int MAbuflen = 100;
    char delim[] = "# ";
    
    char buf[MAbuflen + 1 + strlen(delim)];
    int size = sizeof(buf);
    fgets(buf, size, stdin); // Put input into buff
    size_t buflen = strlen(buf);
    
    
    strcat(buf, delim);
    buf[buflen - 1] = ' ';
    
    
    // Read saved position and string data from save file
    FILE* savedfp = fopen("/home/seth/tmp/saved", "r");
    if (savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }
    
    char savedstr[512];
    fgets(savedstr, 512, savedfp);    // Line 1 of saved file into savedstr
    int pos = getw(savedfp);          // Line 2 of saved file into savedpos
    
    
    // If the string to be scrolled is changed then reset scroll position
    savedstr[strlen(savedstr) - 1] = '\0';
    
    if (strcmp(buf, savedstr) == 0) {
        WriteToSave(buf, pos, 0);
        fclose (savedfp);
        return 0;
    }
    
    WriteToSave(buf, pos, 1);
    fclose (savedfp);
    
    return 0;
}