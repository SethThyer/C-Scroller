#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>






int WriteToSave(char buf[], int pos) {

    FILE* savedfp = fopen("saved", "w");

    char tmp[512];
    for (int i=0; i < (int)strlen(buf); i++) {
        tmp[i] = buf[i + pos];
    }
    printf("%s\n", tmp);
    pos++;
    printf("%i", pos);
    fwrite(&tmp, strlen(tmp), 1, savedfp);  
    fwrite(&pos, sizeof(pos), 1, savedfp);  

    fclose(savedfp);
    return 0;
}



int main (void) {

    int maxLength = 100;
    // Variables

   // fseek(stdin, 0L, SEEK_END);
   // int long length = ftell(stdin);
   // printf("%li", length);

    char buf[maxLength + 1];
    int size = sizeof(buf);
    fgets(buf, size, stdin);






    FILE* savedfp = fopen("saved", "r");
    
    if(savedfp == NULL) {
        printf("Save file not found\n");
        return -1;
    }

    char savedstr[512];
    char savedstrpos[512], *endp;
    fgets(savedstr, 512, savedfp);
    fgets(savedstrpos, 512, savedfp);

    if (strcmp(buf, savedstr) == 0) {
        printf("SAME\n");
    }
    int pos = strtol(savedstrpos, &endp, 0);
    printf("NUMBER= ");
    printf("%i\n", pos);

    WriteToSave(buf, pos);
    // check if the input matches the saved input so it knows when to change the saved file or to continue to draw from it



    fclose (savedfp);


    




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