#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main (void) {

    int maxLength = 100;
    // Variables

   // fseek(stdin, 0L, SEEK_END);
   // int long length = ftell(stdin);
   // printf("%li", length);

    char buf[maxLength + 1];
    int size = sizeof(buf);
    fgets(buf, size, stdin);

    char tmp[256]={0x0};
    char writeTo[sizeof(tmp)];





    FILE* savedfp = fopen("saved", "r");
    
    if(savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }

    char savedstr[512];
    fgets(savedstr, 512, savedfp);

    fclose (savedfp);


    char *fpdef = NULL;
    char *fpalt = NULL;
    int setswitch = 1;

    // Split the file into 2 
    char* pch = NULL;

    //printf ("%s", buf);

    char spacers[] = "\n"; 

    pch = strtok(savedstr, spacers);

    while (pch != NULL) {

        printf("%s", savedstr);

        pch = strtok(NULL, spacers);

    }
    
    




    //printf("def: %d\n", fpdef);
    //printf("alt: %d\n", fpalt);


    // for (int i; i < length; i++) {

    //     writeTo[i] = buf[i + 1];
    // }

    // Assign num to each char
    //x.tochar[]
    
    // Read from positionfile to get scroll position
    //z = file.num     //[z=5]
    
    // Create new array to hold produced value
    //y = Array[x.length]
    
    //for loop x.length {
    //  g = RelativePosition(z, i)
    //  y[i] = x[i + g]
    //}
    
    // Write to positionfile
    //file.num = z + 1
    //if (z + 1 > length) file.num = 0
    
    //void RelativePosition(h, l) {
    //  if (h + l + 1 > x.length) {
    //  h -= x.length
    //  RelativePosition(h)
    //  }

    //  New cut array
    //r = Array[length]
    //for loop length {
    //  r[i] = y[i]
    //}

    return 0;
}
