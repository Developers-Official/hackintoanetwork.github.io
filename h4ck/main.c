include<stdio.h>
include<stdlib.h>
include<time.h>

int main(void)
{
    int bm, dr, w, s, kent;
    printf("학생 수 : ");
    scanf("%d", &bm);
    printf("책상 열의 개수 : ");
    scanf("%d", &dr);
    int aoa[bm];
    for(int i=0; i<bm; i++)
    {
        aoa[i]=i+1;
    }
    srand(time(NULL));
    for(int j=1; j<101; j++)
    {
        w=rand()%bm;
        s=rand()%bm;
        kent=aoa[w];
        aoa[a]=aoa[s];
        aoa[s]=kent;
    }
    for(int c=0; c<bm; c++)
    {
        printf("%d\t",aoa[c]);
        if ((c+1)%dr==0)
        {
            printf("\n");
        }
    }
    return 0;
}

