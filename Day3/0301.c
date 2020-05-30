#include<stdio.h>
#include<stdlib.h>

double *get_mean(int ndim, double **data, int ndata){
    double *mean ;
    mean = (double*)malloc(ndim*sizeof(double));
    for(int i= 0; i < ndim; i++){
        for(int j =0 ; j < ndata; j++){
           mean[i] += data[j][i];
        }
        mean[i] = mean[i]/ndata;
    }
    return mean;
}

double **get_cova(int ndim, double **data, int ndata){
    double **cova;
    double *mean;
    cova = (double **)malloc(ndim * sizeof(double *));
    for(int i = 0; i < ndim; i++){
        cova[i] = (double *)malloc(ndim * sizeof(double));
        if(cova[i] == NULL){
            perror("メモリの確保に失敗");
        }
    }
    mean = get_mean(ndim,data,ndata);
    for(int i = 0; i< ndim; i++){
        for(int j =0 ; j<ndim;j++){
            for(int n =0; n<ndata;n++){
                cova[i][j] += (data[n][i]-mean[i])
                              *(data[n][j]-mean[j])/ndata;
            }
        }
    }
    return cova;
}

int main(void){
    double **data, **cova, *mean;
    int ndata, ndim;
    int i = 0;

    FILE *fp;
    fp = fopen("A01M0007-0007.dat","r");
    if(fp == NULL){
        printf("there is an error\n");
        exit(0);
    }
    fscanf(fp, "%d %d",&ndata,&ndim);
   
    data = (double **)malloc(ndata * sizeof(double *));
    if(data == NULL) {
        perror("メモリの確保に失敗");
    }
    for(i = 0; i < ndata; i++){
        data[i] = (double *)malloc(ndim * sizeof(double));
        if(data[i] == NULL){
            perror("メモリの確保に失敗");
        }
    }
    i=0;
    while(i < ndata){
        for(int j=0;j<ndim;j++){
            fscanf(fp, "%lf ", &data[i][j]);
        }
        i++;
    }
    //Mean
    mean = get_mean(ndim,data,ndata);
    for(int i=0; i<ndim;i++){
        printf("mean[%d]=%f\n",i,mean[i]);
    }

    //cova
    cova = get_cova(ndim,data,ndata);
    for(int i = 0; i<ndim;i++){
        for(int j = 0; j<ndim;j++){
            printf("cova[%d][%d]=%f  ",i,j,cova[i][j]);
        }
        printf("\n");
    }

    free(get_mean(ndim,data,ndata));
    for(i = 0; i < ndata; i++){
        free(data[i]);
    }
    free(data); 
    fclose(fp);
    return 0;
}