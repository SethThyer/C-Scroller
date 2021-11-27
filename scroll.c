#include <stdio.h>
#include <stdlib.h>

#include <wchar.h>
#include <string.h>
#include <locale.h>


int WriteToSave(wchar_t buf[], int pos, int isnew) {
    int maxlength = 29; // Change this to your liking
    wchar_t newl = L'\n';
    
    FILE* savedfp = fopen("/home/seth/tmp/saved", "w");
    if(savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }
    
    if (isnew == 1)
        pos = 0;
    
    
    // size of buffer 
    size_t mls;
    int buflen = wcslen(buf);
    
    if ((4 * maxlength) > buflen) {
        mls = (4 * maxlength);
    }
    else {
        mls = buflen;
    }
    
    wchar_t *altbuf = malloc(mls);
    
    for (int it=0; it < mls / 4; it++) {
        altbuf[it] = ' ';
        
        if (it < buflen) {
            altbuf[it] = buf[it];
        }
    }
    int full = wcslen(altbuf);
    
    
    // Don't scroll if input is smaller than available space.
    // Delete this if statement to always scroll regardless if input size.
    if (buflen <= maxlength) {
        
        if (maxlength-buflen > 1) {
            
            int inter = (maxlength - buflen) / 2;
            int intereven = 1;
            
            if (buflen % 2 == 1){
                inter = (maxlength - buflen - 1) / 2;
                intereven = 0;
            }
            
            for (int i=0; i <= inter; i++) {
                altbuf[i] = ' ';
            }
            
            for (int it=0; it<=buflen+1; it++) {
                altbuf[it+inter+1] = buf[it];
            }
            
            if (intereven == 0) {
                for (int in=0; in < inter+1; in++) {
                    altbuf[in+inter+buflen+1] = ' ';
                }
            }
            else {
                for (int in=0; in < inter+1; in++) {
                    altbuf[in+inter+buflen] = ' ';
                }
            }
        }
        
        fwrite(buf, buflen, 1, savedfp); 
        fwrite(&newl, 1, 1, savedfp);
        putw(pos, savedfp);
        
        //printf("|");
        wprintf(L"%ls",altbuf);
        //printf("|");
        
        return 0;
    }
    
    // Scrolling happens here    
    wchar_t tmp[full * 2];
    int offset = full - pos;
    
    for (int i=0; i < full; i++) 
        tmp[i + pos] = altbuf[i];
    
    for (int in=0; in < pos; in++)
        tmp[in] = altbuf[in + offset];
    
    for (int it=maxlength; it < wcslen(tmp); it++) {
        tmp[it] = '\0';
    }
    
    
    //printf("|");  
    wprintf(L"%ls\n", tmp);
    //printf("|");
    
    pos = pos + 1;
    if (pos > full) 
        pos = 0;
    
    
    // DEUBUG 
    //printf("Len:%i\n", full);
    //printf("POS:%i\n", pos);
    
    
    // Write new position to file
    fwrite(buf, wcslen(buf), 1, savedfp); 
    fwrite(&newl, 1, 1, savedfp);
    putw(pos, savedfp);
    
    free(altbuf);
    fclose(savedfp);
    return 0;
}


int main (void) {
    setlocale(LC_ALL, "en_US.utf16");

    int MAbuflen = 100;
    wchar_t delim[] = L"# ";
    
    wchar_t buf[(MAbuflen + 1) * 4 + wcslen(delim)];
    int size = sizeof(buf);
    fgetws(buf, size, stdin); // Put input into buff
    size_t buflen = wcslen(buf);
    
    wcscat(buf, delim);
    buf[buflen - 1] = ' ';
    
    
    // Read saved position and string data from save file
    FILE* savedfp = fopen("/home/seth/tmp/saved", "r");
    if (savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }
    
    wchar_t savedstr[512 * 4];
    fgetws(savedstr, 512 * 4, savedfp);
    int pos = getw(savedfp);
    
    
    // If the string to be scrolled is changed then reset scroll position
    //savedstr[wcslen(savedstr) - 1] = '\0';

    wprintf(L"%ls\n", savedstr);
    wprintf(L"%ls\n", buf);
    printf("DONE\n");

    if (wcscmp(buf, savedstr) == 0) {
        WriteToSave(buf, pos, 0);
        fclose (savedfp);
        printf("DAS");
        return 0;
    }
    WriteToSave(buf, pos, 1);
    fclose (savedfp);
    
    return 0;
}