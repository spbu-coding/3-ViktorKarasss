#include <stdio.h>
#include <math.h>

struct point_f{
    float x1;
    float x2;
};

struct point_d{
    double x1;
    double x2;
};

float calc_norm_f(struct point_f point1, struct point_f point2) {
    return sqrtf((point1.x1 - point2.x1) * (point1.x1 - point2.x1)
    + (point1.x2 - point2.x2) * (point1.x2 - point2.x2));
}

double calc_norm_d(struct point_d point1, struct point_d point2) {
    return sqrt((point1.x1 - point2.x1) * (point1.x1 - point2.x1)
    + (point1.x2 - point2.x2) * (point1.x2 - point2.x2));
}

struct point_d calc_solve_d(double delta){
    struct point_d solve;
    solve.x2 = (2.0001 + delta - 2.0) / 0.0001;
    solve.x1 = 2.0 - solve.x2;
    return solve;
}

struct point_f calc_solve_f(float delta){
    struct point_f solve;
    solve.x2 = (2.0001f + delta - 2.0f) / 0.0001f;
    solve.x1 = 2.0f - solve.x2;
    return solve;
}

void output(int cnt,struct point_d result_d,struct point_f result_f,
        struct point_d delta_result_d,struct point_f delta_result_f,
            double delta_d,float delta_f, double norma_d,float norma_f){
    printf("\n Experiment: %d \n", cnt);
    printf("%s\n", "In float:");
    printf("Solve x1: %.7f x2: %.7f \n", result_f.x1,  result_f.x2);
    printf("Delta_solve x1: %.7f x2: %.7f \n", delta_result_f.x1,  delta_result_f.x2);
    printf("Delta: %.7f \n", delta_f);
    printf("Norma: %.7f \n", norma_f);
    printf("%s\n", "In double:");
    printf("Solve x1: %.16lf x2: %.16lf \n", result_d.x1,  result_d.x2);
    printf("Delta_solve x1: %.16lf x2: %.16lf \n", delta_result_d.x1,  delta_result_d.x2);
    printf("Delta: %.16lf \n", delta_d);
    printf("Norma: %.16lf \n", norma_d);
}

void experiment(struct point_d result_d,struct point_f result_f,int *cnt,
        double *delta_d,float *delta_f, double *norma_d,float *norma_f){
    struct point_d delta_result_d = calc_solve_d(*delta_d);
    struct point_f delta_result_f = calc_solve_f(*delta_f);

    *norma_d = calc_norm_d(result_d,delta_result_d);
    *norma_f = calc_norm_f(result_f,delta_result_f);

    output(*cnt,result_d,result_f,delta_result_d,delta_result_f,
           *delta_d,*delta_f,*norma_d,*norma_f);

    *delta_f /= 2.0f;
    *delta_d /= 2.0;
    *cnt += 1;
}


int main() {
    struct point_d result_d = calc_solve_d(0.0); // first try
    struct point_f result_f = calc_solve_f(0.0f);
    //struct point_d result_d = {1,1}; second try
    //struct point_f result_f = {1,1};
    int cnt = 1;
    double delta_d = 0.0001;
    float delta_f = 0.0001f;
    double norma_d;
    float norma_f;
    const double epsilon_d = 0.000001;
    const float epsilon_f = 0.000001f;
    do{
        experiment(result_d,result_f, &cnt,&delta_d,&delta_f, &norma_d, &norma_f);
    }while(norma_f > epsilon_f && norma_d > epsilon_d);

    return 0;
}
