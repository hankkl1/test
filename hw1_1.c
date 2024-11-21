#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_M_N 32

int cover[MAX_M_N];
int sum[MAX_M_N];
int n, m;
int full_part;
int total = 0;
void trace_back();
void track()
{
    for (int i = 0; i < m; i++)
    {
        trace_back(i, i, cover[i]);
    }
}

void trace_back(int start_pt, int current_pt, int mask)
{
    if (current_pt < 0)
    {
        return;
    }
    if ((mask | cover[current_pt]) == full_part)
    {
        sum[start_pt]++;
    }
    for (int i = current_pt - 1; i >= 0; i--)
    {
        trace_back(start_pt, i, mask | cover[i]);
    }
}

int main(int argc, char *argv[])
{

    scanf("%d %d", &n, &m);
    full_part = (1 << n) - 1;

    for (int i = 0; i < m; i++)
    {
        int count, cost;
        scanf("%d %d", &count, &cost);
        cover[i] = 0; // initialize
        sum[i] = 0;
        for (int j = 0; j < count; j++)
        {
            int part;
            scanf("%d", &part);
            cover[i] |= (1 << (part - 1));
        }
    }
    track();

    for (int i = 0; i < m; i++)
    {
        total += sum[i];
        //printf("%d\n", sum[i]);
    }
    printf("%d",total);
    return 0;
}