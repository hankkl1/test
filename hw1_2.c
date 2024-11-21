#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "mpi.h"
int n;

typedef struct{
    int x;
    int y;
    int id;
}Point;

int compare(const void *a, const void *b){
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    int diff = (p1->x - p2->x);
    if (diff == 0){ //same x
        return (p1->y - p2->y);
    }
    return diff;
}

/*OA cross OB, if>0, then OA to OB is counter clockwise*/
double cross(Point o, Point a, Point b){
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

void Andrew_monotone_chain(Point *points, Point *ch, int n, int *m_out){
    int m = 0; //counting how many points in ch

    /*the upper part of convex hull*/
    for (int i=0; i<n; i++){
        while(m>=2 && cross(ch[m-2],ch[m-1],points[i])>0){
            m--;
        }
        ch[m++]=points[i];
    }

    /*the lower part of convex hull*/
    //t means the points in the upper convex hull
    //the last point in points will be in convex hull
    for (int i = n-2, t=m+1; i>=0; i--){
        while(m>=t && cross(ch[m-2],ch[m-1],points[i])>0){
            m--;
        }
        if (points[i].id == ch[0].id) break;
        ch[m++]=points[i];
    }

    //m--; //contains the start point twice, so minus one

    *m_out = m;
}
int main(int argc, char *argv[]){

    scanf("%d", &n);
    Point *points;
    points = (Point *)malloc(n * sizeof(Point));
    Point *ch; //Convex hull
    ch =  (Point *)malloc((125) * sizeof(Point));

    /*Read inputs */
    for (int i=0; i<n; i++){
        points[i].id = i+1;
        scanf("%d %d", &points[i].x, &points[i].y);
    }

    /*Sorting the points*/
    qsort(points,n,sizeof(Point),compare);
    //printf("%d",2*sizeof(Point));
    
    
    int m;
    Andrew_monotone_chain(points, ch, n, &m);
    for (int i=0; i<m; i++){
        printf("%d ",ch[i].id);
    }
    return 0;
}