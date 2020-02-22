#include<stdio.h>

#define DIM 40
char a[DIM][DIM];

char inv_a[DIM][DIM];

int n = 3;

void init(){
    int i,j;
    for (i=0;i<DIM;i++){
        for (j=0;j<DIM;j++){
            a[i][j] = 0;
            inv_a[i][j] = 0;
        }
    }
    for (i=0;i<DIM;i++){
        inv_a[i][i] = 1;
    }
}


void print_mat(){
    int i,j;
    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf ("%d ",(int)a[i][j]);
        }
        printf("| ");
        for(j=0;j<n;j++){
            printf ("%d ",(int)inv_a[i][j]);
        }
        printf("\n");

    }
    printf("\n");
}

void add_row(int k,int l){
    /*Add the k'th row to l'th row
     and put the result in the l'th row
     addition is done modulo 2 to emulate exor
    */
    int i;

    for (i=0;i<n;i++){
        a[l][i] = (a[k][i]+ a[l][i]) % 2;
        inv_a[l][i] = (inv_a[k][i]+ inv_a[l][i]) % 2;

    }

    printf ("r%d <= r%d + r%d\n\n",l,k,l);
    print_mat();
}

void swap_row(int k, int l){
    int i,t;
    for (i=0;i<n;i++){
        t = a[k][i];
        a[k][i] = a[l][i];
        a[l][i] = t;

        t = inv_a[k][i];
        inv_a[k][i] = inv_a[l][i];
        inv_a[l][i] = t;
    }
    printf("r%d <=> r%d \n\n",k,l);
    print_mat();
}

void inverse_mat(){
    int target = 0;
    int dest = -1;
    int i;

    //make the a matrix upper triangular
    while (target !=n){
        //if target location is 0 then find a row below with 1 and swap with the target's row
        if (a[target][target] == 0){
            for (i=target+1;i<n;i++){
                if (a[i][target]==1){
                    dest = i;
                    break;
                }
            }
            if (dest == -1){
                printf ("Singular matrix is not invertible.\n");
                return;
            }
            else {
                swap_row(target,dest);
            }
        }
        // now eliminate all the 1's below the target location
        for (i=target+1;i<n;i++){
            if (a[i][target]==1){
                add_row(target, i);
            }
        }
        //now target the next diagonal entry
        target++;
    }

    //now make the matrix diagonal
    target = n-1;
    while (target>0){
        if (a[target][target]==0) {
            printf ("Singular matrix is not invertible B.\n");
            return;
        }
        for (i=target-1;i>=0;i--){
            if (a[i][target]==1){
                add_row(target, i);
            }
        }
        target--;
    }

}


void set_mat_1(){
    n=3;
    a[0][0] = 1;
    a[0][1] = 1;
    a[1][1] = 1;
    a[1][2] = 1;
    a[2][0] = 1;
}


void set_mat_2(){
    n=3;
    a[0][1] = 1;
    a[1][2] = 1;
    a[2][0] = 1;
}


void set_mat_3(){
    n=4;
    a[0][0] = 1;
    a[0][1] = 1;

    a[2][1] = 1;
    a[2][2] = 1;

    a[1][0] = 1;
    a[3][1] = 1;
    a[3][3] = 1;
}


int main(){
    init();
    set_mat_3();
    print_mat();
    inverse_mat();
    //print_mat();
    /*
    add_row(0,2);
    print_mat();
    swap_row(1,2);
    print_mat();
    add_row(1,2);
    print_mat();
    add_row(1,0);
    print_mat();
    */
}



