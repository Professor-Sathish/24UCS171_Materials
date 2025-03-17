#include <stdio.h>
int main () { 
    int count; 
    scanf ("%d", &count); 
    char letter;
    scanf("%c",&letter);

    int nseq = 1;  

    for (int j = 0; j < count; j++) { 
        for (int i = 0; i < j+1; i++) {
            if(letter >='A'&& letter <='Z')
            {
                printf("%c\t",letter);
                letter++;
                if (letter>'Z')
                {
                    letter='A';
                }
            }
            else{
                printf ("%2d\t", nseq++);
            }
            
        }
        printf ("\n");
    }

    return 0; 
}
