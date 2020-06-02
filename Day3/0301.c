#include<stdio.h>
#include<stdlib.h>

//使う関数 
double *get_mean(int ndim, double **data, int ndata);
double **get_cova(int ndim, double **data, int ndata);

//平均ベクトル関数
double *get_mean(int ndim, double **data, int ndata){
    double *mean; //平均ベクトル

    //平均ベクトルに動的に１次元配列領域を確保する 
    mean = (double*)malloc(ndim*sizeof(double));

    //平均ベクトルの要素の値を求める
    for(int i= 0; i < ndim; i++){
        for(int j =0 ; j < ndata; j++){
           mean[i] += data[j][i];
        }
        mean[i] = mean[i]/ndata;
    }
    return mean;
}

//分散共分散行列 関数
double **get_cova(int ndim, double **data, int ndata){
    double **cova;  //分散共分散行列
    double *mean;  //平均ベクトル
    //分散共分散行列に動的に2次元配列領域を確保する 
    cova = (double **)malloc(ndim * sizeof(double *));
    for(int i = 0; i < ndim; i++){
        cova[i] = (double *)malloc(ndim * sizeof(double));
        if(cova[i] == NULL){
            perror("メモリの確保に失敗");
        }
    }
    //平均ベクトルを求める
    mean = get_mean(ndim,data,ndata);
    //分散共分散行列の要素を求める
    for(int i = 0; i< ndim; i++){
        for(int j =0 ; j<ndim;j++){
            for(int n =0; n<ndata;n++){
                cova[i][j] += (data[n][i]-mean[i])
                              *(data[n][j]-mean[j]);
            }
            cova[i][j] = cova[i][j]/ndata;
        }
    }
    return cova;
}

//main()関数
int main(void){
    double **data, **cova, *mean;//データ、分散共分散行列、平均ベクトル
    int ndata, ndim;// データの個数, データの各フレームの次元数
    int i = 0;

    //音声データを特徴量化したデータを開き、 
    FILE *fp;
    fp = fopen("A01M0007-0007.dat","r");
    if(fp == NULL){
        printf("there is an error\n");
        exit(0);
    }
    //データの個数, データの各フレームの次元数を確認する
    fscanf(fp, "%d %d",&ndata,&ndim);
   
    //ファイルのデータを保存するために、動的に2次元配列領域を作る
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

    //ファイルのデータを保存する
    i=0;
    while(i < ndata){
        for(int j=0;j<ndim;j++){
            fscanf(fp, "%lf ", &data[i][j]);
        }
        i++;
    }

    //平均ベクトル
    mean = get_mean(ndim,data,ndata);
    printf("平均ベクトル:\n");
    for(int i=0; i<ndim;i++){
        printf("mean[%d]=%f\n",i,mean[i]);
    }

    //分散共分散行列
    cova = get_cova(ndim,data,ndata);
    printf("\n分散共分散行列:\n");
    for(int i = 0; i<ndim;i++){
        for(int j = 0; j<ndim;j++){
            printf("%f ",cova[i][j]);
        }
        printf("\n");
    }

    //メモリを解放する
    free(get_mean(ndim,data,ndata));
    for(i = 0; i < ndata; i++){
        free(data[i]);
    }
    free(data); 
    fclose(fp);
    return 0;
}