#ifndef KWDHD_KWDHDLIB
#define KWDHD_KWDHDLIB

// some helper function...

void PrintIntArr(int **arr, int x, int y)
{
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
            printf("%d ",arr[i][j]);
        printf("\n");
    }
}
#endif